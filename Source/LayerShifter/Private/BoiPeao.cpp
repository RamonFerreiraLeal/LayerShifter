// Fill out your copyright notice in the Description page of Project Settings.


#include "BoiPeao.h"

// Sets default values
ABoiPeao::ABoiPeao()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Cena"));

	Colisao = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Colisao"));
	Colisao->SetupAttachment(RootComponent);

	Malha = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MalhaPersonagem"));
	Malha->AttachToComponent(Colisao, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	Colisao->OnComponentHit.AddDynamic(this, &ABoiPeao::OnCapsuleHit);

	MovimentoNoFrame = FVector::ZeroVector;

	EstaNoChao = false;
}

// Called when the game starts or when spawned
void ABoiPeao::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoiPeao::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if (!EstaNoChao) {
		AddActorWorldOffset(GetGravityDirection());
	}

	if (!MovimentoNoFrame.IsNearlyZero()) {
		AddActorWorldOffset(MovimentoNoFrame * DeltaTime);
	}
}

// Called to bind functionality to input
void ABoiPeao::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABoiPeao::OnCapsuleHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (Hit.IsValidBlockingHit()) {
		EstaNoChao = true;
		UE_LOG(LogTemp, Display, TEXT("Entrou em contato"));
		
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("Bloco invalido"));
	}
}