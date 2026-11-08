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
	EnhancedInput->BindAction(IA_Pular, ETriggerEvent::Triggered, this, &AMyPlayerController::Pular);
}

void AMyPlayerController::IniciarMovimento(const FInputActionValue& value) {
	float Movimento = value.Get<float>();
	Peao->DirecaoMovimento = FVector(0.0f, FMath::Clamp(Movimento,-1.f, 1.f), 0.0f);
}

void AMyPlayerController::Pular(const FInputActionValue& value) {
	Peao->Forca.Z = 500.f;
	Peao->EstaNoChao = false;
}