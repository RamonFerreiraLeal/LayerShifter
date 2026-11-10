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

	FHitResult Hit;
	FHitResult HitVerificaChao;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(HitVerificaChao, GetActorLocation(), GetActorLocation() + FVector::DownVector * (110.f), ECC_Visibility, Params);
	DrawDebugLine(GetWorld(), HitVerificaChao.TraceStart, HitVerificaChao.ImpactPoint, FColor::Red, false, -1.0f, 1, 5.0f);

	if (!DirecaoMovimento.IsNearlyZero()) {
		if (HitVerificaChao.IsValidBlockingHit()) {
			DirecaoMovimento = FVector::VectorPlaneProject(DirecaoMovimento, HitVerificaChao.ImpactNormal);
		}

		AddActorWorldOffset(DirecaoMovimento * Velocidade * DeltaTime, true, &Hit);

		if (Hit.bBlockingHit && Hit.ImpactNormal.Z > 0.8f) {
			Forca.Z = 0.f;
		}
	}

	if (!HitVerificaChao.IsValidBlockingHit()|| Forca.Z > 0.0f) {
		Forca.Z += ForcaDeGravidade * DeltaTime;
		AddActorWorldOffset(Forca * DeltaTime, true, &Hit);

		if (Hit.ImpactNormal.Z <= -0.3f && Hit.ImpactNormal.Z >= -1.1f || Hit.ImpactNormal.Z > 0.8f) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Bateu no teto ou no chao"));
			Forca.Z = 0.0f;
		}

		if (Hit.bBlockingHit && Hit.ImpactNormal.Z < 0.8f) {
			AddActorWorldOffset(FVector::VectorPlaneProject(Forca, Hit.ImpactNormal) * DeltaTime, true);
		}
	}
}

/*if (!EstaNoChao) {
		Forca.Z += ForcaDeGravidade * DeltaTime;
	}

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (EstaNoChao) {

		GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), (GetActorLocation() + FVector::DownVector * 110.f), ECC_Visibility, Params);

		DrawDebugLine(GetWorld(), HitResult.TraceStart, HitResult.ImpactPoint, FColor::Red, false, -1.0f, 1, 5.0f);
		DrawDebugCoordinateSystem(GetWorld(), HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation(), 10.f, false, -1.0f, 1, 5.0f);

		if (HitResult.bBlockingHit) {
			DirecaoMovimento = FVector::CrossProduct(HitResult.ImpactNormal, FVector(1.0f, 0.f, 0.f)).GetUnsafeNormal() * DirecaoMovimento.Y;
		}

		DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + DirecaoMovimento * 100.f, FColor::Purple, false, -1.0f, 1, 5.0f);
		UE_LOG(LogTemp, Display, TEXT("Vetor2 de Impact %s"), *HitResult.ImpactNormal.ToString());
	}

	FVector MovimentoAtual = DirecaoMovimento * Velocidade * DeltaTime;

	MovimentoAtual += Forca * DeltaTime;

	if (!MovimentoAtual.IsNearlyZero()) {
		FHitResult Hit;
		AddActorWorldOffset(MovimentoAtual, true, &Hit);
		
		//Verifica proximo movimento
		FHitResult HitResultProximoPasso;
		GetWorld()->LineTraceSingleByChannel(HitResultProximoPasso, GetActorLocation(), GetActorLocation() + (FVector::DownVector) * 110.f + (DirecaoMovimento * 60.f), ECC_Visibility, Params);
		DrawDebugLine(GetWorld(), HitResultProximoPasso.TraceStart, HitResultProximoPasso.ImpactPoint, FColor::Red, false, -1.0f, 1, 5.0f);

		UE_LOG(LogTemp, Display, TEXT("Hit Impact Normal %s"), *Hit.ImpactNormal.ToString());


		if ((Hit.ImpactNormal.Z > 0.8f || HitResult.bBlockingHit && Hit.IsValidBlockingHit())) {
			EstaNoChao = true;
			EstaNaParede = false;
			Forca.Z = 0.0f;
		}else {
			EstaNoChao = false;
		}
		if ((Hit.ImpactNormal.Y > 0.6f || Hit.ImpactNormal.Y < -0.6f)) {
			EstaNaParede = true;
			UE_LOG(LogTemp, Display, TEXT("Esta Na Parede"));

			FVector Margem = Hit.ImpactPoint - (GetActorLocation() + FVector::DownVector * 95.f);

			if (HitResultProximoPasso.bBlockingHit && Margem.Z > 0.0f && Margem.Z < 20.f) {
				//FVector Slide = FVector::VectorPlaneProject(MovimentoAtual, Hit.ImpactNormal);
				//AddActorLocalOffset(Slide, false);

				UE_LOG(LogTemp, Display, TEXT("Entrou em subir degrau"));

				AddActorLocalOffset(Margem, true);

				AddActorLocalOffset(MovimentoAtual, true);
			}
			else {
				AddActorWorldOffset(FVector::VectorPlaneProject(Forca, Hit.ImpactNormal) * DeltaTime, true);
			}
		}
	}*/

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