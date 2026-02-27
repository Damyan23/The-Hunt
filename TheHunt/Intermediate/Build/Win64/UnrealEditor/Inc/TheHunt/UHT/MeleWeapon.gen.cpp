// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Items/Weapon/MeleWeapon.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeMeleWeapon() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor();
THEHUNT_API UClass* Z_Construct_UClass_AMeleWeapon();
THEHUNT_API UClass* Z_Construct_UClass_AMeleWeapon_NoRegister();
THEHUNT_API UClass* Z_Construct_UClass_UItemDefinition_NoRegister();
UPackage* Z_Construct_UPackage__Script_TheHunt();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AMeleWeapon **************************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AMeleWeapon;
UClass* AMeleWeapon::GetPrivateStaticClass()
{
	using TClass = AMeleWeapon;
	if (!Z_Registration_Info_UClass_AMeleWeapon.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("MeleWeapon"),
			Z_Registration_Info_UClass_AMeleWeapon.InnerSingleton,
			StaticRegisterNativesAMeleWeapon,
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
	return Z_Registration_Info_UClass_AMeleWeapon.InnerSingleton;
}
UClass* Z_Construct_UClass_AMeleWeapon_NoRegister()
{
	return AMeleWeapon::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AMeleWeapon_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Items/Weapon/MeleWeapon.h" },
		{ "ModuleRelativePath", "Items/Weapon/MeleWeapon.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemInfo_MetaData[] = {
		{ "Category", "Item" },
		{ "ModuleRelativePath", "Items/Weapon/MeleWeapon.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class AMeleWeapon constinit property declarations ******************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ItemInfo;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AMeleWeapon constinit property declarations ********************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMeleWeapon>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AMeleWeapon_Statics

// ********** Begin Class AMeleWeapon Property Definitions *****************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMeleWeapon_Statics::NewProp_ItemInfo = { "ItemInfo", nullptr, (EPropertyFlags)0x0114000000010001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMeleWeapon, ItemInfo), Z_Construct_UClass_UItemDefinition_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemInfo_MetaData), NewProp_ItemInfo_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMeleWeapon_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMeleWeapon_Statics::NewProp_ItemInfo,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMeleWeapon_Statics::PropPointers) < 2048);
// ********** End Class AMeleWeapon Property Definitions *******************************************
UObject* (*const Z_Construct_UClass_AMeleWeapon_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_TheHunt,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMeleWeapon_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMeleWeapon_Statics::ClassParams = {
	&AMeleWeapon::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AMeleWeapon_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AMeleWeapon_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMeleWeapon_Statics::Class_MetaDataParams), Z_Construct_UClass_AMeleWeapon_Statics::Class_MetaDataParams)
};
void AMeleWeapon::StaticRegisterNativesAMeleWeapon()
{
}
UClass* Z_Construct_UClass_AMeleWeapon()
{
	if (!Z_Registration_Info_UClass_AMeleWeapon.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMeleWeapon.OuterSingleton, Z_Construct_UClass_AMeleWeapon_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMeleWeapon.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AMeleWeapon);
AMeleWeapon::~AMeleWeapon() {}
// ********** End Class AMeleWeapon ****************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Items_Weapon_MeleWeapon_h__Script_TheHunt_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMeleWeapon, AMeleWeapon::StaticClass, TEXT("AMeleWeapon"), &Z_Registration_Info_UClass_AMeleWeapon, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMeleWeapon), 1132332667U) },
	};
}; // Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Items_Weapon_MeleWeapon_h__Script_TheHunt_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Items_Weapon_MeleWeapon_h__Script_TheHunt_3669291855{
	TEXT("/Script/TheHunt"),
	Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Items_Weapon_MeleWeapon_h__Script_TheHunt_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Items_Weapon_MeleWeapon_h__Script_TheHunt_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
