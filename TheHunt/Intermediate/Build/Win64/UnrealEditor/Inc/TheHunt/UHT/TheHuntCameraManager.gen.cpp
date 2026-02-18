// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TheHuntCameraManager.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeTheHuntCameraManager() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_APlayerCameraManager();
THEHUNT_API UClass* Z_Construct_UClass_ATheHuntCameraManager();
THEHUNT_API UClass* Z_Construct_UClass_ATheHuntCameraManager_NoRegister();
UPackage* Z_Construct_UPackage__Script_TheHunt();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ATheHuntCameraManager ****************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_ATheHuntCameraManager;
UClass* ATheHuntCameraManager::GetPrivateStaticClass()
{
	using TClass = ATheHuntCameraManager;
	if (!Z_Registration_Info_UClass_ATheHuntCameraManager.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("TheHuntCameraManager"),
			Z_Registration_Info_UClass_ATheHuntCameraManager.InnerSingleton,
			StaticRegisterNativesATheHuntCameraManager,
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
	return Z_Registration_Info_UClass_ATheHuntCameraManager.InnerSingleton;
}
UClass* Z_Construct_UClass_ATheHuntCameraManager_NoRegister()
{
	return ATheHuntCameraManager::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ATheHuntCameraManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Basic First Person camera manager.\n *  Limits min/max look pitch.\n */" },
#endif
		{ "IncludePath", "TheHuntCameraManager.h" },
		{ "ModuleRelativePath", "TheHuntCameraManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Basic First Person camera manager.\nLimits min/max look pitch." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class ATheHuntCameraManager constinit property declarations ********************
// ********** End Class ATheHuntCameraManager constinit property declarations **********************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATheHuntCameraManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_ATheHuntCameraManager_Statics
UObject* (*const Z_Construct_UClass_ATheHuntCameraManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayerCameraManager,
	(UObject* (*)())Z_Construct_UPackage__Script_TheHunt,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATheHuntCameraManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ATheHuntCameraManager_Statics::ClassParams = {
	&ATheHuntCameraManager::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008002ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATheHuntCameraManager_Statics::Class_MetaDataParams), Z_Construct_UClass_ATheHuntCameraManager_Statics::Class_MetaDataParams)
};
void ATheHuntCameraManager::StaticRegisterNativesATheHuntCameraManager()
{
}
UClass* Z_Construct_UClass_ATheHuntCameraManager()
{
	if (!Z_Registration_Info_UClass_ATheHuntCameraManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATheHuntCameraManager.OuterSingleton, Z_Construct_UClass_ATheHuntCameraManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ATheHuntCameraManager.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ATheHuntCameraManager);
ATheHuntCameraManager::~ATheHuntCameraManager() {}
// ********** End Class ATheHuntCameraManager ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_TheHuntCameraManager_h__Script_TheHunt_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ATheHuntCameraManager, ATheHuntCameraManager::StaticClass, TEXT("ATheHuntCameraManager"), &Z_Registration_Info_UClass_ATheHuntCameraManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATheHuntCameraManager), 3970501068U) },
	};
}; // Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_TheHuntCameraManager_h__Script_TheHunt_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_TheHuntCameraManager_h__Script_TheHunt_880532495{
	TEXT("/Script/TheHunt"),
	Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_TheHuntCameraManager_h__Script_TheHunt_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_TheHuntCameraManager_h__Script_TheHunt_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
