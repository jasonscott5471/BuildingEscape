// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFrameWork/Actor.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	ActorThatOpensDoor = GetWorld()->GetFirstPlayerController()->GetPawn();

}

void UOpenDoor::OpenDoor()
{
	// find owning actor
	//AActor* varOwner = GetOwner();

	//create rotator
	FRotator NewRotation = FRotator(0.0f, OpenAngle, 0.0f);

	//set door rotation
	Owner->SetActorRotation(NewRotation);
}


void UOpenDoor::CloseDoor()
{
	// find owning actor
	//AActor* varOwner = GetOwner();

	//create rotator
	//FRotator NewRotation = FRotator(0.0f, 0.0f, 0.0f);

	//set door rotation
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the trigger volume 
	//if actor has trigger volumed
	if (PressurePlate->IsOverlappingActor(ActorThatOpensDoor))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	//Check if its time to close the door based upon exposed variable
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}


}

