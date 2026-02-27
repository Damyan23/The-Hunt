// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Items/ItemDefinition.h"

#ifdef THEHUNT_ItemDefinition_generated_h
#error "ItemDefinition.generated.h already included, missing '#pragma once' in ItemDefinition.h"
#endif
#define THEHUNT_ItemDefinition_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UItemDefinition **********************************************************
struct Z_Construct_UClass_UItemDefinition_Statics;
THEHUNT_API UClass* Z_Construct_UClass_UItemDefinition_NoRegister();

#define FID_TheHunt_Source_TheHunt_Items_ItemDefinition_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUItemDefinition(); \
	friend struct ::Z_Construct_UClass_UItemDefinition_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend THEHUNT_API UClass* ::Z_Construct_UClass_UItemDefinition_NoRegister(); \
public: \
	DECLARE_CLASS2(UItemDefinition, UDataAsset, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/TheHunt"), Z_Construct_UClass_UItemDefinition_NoRegister) \
	DECLARE_SERIALIZER(UItemDefinition)


#define FID_TheHunt_Source_TheHunt_Items_ItemDefinition_h_16_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UItemDefinition(UItemDefinition&&) = delete; \
	UItemDefinition(const UItemDefinition&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UItemDefinition); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UItemDefinition); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UItemDefinition) \
	NO_API virtual ~UItemDefinition();


#define FID_TheHunt_Source_TheHunt_Items_ItemDefinition_h_13_PROLOG
#define FID_TheHunt_Source_TheHunt_Items_ItemDefinition_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TheHunt_Source_TheHunt_Items_ItemDefinition_h_16_INCLASS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_Items_ItemDefinition_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UItemDefinition;

// ********** End Class UItemDefinition ************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TheHunt_Source_TheHunt_Items_ItemDefinition_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
