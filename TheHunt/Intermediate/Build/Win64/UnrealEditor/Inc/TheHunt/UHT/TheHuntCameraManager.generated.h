// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "TheHuntCameraManager.h"

#ifdef THEHUNT_TheHuntCameraManager_generated_h
#error "TheHuntCameraManager.generated.h already included, missing '#pragma once' in TheHuntCameraManager.h"
#endif
#define THEHUNT_TheHuntCameraManager_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ATheHuntCameraManager ****************************************************
struct Z_Construct_UClass_ATheHuntCameraManager_Statics;
THEHUNT_API UClass* Z_Construct_UClass_ATheHuntCameraManager_NoRegister();

#define FID_TheHunt_Source_TheHunt_TheHuntCameraManager_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATheHuntCameraManager(); \
	friend struct ::Z_Construct_UClass_ATheHuntCameraManager_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend THEHUNT_API UClass* ::Z_Construct_UClass_ATheHuntCameraManager_NoRegister(); \
public: \
	DECLARE_CLASS2(ATheHuntCameraManager, APlayerCameraManager, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/TheHunt"), Z_Construct_UClass_ATheHuntCameraManager_NoRegister) \
	DECLARE_SERIALIZER(ATheHuntCameraManager)


#define FID_TheHunt_Source_TheHunt_TheHuntCameraManager_h_16_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ATheHuntCameraManager(ATheHuntCameraManager&&) = delete; \
	ATheHuntCameraManager(const ATheHuntCameraManager&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATheHuntCameraManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATheHuntCameraManager); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ATheHuntCameraManager) \
	NO_API virtual ~ATheHuntCameraManager();


#define FID_TheHunt_Source_TheHunt_TheHuntCameraManager_h_13_PROLOG
#define FID_TheHunt_Source_TheHunt_TheHuntCameraManager_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TheHunt_Source_TheHunt_TheHuntCameraManager_h_16_INCLASS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_TheHuntCameraManager_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ATheHuntCameraManager;

// ********** End Class ATheHuntCameraManager ******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TheHunt_Source_TheHunt_TheHuntCameraManager_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
