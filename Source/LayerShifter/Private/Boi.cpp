// Fill out your copyright notice in the Description page of Project Settings.


#include "Boi.h"

// Sets default values
ABoi::ABoi()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoi::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABoi::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

