// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Animations/Notifies/EnableHitbox.h"

#ifdef THEHUNT_EnableHitbox_generated_h
#error "EnableHitbox.generated.h already included, missing '#pragma once' in EnableHitbox.h"
#endif
#define THEHUNT_EnableHitbox_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UEnableHitbox ************************************************************
struct Z_Construct_UClass_UEnableHitbox_Statics;
THEHUNT_API UClass* Z_Construct_UClass_UEnableHitbox_NoRegister();

#define FID_TheHunt_Source_TheHunt_Animations_Notifies_EnableHitbox_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUEnableHitbox(); \
	friend struct ::Z_Construct_UClass_UEnableHitbox_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend THEHUNT_API UClass* ::Z_Construct_UClass_UEnableHitbox_NoRegister(); \
public: \
	DECLARE_CLASS2(UEnableHitbox, UAnimNotify, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/TheHunt"), Z_Construct_UClass_UEnableHitbox_NoRegister) \
	DECLARE_SERIALIZER(UEnableHitbox)


#define FID_TheHunt_Source_TheHunt_Animations_Notifies_EnableHitbox_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UEnableHitbox(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UEnableHitbox(UEnableHitbox&&) = delete; \
	UEnableHitbox(const UEnableHitbox&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UEnableHitbox); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UEnableHitbox); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UEnableHitbox) \
	NO_API virtual ~UEnableHitbox();


#define FID_TheHunt_Source_TheHunt_Animations_Notifies_EnableHitbox_h_12_PROLOG
#define FID_TheHunt_Source_TheHunt_Animations_Notifies_EnableHitbox_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TheHunt_Source_TheHunt_Animations_Notifies_EnableHitbox_h_15_INCLASS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_Animations_Notifies_EnableHitbox_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UEnableHitbox;

// ********** End Class UEnableHitbox **************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TheHunt_Source_TheHunt_Animations_Notifies_EnableHitbox_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
