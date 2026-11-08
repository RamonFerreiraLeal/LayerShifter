// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "BoiPeao.h"
#include "MyPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ABoiPeao;
class ULocalPlayer;

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

public:

	void IniciarMovimento(const FInputActionValue& value);

	void Pular(const FInputActionValue& value);
};
