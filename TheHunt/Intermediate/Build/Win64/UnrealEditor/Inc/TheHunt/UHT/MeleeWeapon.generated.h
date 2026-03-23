// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Items/Weapon/MeleeWeapon.h"

#ifdef THEHUNT_MeleeWeapon_generated_h
#error "MeleeWeapon.generated.h already included, missing '#pragma once' in MeleeWeapon.h"
#endif
#define THEHUNT_MeleeWeapon_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class UPrimitiveComponent;
struct FHitResult;

// ********** Begin Class AMeleeWeapon *************************************************************
#define FID_TheHunt_Source_TheHunt_Items_Weapon_MeleeWeapon_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnSwordHit);


struct Z_Construct_UClass_AMeleeWeapon_Statics;
THEHUNT_API UClass* Z_Construct_UClass_AMeleeWeapon_NoRegister();

#define FID_TheHunt_Source_TheHunt_Items_Weapon_MeleeWeapon_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMeleeWeapon(); \
	friend struct ::Z_Construct_UClass_AMeleeWeapon_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend THEHUNT_API UClass* ::Z_Construct_UClass_AMeleeWeapon_NoRegister(); \
public: \
	DECLARE_CLASS2(AMeleeWeapon, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TheHunt"), Z_Construct_UClass_AMeleeWeapon_NoRegister) \
	DECLARE_SERIALIZER(AMeleeWeapon)


#define FID_TheHunt_Source_TheHunt_Items_Weapon_MeleeWeapon_h_14_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AMeleeWeapon(AMeleeWeapon&&) = delete; \
	AMeleeWeapon(const AMeleeWeapon&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMeleeWeapon); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMeleeWeapon); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AMeleeWeapon) \
	NO_API virtual ~AMeleeWeapon();


#define FID_TheHunt_Source_TheHunt_Items_Weapon_MeleeWeapon_h_11_PROLOG
#define FID_TheHunt_Source_TheHunt_Items_Weapon_MeleeWeapon_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TheHunt_Source_TheHunt_Items_Weapon_MeleeWeapon_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_Items_Weapon_MeleeWeapon_h_14_INCLASS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_Items_Weapon_MeleeWeapon_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AMeleeWeapon;

// ********** End Class AMeleeWeapon ***************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TheHunt_Source_TheHunt_Items_Weapon_MeleeWeapon_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
