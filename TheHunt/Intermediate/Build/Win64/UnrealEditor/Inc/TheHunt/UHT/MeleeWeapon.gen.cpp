// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Items/Weapon/MeleeWeapon.h"
#include "Engine/HitResult.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeMeleeWeapon() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FTransform();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UCapsuleComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UPrimitiveComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
THEHUNT_API UClass* Z_Construct_UClass_AMeleeWeapon();
THEHUNT_API UClass* Z_Construct_UClass_AMeleeWeapon_NoRegister();
THEHUNT_API UClass* Z_Construct_UClass_UItemDefinition_NoRegister();
UPackage* Z_Construct_UPackage__Script_TheHunt();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AMeleeWeapon Function OnSwordHit *****************************************
struct Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics
{
	struct MeleeWeapon_eventOnSwordHit_Parms
	{
		UPrimitiveComponent* OverlappedComp;
		AActor* OtherActor;
		UPrimitiveComponent* OtherComp;
		int32 OtherBodyIndex;
		bool bFromSweep;
		FHitResult SweepResult;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Items/Weapon/MeleeWeapon.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OverlappedComp_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherComp_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SweepResult_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnSwordHit constinit property declarations ****************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OverlappedComp;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherComp;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OtherBodyIndex;
	static void NewProp_bFromSweep_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bFromSweep;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SweepResult;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function OnSwordHit constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function OnSwordHit Property Definitions ***************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::NewProp_OverlappedComp = { "OverlappedComp", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MeleeWeapon_eventOnSwordHit_Parms, OverlappedComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OverlappedComp_MetaData), NewProp_OverlappedComp_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MeleeWeapon_eventOnSwordHit_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::NewProp_OtherComp = { "OtherComp", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MeleeWeapon_eventOnSwordHit_Parms, OtherComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherComp_MetaData), NewProp_OtherComp_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::NewProp_OtherBodyIndex = { "OtherBodyIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MeleeWeapon_eventOnSwordHit_Parms, OtherBodyIndex), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::NewProp_bFromSweep_SetBit(void* Obj)
{
	((MeleeWeapon_eventOnSwordHit_Parms*)Obj)->bFromSweep = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::NewProp_bFromSweep = { "bFromSweep", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(MeleeWeapon_eventOnSwordHit_Parms), &Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::NewProp_bFromSweep_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::NewProp_SweepResult = { "SweepResult", nullptr, (EPropertyFlags)0x0010008008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MeleeWeapon_eventOnSwordHit_Parms, SweepResult), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SweepResult_MetaData), NewProp_SweepResult_MetaData) }; // 222120718
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::NewProp_OverlappedComp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::NewProp_OtherActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::NewProp_OtherComp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::NewProp_OtherBodyIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::NewProp_bFromSweep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::NewProp_SweepResult,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::PropPointers) < 2048);
// ********** End Function OnSwordHit Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMeleeWeapon, nullptr, "OnSwordHit", 	Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::MeleeWeapon_eventOnSwordHit_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::MeleeWeapon_eventOnSwordHit_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMeleeWeapon_OnSwordHit()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMeleeWeapon_OnSwordHit_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMeleeWeapon::execOnSwordHit)
{
	P_GET_OBJECT(UPrimitiveComponent,Z_Param_OverlappedComp);
	P_GET_OBJECT(AActor,Z_Param_OtherActor);
	P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp);
	P_GET_PROPERTY(FIntProperty,Z_Param_OtherBodyIndex);
	P_GET_UBOOL(Z_Param_bFromSweep);
	P_GET_STRUCT_REF(FHitResult,Z_Param_Out_SweepResult);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnSwordHit(Z_Param_OverlappedComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_OtherBodyIndex,Z_Param_bFromSweep,Z_Param_Out_SweepResult);
	P_NATIVE_END;
}
// ********** End Class AMeleeWeapon Function OnSwordHit *******************************************

// ********** Begin Class AMeleeWeapon *************************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AMeleeWeapon;
UClass* AMeleeWeapon::GetPrivateStaticClass()
{
	using TClass = AMeleeWeapon;
	if (!Z_Registration_Info_UClass_AMeleeWeapon.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("MeleeWeapon"),
			Z_Registration_Info_UClass_AMeleeWeapon.InnerSingleton,
			StaticRegisterNativesAMeleeWeapon,
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
	return Z_Registration_Info_UClass_AMeleeWeapon.InnerSingleton;
}
UClass* Z_Construct_UClass_AMeleeWeapon_NoRegister()
{
	return AMeleeWeapon::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AMeleeWeapon_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Items/Weapon/MeleeWeapon.h" },
		{ "ModuleRelativePath", "Items/Weapon/MeleeWeapon.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Capsule_MetaData[] = {
		{ "Category", "MeleeWeapon" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Items/Weapon/MeleeWeapon.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WeaponMesh_MetaData[] = {
		{ "Category", "MeleeWeapon" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Items/Weapon/MeleeWeapon.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemDefinition_MetaData[] = {
		{ "Category", "Item" },
		{ "ModuleRelativePath", "Items/Weapon/MeleeWeapon.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttachOffset_MetaData[] = {
		{ "Category", "Attachment" },
		{ "ModuleRelativePath", "Items/Weapon/MeleeWeapon.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttachSocketName_MetaData[] = {
		{ "Category", "Attachment" },
		{ "ModuleRelativePath", "Items/Weapon/MeleeWeapon.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class AMeleeWeapon constinit property declarations *****************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Capsule;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WeaponMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ItemDefinition;
	static const UECodeGen_Private::FStructPropertyParams NewProp_AttachOffset;
	static const UECodeGen_Private::FNamePropertyParams NewProp_AttachSocketName;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AMeleeWeapon constinit property declarations *******************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("OnSwordHit"), .Pointer = &AMeleeWeapon::execOnSwordHit },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AMeleeWeapon_OnSwordHit, "OnSwordHit" }, // 26992310
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMeleeWeapon>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AMeleeWeapon_Statics

// ********** Begin Class AMeleeWeapon Property Definitions ****************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMeleeWeapon_Statics::NewProp_Capsule = { "Capsule", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMeleeWeapon, Capsule), Z_Construct_UClass_UCapsuleComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Capsule_MetaData), NewProp_Capsule_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMeleeWeapon_Statics::NewProp_WeaponMesh = { "WeaponMesh", nullptr, (EPropertyFlags)0x01140000000a000d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMeleeWeapon, WeaponMesh), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WeaponMesh_MetaData), NewProp_WeaponMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMeleeWeapon_Statics::NewProp_ItemDefinition = { "ItemDefinition", nullptr, (EPropertyFlags)0x0114000000010001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMeleeWeapon, ItemDefinition), Z_Construct_UClass_UItemDefinition_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemDefinition_MetaData), NewProp_ItemDefinition_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AMeleeWeapon_Statics::NewProp_AttachOffset = { "AttachOffset", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMeleeWeapon, AttachOffset), Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttachOffset_MetaData), NewProp_AttachOffset_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_AMeleeWeapon_Statics::NewProp_AttachSocketName = { "AttachSocketName", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMeleeWeapon, AttachSocketName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttachSocketName_MetaData), NewProp_AttachSocketName_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMeleeWeapon_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMeleeWeapon_Statics::NewProp_Capsule,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMeleeWeapon_Statics::NewProp_WeaponMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMeleeWeapon_Statics::NewProp_ItemDefinition,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMeleeWeapon_Statics::NewProp_AttachOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMeleeWeapon_Statics::NewProp_AttachSocketName,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMeleeWeapon_Statics::PropPointers) < 2048);
// ********** End Class AMeleeWeapon Property Definitions ******************************************
UObject* (*const Z_Construct_UClass_AMeleeWeapon_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_TheHunt,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMeleeWeapon_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMeleeWeapon_Statics::ClassParams = {
	&AMeleeWeapon::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AMeleeWeapon_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AMeleeWeapon_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMeleeWeapon_Statics::Class_MetaDataParams), Z_Construct_UClass_AMeleeWeapon_Statics::Class_MetaDataParams)
};
void AMeleeWeapon::StaticRegisterNativesAMeleeWeapon()
{
	UClass* Class = AMeleeWeapon::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_AMeleeWeapon_Statics::Funcs));
}
UClass* Z_Construct_UClass_AMeleeWeapon()
{
	if (!Z_Registration_Info_UClass_AMeleeWeapon.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMeleeWeapon.OuterSingleton, Z_Construct_UClass_AMeleeWeapon_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMeleeWeapon.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AMeleeWeapon);
AMeleeWeapon::~AMeleeWeapon() {}
// ********** End Class AMeleeWeapon ***************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Items_Weapon_MeleeWeapon_h__Script_TheHunt_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMeleeWeapon, AMeleeWeapon::StaticClass, TEXT("AMeleeWeapon"), &Z_Registration_Info_UClass_AMeleeWeapon, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMeleeWeapon), 2821087866U) },
	};
}; // Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Items_Weapon_MeleeWeapon_h__Script_TheHunt_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Items_Weapon_MeleeWeapon_h__Script_TheHunt_3188271606{
	TEXT("/Script/TheHunt"),
	Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Items_Weapon_MeleeWeapon_h__Script_TheHunt_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Items_Weapon_MeleeWeapon_h__Script_TheHunt_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
