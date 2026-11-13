// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "BoiPeao.h"
#include "Blueprint/UserWidget.h"
#include "OrquestradorDeLayer.h"
#include "MyPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ABoiPeao;
class ULocalPlayer;
class UUserWidget;

/**
 * 
 */
UCLASS()
class LAYERSHIFTER_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();

	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

private:
	
	ABoiPeao* Peao;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Mover;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Pular;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Alternar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hud")
	TSubclassOf<UUserWidget> HudPadrao;

	UPROPERTY()
	UUserWidget* InstanciaPadrao;

public:

	void IniciarMovimento(const FInputActionValue& value);

	void Pular(const FInputActionValue& value);

	void AlternarCena(const FInputActionValue& value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Orquestrador")
	AOrquestradorDeLayer* OrquestradorDeLayer;
};
