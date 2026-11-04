// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Engine/LocalPlayer.h"
#include "Engine/Engine.h"

class GEngine;

AMyPlayerController::AMyPlayerController() {

}

void AMyPlayerController::BeginPlay() {
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsytem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()) {
		Subsytem->AddMappingContext(InputMapping,0);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Usando o Controller Personalizado"));
	}

	if (GetPawn()){
		Peao = Cast<ABoiPeao>(GetPawn());
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Usando Peao Boi"));
	}
}

void AMyPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInput->BindAction(IA_Mover, ETriggerEvent::Triggered, this, &AMyPlayerController::IniciarMovimento);
}

void AMyPlayerController::IniciarMovimento(const FInputActionValue& value) {
	float Movimento = value.Get<float>();
	Peao->MovimentoNoFrame.Y = Movimento * 100.f;
}