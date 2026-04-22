// Fill out your copyright notice in the Description page of Project Settings.

#include "LootTableRow.h"
#include "DataTableEditorUtils.h"

void FLootTableRow::OnDataTableChanged(const UDataTable* InDataTable, const FName InRowName)
{
	Super::OnDataTableChanged(InDataTable, InRowName);

	if (ItemDefinition && InRowName != ItemDefinition->ItemID)
	{
		FDataTableEditorUtils::RenameRow(
			const_cast<UDataTable*>(InDataTable),
			InRowName,
			ItemDefinition->ItemID);
	}
}
