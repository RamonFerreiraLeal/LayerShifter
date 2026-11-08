// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BoiPeao.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;
class UCameraComponent;

UCLASS()
class LAYERSHIFTER_API ABoiPeao : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABoiPeao();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* Malha;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Collision")
	UCapsuleComponent* Colisao;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	//UCameraComponent* Camera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movimento")
	float Velocidade;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movimento")
	float ForcaDeGravidade;

	bool EstaNoChao;
	bool EstaNaParede;

	FVector DirecaoMovimento;

	FVector DirecaoGravidade;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movimento");
	FVector Forca;

};
