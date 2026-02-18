// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TheHuntGameMode.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeTheHuntGameMode() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
THEHUNT_API UClass* Z_Construct_UClass_ATheHuntGameMode();
THEHUNT_API UClass* Z_Construct_UClass_ATheHuntGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_TheHunt();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ATheHuntGameMode *********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_ATheHuntGameMode;
UClass* ATheHuntGameMode::GetPrivateStaticClass()
{
	using TClass = ATheHuntGameMode;
	if (!Z_Registration_Info_UClass_ATheHuntGameMode.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("TheHuntGameMode"),
			Z_Registration_Info_UClass_ATheHuntGameMode.InnerSingleton,
			StaticRegisterNativesATheHuntGameMode,
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
	return Z_Registration_Info_UClass_ATheHuntGameMode.InnerSingleton;
}
UClass* Z_Construct_UClass_ATheHuntGameMode_NoRegister()
{
	return ATheHuntGameMode::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ATheHuntGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple GameMode for a first person game\n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "TheHuntGameMode.h" },
		{ "ModuleRelativePath", "TheHuntGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple GameMode for a first person game" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class ATheHuntGameMode constinit property declarations *************************
// ********** End Class ATheHuntGameMode constinit property declarations ***************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATheHuntGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_ATheHuntGameMode_Statics
UObject* (*const Z_Construct_UClass_ATheHuntGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_TheHunt,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATheHuntGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ATheHuntGameMode_Statics::ClassParams = {
	&ATheHuntGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008002ADu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATheHuntGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ATheHuntGameMode_Statics::Class_MetaDataParams)
};
void ATheHuntGameMode::StaticRegisterNativesATheHuntGameMode()
{
}
UClass* Z_Construct_UClass_ATheHuntGameMode()
{
	if (!Z_Registration_Info_UClass_ATheHuntGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATheHuntGameMode.OuterSingleton, Z_Construct_UClass_ATheHuntGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ATheHuntGameMode.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ATheHuntGameMode);
ATheHuntGameMode::~ATheHuntGameMode() {}
// ********** End Class ATheHuntGameMode ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_TheHuntGameMode_h__Script_TheHunt_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ATheHuntGameMode, ATheHuntGameMode::StaticClass, TEXT("ATheHuntGameMode"), &Z_Registration_Info_UClass_ATheHuntGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATheHuntGameMode), 236155767U) },
	};
}; // Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_TheHuntGameMode_h__Script_TheHunt_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_TheHuntGameMode_h__Script_TheHunt_4268796449{
	TEXT("/Script/TheHunt"),
	Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_TheHuntGameMode_h__Script_TheHunt_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_TheHuntGameMode_h__Script_TheHunt_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
