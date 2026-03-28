// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GameplayAbilitySystem/Abilities/BasicBlockingAbility.h"

#ifdef THEHUNT_BasicBlockingAbility_generated_h
#error "BasicBlockingAbility.generated.h already included, missing '#pragma once' in BasicBlockingAbility.h"
#endif
#define THEHUNT_BasicBlockingAbility_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UAnimMontage;

// ********** Begin Class UBasicBlockingAbility ****************************************************
#define FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_Abilities_BasicBlockingAbility_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnBlockExitFinished); \
	DECLARE_FUNCTION(execOnMontageCompleted);


struct Z_Construct_UClass_UBasicBlockingAbility_Statics;
THEHUNT_API UClass* Z_Construct_UClass_UBasicBlockingAbility_NoRegister();

#define FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_Abilities_BasicBlockingAbility_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBasicBlockingAbility(); \
	friend struct ::Z_Construct_UClass_UBasicBlockingAbility_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend THEHUNT_API UClass* ::Z_Construct_UClass_UBasicBlockingAbility_NoRegister(); \
public: \
	DECLARE_CLASS2(UBasicBlockingAbility, UGameplayAbility, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/TheHunt"), Z_Construct_UClass_UBasicBlockingAbility_NoRegister) \
	DECLARE_SERIALIZER(UBasicBlockingAbility)


#define FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_Abilities_BasicBlockingAbility_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBasicBlockingAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UBasicBlockingAbility(UBasicBlockingAbility&&) = delete; \
	UBasicBlockingAbility(const UBasicBlockingAbility&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBasicBlockingAbility); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBasicBlockingAbility); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBasicBlockingAbility) \
	NO_API virtual ~UBasicBlockingAbility();


#define FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_Abilities_BasicBlockingAbility_h_12_PROLOG
#define FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_Abilities_BasicBlockingAbility_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_Abilities_BasicBlockingAbility_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_Abilities_BasicBlockingAbility_h_15_INCLASS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_Abilities_BasicBlockingAbility_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UBasicBlockingAbility;

// ********** End Class UBasicBlockingAbility ******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_Abilities_BasicBlockingAbility_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
