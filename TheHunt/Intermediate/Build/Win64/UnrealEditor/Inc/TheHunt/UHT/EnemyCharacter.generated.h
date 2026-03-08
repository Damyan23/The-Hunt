// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Enemy/EnemyCharacter.h"

#ifdef THEHUNT_EnemyCharacter_generated_h
#error "EnemyCharacter.generated.h already included, missing '#pragma once' in EnemyCharacter.h"
#endif
#define THEHUNT_EnemyCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AEnemyCharacter **********************************************************
struct Z_Construct_UClass_AEnemyCharacter_Statics;
THEHUNT_API UClass* Z_Construct_UClass_AEnemyCharacter_NoRegister();

#define FID_TheHunt_Source_TheHunt_Enemy_EnemyCharacter_h_36_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAEnemyCharacter(); \
	friend struct ::Z_Construct_UClass_AEnemyCharacter_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend THEHUNT_API UClass* ::Z_Construct_UClass_AEnemyCharacter_NoRegister(); \
public: \
	DECLARE_CLASS2(AEnemyCharacter, ABaseCharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TheHunt"), Z_Construct_UClass_AEnemyCharacter_NoRegister) \
	DECLARE_SERIALIZER(AEnemyCharacter)


#define FID_TheHunt_Source_TheHunt_Enemy_EnemyCharacter_h_36_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AEnemyCharacter(AEnemyCharacter&&) = delete; \
	AEnemyCharacter(const AEnemyCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEnemyCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEnemyCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AEnemyCharacter) \
	NO_API virtual ~AEnemyCharacter();


#define FID_TheHunt_Source_TheHunt_Enemy_EnemyCharacter_h_33_PROLOG
#define FID_TheHunt_Source_TheHunt_Enemy_EnemyCharacter_h_36_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TheHunt_Source_TheHunt_Enemy_EnemyCharacter_h_36_INCLASS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_Enemy_EnemyCharacter_h_36_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AEnemyCharacter;

// ********** End Class AEnemyCharacter ************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TheHunt_Source_TheHunt_Enemy_EnemyCharacter_h

// ********** Begin Enum EEnemyState ***************************************************************
#define FOREACH_ENUM_EENEMYSTATE(op) \
	op(EEnemyState::Idle) \
	op(EEnemyState::Patrol) \
	op(EEnemyState::Chase) \
	op(EEnemyState::Alert) \
	op(EEnemyState::Attack) \
	op(EEnemyState::Stagger) \
	op(EEnemyState::Dead) 

enum class EEnemyState : uint8;
template<> struct TIsUEnumClass<EEnemyState> { enum { Value = true }; };
template<> THEHUNT_NON_ATTRIBUTED_API UEnum* StaticEnum<EEnemyState>();
// ********** End Enum EEnemyState *****************************************************************

// ********** Begin Enum EEnemyCombatState *********************************************************
#define FOREACH_ENUM_EENEMYCOMBATSTATE(op) \
	op(EEnemyCombatState::None) \
	op(EEnemyCombatState::Strafe) \
	op(EEnemyCombatState::Attacking) \
	op(EEnemyCombatState::Blocking) 

enum class EEnemyCombatState : uint8;
template<> struct TIsUEnumClass<EEnemyCombatState> { enum { Value = true }; };
template<> THEHUNT_NON_ATTRIBUTED_API UEnum* StaticEnum<EEnemyCombatState>();
// ********** End Enum EEnemyCombatState ***********************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
