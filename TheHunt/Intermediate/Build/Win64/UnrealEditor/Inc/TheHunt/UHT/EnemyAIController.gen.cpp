// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Enemy/EnemyAIController.h"
#include "Perception/AIPerceptionTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeEnemyAIController() {}

// ********** Begin Cross Module References ********************************************************
AIMODULE_API UClass* Z_Construct_UClass_AAIController();
AIMODULE_API UClass* Z_Construct_UClass_UAISenseConfig_Hearing_NoRegister();
AIMODULE_API UClass* Z_Construct_UClass_UAISenseConfig_Sight_NoRegister();
AIMODULE_API UScriptStruct* Z_Construct_UScriptStruct_FAIStimulus();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_APawn_NoRegister();
THEHUNT_API UClass* Z_Construct_UClass_AEnemyAIController();
THEHUNT_API UClass* Z_Construct_UClass_AEnemyAIController_NoRegister();
THEHUNT_API UClass* Z_Construct_UClass_AEnemyCharacter_NoRegister();
UPackage* Z_Construct_UPackage__Script_TheHunt();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AEnemyAIController Function Attack ***************************************
struct Z_Construct_UFunction_AEnemyAIController_Attack_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Enemy/EnemyAIController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function Attack constinit property declarations ********************************
// ********** End Function Attack constinit property declarations **********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAIController_Attack_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAIController, nullptr, "Attack", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_Attack_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAIController_Attack_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AEnemyAIController_Attack()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAIController_Attack_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAIController::execAttack)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Attack();
	P_NATIVE_END;
}
// ********** End Class AEnemyAIController Function Attack *****************************************

// ********** Begin Class AEnemyAIController Function Block ****************************************
struct Z_Construct_UFunction_AEnemyAIController_Block_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Enemy/EnemyAIController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function Block constinit property declarations *********************************
// ********** End Function Block constinit property declarations ***********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAIController_Block_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAIController, nullptr, "Block", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_Block_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAIController_Block_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AEnemyAIController_Block()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAIController_Block_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAIController::execBlock)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Block();
	P_NATIVE_END;
}
// ********** End Class AEnemyAIController Function Block ******************************************

// ********** Begin Class AEnemyAIController Function OnAlertTimerExpired **************************
struct Z_Construct_UFunction_AEnemyAIController_OnAlertTimerExpired_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Enemy/EnemyAIController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnAlertTimerExpired constinit property declarations *******************
// ********** End Function OnAlertTimerExpired constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAIController_OnAlertTimerExpired_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAIController, nullptr, "OnAlertTimerExpired", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_OnAlertTimerExpired_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAIController_OnAlertTimerExpired_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AEnemyAIController_OnAlertTimerExpired()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAIController_OnAlertTimerExpired_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAIController::execOnAlertTimerExpired)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnAlertTimerExpired();
	P_NATIVE_END;
}
// ********** End Class AEnemyAIController Function OnAlertTimerExpired ****************************

// ********** Begin Class AEnemyAIController Function OnPerceptionUpdated **************************
struct Z_Construct_UFunction_AEnemyAIController_OnPerceptionUpdated_Statics
{
	struct EnemyAIController_eventOnPerceptionUpdated_Parms
	{
		AActor* Actor;
		FAIStimulus Stimulus;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Enemy/EnemyAIController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnPerceptionUpdated constinit property declarations *******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Actor;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Stimulus;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function OnPerceptionUpdated constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function OnPerceptionUpdated Property Definitions ******************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AEnemyAIController_OnPerceptionUpdated_Statics::NewProp_Actor = { "Actor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EnemyAIController_eventOnPerceptionUpdated_Parms, Actor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AEnemyAIController_OnPerceptionUpdated_Statics::NewProp_Stimulus = { "Stimulus", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EnemyAIController_eventOnPerceptionUpdated_Parms, Stimulus), Z_Construct_UScriptStruct_FAIStimulus, METADATA_PARAMS(0, nullptr) }; // 819600324
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AEnemyAIController_OnPerceptionUpdated_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyAIController_OnPerceptionUpdated_Statics::NewProp_Actor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AEnemyAIController_OnPerceptionUpdated_Statics::NewProp_Stimulus,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_OnPerceptionUpdated_Statics::PropPointers) < 2048);
// ********** End Function OnPerceptionUpdated Property Definitions ********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAIController_OnPerceptionUpdated_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAIController, nullptr, "OnPerceptionUpdated", 	Z_Construct_UFunction_AEnemyAIController_OnPerceptionUpdated_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_OnPerceptionUpdated_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_AEnemyAIController_OnPerceptionUpdated_Statics::EnemyAIController_eventOnPerceptionUpdated_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_OnPerceptionUpdated_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAIController_OnPerceptionUpdated_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AEnemyAIController_OnPerceptionUpdated_Statics::EnemyAIController_eventOnPerceptionUpdated_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AEnemyAIController_OnPerceptionUpdated()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAIController_OnPerceptionUpdated_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAIController::execOnPerceptionUpdated)
{
	P_GET_OBJECT(AActor,Z_Param_Actor);
	P_GET_STRUCT(FAIStimulus,Z_Param_Stimulus);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnPerceptionUpdated(Z_Param_Actor,Z_Param_Stimulus);
	P_NATIVE_END;
}
// ********** End Class AEnemyAIController Function OnPerceptionUpdated ****************************

// ********** Begin Class AEnemyAIController Function Strafe ***************************************
struct Z_Construct_UFunction_AEnemyAIController_Strafe_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Enemy/EnemyAIController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function Strafe constinit property declarations ********************************
// ********** End Function Strafe constinit property declarations **********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAIController_Strafe_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAIController, nullptr, "Strafe", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_Strafe_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAIController_Strafe_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AEnemyAIController_Strafe()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAIController_Strafe_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAIController::execStrafe)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Strafe();
	P_NATIVE_END;
}
// ********** End Class AEnemyAIController Function Strafe *****************************************

// ********** Begin Class AEnemyAIController Function UpdateAlertState *****************************
struct Z_Construct_UFunction_AEnemyAIController_UpdateAlertState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Enemy/EnemyAIController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function UpdateAlertState constinit property declarations **********************
// ********** End Function UpdateAlertState constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAIController_UpdateAlertState_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAIController, nullptr, "UpdateAlertState", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_UpdateAlertState_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAIController_UpdateAlertState_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AEnemyAIController_UpdateAlertState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAIController_UpdateAlertState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAIController::execUpdateAlertState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UpdateAlertState();
	P_NATIVE_END;
}
// ********** End Class AEnemyAIController Function UpdateAlertState *******************************

// ********** Begin Class AEnemyAIController Function UpdateAttackState ****************************
struct Z_Construct_UFunction_AEnemyAIController_UpdateAttackState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ============================================================\n// Combat\n// ============================================================\n" },
#endif
		{ "ModuleRelativePath", "Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Combat" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function UpdateAttackState constinit property declarations *********************
// ********** End Function UpdateAttackState constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAIController_UpdateAttackState_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAIController, nullptr, "UpdateAttackState", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_UpdateAttackState_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAIController_UpdateAttackState_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AEnemyAIController_UpdateAttackState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAIController_UpdateAttackState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAIController::execUpdateAttackState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UpdateAttackState();
	P_NATIVE_END;
}
// ********** End Class AEnemyAIController Function UpdateAttackState ******************************

// ********** Begin Class AEnemyAIController Function UpdateChaseState *****************************
struct Z_Construct_UFunction_AEnemyAIController_UpdateChaseState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Enemy/EnemyAIController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function UpdateChaseState constinit property declarations **********************
// ********** End Function UpdateChaseState constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAIController_UpdateChaseState_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAIController, nullptr, "UpdateChaseState", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_UpdateChaseState_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAIController_UpdateChaseState_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AEnemyAIController_UpdateChaseState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAIController_UpdateChaseState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAIController::execUpdateChaseState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UpdateChaseState();
	P_NATIVE_END;
}
// ********** End Class AEnemyAIController Function UpdateChaseState *******************************

// ********** Begin Class AEnemyAIController Function UpdateCurrentState ***************************
struct Z_Construct_UFunction_AEnemyAIController_UpdateCurrentState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ============================================================\n// State Update\n// ============================================================\n" },
#endif
		{ "ModuleRelativePath", "Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "State Update" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function UpdateCurrentState constinit property declarations ********************
// ********** End Function UpdateCurrentState constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAIController_UpdateCurrentState_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAIController, nullptr, "UpdateCurrentState", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_UpdateCurrentState_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAIController_UpdateCurrentState_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AEnemyAIController_UpdateCurrentState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAIController_UpdateCurrentState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAIController::execUpdateCurrentState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UpdateCurrentState();
	P_NATIVE_END;
}
// ********** End Class AEnemyAIController Function UpdateCurrentState *****************************

// ********** Begin Class AEnemyAIController Function UpdatePatrolState ****************************
struct Z_Construct_UFunction_AEnemyAIController_UpdatePatrolState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Enemy/EnemyAIController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function UpdatePatrolState constinit property declarations *********************
// ********** End Function UpdatePatrolState constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyAIController_UpdatePatrolState_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AEnemyAIController, nullptr, "UpdatePatrolState", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyAIController_UpdatePatrolState_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyAIController_UpdatePatrolState_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AEnemyAIController_UpdatePatrolState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyAIController_UpdatePatrolState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AEnemyAIController::execUpdatePatrolState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UpdatePatrolState();
	P_NATIVE_END;
}
// ********** End Class AEnemyAIController Function UpdatePatrolState ******************************

// ********** Begin Class AEnemyAIController *******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AEnemyAIController;
UClass* AEnemyAIController::GetPrivateStaticClass()
{
	using TClass = AEnemyAIController;
	if (!Z_Registration_Info_UClass_AEnemyAIController.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("EnemyAIController"),
			Z_Registration_Info_UClass_AEnemyAIController.InnerSingleton,
			StaticRegisterNativesAEnemyAIController,
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
	return Z_Registration_Info_UClass_AEnemyAIController.InnerSingleton;
}
UClass* Z_Construct_UClass_AEnemyAIController_NoRegister()
{
	return AEnemyAIController::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AEnemyAIController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "Enemy/EnemyAIController.h" },
		{ "ModuleRelativePath", "Enemy/EnemyAIController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetPlayer_MetaData[] = {
		{ "ModuleRelativePath", "Enemy/EnemyAIController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Enemy_MetaData[] = {
		{ "ModuleRelativePath", "Enemy/EnemyAIController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackRange_MetaData[] = {
		{ "Category", "AI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ============================================================\n// AI Settings\n// ============================================================\n" },
#endif
		{ "ModuleRelativePath", "Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AI Settings" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StrafeMoveSpeed_MetaData[] = {
		{ "Category", "AI" },
		{ "ModuleRelativePath", "Enemy/EnemyAIController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StrafeRange_MetaData[] = {
		{ "Category", "AI" },
		{ "ModuleRelativePath", "Enemy/EnemyAIController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StrafeDirectionCheckInterval_MetaData[] = {
		{ "Category", "AI" },
		{ "ModuleRelativePath", "Enemy/EnemyAIController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SightConfig_MetaData[] = {
		{ "Category", "EnemyAIController" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ============================================================\n// Perception\n// ============================================================\n" },
#endif
		{ "ModuleRelativePath", "Enemy/EnemyAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Perception" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HearingConfig_MetaData[] = {
		{ "Category", "EnemyAIController" },
		{ "ModuleRelativePath", "Enemy/EnemyAIController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class AEnemyAIController constinit property declarations ***********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TargetPlayer;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Enemy;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AttackRange;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StrafeMoveSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StrafeRange;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StrafeDirectionCheckInterval;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SightConfig;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HearingConfig;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AEnemyAIController constinit property declarations *************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("Attack"), .Pointer = &AEnemyAIController::execAttack },
		{ .NameUTF8 = UTF8TEXT("Block"), .Pointer = &AEnemyAIController::execBlock },
		{ .NameUTF8 = UTF8TEXT("OnAlertTimerExpired"), .Pointer = &AEnemyAIController::execOnAlertTimerExpired },
		{ .NameUTF8 = UTF8TEXT("OnPerceptionUpdated"), .Pointer = &AEnemyAIController::execOnPerceptionUpdated },
		{ .NameUTF8 = UTF8TEXT("Strafe"), .Pointer = &AEnemyAIController::execStrafe },
		{ .NameUTF8 = UTF8TEXT("UpdateAlertState"), .Pointer = &AEnemyAIController::execUpdateAlertState },
		{ .NameUTF8 = UTF8TEXT("UpdateAttackState"), .Pointer = &AEnemyAIController::execUpdateAttackState },
		{ .NameUTF8 = UTF8TEXT("UpdateChaseState"), .Pointer = &AEnemyAIController::execUpdateChaseState },
		{ .NameUTF8 = UTF8TEXT("UpdateCurrentState"), .Pointer = &AEnemyAIController::execUpdateCurrentState },
		{ .NameUTF8 = UTF8TEXT("UpdatePatrolState"), .Pointer = &AEnemyAIController::execUpdatePatrolState },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AEnemyAIController_Attack, "Attack" }, // 1270148366
		{ &Z_Construct_UFunction_AEnemyAIController_Block, "Block" }, // 224030542
		{ &Z_Construct_UFunction_AEnemyAIController_OnAlertTimerExpired, "OnAlertTimerExpired" }, // 2371598013
		{ &Z_Construct_UFunction_AEnemyAIController_OnPerceptionUpdated, "OnPerceptionUpdated" }, // 3291875434
		{ &Z_Construct_UFunction_AEnemyAIController_Strafe, "Strafe" }, // 2969210915
		{ &Z_Construct_UFunction_AEnemyAIController_UpdateAlertState, "UpdateAlertState" }, // 87436208
		{ &Z_Construct_UFunction_AEnemyAIController_UpdateAttackState, "UpdateAttackState" }, // 3469734149
		{ &Z_Construct_UFunction_AEnemyAIController_UpdateChaseState, "UpdateChaseState" }, // 1107608376
		{ &Z_Construct_UFunction_AEnemyAIController_UpdateCurrentState, "UpdateCurrentState" }, // 873391574
		{ &Z_Construct_UFunction_AEnemyAIController_UpdatePatrolState, "UpdatePatrolState" }, // 350880478
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEnemyAIController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AEnemyAIController_Statics

// ********** Begin Class AEnemyAIController Property Definitions **********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEnemyAIController_Statics::NewProp_TargetPlayer = { "TargetPlayer", nullptr, (EPropertyFlags)0x0144000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAIController, TargetPlayer), Z_Construct_UClass_APawn_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetPlayer_MetaData), NewProp_TargetPlayer_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEnemyAIController_Statics::NewProp_Enemy = { "Enemy", nullptr, (EPropertyFlags)0x0144000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAIController, Enemy), Z_Construct_UClass_AEnemyCharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Enemy_MetaData), NewProp_Enemy_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyAIController_Statics::NewProp_AttackRange = { "AttackRange", nullptr, (EPropertyFlags)0x0020080000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAIController, AttackRange), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackRange_MetaData), NewProp_AttackRange_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyAIController_Statics::NewProp_StrafeMoveSpeed = { "StrafeMoveSpeed", nullptr, (EPropertyFlags)0x0020080000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAIController, StrafeMoveSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StrafeMoveSpeed_MetaData), NewProp_StrafeMoveSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyAIController_Statics::NewProp_StrafeRange = { "StrafeRange", nullptr, (EPropertyFlags)0x0020080000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAIController, StrafeRange), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StrafeRange_MetaData), NewProp_StrafeRange_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AEnemyAIController_Statics::NewProp_StrafeDirectionCheckInterval = { "StrafeDirectionCheckInterval", nullptr, (EPropertyFlags)0x0020080000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAIController, StrafeDirectionCheckInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StrafeDirectionCheckInterval_MetaData), NewProp_StrafeDirectionCheckInterval_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEnemyAIController_Statics::NewProp_SightConfig = { "SightConfig", nullptr, (EPropertyFlags)0x0124080000020001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAIController, SightConfig), Z_Construct_UClass_UAISenseConfig_Sight_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SightConfig_MetaData), NewProp_SightConfig_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEnemyAIController_Statics::NewProp_HearingConfig = { "HearingConfig", nullptr, (EPropertyFlags)0x0124080000020001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyAIController, HearingConfig), Z_Construct_UClass_UAISenseConfig_Hearing_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HearingConfig_MetaData), NewProp_HearingConfig_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AEnemyAIController_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAIController_Statics::NewProp_TargetPlayer,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAIController_Statics::NewProp_Enemy,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAIController_Statics::NewProp_AttackRange,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAIController_Statics::NewProp_StrafeMoveSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAIController_Statics::NewProp_StrafeRange,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAIController_Statics::NewProp_StrafeDirectionCheckInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAIController_Statics::NewProp_SightConfig,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyAIController_Statics::NewProp_HearingConfig,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyAIController_Statics::PropPointers) < 2048);
// ********** End Class AEnemyAIController Property Definitions ************************************
UObject* (*const Z_Construct_UClass_AEnemyAIController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AAIController,
	(UObject* (*)())Z_Construct_UPackage__Script_TheHunt,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyAIController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AEnemyAIController_Statics::ClassParams = {
	&AEnemyAIController::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AEnemyAIController_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyAIController_Statics::PropPointers),
	0,
	0x009002A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyAIController_Statics::Class_MetaDataParams), Z_Construct_UClass_AEnemyAIController_Statics::Class_MetaDataParams)
};
void AEnemyAIController::StaticRegisterNativesAEnemyAIController()
{
	UClass* Class = AEnemyAIController::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_AEnemyAIController_Statics::Funcs));
}
UClass* Z_Construct_UClass_AEnemyAIController()
{
	if (!Z_Registration_Info_UClass_AEnemyAIController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AEnemyAIController.OuterSingleton, Z_Construct_UClass_AEnemyAIController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AEnemyAIController.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AEnemyAIController);
AEnemyAIController::~AEnemyAIController() {}
// ********** End Class AEnemyAIController *********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Enemy_EnemyAIController_h__Script_TheHunt_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AEnemyAIController, AEnemyAIController::StaticClass, TEXT("AEnemyAIController"), &Z_Registration_Info_UClass_AEnemyAIController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AEnemyAIController), 16361114U) },
	};
}; // Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Enemy_EnemyAIController_h__Script_TheHunt_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Enemy_EnemyAIController_h__Script_TheHunt_2696025379{
	TEXT("/Script/TheHunt"),
	Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Enemy_EnemyAIController_h__Script_TheHunt_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Enemy_EnemyAIController_h__Script_TheHunt_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
