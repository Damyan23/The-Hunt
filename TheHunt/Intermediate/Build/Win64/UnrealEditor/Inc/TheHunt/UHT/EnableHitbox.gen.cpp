// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Animations/Notifies/EnableHitbox.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeEnableHitbox() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UAnimNotify();
THEHUNT_API UClass* Z_Construct_UClass_UEnableHitbox();
THEHUNT_API UClass* Z_Construct_UClass_UEnableHitbox_NoRegister();
UPackage* Z_Construct_UPackage__Script_TheHunt();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UEnableHitbox ************************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UEnableHitbox;
UClass* UEnableHitbox::GetPrivateStaticClass()
{
	using TClass = UEnableHitbox;
	if (!Z_Registration_Info_UClass_UEnableHitbox.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("EnableHitbox"),
			Z_Registration_Info_UClass_UEnableHitbox.InnerSingleton,
			StaticRegisterNativesUEnableHitbox,
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
	return Z_Registration_Info_UClass_UEnableHitbox.InnerSingleton;
}
UClass* Z_Construct_UClass_UEnableHitbox_NoRegister()
{
	return UEnableHitbox::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UEnableHitbox_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Object" },
		{ "IncludePath", "Animations/Notifies/EnableHitbox.h" },
		{ "ModuleRelativePath", "Animations/Notifies/EnableHitbox.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UEnableHitbox constinit property declarations ****************************
// ********** End Class UEnableHitbox constinit property declarations ******************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UEnableHitbox>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UEnableHitbox_Statics
UObject* (*const Z_Construct_UClass_UEnableHitbox_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UAnimNotify,
	(UObject* (*)())Z_Construct_UPackage__Script_TheHunt,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UEnableHitbox_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UEnableHitbox_Statics::ClassParams = {
	&UEnableHitbox::StaticClass,
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
	0x001120A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UEnableHitbox_Statics::Class_MetaDataParams), Z_Construct_UClass_UEnableHitbox_Statics::Class_MetaDataParams)
};
void UEnableHitbox::StaticRegisterNativesUEnableHitbox()
{
}
UClass* Z_Construct_UClass_UEnableHitbox()
{
	if (!Z_Registration_Info_UClass_UEnableHitbox.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UEnableHitbox.OuterSingleton, Z_Construct_UClass_UEnableHitbox_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UEnableHitbox.OuterSingleton;
}
UEnableHitbox::UEnableHitbox(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UEnableHitbox);
UEnableHitbox::~UEnableHitbox() {}
// ********** End Class UEnableHitbox **************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Animations_Notifies_EnableHitbox_h__Script_TheHunt_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UEnableHitbox, UEnableHitbox::StaticClass, TEXT("UEnableHitbox"), &Z_Registration_Info_UClass_UEnableHitbox, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UEnableHitbox), 2662605724U) },
	};
}; // Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Animations_Notifies_EnableHitbox_h__Script_TheHunt_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Animations_Notifies_EnableHitbox_h__Script_TheHunt_2514388016{
	TEXT("/Script/TheHunt"),
	Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Animations_Notifies_EnableHitbox_h__Script_TheHunt_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Animations_Notifies_EnableHitbox_h__Script_TheHunt_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
