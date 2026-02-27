// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Items/ItemEffect.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeItemEffect() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
THEHUNT_API UClass* Z_Construct_UClass_UItemEffect();
THEHUNT_API UClass* Z_Construct_UClass_UItemEffect_NoRegister();
UPackage* Z_Construct_UPackage__Script_TheHunt();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UItemEffect Function ApplyEffect *****************************************
struct Z_Construct_UFunction_UItemEffect_ApplyEffect_Statics
{
	struct ItemEffect_eventApplyEffect_Parms
	{
		AActor* target;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Items/ItemEffect.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ApplyEffect constinit property declarations ***************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_target;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ApplyEffect constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ApplyEffect Property Definitions **************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UItemEffect_ApplyEffect_Statics::NewProp_target = { "target", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ItemEffect_eventApplyEffect_Parms, target), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UItemEffect_ApplyEffect_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UItemEffect_ApplyEffect_Statics::NewProp_target,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UItemEffect_ApplyEffect_Statics::PropPointers) < 2048);
// ********** End Function ApplyEffect Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UItemEffect_ApplyEffect_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UItemEffect, nullptr, "ApplyEffect", 	Z_Construct_UFunction_UItemEffect_ApplyEffect_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UItemEffect_ApplyEffect_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UItemEffect_ApplyEffect_Statics::ItemEffect_eventApplyEffect_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UItemEffect_ApplyEffect_Statics::Function_MetaDataParams), Z_Construct_UFunction_UItemEffect_ApplyEffect_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UItemEffect_ApplyEffect_Statics::ItemEffect_eventApplyEffect_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UItemEffect_ApplyEffect()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UItemEffect_ApplyEffect_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UItemEffect::execApplyEffect)
{
	P_GET_OBJECT(AActor,Z_Param_target);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ApplyEffect(Z_Param_target);
	P_NATIVE_END;
}
// ********** End Class UItemEffect Function ApplyEffect *******************************************

// ********** Begin Class UItemEffect **************************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UItemEffect;
UClass* UItemEffect::GetPrivateStaticClass()
{
	using TClass = UItemEffect;
	if (!Z_Registration_Info_UClass_UItemEffect.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("ItemEffect"),
			Z_Registration_Info_UClass_UItemEffect.InnerSingleton,
			StaticRegisterNativesUItemEffect,
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
	return Z_Registration_Info_UClass_UItemEffect.InnerSingleton;
}
UClass* Z_Construct_UClass_UItemEffect_NoRegister()
{
	return UItemEffect::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UItemEffect_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Items/ItemEffect.h" },
		{ "ModuleRelativePath", "Items/ItemEffect.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UItemEffect constinit property declarations ******************************
// ********** End Class UItemEffect constinit property declarations ********************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ApplyEffect"), .Pointer = &UItemEffect::execApplyEffect },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UItemEffect_ApplyEffect, "ApplyEffect" }, // 2830726604
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UItemEffect>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UItemEffect_Statics
UObject* (*const Z_Construct_UClass_UItemEffect_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_TheHunt,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UItemEffect_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UItemEffect_Statics::ClassParams = {
	&UItemEffect::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UItemEffect_Statics::Class_MetaDataParams), Z_Construct_UClass_UItemEffect_Statics::Class_MetaDataParams)
};
void UItemEffect::StaticRegisterNativesUItemEffect()
{
	UClass* Class = UItemEffect::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UItemEffect_Statics::Funcs));
}
UClass* Z_Construct_UClass_UItemEffect()
{
	if (!Z_Registration_Info_UClass_UItemEffect.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UItemEffect.OuterSingleton, Z_Construct_UClass_UItemEffect_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UItemEffect.OuterSingleton;
}
UItemEffect::UItemEffect(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UItemEffect);
UItemEffect::~UItemEffect() {}
// ********** End Class UItemEffect ****************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Items_ItemEffect_h__Script_TheHunt_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UItemEffect, UItemEffect::StaticClass, TEXT("UItemEffect"), &Z_Registration_Info_UClass_UItemEffect, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UItemEffect), 706319227U) },
	};
}; // Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Items_ItemEffect_h__Script_TheHunt_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Items_ItemEffect_h__Script_TheHunt_1407790230{
	TEXT("/Script/TheHunt"),
	Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Items_ItemEffect_h__Script_TheHunt_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Items_ItemEffect_h__Script_TheHunt_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
