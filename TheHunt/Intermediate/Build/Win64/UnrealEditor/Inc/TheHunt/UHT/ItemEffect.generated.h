// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Items/ItemEffect.h"

#ifdef THEHUNT_ItemEffect_generated_h
#error "ItemEffect.generated.h already included, missing '#pragma once' in ItemEffect.h"
#endif
#define THEHUNT_ItemEffect_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;

// ********** Begin Class UItemEffect **************************************************************
#define FID_TheHunt_Source_TheHunt_Items_ItemEffect_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execApplyEffect);


struct Z_Construct_UClass_UItemEffect_Statics;
THEHUNT_API UClass* Z_Construct_UClass_UItemEffect_NoRegister();

#define FID_TheHunt_Source_TheHunt_Items_ItemEffect_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUItemEffect(); \
	friend struct ::Z_Construct_UClass_UItemEffect_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend THEHUNT_API UClass* ::Z_Construct_UClass_UItemEffect_NoRegister(); \
public: \
	DECLARE_CLASS2(UItemEffect, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/TheHunt"), Z_Construct_UClass_UItemEffect_NoRegister) \
	DECLARE_SERIALIZER(UItemEffect)


#define FID_TheHunt_Source_TheHunt_Items_ItemEffect_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UItemEffect(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UItemEffect(UItemEffect&&) = delete; \
	UItemEffect(const UItemEffect&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UItemEffect); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UItemEffect); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UItemEffect) \
	NO_API virtual ~UItemEffect();


#define FID_TheHunt_Source_TheHunt_Items_ItemEffect_h_12_PROLOG
#define FID_TheHunt_Source_TheHunt_Items_ItemEffect_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TheHunt_Source_TheHunt_Items_ItemEffect_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_Items_ItemEffect_h_15_INCLASS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_Items_ItemEffect_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UItemEffect;

// ********** End Class UItemEffect ****************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TheHunt_Source_TheHunt_Items_ItemEffect_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
