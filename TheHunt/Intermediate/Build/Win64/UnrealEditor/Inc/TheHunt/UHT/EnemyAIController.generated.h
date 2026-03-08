// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Enemy/EnemyAIController.h"

#ifdef THEHUNT_EnemyAIController_generated_h
#error "EnemyAIController.generated.h already included, missing '#pragma once' in EnemyAIController.h"
#endif
#define THEHUNT_EnemyAIController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
struct FAIStimulus;

// ********** Begin Class AEnemyAIController *******************************************************
#define FID_TheHunt_Source_TheHunt_Enemy_EnemyAIController_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnAlertTimerExpired); \
	DECLARE_FUNCTION(execOnPerceptionUpdated); \
	DECLARE_FUNCTION(execBlock); \
	DECLARE_FUNCTION(execAttack); \
	DECLARE_FUNCTION(execStrafe); \
	DECLARE_FUNCTION(execUpdateAttackState); \
	DECLARE_FUNCTION(execUpdatePatrolState); \
	DECLARE_FUNCTION(execUpdateAlertState); \
	DECLARE_FUNCTION(execUpdateChaseState); \
	DECLARE_FUNCTION(execUpdateCurrentState);


struct Z_Construct_UClass_AEnemyAIController_Statics;
THEHUNT_API UClass* Z_Construct_UClass_AEnemyAIController_NoRegister();

#define FID_TheHunt_Source_TheHunt_Enemy_EnemyAIController_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAEnemyAIController(); \
	friend struct ::Z_Construct_UClass_AEnemyAIController_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend THEHUNT_API UClass* ::Z_Construct_UClass_AEnemyAIController_NoRegister(); \
public: \
	DECLARE_CLASS2(AEnemyAIController, AAIController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TheHunt"), Z_Construct_UClass_AEnemyAIController_NoRegister) \
	DECLARE_SERIALIZER(AEnemyAIController)


#define FID_TheHunt_Source_TheHunt_Enemy_EnemyAIController_h_18_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AEnemyAIController(AEnemyAIController&&) = delete; \
	AEnemyAIController(const AEnemyAIController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEnemyAIController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEnemyAIController); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AEnemyAIController) \
	NO_API virtual ~AEnemyAIController();


#define FID_TheHunt_Source_TheHunt_Enemy_EnemyAIController_h_15_PROLOG
#define FID_TheHunt_Source_TheHunt_Enemy_EnemyAIController_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TheHunt_Source_TheHunt_Enemy_EnemyAIController_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_Enemy_EnemyAIController_h_18_INCLASS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_Enemy_EnemyAIController_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AEnemyAIController;

// ********** End Class AEnemyAIController *********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TheHunt_Source_TheHunt_Enemy_EnemyAIController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
