// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "TheHuntPlayerController.h"

#ifdef THEHUNT_TheHuntPlayerController_generated_h
#error "TheHuntPlayerController.generated.h already included, missing '#pragma once' in TheHuntPlayerController.h"
#endif
#define THEHUNT_TheHuntPlayerController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ATheHuntPlayerController *************************************************
struct Z_Construct_UClass_ATheHuntPlayerController_Statics;
THEHUNT_API UClass* Z_Construct_UClass_ATheHuntPlayerController_NoRegister();

#define FID_TheHunt_Source_TheHunt_TheHuntPlayerController_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATheHuntPlayerController(); \
	friend struct ::Z_Construct_UClass_ATheHuntPlayerController_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend THEHUNT_API UClass* ::Z_Construct_UClass_ATheHuntPlayerController_NoRegister(); \
public: \
	DECLARE_CLASS2(ATheHuntPlayerController, APlayerController, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/TheHunt"), Z_Construct_UClass_ATheHuntPlayerController_NoRegister) \
	DECLARE_SERIALIZER(ATheHuntPlayerController)


#define FID_TheHunt_Source_TheHunt_TheHuntPlayerController_h_20_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ATheHuntPlayerController(ATheHuntPlayerController&&) = delete; \
	ATheHuntPlayerController(const ATheHuntPlayerController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATheHuntPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATheHuntPlayerController); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ATheHuntPlayerController) \
	NO_API virtual ~ATheHuntPlayerController();


#define FID_TheHunt_Source_TheHunt_TheHuntPlayerController_h_17_PROLOG
#define FID_TheHunt_Source_TheHunt_TheHuntPlayerController_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TheHunt_Source_TheHunt_TheHuntPlayerController_h_20_INCLASS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_TheHuntPlayerController_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ATheHuntPlayerController;

// ********** End Class ATheHuntPlayerController ***************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TheHunt_Source_TheHunt_TheHuntPlayerController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
