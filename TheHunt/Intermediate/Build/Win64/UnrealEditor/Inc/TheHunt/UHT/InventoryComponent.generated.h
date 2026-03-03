// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Inventory/InventoryComponent.h"

#ifdef THEHUNT_InventoryComponent_generated_h
#error "InventoryComponent.generated.h already included, missing '#pragma once' in InventoryComponent.h"
#endif
#define THEHUNT_InventoryComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UTexture2D;

// ********** Begin Delegate FOnSlotUpdated ********************************************************
#define FID_TheHunt_Source_TheHunt_Inventory_InventoryComponent_h_25_DELEGATE \
static void FOnSlotUpdated_DelegateWrapper(const FMulticastScriptDelegate& OnSlotUpdated, int32 SlotIndex, UTexture2D* Icon);


// ********** End Delegate FOnSlotUpdated **********************************************************

// ********** Begin Class UInventoryComponent ******************************************************
struct Z_Construct_UClass_UInventoryComponent_Statics;
THEHUNT_API UClass* Z_Construct_UClass_UInventoryComponent_NoRegister();

#define FID_TheHunt_Source_TheHunt_Inventory_InventoryComponent_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUInventoryComponent(); \
	friend struct ::Z_Construct_UClass_UInventoryComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend THEHUNT_API UClass* ::Z_Construct_UClass_UInventoryComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UInventoryComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TheHunt"), Z_Construct_UClass_UInventoryComponent_NoRegister) \
	DECLARE_SERIALIZER(UInventoryComponent)


#define FID_TheHunt_Source_TheHunt_Inventory_InventoryComponent_h_16_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UInventoryComponent(UInventoryComponent&&) = delete; \
	UInventoryComponent(const UInventoryComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UInventoryComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInventoryComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UInventoryComponent) \
	NO_API virtual ~UInventoryComponent();


#define FID_TheHunt_Source_TheHunt_Inventory_InventoryComponent_h_13_PROLOG
#define FID_TheHunt_Source_TheHunt_Inventory_InventoryComponent_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TheHunt_Source_TheHunt_Inventory_InventoryComponent_h_16_INCLASS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_Inventory_InventoryComponent_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UInventoryComponent;

// ********** End Class UInventoryComponent ********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TheHunt_Source_TheHunt_Inventory_InventoryComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
