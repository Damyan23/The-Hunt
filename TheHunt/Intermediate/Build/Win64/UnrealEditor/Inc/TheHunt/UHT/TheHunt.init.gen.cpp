// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTheHunt_init() {}
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");	THEHUNT_API UFunction* Z_Construct_UDelegateFunction_TheHunt_BulletCountUpdatedDelegate__DelegateSignature();
	THEHUNT_API UFunction* Z_Construct_UDelegateFunction_TheHunt_DamagedDelegate__DelegateSignature();
	THEHUNT_API UFunction* Z_Construct_UDelegateFunction_TheHunt_PawnDeathDelegate__DelegateSignature();
	THEHUNT_API UFunction* Z_Construct_UDelegateFunction_TheHunt_SprintStateChangedDelegate__DelegateSignature();
	THEHUNT_API UFunction* Z_Construct_UDelegateFunction_TheHunt_UpdateSprintMeterDelegate__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_TheHunt;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_TheHunt()
	{
		if (!Z_Registration_Info_UPackage__Script_TheHunt.OuterSingleton)
		{
		static UObject* (*const SingletonFuncArray[])() = {
			(UObject* (*)())Z_Construct_UDelegateFunction_TheHunt_BulletCountUpdatedDelegate__DelegateSignature,
			(UObject* (*)())Z_Construct_UDelegateFunction_TheHunt_DamagedDelegate__DelegateSignature,
			(UObject* (*)())Z_Construct_UDelegateFunction_TheHunt_PawnDeathDelegate__DelegateSignature,
			(UObject* (*)())Z_Construct_UDelegateFunction_TheHunt_SprintStateChangedDelegate__DelegateSignature,
			(UObject* (*)())Z_Construct_UDelegateFunction_TheHunt_UpdateSprintMeterDelegate__DelegateSignature,
		};
		static const UECodeGen_Private::FPackageParams PackageParams = {
			"/Script/TheHunt",
			SingletonFuncArray,
			UE_ARRAY_COUNT(SingletonFuncArray),
			PKG_CompiledIn | 0x00000000,
			0x11B3D3C5,
			0x44BB4873,
			METADATA_PARAMS(0, nullptr)
		};
		UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_TheHunt.OuterSingleton, PackageParams);
	}
	return Z_Registration_Info_UPackage__Script_TheHunt.OuterSingleton;
}
static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_TheHunt(Z_Construct_UPackage__Script_TheHunt, TEXT("/Script/TheHunt"), Z_Registration_Info_UPackage__Script_TheHunt, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x11B3D3C5, 0x44BB4873));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
