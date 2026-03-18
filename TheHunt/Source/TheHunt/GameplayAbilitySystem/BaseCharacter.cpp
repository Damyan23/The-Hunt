// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "SwordActor.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	BaseAttributes = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("BaseAttributesSet"));
}

void ABaseCharacter::AttachWeapon()
{
    if (Weapon) return;

    USkeletalMeshComponent* MeshComp = GetMesh();
    if (!MeshComp || !MeshComp->GetSkeletalMeshAsset()) return; // silently skip if no mesh
    if (!MeshComp->DoesSocketExist(FName("Sword_joint"))) return; // skip if no socket

    FActorSpawnParameters Params;
    Params.Owner = this;
    Weapon = GetWorld()->SpawnActor<ASwordActor>(ASwordActor::StaticClass(), Params);

    if (Weapon)
    {
        Weapon->AttachToComponent(MeshComp,
            FAttachmentTransformRules::SnapToTargetNotIncludingScale,
            FName("Sword_joint"));
    }
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
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

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void ABaseCharacter::Die()
{
}

