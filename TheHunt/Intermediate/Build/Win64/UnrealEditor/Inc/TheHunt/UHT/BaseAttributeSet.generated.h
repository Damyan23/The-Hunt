// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GameplayAbilitySystem/BaseAttributeSet.h"

#ifdef THEHUNT_BaseAttributeSet_generated_h
#error "BaseAttributeSet.generated.h already included, missing '#pragma once' in BaseAttributeSet.h"
#endif
#define THEHUNT_BaseAttributeSet_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UBaseAttributeSet ********************************************************
struct Z_Construct_UClass_UBaseAttributeSet_Statics;
THEHUNT_API UClass* Z_Construct_UClass_UBaseAttributeSet_NoRegister();

#define FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_BaseAttributeSet_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBaseAttributeSet(); \
	friend struct ::Z_Construct_UClass_UBaseAttributeSet_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend THEHUNT_API UClass* ::Z_Construct_UClass_UBaseAttributeSet_NoRegister(); \
public: \
	DECLARE_CLASS2(UBaseAttributeSet, UAttributeSet, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/TheHunt"), Z_Construct_UClass_UBaseAttributeSet_NoRegister) \
	DECLARE_SERIALIZER(UBaseAttributeSet)


#define FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_BaseAttributeSet_h_16_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UBaseAttributeSet(UBaseAttributeSet&&) = delete; \
	UBaseAttributeSet(const UBaseAttributeSet&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBaseAttributeSet); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBaseAttributeSet); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UBaseAttributeSet) \
	NO_API virtual ~UBaseAttributeSet();


#define FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_BaseAttributeSet_h_13_PROLOG
#define FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_BaseAttributeSet_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_BaseAttributeSet_h_16_INCLASS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_BaseAttributeSet_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UBaseAttributeSet;

// ********** End Class UBaseAttributeSet **********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_BaseAttributeSet_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
