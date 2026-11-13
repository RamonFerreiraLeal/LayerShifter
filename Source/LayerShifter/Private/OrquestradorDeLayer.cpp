// Fill out your copyright notice in the Description page of Project Settings.


#include "OrquestradorDeLayer.h"
#include "MyPlayerController.h"

// Sets default values
AOrquestradorDeLayer::AOrquestradorDeLayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IndexAtual = 0;
}

// Called when the game starts or when spawned
void AOrquestradorDeLayer::BeginPlay()
{
	Super::BeginPlay();
	
	for (TSubclassOf<AActor> SceneComp : ListaDeCenas) {
		AActor* Temp = GetWorld()->SpawnActor<AActor>(SceneComp, GetActorLocation(), GetActorRotation());
		
		Temp->SetActorHiddenInGame(true);
		Temp->SetActorEnableCollision(false);
		Temp->SetActorTickEnabled(false);

		Cenas.Add(Temp);
	}

	Cenas[0]->SetActorHiddenInGame(false);
	Cenas[0]->SetActorEnableCollision(true);
	Cenas[0]->SetActorTickEnabled(true);

	AMyPlayerController* PC = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	PC->OrquestradorDeLayer = this;

}

// Called every frame
void AOrquestradorDeLayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOrquestradorDeLayer::AlternaLayer() {
	Cenas[IndexAtual]->SetActorHiddenInGame(true);
	Cenas[IndexAtual]->SetActorEnableCollision(false);
	Cenas[IndexAtual]->SetActorTickEnabled(false);


	if (IndexAtual == Cenas.Num() - 1) {
		IndexAtual = 0;
	}
	else {
		IndexAtual++;
	}

	Cenas[IndexAtual]->Reset();
	Cenas[IndexAtual]->SetActorHiddenInGame(false);
	Cenas[IndexAtual]->SetActorEnableCollision(true);
	Cenas[IndexAtual]->SetActorTickEnabled(true);
}

