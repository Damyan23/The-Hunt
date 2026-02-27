// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Items/ItemDefinition.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeItemDefinition() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UClass_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UDataAsset();
THEHUNT_API UClass* Z_Construct_UClass_UItemDefinition();
THEHUNT_API UClass* Z_Construct_UClass_UItemDefinition_NoRegister();
THEHUNT_API UClass* Z_Construct_UClass_UItemEffect_NoRegister();
UPackage* Z_Construct_UPackage__Script_TheHunt();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UItemDefinition **********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UItemDefinition;
UClass* UItemDefinition::GetPrivateStaticClass()
{
	using TClass = UItemDefinition;
	if (!Z_Registration_Info_UClass_UItemDefinition.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("ItemDefinition"),
			Z_Registration_Info_UClass_UItemDefinition.InnerSingleton,
			StaticRegisterNativesUItemDefinition,
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
	return Z_Registration_Info_UClass_UItemDefinition.InnerSingleton;
}
UClass* Z_Construct_UClass_UItemDefinition_NoRegister()
{
	return UItemDefinition::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UItemDefinition_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Items/ItemDefinition.h" },
		{ "ModuleRelativePath", "Items/ItemDefinition.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemID_MetaData[] = {
		{ "Category", "Item" },
		{ "ModuleRelativePath", "Items/ItemDefinition.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Effects_MetaData[] = {
		{ "Category", "Item" },
		{ "ModuleRelativePath", "Items/ItemDefinition.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UItemDefinition constinit property declarations **************************
	static const UECodeGen_Private::FNamePropertyParams NewProp_ItemID;
	static const UECodeGen_Private::FClassPropertyParams NewProp_Effects_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Effects;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UItemDefinition constinit property declarations ****************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UItemDefinition>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UItemDefinition_Statics

// ********** Begin Class UItemDefinition Property Definitions *************************************
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UItemDefinition_Statics::NewProp_ItemID = { "ItemID", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UItemDefinition, ItemID), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemID_MetaData), NewProp_ItemID_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UItemDefinition_Statics::NewProp_Effects_Inner = { "Effects", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_UItemEffect_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UItemDefinition_Statics::NewProp_Effects = { "Effects", nullptr, (EPropertyFlags)0x0014000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UItemDefinition, Effects), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Effects_MetaData), NewProp_Effects_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UItemDefinition_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UItemDefinition_Statics::NewProp_ItemID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UItemDefinition_Statics::NewProp_Effects_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UItemDefinition_Statics::NewProp_Effects,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UItemDefinition_Statics::PropPointers) < 2048);
// ********** End Class UItemDefinition Property Definitions ***************************************
UObject* (*const Z_Construct_UClass_UItemDefinition_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDataAsset,
	(UObject* (*)())Z_Construct_UPackage__Script_TheHunt,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UItemDefinition_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UItemDefinition_Statics::ClassParams = {
	&UItemDefinition::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UItemDefinition_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UItemDefinition_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UItemDefinition_Statics::Class_MetaDataParams), Z_Construct_UClass_UItemDefinition_Statics::Class_MetaDataParams)
};
void UItemDefinition::StaticRegisterNativesUItemDefinition()
{
}
UClass* Z_Construct_UClass_UItemDefinition()
{
	if (!Z_Registration_Info_UClass_UItemDefinition.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UItemDefinition.OuterSingleton, Z_Construct_UClass_UItemDefinition_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UItemDefinition.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UItemDefinition);
UItemDefinition::~UItemDefinition() {}
// ********** End Class UItemDefinition ************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Items_ItemDefinition_h__Script_TheHunt_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UItemDefinition, UItemDefinition::StaticClass, TEXT("UItemDefinition"), &Z_Registration_Info_UClass_UItemDefinition, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UItemDefinition), 3125937050U) },
	};
}; // Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Items_ItemDefinition_h__Script_TheHunt_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Items_ItemDefinition_h__Script_TheHunt_465546927{
	TEXT("/Script/TheHunt"),
	Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Items_ItemDefinition_h__Script_TheHunt_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Items_ItemDefinition_h__Script_TheHunt_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
