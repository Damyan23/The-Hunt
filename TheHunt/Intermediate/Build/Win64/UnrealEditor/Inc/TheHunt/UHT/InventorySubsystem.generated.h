// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Inventory/InventorySubsystem.h"

#ifdef THEHUNT_InventorySubsystem_generated_h
#error "InventorySubsystem.generated.h already included, missing '#pragma once' in InventorySubsystem.h"
#endif
#define THEHUNT_InventorySubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UInventorySubsystem ******************************************************
struct Z_Construct_UClass_UInventorySubsystem_Statics;
THEHUNT_API UClass* Z_Construct_UClass_UInventorySubsystem_NoRegister();

#define FID_TheHunt_Source_TheHunt_Inventory_InventorySubsystem_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUInventorySubsystem(); \
	friend struct ::Z_Construct_UClass_UInventorySubsystem_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend THEHUNT_API UClass* ::Z_Construct_UClass_UInventorySubsystem_NoRegister(); \
public: \
	DECLARE_CLASS2(UInventorySubsystem, UGameInstanceSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/TheHunt"), Z_Construct_UClass_UInventorySubsystem_NoRegister) \
	DECLARE_SERIALIZER(UInventorySubsystem)


#define FID_TheHunt_Source_TheHunt_Inventory_InventorySubsystem_h_18_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UInventorySubsystem(); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UInventorySubsystem(UInventorySubsystem&&) = delete; \
	UInventorySubsystem(const UInventorySubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UInventorySubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInventorySubsystem); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UInventorySubsystem) \
	NO_API virtual ~UInventorySubsystem();


#define FID_TheHunt_Source_TheHunt_Inventory_InventorySubsystem_h_15_PROLOG
#define FID_TheHunt_Source_TheHunt_Inventory_InventorySubsystem_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TheHunt_Source_TheHunt_Inventory_InventorySubsystem_h_18_INCLASS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_Inventory_InventorySubsystem_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UInventorySubsystem;

// ********** End Class UInventorySubsystem ********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TheHunt_Source_TheHunt_Inventory_InventorySubsystem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
