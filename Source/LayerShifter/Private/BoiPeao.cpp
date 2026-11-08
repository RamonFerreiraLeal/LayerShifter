// Fill out your copyright notice in the Description page of Project Settings.


#include "BoiPeao.h"

// Sets default values
ABoiPeao::ABoiPeao()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Colisao = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Colisao"));
	Colisao->InitCapsuleSize(45.f, 95.f);
	RootComponent = Colisao;

	Malha = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MalhaPersonagem"));
	Malha->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	//Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//Camera->SetupAttachment(RootComponent);

	EstaNoChao = false;
	Velocidade = 300.f;
	ForcaDeGravidade = -987.0f;
	Forca = FVector::ZeroVector;
}

// Called when the game starts or when spawned
void ABoiPeao::BeginPlay()
{
	Super::BeginPlay();

	Colisao->OnComponentBeginOverlap.AddDynamic(this, &ABoiPeao::OnBeginOverlap);
	Colisao->OnComponentEndOverlap.AddDynamic(this, &ABoiPeao::OnEndOverlap);

}

// Called every frame
void ABoiPeao::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!EstaNoChao) {
		Forca.Z += ForcaDeGravidade * DeltaTime;
	}

	FHitResult HitResult;
	

	if (EstaNoChao) {
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		//GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), (GetActorLocation() + FVector::DownVector * 100.f) + DirecaoMovimento * 50.f, ECC_Visibility, Params);
		GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), (GetActorLocation() + FVector::DownVector * 110.f), ECC_Visibility, Params);

		DrawDebugLine(GetWorld(), HitResult.TraceStart, HitResult.ImpactPoint, FColor::Red, false, -1.0f, 1, 5.0f);
		DrawDebugCoordinateSystem(GetWorld(), HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation(), 10.f, false, -1.0f, 1, 5.0f);

		if (HitResult.bBlockingHit) {
			DirecaoMovimento = FVector::CrossProduct(HitResult.ImpactNormal, FVector(1.0f, 0.f, 0.f)).GetUnsafeNormal().GetAbs() * DirecaoMovimento.Y;
		}

		DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + DirecaoMovimento * 100.f, FColor::Red, false, -1.0f, 1, 5.0f);
		UE_LOG(LogTemp, Display, TEXT("Vetor2 de Impact %s"), *HitResult.ImpactNormal.ToString());
	}

	FVector MovimentoAtual = DirecaoMovimento * Velocidade * DeltaTime;

	MovimentoAtual += Forca * DeltaTime;

	if (!MovimentoAtual.IsNearlyZero()) {

		FHitResult Hit;
		AddActorWorldOffset(MovimentoAtual, true, &Hit);

		//UE_LOG(LogTemp, Display, TEXT("Vetor de Impact %s"), *Hit.ImpactNormal.ToString());

		if ((Hit.ImpactNormal.Z > 0.7f || HitResult.ImpactNormal.Z > 0.7f)) {
			EstaNoChao = true;
			EstaNaParede = false;
			Forca.Z = 0.0f;
		}
		else if (!EstaNoChao && (Hit.ImpactNormal.Y > 0.7f || Hit.ImpactNormal.Y < -0.7f)) {
			EstaNaParede = true;
			UE_LOG(LogTemp, Display, TEXT("Esta na parede"));
			AddActorWorldOffset(FVector::VectorPlaneProject(Forca, Hit.ImpactNormal) * DeltaTime, true);
		}
		else {
			EstaNoChao = false;
		}
	}

}

// Called to bind functionality to input
void ABoiPeao::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABoiPeao::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Display, TEXT("Funciona em contato"));

	//UE_LOG(LogTemp, Display, TEXT("Tempo em movimento %f , MovimentoAtual %s"), TempoEmMovimento, *MovimentoNoFrame.ToString());

	if (SweepResult.ImpactNormal != FVector::DownVector) {
		EstaNoChao = true;
		UE_LOG(LogTemp, Display, TEXT("Entrou em contato"));
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("Bloco invalido"));

	}
}

void ABoiPeao::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	//UE_LOG(LogTemp, Display, TEXT("Tempo em movimento %f , MovimentoAtual %s"), TempoEmMovimento, *MovimentoNoFrame.ToString());
	UE_LOG(LogTemp, Display, TEXT("Caindo"));
}