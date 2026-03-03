// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Inventory/InventorySubsystem.h"
#include "Engine/GameInstance.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeInventorySubsystem() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UGameInstanceSubsystem();
THEHUNT_API UClass* Z_Construct_UClass_UInventorySubsystem();
THEHUNT_API UClass* Z_Construct_UClass_UInventorySubsystem_NoRegister();
UPackage* Z_Construct_UPackage__Script_TheHunt();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UInventorySubsystem ******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UInventorySubsystem;
UClass* UInventorySubsystem::GetPrivateStaticClass()
{
	using TClass = UInventorySubsystem;
	if (!Z_Registration_Info_UClass_UInventorySubsystem.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("InventorySubsystem"),
			Z_Registration_Info_UClass_UInventorySubsystem.InnerSingleton,
			StaticRegisterNativesUInventorySubsystem,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UInventorySubsystem.InnerSingleton;
}
UClass* Z_Construct_UClass_UInventorySubsystem_NoRegister()
{
	return UInventorySubsystem::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UInventorySubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Inventory/InventorySubsystem.h" },
		{ "ModuleRelativePath", "Inventory/InventorySubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UInventorySubsystem constinit property declarations **********************
// ********** End Class UInventorySubsystem constinit property declarations ************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UInventorySubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UInventorySubsystem_Statics
UObject* (*const Z_Construct_UClass_UInventorySubsystem_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameInstanceSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_TheHunt,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInventorySubsystem_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UInventorySubsystem_Statics::ClassParams = {
	&UInventorySubsystem::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UInventorySubsystem_Statics::Class_MetaDataParams), Z_Construct_UClass_UInventorySubsystem_Statics::Class_MetaDataParams)
};
void UInventorySubsystem::StaticRegisterNativesUInventorySubsystem()
{
}
UClass* Z_Construct_UClass_UInventorySubsystem()
{
	if (!Z_Registration_Info_UClass_UInventorySubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UInventorySubsystem.OuterSingleton, Z_Construct_UClass_UInventorySubsystem_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UInventorySubsystem.OuterSingleton;
}
UInventorySubsystem::UInventorySubsystem() {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UInventorySubsystem);
UInventorySubsystem::~UInventorySubsystem() {}
// ********** End Class UInventorySubsystem ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Inventory_InventorySubsystem_h__Script_TheHunt_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UInventorySubsystem, UInventorySubsystem::StaticClass, TEXT("UInventorySubsystem"), &Z_Registration_Info_UClass_UInventorySubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UInventorySubsystem), 1367095329U) },
	};
}; // Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Inventory_InventorySubsystem_h__Script_TheHunt_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Inventory_InventorySubsystem_h__Script_TheHunt_3237621437{
	TEXT("/Script/TheHunt"),
	Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Inventory_InventorySubsystem_h__Script_TheHunt_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Inventory_InventorySubsystem_h__Script_TheHunt_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
