// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Animations/Notifies/DissableHitbox.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeDissableHitbox() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UAnimNotify();
THEHUNT_API UClass* Z_Construct_UClass_UDissableHitbox();
THEHUNT_API UClass* Z_Construct_UClass_UDissableHitbox_NoRegister();
UPackage* Z_Construct_UPackage__Script_TheHunt();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UDissableHitbox **********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UDissableHitbox;
UClass* UDissableHitbox::GetPrivateStaticClass()
{
	using TClass = UDissableHitbox;
	if (!Z_Registration_Info_UClass_UDissableHitbox.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("DissableHitbox"),
			Z_Registration_Info_UClass_UDissableHitbox.InnerSingleton,
			StaticRegisterNativesUDissableHitbox,
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
	return Z_Registration_Info_UClass_UDissableHitbox.InnerSingleton;
}
UClass* Z_Construct_UClass_UDissableHitbox_NoRegister()
{
	return UDissableHitbox::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UDissableHitbox_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Object" },
		{ "IncludePath", "Animations/Notifies/DissableHitbox.h" },
		{ "ModuleRelativePath", "Animations/Notifies/DissableHitbox.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDissableHitbox constinit property declarations **************************
// ********** End Class UDissableHitbox constinit property declarations ****************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDissableHitbox>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UDissableHitbox_Statics
UObject* (*const Z_Construct_UClass_UDissableHitbox_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UAnimNotify,
	(UObject* (*)())Z_Construct_UPackage__Script_TheHunt,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UDissableHitbox_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UDissableHitbox_Statics::ClassParams = {
	&UDissableHitbox::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UDissableHitbox_Statics::Class_MetaDataParams), Z_Construct_UClass_UDissableHitbox_Statics::Class_MetaDataParams)
};
void UDissableHitbox::StaticRegisterNativesUDissableHitbox()
{
}
UClass* Z_Construct_UClass_UDissableHitbox()
{
	if (!Z_Registration_Info_UClass_UDissableHitbox.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDissableHitbox.OuterSingleton, Z_Construct_UClass_UDissableHitbox_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UDissableHitbox.OuterSingleton;
}
UDissableHitbox::UDissableHitbox(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDissableHitbox);
UDissableHitbox::~UDissableHitbox() {}
// ********** End Class UDissableHitbox ************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Animations_Notifies_DissableHitbox_h__Script_TheHunt_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDissableHitbox, UDissableHitbox::StaticClass, TEXT("UDissableHitbox"), &Z_Registration_Info_UClass_UDissableHitbox, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDissableHitbox), 2610403433U) },
	};
}; // Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Animations_Notifies_DissableHitbox_h__Script_TheHunt_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Animations_Notifies_DissableHitbox_h__Script_TheHunt_2490691419{
	TEXT("/Script/TheHunt"),
	Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Animations_Notifies_DissableHitbox_h__Script_TheHunt_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Animations_Notifies_DissableHitbox_h__Script_TheHunt_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
