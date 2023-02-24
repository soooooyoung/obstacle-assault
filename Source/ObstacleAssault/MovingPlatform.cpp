// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
}

// Called every frame
// Scope Resolution Operator "::" : Looks inside a class,
// the same way "." operator looks inside an "instance" of a class.

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// DeltaTime is how long each frame took to execute
	// When we mulitply something by DeltaTime it makes it independant on frame rate.

	// 1. Move platform forwards

	// Get current location
	FVector CurrentLocation = GetActorLocation();
	// Add vector to that location
	CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
	// Set the location
	SetActorLocation(CurrentLocation);

	// 2. Send platform back after certain distance

	// Check how far it's moved
	// May also use "Distance"
	float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);

	if (DistanceMoved > PlatformMoveDistance)
	{

		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		// Resetting the start location so that move distance overflowed by high framerates or velocity
		// may not alter the total distance
		StartLocation = StartLocation + (MoveDirection * PlatformMoveDistance);
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
}
