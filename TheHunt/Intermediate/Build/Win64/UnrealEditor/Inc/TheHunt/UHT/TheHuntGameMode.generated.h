// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "TheHuntGameMode.h"

#ifdef THEHUNT_TheHuntGameMode_generated_h
#error "TheHuntGameMode.generated.h already included, missing '#pragma once' in TheHuntGameMode.h"
#endif
#define THEHUNT_TheHuntGameMode_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ATheHuntGameMode *********************************************************
struct Z_Construct_UClass_ATheHuntGameMode_Statics;
THEHUNT_API UClass* Z_Construct_UClass_ATheHuntGameMode_NoRegister();

#define FID_TheHunt_Source_TheHunt_TheHuntGameMode_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATheHuntGameMode(); \
	friend struct ::Z_Construct_UClass_ATheHuntGameMode_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend THEHUNT_API UClass* ::Z_Construct_UClass_ATheHuntGameMode_NoRegister(); \
public: \
	DECLARE_CLASS2(ATheHuntGameMode, AGameModeBase, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/TheHunt"), Z_Construct_UClass_ATheHuntGameMode_NoRegister) \
	DECLARE_SERIALIZER(ATheHuntGameMode)


#define FID_TheHunt_Source_TheHunt_TheHuntGameMode_h_15_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ATheHuntGameMode(ATheHuntGameMode&&) = delete; \
	ATheHuntGameMode(const ATheHuntGameMode&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATheHuntGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATheHuntGameMode); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ATheHuntGameMode) \
	NO_API virtual ~ATheHuntGameMode();


#define FID_TheHunt_Source_TheHunt_TheHuntGameMode_h_12_PROLOG
#define FID_TheHunt_Source_TheHunt_TheHuntGameMode_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TheHunt_Source_TheHunt_TheHuntGameMode_h_15_INCLASS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_TheHuntGameMode_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ATheHuntGameMode;

// ********** End Class ATheHuntGameMode ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TheHunt_Source_TheHunt_TheHuntGameMode_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
