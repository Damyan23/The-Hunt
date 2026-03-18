// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Animations/Notifies/DissableHitbox.h"

#ifdef THEHUNT_DissableHitbox_generated_h
#error "DissableHitbox.generated.h already included, missing '#pragma once' in DissableHitbox.h"
#endif
#define THEHUNT_DissableHitbox_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UDissableHitbox **********************************************************
struct Z_Construct_UClass_UDissableHitbox_Statics;
THEHUNT_API UClass* Z_Construct_UClass_UDissableHitbox_NoRegister();

#define FID_TheHunt_Source_TheHunt_Animations_Notifies_DissableHitbox_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUDissableHitbox(); \
	friend struct ::Z_Construct_UClass_UDissableHitbox_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend THEHUNT_API UClass* ::Z_Construct_UClass_UDissableHitbox_NoRegister(); \
public: \
	DECLARE_CLASS2(UDissableHitbox, UAnimNotify, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/TheHunt"), Z_Construct_UClass_UDissableHitbox_NoRegister) \
	DECLARE_SERIALIZER(UDissableHitbox)


#define FID_TheHunt_Source_TheHunt_Animations_Notifies_DissableHitbox_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UDissableHitbox(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UDissableHitbox(UDissableHitbox&&) = delete; \
	UDissableHitbox(const UDissableHitbox&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UDissableHitbox); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDissableHitbox); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UDissableHitbox) \
	NO_API virtual ~UDissableHitbox();


#define FID_TheHunt_Source_TheHunt_Animations_Notifies_DissableHitbox_h_12_PROLOG
#define FID_TheHunt_Source_TheHunt_Animations_Notifies_DissableHitbox_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TheHunt_Source_TheHunt_Animations_Notifies_DissableHitbox_h_15_INCLASS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_Animations_Notifies_DissableHitbox_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UDissableHitbox;

// ********** End Class UDissableHitbox ************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TheHunt_Source_TheHunt_Animations_Notifies_DissableHitbox_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
