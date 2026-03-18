// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "SwordActor.h"

#ifdef THEHUNT_SwordActor_generated_h
#error "SwordActor.generated.h already included, missing '#pragma once' in SwordActor.h"
#endif
#define THEHUNT_SwordActor_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class UPrimitiveComponent;
struct FHitResult;

// ********** Begin Class ASwordActor **************************************************************
#define FID_TheHunt_Source_TheHunt_SwordActor_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnSwordHit);


struct Z_Construct_UClass_ASwordActor_Statics;
THEHUNT_API UClass* Z_Construct_UClass_ASwordActor_NoRegister();

#define FID_TheHunt_Source_TheHunt_SwordActor_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASwordActor(); \
	friend struct ::Z_Construct_UClass_ASwordActor_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend THEHUNT_API UClass* ::Z_Construct_UClass_ASwordActor_NoRegister(); \
public: \
	DECLARE_CLASS2(ASwordActor, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TheHunt"), Z_Construct_UClass_ASwordActor_NoRegister) \
	DECLARE_SERIALIZER(ASwordActor)


#define FID_TheHunt_Source_TheHunt_SwordActor_h_14_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ASwordActor(ASwordActor&&) = delete; \
	ASwordActor(const ASwordActor&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASwordActor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASwordActor); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ASwordActor) \
	NO_API virtual ~ASwordActor();


#define FID_TheHunt_Source_TheHunt_SwordActor_h_11_PROLOG
#define FID_TheHunt_Source_TheHunt_SwordActor_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TheHunt_Source_TheHunt_SwordActor_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_SwordActor_h_14_INCLASS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_SwordActor_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ASwordActor;

// ********** End Class ASwordActor ****************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TheHunt_Source_TheHunt_SwordActor_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
