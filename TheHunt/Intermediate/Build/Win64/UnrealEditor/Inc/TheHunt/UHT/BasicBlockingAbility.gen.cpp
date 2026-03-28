// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameplayAbilitySystem/Abilities/BasicBlockingAbility.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeBasicBlockingAbility() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UClass_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UAnimMontage_NoRegister();
GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UGameplayAbility();
GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UGameplayEffect_NoRegister();
THEHUNT_API UClass* Z_Construct_UClass_UBasicBlockingAbility();
THEHUNT_API UClass* Z_Construct_UClass_UBasicBlockingAbility_NoRegister();
UPackage* Z_Construct_UPackage__Script_TheHunt();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UBasicBlockingAbility Function OnBlockExitFinished ***********************
struct Z_Construct_UFunction_UBasicBlockingAbility_OnBlockExitFinished_Statics
{
	struct BasicBlockingAbility_eventOnBlockExitFinished_Parms
	{
		UAnimMontage* Montage;
		bool bInterrupted;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "GameplayAbilitySystem/Abilities/BasicBlockingAbility.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnBlockExitFinished constinit property declarations *******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Montage;
	static void NewProp_bInterrupted_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bInterrupted;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function OnBlockExitFinished constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function OnBlockExitFinished Property Definitions ******************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBasicBlockingAbility_OnBlockExitFinished_Statics::NewProp_Montage = { "Montage", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BasicBlockingAbility_eventOnBlockExitFinished_Parms, Montage), Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UBasicBlockingAbility_OnBlockExitFinished_Statics::NewProp_bInterrupted_SetBit(void* Obj)
{
	((BasicBlockingAbility_eventOnBlockExitFinished_Parms*)Obj)->bInterrupted = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UBasicBlockingAbility_OnBlockExitFinished_Statics::NewProp_bInterrupted = { "bInterrupted", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(BasicBlockingAbility_eventOnBlockExitFinished_Parms), &Z_Construct_UFunction_UBasicBlockingAbility_OnBlockExitFinished_Statics::NewProp_bInterrupted_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBasicBlockingAbility_OnBlockExitFinished_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBasicBlockingAbility_OnBlockExitFinished_Statics::NewProp_Montage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBasicBlockingAbility_OnBlockExitFinished_Statics::NewProp_bInterrupted,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBasicBlockingAbility_OnBlockExitFinished_Statics::PropPointers) < 2048);
// ********** End Function OnBlockExitFinished Property Definitions ********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBasicBlockingAbility_OnBlockExitFinished_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBasicBlockingAbility, nullptr, "OnBlockExitFinished", 	Z_Construct_UFunction_UBasicBlockingAbility_OnBlockExitFinished_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UBasicBlockingAbility_OnBlockExitFinished_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UBasicBlockingAbility_OnBlockExitFinished_Statics::BasicBlockingAbility_eventOnBlockExitFinished_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBasicBlockingAbility_OnBlockExitFinished_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBasicBlockingAbility_OnBlockExitFinished_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UBasicBlockingAbility_OnBlockExitFinished_Statics::BasicBlockingAbility_eventOnBlockExitFinished_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBasicBlockingAbility_OnBlockExitFinished()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBasicBlockingAbility_OnBlockExitFinished_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBasicBlockingAbility::execOnBlockExitFinished)
{
	P_GET_OBJECT(UAnimMontage,Z_Param_Montage);
	P_GET_UBOOL(Z_Param_bInterrupted);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnBlockExitFinished(Z_Param_Montage,Z_Param_bInterrupted);
	P_NATIVE_END;
}
// ********** End Class UBasicBlockingAbility Function OnBlockExitFinished *************************

// ********** Begin Class UBasicBlockingAbility Function OnMontageCompleted ************************
struct Z_Construct_UFunction_UBasicBlockingAbility_OnMontageCompleted_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "GameplayAbilitySystem/Abilities/BasicBlockingAbility.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnMontageCompleted constinit property declarations ********************
// ********** End Function OnMontageCompleted constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBasicBlockingAbility_OnMontageCompleted_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UBasicBlockingAbility, nullptr, "OnMontageCompleted", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBasicBlockingAbility_OnMontageCompleted_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBasicBlockingAbility_OnMontageCompleted_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UBasicBlockingAbility_OnMontageCompleted()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBasicBlockingAbility_OnMontageCompleted_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBasicBlockingAbility::execOnMontageCompleted)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnMontageCompleted();
	P_NATIVE_END;
}
// ********** End Class UBasicBlockingAbility Function OnMontageCompleted **************************

// ********** Begin Class UBasicBlockingAbility ****************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UBasicBlockingAbility;
UClass* UBasicBlockingAbility::GetPrivateStaticClass()
{
	using TClass = UBasicBlockingAbility;
	if (!Z_Registration_Info_UClass_UBasicBlockingAbility.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("BasicBlockingAbility"),
			Z_Registration_Info_UClass_UBasicBlockingAbility.InnerSingleton,
			StaticRegisterNativesUBasicBlockingAbility,
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
	return Z_Registration_Info_UClass_UBasicBlockingAbility.InnerSingleton;
}
UClass* Z_Construct_UClass_UBasicBlockingAbility_NoRegister()
{
	return UBasicBlockingAbility::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UBasicBlockingAbility_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "GameplayAbilitySystem/Abilities/BasicBlockingAbility.h" },
		{ "ModuleRelativePath", "GameplayAbilitySystem/Abilities/BasicBlockingAbility.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BlockMontage_MetaData[] = {
		{ "Category", "Attack" },
		{ "ModuleRelativePath", "GameplayAbilitySystem/Abilities/BasicBlockingAbility.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BlockEffect_MetaData[] = {
		{ "Category", "Attack" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// The effect applied to the hit target\n" },
#endif
		{ "ModuleRelativePath", "GameplayAbilitySystem/Abilities/BasicBlockingAbility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The effect applied to the hit target" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UBasicBlockingAbility constinit property declarations ********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BlockMontage;
	static const UECodeGen_Private::FClassPropertyParams NewProp_BlockEffect;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UBasicBlockingAbility constinit property declarations **********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("OnBlockExitFinished"), .Pointer = &UBasicBlockingAbility::execOnBlockExitFinished },
		{ .NameUTF8 = UTF8TEXT("OnMontageCompleted"), .Pointer = &UBasicBlockingAbility::execOnMontageCompleted },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UBasicBlockingAbility_OnBlockExitFinished, "OnBlockExitFinished" }, // 525412435
		{ &Z_Construct_UFunction_UBasicBlockingAbility_OnMontageCompleted, "OnMontageCompleted" }, // 1050041977
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBasicBlockingAbility>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UBasicBlockingAbility_Statics

// ********** Begin Class UBasicBlockingAbility Property Definitions *******************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UBasicBlockingAbility_Statics::NewProp_BlockMontage = { "BlockMontage", nullptr, (EPropertyFlags)0x0124080000010001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBasicBlockingAbility, BlockMontage), Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BlockMontage_MetaData), NewProp_BlockMontage_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UBasicBlockingAbility_Statics::NewProp_BlockEffect = { "BlockEffect", nullptr, (EPropertyFlags)0x0024080000010001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBasicBlockingAbility, BlockEffect), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_UGameplayEffect_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BlockEffect_MetaData), NewProp_BlockEffect_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBasicBlockingAbility_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBasicBlockingAbility_Statics::NewProp_BlockMontage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBasicBlockingAbility_Statics::NewProp_BlockEffect,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBasicBlockingAbility_Statics::PropPointers) < 2048);
// ********** End Class UBasicBlockingAbility Property Definitions *********************************
UObject* (*const Z_Construct_UClass_UBasicBlockingAbility_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameplayAbility,
	(UObject* (*)())Z_Construct_UPackage__Script_TheHunt,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBasicBlockingAbility_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBasicBlockingAbility_Statics::ClassParams = {
	&UBasicBlockingAbility::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UBasicBlockingAbility_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UBasicBlockingAbility_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBasicBlockingAbility_Statics::Class_MetaDataParams), Z_Construct_UClass_UBasicBlockingAbility_Statics::Class_MetaDataParams)
};
void UBasicBlockingAbility::StaticRegisterNativesUBasicBlockingAbility()
{
	UClass* Class = UBasicBlockingAbility::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UBasicBlockingAbility_Statics::Funcs));
}
UClass* Z_Construct_UClass_UBasicBlockingAbility()
{
	if (!Z_Registration_Info_UClass_UBasicBlockingAbility.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBasicBlockingAbility.OuterSingleton, Z_Construct_UClass_UBasicBlockingAbility_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBasicBlockingAbility.OuterSingleton;
}
UBasicBlockingAbility::UBasicBlockingAbility(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UBasicBlockingAbility);
UBasicBlockingAbility::~UBasicBlockingAbility() {}
// ********** End Class UBasicBlockingAbility ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_Abilities_BasicBlockingAbility_h__Script_TheHunt_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBasicBlockingAbility, UBasicBlockingAbility::StaticClass, TEXT("UBasicBlockingAbility"), &Z_Registration_Info_UClass_UBasicBlockingAbility, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBasicBlockingAbility), 1747535505U) },
	};
}; // Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_Abilities_BasicBlockingAbility_h__Script_TheHunt_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_Abilities_BasicBlockingAbility_h__Script_TheHunt_1643980492{
	TEXT("/Script/TheHunt"),
	Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_Abilities_BasicBlockingAbility_h__Script_TheHunt_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_GameplayAbilitySystem_Abilities_BasicBlockingAbility_h__Script_TheHunt_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
