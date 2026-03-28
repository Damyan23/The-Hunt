// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Enemy/EnemyCharacter.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeEnemyCharacter() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
THEHUNT_API UClass* Z_Construct_UClass_ABaseCharacter();
THEHUNT_API UClass* Z_Construct_UClass_AEnemyCharacter();
THEHUNT_API UClass* Z_Construct_UClass_AEnemyCharacter_NoRegister();
THEHUNT_API UEnum* Z_Construct_UEnum_TheHunt_EEnemyCombatState();
THEHUNT_API UEnum* Z_Construct_UEnum_TheHunt_EEnemyState();
UPackage* Z_Construct_UPackage__Script_TheHunt();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EEnemyState ***************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EEnemyState;
static UEnum* EEnemyState_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EEnemyState.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EEnemyState.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_TheHunt_EEnemyState, (UObject*)Z_Construct_UPackage__Script_TheHunt(), TEXT("EEnemyState"));
	}
	return Z_Registration_Info_UEnum_EEnemyState.OuterSingleton;
}
template<> THEHUNT_NON_ATTRIBUTED_API UEnum* StaticEnum<EEnemyState>()
{
	return EEnemyState_StaticEnum();
}
struct Z_Construct_UEnum_TheHunt_EEnemyState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Alert.Comment", "/**\n * \n */" },
		{ "Alert.Name", "EEnemyState::Alert" },
		{ "Attack.Comment", "/**\n * \n */" },
		{ "Attack.Name", "EEnemyState::Attack" },
		{ "BlueprintType", "true" },
		{ "Chase.Comment", "/**\n * \n */" },
		{ "Chase.Name", "EEnemyState::Chase" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "Dead.Comment", "/**\n * \n */" },
		{ "Dead.Name", "EEnemyState::Dead" },
		{ "Idle.Comment", "/**\n * \n */" },
		{ "Idle.Name", "EEnemyState::Idle" },
		{ "ModuleRelativePath", "Enemy/EnemyCharacter.h" },
		{ "Patrol.Comment", "/**\n * \n */" },
		{ "Patrol.Name", "EEnemyState::Patrol" },
		{ "Stagger.Comment", "/**\n * \n */" },
		{ "Stagger.Name", "EEnemyState::Stagger" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EEnemyState::Idle", (int64)EEnemyState::Idle },
		{ "EEnemyState::Patrol", (int64)EEnemyState::Patrol },
		{ "EEnemyState::Chase", (int64)EEnemyState::Chase },
		{ "EEnemyState::Alert", (int64)EEnemyState::Alert },
		{ "EEnemyState::Attack", (int64)EEnemyState::Attack },
		{ "EEnemyState::Stagger", (int64)EEnemyState::Stagger },
		{ "EEnemyState::Dead", (int64)EEnemyState::Dead },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_TheHunt_EEnemyState_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_TheHunt_EEnemyState_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_TheHunt,
	nullptr,
	"EEnemyState",
	"EEnemyState",
	Z_Construct_UEnum_TheHunt_EEnemyState_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_TheHunt_EEnemyState_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_TheHunt_EEnemyState_Statics::Enum_MetaDataParams), Z_Construct_UEnum_TheHunt_EEnemyState_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_TheHunt_EEnemyState()
{
	if (!Z_Registration_Info_UEnum_EEnemyState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EEnemyState.InnerSingleton, Z_Construct_UEnum_TheHunt_EEnemyState_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EEnemyState.InnerSingleton;
}
// ********** End Enum EEnemyState *****************************************************************

// ********** Begin Enum EEnemyCombatState *********************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EEnemyCombatState;
static UEnum* EEnemyCombatState_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EEnemyCombatState.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EEnemyCombatState.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_TheHunt_EEnemyCombatState, (UObject*)Z_Construct_UPackage__Script_TheHunt(), TEXT("EEnemyCombatState"));
	}
	return Z_Registration_Info_UEnum_EEnemyCombatState.OuterSingleton;
}
template<> THEHUNT_NON_ATTRIBUTED_API UEnum* StaticEnum<EEnemyCombatState>()
{
	return EEnemyCombatState_StaticEnum();
}
struct Z_Construct_UEnum_TheHunt_EEnemyCombatState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Attacking.Name", "EEnemyCombatState::Attacking" },
		{ "Blocking.Name", "EEnemyCombatState::Blocking" },
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Enemy/EnemyCharacter.h" },
		{ "None.Name", "EEnemyCombatState::None" },
		{ "Strafe.Name", "EEnemyCombatState::Strafe" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EEnemyCombatState::None", (int64)EEnemyCombatState::None },
		{ "EEnemyCombatState::Strafe", (int64)EEnemyCombatState::Strafe },
		{ "EEnemyCombatState::Attacking", (int64)EEnemyCombatState::Attacking },
		{ "EEnemyCombatState::Blocking", (int64)EEnemyCombatState::Blocking },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_TheHunt_EEnemyCombatState_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_TheHunt_EEnemyCombatState_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_TheHunt,
	nullptr,
	"EEnemyCombatState",
	"EEnemyCombatState",
	Z_Construct_UEnum_TheHunt_EEnemyCombatState_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_TheHunt_EEnemyCombatState_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_TheHunt_EEnemyCombatState_Statics::Enum_MetaDataParams), Z_Construct_UEnum_TheHunt_EEnemyCombatState_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_TheHunt_EEnemyCombatState()
{
	if (!Z_Registration_Info_UEnum_EEnemyCombatState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EEnemyCombatState.InnerSingleton, Z_Construct_UEnum_TheHunt_EEnemyCombatState_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EEnemyCombatState.InnerSingleton;
}
// ********** End Enum EEnemyCombatState ***********************************************************

// ********** Begin Class AEnemyCharacter **********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AEnemyCharacter;
UClass* AEnemyCharacter::GetPrivateStaticClass()
{
	using TClass = AEnemyCharacter;
	if (!Z_Registration_Info_UClass_AEnemyCharacter.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("EnemyCharacter"),
			Z_Registration_Info_UClass_AEnemyCharacter.InnerSingleton,
			StaticRegisterNativesAEnemyCharacter,
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
	return Z_Registration_Info_UClass_AEnemyCharacter.InnerSingleton;
}
UClass* Z_Construct_UClass_AEnemyCharacter_NoRegister()
{
	return AEnemyCharacter::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AEnemyCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Enemy/EnemyCharacter.h" },
		{ "ModuleRelativePath", "Enemy/EnemyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentState_MetaData[] = {
		{ "Category", "AI" },
		{ "ModuleRelativePath", "Enemy/EnemyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CombatState_MetaData[] = {
		{ "Category", "AI" },
		{ "ModuleRelativePath", "Enemy/EnemyCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PatrolPoints_MetaData[] = {
		{ "Category", "AI" },
		{ "ModuleRelativePath", "Enemy/EnemyCharacter.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class AEnemyCharacter constinit property declarations **************************
	static const UECodeGen_Private::FBytePropertyParams NewProp_CurrentState_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_CurrentState;
	static const UECodeGen_Private::FBytePropertyParams NewProp_CombatState_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_CombatState;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PatrolPoints_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_PatrolPoints;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AEnemyCharacter constinit property declarations ****************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEnemyCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AEnemyCharacter_Statics

// ********** Begin Class AEnemyCharacter Property Definitions *************************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AEnemyCharacter_Statics::NewProp_CurrentState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AEnemyCharacter_Statics::NewProp_CurrentState = { "CurrentState", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyCharacter, CurrentState), Z_Construct_UEnum_TheHunt_EEnemyState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentState_MetaData), NewProp_CurrentState_MetaData) }; // 167400890
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AEnemyCharacter_Statics::NewProp_CombatState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AEnemyCharacter_Statics::NewProp_CombatState = { "CombatState", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyCharacter, CombatState), Z_Construct_UEnum_TheHunt_EEnemyCombatState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CombatState_MetaData), NewProp_CombatState_MetaData) }; // 3517014261
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEnemyCharacter_Statics::NewProp_PatrolPoints_Inner = { "PatrolPoints", nullptr, (EPropertyFlags)0x0104000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AEnemyCharacter_Statics::NewProp_PatrolPoints = { "PatrolPoints", nullptr, (EPropertyFlags)0x0114000000000801, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyCharacter, PatrolPoints), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PatrolPoints_MetaData), NewProp_PatrolPoints_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AEnemyCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyCharacter_Statics::NewProp_CurrentState_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyCharacter_Statics::NewProp_CurrentState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyCharacter_Statics::NewProp_CombatState_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyCharacter_Statics::NewProp_CombatState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyCharacter_Statics::NewProp_PatrolPoints_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyCharacter_Statics::NewProp_PatrolPoints,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyCharacter_Statics::PropPointers) < 2048);
// ********** End Class AEnemyCharacter Property Definitions ***************************************
UObject* (*const Z_Construct_UClass_AEnemyCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ABaseCharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_TheHunt,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AEnemyCharacter_Statics::ClassParams = {
	&AEnemyCharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AEnemyCharacter_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyCharacter_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_AEnemyCharacter_Statics::Class_MetaDataParams)
};
void AEnemyCharacter::StaticRegisterNativesAEnemyCharacter()
{
}
UClass* Z_Construct_UClass_AEnemyCharacter()
{
	if (!Z_Registration_Info_UClass_AEnemyCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AEnemyCharacter.OuterSingleton, Z_Construct_UClass_AEnemyCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AEnemyCharacter.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AEnemyCharacter);
AEnemyCharacter::~AEnemyCharacter() {}
// ********** End Class AEnemyCharacter ************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Enemy_EnemyCharacter_h__Script_TheHunt_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EEnemyState_StaticEnum, TEXT("EEnemyState"), &Z_Registration_Info_UEnum_EEnemyState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 167400890U) },
		{ EEnemyCombatState_StaticEnum, TEXT("EEnemyCombatState"), &Z_Registration_Info_UEnum_EEnemyCombatState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3517014261U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AEnemyCharacter, AEnemyCharacter::StaticClass, TEXT("AEnemyCharacter"), &Z_Registration_Info_UClass_AEnemyCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AEnemyCharacter), 107089028U) },
	};
}; // Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Enemy_EnemyCharacter_h__Script_TheHunt_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Enemy_EnemyCharacter_h__Script_TheHunt_796060373{
	TEXT("/Script/TheHunt"),
	Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Enemy_EnemyCharacter_h__Script_TheHunt_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Enemy_EnemyCharacter_h__Script_TheHunt_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Enemy_EnemyCharacter_h__Script_TheHunt_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Enemy_EnemyCharacter_h__Script_TheHunt_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
