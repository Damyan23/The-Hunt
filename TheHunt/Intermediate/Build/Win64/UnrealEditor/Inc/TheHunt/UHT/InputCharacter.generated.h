// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "InputPlayer/InputCharacter.h"

#ifdef THEHUNT_InputCharacter_generated_h
#error "InputCharacter.generated.h already included, missing '#pragma once' in InputCharacter.h"
#endif
#define THEHUNT_InputCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AInputCharacter **********************************************************
struct Z_Construct_UClass_AInputCharacter_Statics;
THEHUNT_API UClass* Z_Construct_UClass_AInputCharacter_NoRegister();

#define FID_TheHunt_Source_TheHunt_InputPlayer_InputCharacter_h_11_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAInputCharacter(); \
	friend struct ::Z_Construct_UClass_AInputCharacter_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend THEHUNT_API UClass* ::Z_Construct_UClass_AInputCharacter_NoRegister(); \
public: \
	DECLARE_CLASS2(AInputCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TheHunt"), Z_Construct_UClass_AInputCharacter_NoRegister) \
	DECLARE_SERIALIZER(AInputCharacter)


#define FID_TheHunt_Source_TheHunt_InputPlayer_InputCharacter_h_11_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AInputCharacter(AInputCharacter&&) = delete; \
	AInputCharacter(const AInputCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AInputCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AInputCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AInputCharacter) \
	NO_API virtual ~AInputCharacter();


#define FID_TheHunt_Source_TheHunt_InputPlayer_InputCharacter_h_8_PROLOG
#define FID_TheHunt_Source_TheHunt_InputPlayer_InputCharacter_h_11_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TheHunt_Source_TheHunt_InputPlayer_InputCharacter_h_11_INCLASS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_InputPlayer_InputCharacter_h_11_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AInputCharacter;

// ********** End Class AInputCharacter ************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TheHunt_Source_TheHunt_InputPlayer_InputCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
