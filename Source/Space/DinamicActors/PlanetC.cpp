// Fill out your copyright notice in the Description page of Project Settings.

#include "PlanetC.h"
#include "EngineUtils.h"

// Sets default values
APlanetC::APlanetC()
{
	this->name = this->GetName();
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlanetC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlanetC::Tick(float DeltaTime)
{
	t = DeltaTime;

	otherVectors.Empty();
	FString str="ads";
	selfCoord = this->GetActorLocation();
	
	for (TActorIterator<APlanetC> OtherPlanet(GetWorld()); OtherPlanet; ++OtherPlanet)
	{
		otherVectorLocation = OtherPlanet->GetActorLocation();
		if (this != *OtherPlanet) {
			//OtherPlanet->mass;
			//OtherPlanet->selfCoord;
			forwardVector = otherVectorLocation - selfCoord;

			str = FString::Printf(TEXT("name %s   loc by x %f"), *name, OtherPlanet->GetActorLocation().X);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, str);
			if (forwardVector.Size() < 10) {
				OtherPlanet->selfVelocity = (OtherPlanet->selfVelocity*OtherPlanet->mass + this->selfVelocity*this->mass) / (OtherPlanet->mass + this->mass);
				this->selfVelocity = OtherPlanet->selfVelocity;
			}
			else {
				distance = forwardVector.X*forwardVector.X + forwardVector.Y*forwardVector.Y + forwardVector.Z*forwardVector.Z;
			}
			addAcseleration = gravity * OtherPlanet->mass / distance;
			//distance.Normalize();
			addvelocity = addvelocity + forwardVector*addAcseleration;
		}
	}
	
	selfVelocity = selfVelocity+ addvelocity;
	selfCoord = selfCoord + selfVelocity;

	addvelocity=FVector(0,0,0);
	this->SetActorLocation(selfCoord);

	
	Super::Tick(DeltaTime);
}

FVector APlanetC::changeLoc(FVector f0, TArray<float> m, TArray<FVector> otherVector, TArray<float> radius)
{
	selfCoord = f0;
	FVector a1 = APlanetC::a(m, otherVector, radius);
	v1 = APlanetC::velocity(a1);
	return f0 + v1 * t + a1 * t*t / 2;
}



FVector APlanetC::velocity(FVector a)
{

	v1 = v1 + a * t;
	return v1;
}
FVector APlanetC::a(TArray<float> m, TArray<FVector> f, TArray<float> radius)
{
	int i;
	FVector result(0, 0, 0), f1(0, 0, 0);
	int32 l = m.Num();
	float distance;
	for (i = 0; i < l; i++) {
		f1 = f[i] - selfCoord;
		distance = f1.X*f1.X + f1.Y*f1.Y + f1.Z*f1.Z;
		if (distance < (radius[i] + r)) {
			len_a = 5 * m[i] / (distance)-m[i] * 2;
		}
		else {
			len_a = 5 * m[i] / (distance);
		}
		f1.Normalize();
		result = result + f1 * len_a;
	}

	return result;
}