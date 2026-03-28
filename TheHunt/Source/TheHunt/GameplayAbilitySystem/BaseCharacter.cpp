    // Fill out your copyright notice in the Description page of Project Settings.


    #include "BaseCharacter.h"
    #include "AbilitySystemComponent.h"

    // Sets default values
    ABaseCharacter::ABaseCharacter()
    {
 	    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	    PrimaryActorTick.bCanEverTick = true;

	    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	    BaseAttributes = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("BaseAttributesSet"));
    }

    // Called when the game starts or when spawned
    void ABaseCharacter::BeginPlay()
    {
	    Super::BeginPlay();

        FGameplayEffectContextHandle Context = AbilitySystemComponent->MakeEffectContext();
        FGameplayEffectSpecHandle Spec = AbilitySystemComponent->MakeOutgoingSpec(
            StaminaRegen, 1.f, Context);
        AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());

        AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
            UBaseAttributeSet::GetHealthAttribute())
            .AddUObject(this, &ABaseCharacter::OnHealthChanged);

        AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetStaggerAttribute()).AddUObject(this, &ABaseCharacter::OnStaggerChanged);
    }


    // Called every frame
    void ABaseCharacter::Tick(float DeltaTime)
    {
	    Super::Tick(DeltaTime);

    }

    void ABaseCharacter::PostInitializeComponents()
    {
        Super::PostInitializeComponents();
        AbilitySystemComponent->InitAbilityActorInfo(this, this);
        GrantDefaultAbilities();
        AttachWeapon();
    }

    void ABaseCharacter::InitializeAttributes()
    {
    }

    void ABaseCharacter::GrantDefaultAbilities()
    {
        if (!AbilitySystemComponent) return;

        for (TSubclassOf<UGameplayAbility>& Ability : DefaultAbilities)
        {
            if (Ability)
            {
                FGameplayAbilitySpec Spec = FGameplayAbilitySpec(Ability, 1);
                AbilitySystemComponent->GiveAbility(Spec);
                UE_LOG(LogTemp, Warning, TEXT("Granted ability: %s"), *Ability->GetName());
            }
        }
    }

    void ABaseCharacter::AttachWeapon()
    {
    }   

    UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
    {
	    return AbilitySystemComponent;
    }


    void ABaseCharacter::Die()
    {
    }

    void ABaseCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
    {
        if (Data.NewValue < Data.OldValue) // took damage
        {
            if (GettingHitMontage)
            {
                const UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

                UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();
                FName CurrentSection = AnimInstance->Montage_GetCurrentSection(CurrentMontage);

                UE_LOG(LogTemp, Warning, TEXT("Current Section: %s"), *AnimInstance->Montage_GetCurrentSection(CurrentMontage).ToString());

                if (AnimInstance->Montage_GetCurrentSection(CurrentMontage) == FName("Cancelable")) 
                {
                    GetMesh()->GetAnimInstance()->Montage_Play(GettingHitMontage);
                };
            }
        }
    }

    void ABaseCharacter::OnStaggerChanged(const FOnAttributeChangeData& Data)
    {
        if (AbilitySystemComponent->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Stunned")))
            return;

        float MaxStagger = AbilitySystemComponent->GetNumericAttribute(
            UBaseAttributeSet::GetMaxStaggerAttribute());

        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
        UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();

        if (Data.NewValue >= MaxStagger)
        {
            OnGuardBroken();
        }

        if (AnimInstance->Montage_GetCurrentSection(CurrentMontage) == FName("BlockHold"))
        {
            AnimInstance->Montage_JumpToSection(FName("BlockImpact"), CurrentMontage);
        }
    }

    void ABaseCharacter::OnGuardBroken()
    {
        FGameplayTagContainer BlockTag;
        BlockTag.AddTag(FGameplayTag::RequestGameplayTag("Ability.Block"));
        AbilitySystemComponent->CancelAbilities(&BlockTag);

        AbilitySystemComponent->AddLooseGameplayTags(FGameplayTagContainer(FGameplayTag::RequestGameplayTag("State.Stunned")));

        if (StaggerMontage)
            GetMesh()->GetAnimInstance()->Montage_Play(StaggerMontage);

        FTimerHandle StunTimer;
        GetWorldTimerManager().SetTimer(StunTimer, [this]()
        {
            UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
            if (StaggerMontage && AnimInstance)
                AnimInstance->Montage_JumpToSection(FName("StaggerExit"), StaggerMontage);

            AbilitySystemComponent->RemoveLooseGameplayTags(FGameplayTagContainer(FGameplayTag::RequestGameplayTag("State.Stunned")));

            AbilitySystemComponent->ApplyGameplayEffectToSelf(
                StaggerResetEffect.GetDefaultObject(), 1.f,
                AbilitySystemComponent->MakeEffectContext());

        }, StunDuration, false);
    }

