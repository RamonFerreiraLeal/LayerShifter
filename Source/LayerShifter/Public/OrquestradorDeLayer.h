// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OrquestradorDeLayer.generated.h"

UCLASS()
class LAYERSHIFTER_API AOrquestradorDeLayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrquestradorDeLayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cenas")
	TArray<TSubclassOf<AActor>> ListaDeCenas;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> Cenas;

	UPROPERTY()
	int32 IndexAtual;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void AlternaLayer();
};
