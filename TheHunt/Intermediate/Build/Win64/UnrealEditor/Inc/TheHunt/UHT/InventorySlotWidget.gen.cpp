// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Inventory/UI/InventorySlotWidget.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeInventorySlotWidget() {}

// ********** Begin Cross Module References ********************************************************
THEHUNT_API UClass* Z_Construct_UClass_UInventorySlotWidget();
THEHUNT_API UClass* Z_Construct_UClass_UInventorySlotWidget_NoRegister();
THEHUNT_API UFunction* Z_Construct_UDelegateFunction_UInventorySlotWidget_OnSlotClicked__DelegateSignature();
UMG_API UClass* Z_Construct_UClass_UButton_NoRegister();
UMG_API UClass* Z_Construct_UClass_UImage_NoRegister();
UMG_API UClass* Z_Construct_UClass_USizeBox_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget();
UPackage* Z_Construct_UPackage__Script_TheHunt();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnSlotClicked ********************************************************
struct Z_Construct_UDelegateFunction_UInventorySlotWidget_OnSlotClicked__DelegateSignature_Statics
{
	struct InventorySlotWidget_eventOnSlotClicked_Parms
	{
		int32 Index;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Inventory/UI/InventorySlotWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnSlotClicked constinit property declarations ************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_Index;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnSlotClicked constinit property declarations **************************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnSlotClicked Property Definitions ***********************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_UInventorySlotWidget_OnSlotClicked__DelegateSignature_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(InventorySlotWidget_eventOnSlotClicked_Parms, Index), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_UInventorySlotWidget_OnSlotClicked__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_UInventorySlotWidget_OnSlotClicked__DelegateSignature_Statics::NewProp_Index,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_UInventorySlotWidget_OnSlotClicked__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FOnSlotClicked Property Definitions *************************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_UInventorySlotWidget_OnSlotClicked__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UInventorySlotWidget, nullptr, "OnSlotClicked__DelegateSignature", 	Z_Construct_UDelegateFunction_UInventorySlotWidget_OnSlotClicked__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_UInventorySlotWidget_OnSlotClicked__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_UInventorySlotWidget_OnSlotClicked__DelegateSignature_Statics::InventorySlotWidget_eventOnSlotClicked_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_UInventorySlotWidget_OnSlotClicked__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_UInventorySlotWidget_OnSlotClicked__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_UInventorySlotWidget_OnSlotClicked__DelegateSignature_Statics::InventorySlotWidget_eventOnSlotClicked_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_UInventorySlotWidget_OnSlotClicked__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_UInventorySlotWidget_OnSlotClicked__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void UInventorySlotWidget::FOnSlotClicked_DelegateWrapper(const FMulticastScriptDelegate& OnSlotClicked, int32 Index)
{
	struct InventorySlotWidget_eventOnSlotClicked_Parms
	{
		int32 Index;
	};
	InventorySlotWidget_eventOnSlotClicked_Parms Parms;
	Parms.Index=Index;
	OnSlotClicked.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnSlotClicked **********************************************************

// ********** Begin Class UInventorySlotWidget Function OnButtonClicked ****************************
struct Z_Construct_UFunction_UInventorySlotWidget_OnButtonClicked_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Inventory/UI/InventorySlotWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnButtonClicked constinit property declarations ***********************
// ********** End Function OnButtonClicked constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UInventorySlotWidget_OnButtonClicked_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UInventorySlotWidget, nullptr, "OnButtonClicked", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UInventorySlotWidget_OnButtonClicked_Statics::Function_MetaDataParams), Z_Construct_UFunction_UInventorySlotWidget_OnButtonClicked_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UInventorySlotWidget_OnButtonClicked()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UInventorySlotWidget_OnButtonClicked_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UInventorySlotWidget::execOnButtonClicked)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnButtonClicked();
	P_NATIVE_END;
}
// ********** End Class UInventorySlotWidget Function OnButtonClicked ******************************

// ********** Begin Class UInventorySlotWidget *****************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UInventorySlotWidget;
UClass* UInventorySlotWidget::GetPrivateStaticClass()
{
	using TClass = UInventorySlotWidget;
	if (!Z_Registration_Info_UClass_UInventorySlotWidget.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("InventorySlotWidget"),
			Z_Registration_Info_UClass_UInventorySlotWidget.InnerSingleton,
			StaticRegisterNativesUInventorySlotWidget,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UInventorySlotWidget.InnerSingleton;
}
UClass* Z_Construct_UClass_UInventorySlotWidget_NoRegister()
{
	return UInventorySlotWidget::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UInventorySlotWidget_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Inventory/UI/InventorySlotWidget.h" },
		{ "ModuleRelativePath", "Inventory/UI/InventorySlotWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SlotIcon_MetaData[] = {
		{ "Category", "Inventory" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Inventory/UI/InventorySlotWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Button_MetaData[] = {
		{ "Category", "Inventory" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Inventory/UI/InventorySlotWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SizeBox_MetaData[] = {
		{ "BindWidget", "" },
		{ "Category", "InventorySlotWidget" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Inventory/UI/InventorySlotWidget.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnSlotClicked_MetaData[] = {
		{ "ModuleRelativePath", "Inventory/UI/InventorySlotWidget.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UInventorySlotWidget constinit property declarations *********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SlotIcon;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Button;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SizeBox;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnSlotClicked;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UInventorySlotWidget constinit property declarations ***********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("OnButtonClicked"), .Pointer = &UInventorySlotWidget::execOnButtonClicked },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UInventorySlotWidget_OnButtonClicked, "OnButtonClicked" }, // 2513497002
		{ &Z_Construct_UDelegateFunction_UInventorySlotWidget_OnSlotClicked__DelegateSignature, "OnSlotClicked__DelegateSignature" }, // 3734369876
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UInventorySlotWidget>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UInventorySlotWidget_Statics

// ********** Begin Class UInventorySlotWidget Property Definitions ********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UInventorySlotWidget_Statics::NewProp_SlotIcon = { "SlotIcon", nullptr, (EPropertyFlags)0x012408000008000d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInventorySlotWidget, SlotIcon), Z_Construct_UClass_UImage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SlotIcon_MetaData), NewProp_SlotIcon_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UInventorySlotWidget_Statics::NewProp_Button = { "Button", nullptr, (EPropertyFlags)0x012408000008000d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInventorySlotWidget, Button), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Button_MetaData), NewProp_Button_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UInventorySlotWidget_Statics::NewProp_SizeBox = { "SizeBox", nullptr, (EPropertyFlags)0x011400000008000c, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInventorySlotWidget, SizeBox), Z_Construct_UClass_USizeBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SizeBox_MetaData), NewProp_SizeBox_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UInventorySlotWidget_Statics::NewProp_OnSlotClicked = { "OnSlotClicked", nullptr, (EPropertyFlags)0x0010000000080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UInventorySlotWidget, OnSlotClicked), Z_Construct_UDelegateFunction_UInventorySlotWidget_OnSlotClicked__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnSlotClicked_MetaData), NewProp_OnSlotClicked_MetaData) }; // 3734369876
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UInventorySlotWidget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInventorySlotWidget_Statics::NewProp_SlotIcon,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInventorySlotWidget_Statics::NewProp_Button,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInventorySlotWidget_Statics::NewProp_SizeBox,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInventorySlotWidget_Statics::NewProp_OnSlotClicked,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInventorySlotWidget_Statics::PropPointers) < 2048);
// ********** End Class UInventorySlotWidget Property Definitions **********************************
UObject* (*const Z_Construct_UClass_UInventorySlotWidget_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UUserWidget,
	(UObject* (*)())Z_Construct_UPackage__Script_TheHunt,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UInventorySlotWidget_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UInventorySlotWidget_Statics::ClassParams = {
	&UInventorySlotWidget::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UInventorySlotWidget_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UInventorySlotWidget_Statics::PropPointers),
	0,
	0x00B010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UInventorySlotWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_UInventorySlotWidget_Statics::Class_MetaDataParams)
};
void UInventorySlotWidget::StaticRegisterNativesUInventorySlotWidget()
{
	UClass* Class = UInventorySlotWidget::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UInventorySlotWidget_Statics::Funcs));
}
UClass* Z_Construct_UClass_UInventorySlotWidget()
{
	if (!Z_Registration_Info_UClass_UInventorySlotWidget.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UInventorySlotWidget.OuterSingleton, Z_Construct_UClass_UInventorySlotWidget_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UInventorySlotWidget.OuterSingleton;
}
UInventorySlotWidget::UInventorySlotWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UInventorySlotWidget);
UInventorySlotWidget::~UInventorySlotWidget() {}
// ********** End Class UInventorySlotWidget *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Inventory_UI_InventorySlotWidget_h__Script_TheHunt_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UInventorySlotWidget, UInventorySlotWidget::StaticClass, TEXT("UInventorySlotWidget"), &Z_Registration_Info_UClass_UInventorySlotWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UInventorySlotWidget), 2136506354U) },
	};
}; // Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Inventory_UI_InventorySlotWidget_h__Script_TheHunt_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Inventory_UI_InventorySlotWidget_h__Script_TheHunt_872127221{
	TEXT("/Script/TheHunt"),
	Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Inventory_UI_InventorySlotWidget_h__Script_TheHunt_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TheHunt_Source_TheHunt_Inventory_UI_InventorySlotWidget_h__Script_TheHunt_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
