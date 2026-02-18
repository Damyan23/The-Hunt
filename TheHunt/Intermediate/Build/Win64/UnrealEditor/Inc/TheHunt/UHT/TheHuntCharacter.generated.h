// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "TheHuntCharacter.h"

#ifdef THEHUNT_TheHuntCharacter_generated_h
#error "TheHuntCharacter.generated.h already included, missing '#pragma once' in TheHuntCharacter.h"
#endif
#define THEHUNT_TheHuntCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ATheHuntCharacter ********************************************************
#define FID_TheHunt_Source_TheHunt_TheHuntCharacter_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDoJumpEnd); \
	DECLARE_FUNCTION(execDoJumpStart); \
	DECLARE_FUNCTION(execDoMove); \
	DECLARE_FUNCTION(execDoAim);


struct Z_Construct_UClass_ATheHuntCharacter_Statics;
THEHUNT_API UClass* Z_Construct_UClass_ATheHuntCharacter_NoRegister();

#define FID_TheHunt_Source_TheHunt_TheHuntCharacter_h_24_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATheHuntCharacter(); \
	friend struct ::Z_Construct_UClass_ATheHuntCharacter_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend THEHUNT_API UClass* ::Z_Construct_UClass_ATheHuntCharacter_NoRegister(); \
public: \
	DECLARE_CLASS2(ATheHuntCharacter, ACharacter, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/TheHunt"), Z_Construct_UClass_ATheHuntCharacter_NoRegister) \
	DECLARE_SERIALIZER(ATheHuntCharacter)


#define FID_TheHunt_Source_TheHunt_TheHuntCharacter_h_24_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ATheHuntCharacter(ATheHuntCharacter&&) = delete; \
	ATheHuntCharacter(const ATheHuntCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATheHuntCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATheHuntCharacter); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ATheHuntCharacter) \
	NO_API virtual ~ATheHuntCharacter();


#define FID_TheHunt_Source_TheHunt_TheHuntCharacter_h_21_PROLOG
#define FID_TheHunt_Source_TheHunt_TheHuntCharacter_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TheHunt_Source_TheHunt_TheHuntCharacter_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_TheHuntCharacter_h_24_INCLASS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_TheHuntCharacter_h_24_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ATheHuntCharacter;

// ********** End Class ATheHuntCharacter **********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TheHunt_Source_TheHunt_TheHuntCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
