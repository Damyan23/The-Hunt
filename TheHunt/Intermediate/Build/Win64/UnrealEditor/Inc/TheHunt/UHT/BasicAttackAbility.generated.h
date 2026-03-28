// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GameplayAbilitySystem/BasicAttackAbility.h"

#ifdef THEHUNT_BasicAttackAbility_generated_h
#error "BasicAttackAbility.generated.h already included, missing '#pragma once' in BasicAttackAbility.h"
#endif
#define THEHUNT_BasicAttackAbility_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UAnimMontage;

// ********** Begin Class UBasicAttackAbility ******************************************************
#define FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_BasicAttackAbility_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnMontageEnded); \
	DECLARE_FUNCTION(execOnMontageCompleted);


struct Z_Construct_UClass_UBasicAttackAbility_Statics;
THEHUNT_API UClass* Z_Construct_UClass_UBasicAttackAbility_NoRegister();

#define FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_BasicAttackAbility_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBasicAttackAbility(); \
	friend struct ::Z_Construct_UClass_UBasicAttackAbility_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend THEHUNT_API UClass* ::Z_Construct_UClass_UBasicAttackAbility_NoRegister(); \
public: \
	DECLARE_CLASS2(UBasicAttackAbility, UGameplayAbility, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/TheHunt"), Z_Construct_UClass_UBasicAttackAbility_NoRegister) \
	DECLARE_SERIALIZER(UBasicAttackAbility)


#define FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_BasicAttackAbility_h_16_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UBasicAttackAbility(UBasicAttackAbility&&) = delete; \
	UBasicAttackAbility(const UBasicAttackAbility&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBasicAttackAbility); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBasicAttackAbility); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UBasicAttackAbility) \
	NO_API virtual ~UBasicAttackAbility();


#define FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_BasicAttackAbility_h_13_PROLOG
#define FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_BasicAttackAbility_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_BasicAttackAbility_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_BasicAttackAbility_h_16_INCLASS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_BasicAttackAbility_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UBasicAttackAbility;

// ********** End Class UBasicAttackAbility ********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_BasicAttackAbility_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
