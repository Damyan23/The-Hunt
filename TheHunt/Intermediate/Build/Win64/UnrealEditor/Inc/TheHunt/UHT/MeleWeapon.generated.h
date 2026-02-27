// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Items/Weapon/MeleWeapon.h"

#ifdef THEHUNT_MeleWeapon_generated_h
#error "MeleWeapon.generated.h already included, missing '#pragma once' in MeleWeapon.h"
#endif
#define THEHUNT_MeleWeapon_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AMeleWeapon **************************************************************
struct Z_Construct_UClass_AMeleWeapon_Statics;
THEHUNT_API UClass* Z_Construct_UClass_AMeleWeapon_NoRegister();

#define FID_TheHunt_Source_TheHunt_Items_Weapon_MeleWeapon_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMeleWeapon(); \
	friend struct ::Z_Construct_UClass_AMeleWeapon_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend THEHUNT_API UClass* ::Z_Construct_UClass_AMeleWeapon_NoRegister(); \
public: \
	DECLARE_CLASS2(AMeleWeapon, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/TheHunt"), Z_Construct_UClass_AMeleWeapon_NoRegister) \
	DECLARE_SERIALIZER(AMeleWeapon)


#define FID_TheHunt_Source_TheHunt_Items_Weapon_MeleWeapon_h_13_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AMeleWeapon(AMeleWeapon&&) = delete; \
	AMeleWeapon(const AMeleWeapon&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMeleWeapon); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMeleWeapon); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AMeleWeapon) \
	NO_API virtual ~AMeleWeapon();


#define FID_TheHunt_Source_TheHunt_Items_Weapon_MeleWeapon_h_10_PROLOG
#define FID_TheHunt_Source_TheHunt_Items_Weapon_MeleWeapon_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TheHunt_Source_TheHunt_Items_Weapon_MeleWeapon_h_13_INCLASS_NO_PURE_DECLS \
	FID_TheHunt_Source_TheHunt_Items_Weapon_MeleWeapon_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AMeleWeapon;

// ********** End Class AMeleWeapon ****************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TheHunt_Source_TheHunt_Items_Weapon_MeleWeapon_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
