// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlanetC.generated.h"

UCLASS()
class SPACE_API APlanetC : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlanetC();

protected:
	FString name;
	FVector v1;
	FVector selfCoord; 
	FVector addvelocity;
	TArray<FVector> otherVectors;
	FVector forwardVector;

	UPROPERTY(EditAnywhere)
		float mass;
	UPROPERTY(EditAnywhere)
		float gravity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector selfVelocity;

	FVector otherVectorLocation;
	float addAcseleration;
	float distance;
	float r;
	float t;
	float len_a;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//UFUNCTION(BlueprintCallable)
	//	float changeloc(float x0, TArray<float> m, TArray<float> x);

	UFUNCTION(BlueprintCallable)
		FVector changeLoc(FVector f0, TArray<float> m, TArray<FVector> f, TArray<float> radius);

	FVector velocity(FVector a);
	FVector a(TArray<float> m, TArray<FVector> f, TArray<float> radius);



};
