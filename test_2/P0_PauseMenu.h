// // Fill out your copyright notice in the Description page of Project Settings.
//
// #pragma once
//
// #include "CoreMinimal.h"
// #include "Blueprint/UserWidget.h"
// #include "P0_PauseMenu.generated.h"
//
// class UTextBlock;
// class UVerticalBox;
// /**
//  * 
//  */
// UCLASS()
// class TEST_2_API UP0_PauseMenu : public UUserWidget
// {
// 	GENERATED_BODY()
//
// protected:
// 	virtual void NativeConstruct() override;
//
// 	UFUNCTION(BlueprintCallable, Category = "Menu")
// 	void CloseMenu();
// 	
// 	UPROPERTY(meta = (BindWidget))
// 	UTextBlock* MenuText;
//
// 	UPROPERTY(meta = (BindWidget))
// 	UVerticalBox* ChoicesContainer;
// };
