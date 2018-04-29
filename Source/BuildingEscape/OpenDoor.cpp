// Fill out your copyright notice in the Description page of Project Settings.

/*
#include "OpenDoor.h"
#include "GameFrameWork/Actor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
*/
#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFrameWork/Actor.h"
#include "Components/PrimitiveComponent.h"


//selement: this variable does nothing just acts like a mental flag to denote when Unreal is using an OUT parameter
#define OUT

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
	
	//By Vid 91 we did not require an actor that opens door so we are remming it out
	//ActorThatOpensDoor = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PressurePlate)
	{

		UE_LOG(LogTemp, Error, TEXT("Error raised while trying to invoke pressure plate object:%s"),
			*GetOwner()->GetName());
	}

}

void UOpenDoor::OpenDoor()
{
	// find owning actor
	//AActor* varOwner = GetOwner();

	/*
	
	//create rotator
	FRotator NewRotation = FRotator(0.0f, OpenAngle, 0.0f);

	//set door rotation
	Owner->SetActorRotation(NewRotation);
	*/

	OnOpenRequest.Broadcast(); //selement broadcast the OpenDoor event so we can wire it up inside Open_Door_Bp in UE4 editor (example of C++ integrating with BP)
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
	
	//By Vid 91 we did not require an actor that opens door so we are remming it out
	//if (PressurePlate->IsOverlappingActor(ActorThatOpensDoor))
	if (GetTotalMassOfActorsOnDoorTriggerPlate()> 18.0f) //TODO create exposed UE4 property variable to expose this
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

float UOpenDoor::GetTotalMassOfActorsOnDoorTriggerPlate()
{
	float TotalMass = 0.0f;
	TArray<AActor*> OverlappingActors;
	//find all the overlapping actors
	if (!PressurePlate) { return TotalMass; } //error checking

	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	//iterate and sum all masses
	for (const auto* Actor : OverlappingActors)  //if OverlappingActors is returning error read the following post. It doesn't stop from compiling and running https://community.gamedev.tv/t/range-based-for-requires-begin-function/41323
	{

		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName());

	}
	

	

	return TotalMass;
	
}