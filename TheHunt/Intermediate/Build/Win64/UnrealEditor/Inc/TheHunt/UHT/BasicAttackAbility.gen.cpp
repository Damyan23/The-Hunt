// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameplayAbilitySystem/BasicAttackAbility.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeBasicAttackAbility() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UClass_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UAnimMontage_NoRegister();
GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UGameplayAbility();
GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UGameplayEffect_NoRegister();
THEHUNT_API UClass* Z_Construct_UClass_UBasicAttackAbility();
THEHUNT_API UClass* Z_Construct_UClass_UBasicAttackAbility_NoRegister();
UPackage* Z_Construct_UPackage__Script_TheHunt();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UBasicAttackAbility Function OnMontageCompleted **************************
struct Z_Construct_UFunction_UBasicAttackAbility_OnMontageCompleted_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "GameplayAbilitySystem/BasicAttackAbility.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnMontageCompleted constinit property declarations ********************
// ********** End Function OnMontageCompleted constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBasicAttackAbility_OnMontageCompleted_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBasicAttackAbility, nullptr, "OnMontageCompleted", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBasicAttackAbility_OnMontageCompleted_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBasicAttackAbility_OnMontageCompleted_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UBasicAttackAbility_OnMontageCompleted()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBasicAttackAbility_OnMontageCompleted_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBasicAttackAbility::execOnMontageCompleted)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnMontageCompleted();
	P_NATIVE_END;
}
// ********** End Class UBasicAttackAbility Function OnMontageCompleted ****************************

// ********** Begin Class UBasicAttackAbility Function OnMontageEnded ******************************
struct Z_Construct_UFunction_UBasicAttackAbility_OnMontageEnded_Statics
{
	struct BasicAttackAbility_eventOnMontageEnded_Parms
	{
		UAnimMontage* Montage;
		bool bInterrupted;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "GameplayAbilitySystem/BasicAttackAbility.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnMontageEnded constinit property declarations ************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Montage;
	static void NewProp_bInterrupted_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bInterrupted;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function OnMontageEnded constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function OnMontageEnded Property Definitions ***********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBasicAttackAbility_OnMontageEnded_Statics::NewProp_Montage = { "Montage", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BasicAttackAbility_eventOnMontageEnded_Parms, Montage), Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UBasicAttackAbility_OnMontageEnded_Statics::NewProp_bInterrupted_SetBit(void* Obj)
{
	((BasicAttackAbility_eventOnMontageEnded_Parms*)Obj)->bInterrupted = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UBasicAttackAbility_OnMontageEnded_Statics::NewProp_bInterrupted = { "bInterrupted", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(BasicAttackAbility_eventOnMontageEnded_Parms), &Z_Construct_UFunction_UBasicAttackAbility_OnMontageEnded_Statics::NewProp_bInterrupted_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBasicAttackAbility_OnMontageEnded_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBasicAttackAbility_OnMontageEnded_Statics::NewProp_Montage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBasicAttackAbility_OnMontageEnded_Statics::NewProp_bInterrupted,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBasicAttackAbility_OnMontageEnded_Statics::PropPointers) < 2048);
// ********** End Function OnMontageEnded Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBasicAttackAbility_OnMontageEnded_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBasicAttackAbility, nullptr, "OnMontageEnded", 	Z_Construct_UFunction_UBasicAttackAbility_OnMontageEnded_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBasicAttackAbility_OnMontageEnded_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBasicAttackAbility_OnMontageEnded_Statics::BasicAttackAbility_eventOnMontageEnded_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBasicAttackAbility_OnMontageEnded_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBasicAttackAbility_OnMontageEnded_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBasicAttackAbility_OnMontageEnded_Statics::BasicAttackAbility_eventOnMontageEnded_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBasicAttackAbility_OnMontageEnded()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBasicAttackAbility_OnMontageEnded_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBasicAttackAbility::execOnMontageEnded)
{
	P_GET_OBJECT(UAnimMontage,Z_Param_Montage);
	P_GET_UBOOL(Z_Param_bInterrupted);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnMontageEnded(Z_Param_Montage,Z_Param_bInterrupted);
	P_NATIVE_END;
}
// ********** End Class UBasicAttackAbility Function OnMontageEnded ********************************

// ********** Begin Class UBasicAttackAbility ******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UBasicAttackAbility;
UClass* UBasicAttackAbility::GetPrivateStaticClass()
{
	using TClass = UBasicAttackAbility;
	if (!Z_Registration_Info_UClass_UBasicAttackAbility.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("BasicAttackAbility"),
			Z_Registration_Info_UClass_UBasicAttackAbility.InnerSingleton,
			StaticRegisterNativesUBasicAttackAbility,
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
	return Z_Registration_Info_UClass_UBasicAttackAbility.InnerSingleton;
}
UClass* Z_Construct_UClass_UBasicAttackAbility_NoRegister()
{
	return UBasicAttackAbility::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UBasicAttackAbility_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "GameplayAbilitySystem/BasicAttackAbility.h" },
		{ "ModuleRelativePath", "GameplayAbilitySystem/BasicAttackAbility.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackMontage_MetaData[] = {
		{ "Category", "Attack" },
		{ "ModuleRelativePath", "GameplayAbilitySystem/BasicAttackAbility.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DamageEffect_MetaData[] = {
		{ "Category", "Attack" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// The effect applied to the hit target\n" },
#endif
		{ "ModuleRelativePath", "GameplayAbilitySystem/BasicAttackAbility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The effect applied to the hit target" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StaggerEffect_MetaData[] = {
		{ "Category", "Attack" },
		{ "ModuleRelativePath", "GameplayAbilitySystem/BasicAttackAbility.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UBasicAttackAbility constinit property declarations **********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AttackMontage;
	static const UECodeGen_Private::FClassPropertyParams NewProp_DamageEffect;
	static const UECodeGen_Private::FClassPropertyParams NewProp_StaggerEffect;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UBasicAttackAbility constinit property declarations ************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("OnMontageCompleted"), .Pointer = &UBasicAttackAbility::execOnMontageCompleted },
		{ .NameUTF8 = UTF8TEXT("OnMontageEnded"), .Pointer = &UBasicAttackAbility::execOnMontageEnded },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UBasicAttackAbility_OnMontageCompleted, "OnMontageCompleted" }, // 743377644
		{ &Z_Construct_UFunction_UBasicAttackAbility_OnMontageEnded, "OnMontageEnded" }, // 1860062056
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBasicAttackAbility>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UBasicAttackAbility_Statics

// ********** Begin Class UBasicAttackAbility Property Definitions *********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UBasicAttackAbility_Statics::NewProp_AttackMontage = { "AttackMontage", nullptr, (EPropertyFlags)0x0114000000010001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBasicAttackAbility, AttackMontage), Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackMontage_MetaData), NewProp_AttackMontage_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UBasicAttackAbility_Statics::NewProp_DamageEffect = { "DamageEffect", nullptr, (EPropertyFlags)0x0014000000010001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBasicAttackAbility, DamageEffect), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_UGameplayEffect_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DamageEffect_MetaData), NewProp_DamageEffect_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UBasicAttackAbility_Statics::NewProp_StaggerEffect = { "StaggerEffect", nullptr, (EPropertyFlags)0x0014000000010001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBasicAttackAbility, StaggerEffect), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_UGameplayEffect_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StaggerEffect_MetaData), NewProp_StaggerEffect_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBasicAttackAbility_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBasicAttackAbility_Statics::NewProp_AttackMontage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBasicAttackAbility_Statics::NewProp_DamageEffect,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBasicAttackAbility_Statics::NewProp_StaggerEffect,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBasicAttackAbility_Statics::PropPointers) < 2048);
// ********** End Class UBasicAttackAbility Property Definitions ***********************************
UObject* (*const Z_Construct_UClass_UBasicAttackAbility_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameplayAbility,
	(UObject* (*)())Z_Construct_UPackage__Script_TheHunt,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBasicAttackAbility_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBasicAttackAbility_Statics::ClassParams = {
	&UBasicAttackAbility::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UBasicAttackAbility_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UBasicAttackAbility_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBasicAttackAbility_Statics::Class_MetaDataParams), Z_Construct_UClass_UBasicAttackAbility_Statics::Class_MetaDataParams)
};
void UBasicAttackAbility::StaticRegisterNativesUBasicAttackAbility()
{
	UClass* Class = UBasicAttackAbility::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UBasicAttackAbility_Statics::Funcs));
}
UClass* Z_Construct_UClass_UBasicAttackAbility()
{
	if (!Z_Registration_Info_UClass_UBasicAttackAbility.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBasicAttackAbility.OuterSingleton, Z_Construct_UClass_UBasicAttackAbility_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBasicAttackAbility.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UBasicAttackAbility);
UBasicAttackAbility::~UBasicAttackAbility() {}
// ********** End Class UBasicAttackAbility ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_BasicAttackAbility_h__Script_TheHunt_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBasicAttackAbility, UBasicAttackAbility::StaticClass, TEXT("UBasicAttackAbility"), &Z_Registration_Info_UClass_UBasicAttackAbility, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBasicAttackAbility), 338901802U) },
	};
}; // Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_BasicAttackAbility_h__Script_TheHunt_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_BasicAttackAbility_h__Script_TheHunt_2574222894{
	TEXT("/Script/TheHunt"),
	Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_BasicAttackAbility_h__Script_TheHunt_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_BasicAttackAbility_h__Script_TheHunt_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
