// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFrameWork/Actor.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	///UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty! selement custom code..."));

	FindPhysicsHandleComponent();
	SetupInputComponent();
	
}


void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("UGrabber::Grab fired! selement custom code..."));
	
	///Line trace and see if we reach any actors with physics body collision channel set
	GetFirstPhysicsBodyInReach();

	///If we hit something then attach a physics handle
	//TODO attach physics handle

}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("UGrabber::Release fired! selement custom code..."));
	//TODO release physics handle

}
void UGrabber::FindPhysicsHandleComponent()
{
	///Look for attached Physics Handle myPhysicsHandle
	myPhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (myPhysicsHandle) //if it exists do the following
	{

		//working nothing to do though
	}
	else
	{

		UE_LOG(LogTemp, Error, TEXT("Error raised while trying invoke myPhysicsHandle with object:%s"),
			*GetOwner()->GetName());

	}
}
void UGrabber::SetupInputComponent()
{
	///Look for attached Input Compt 
	myInputComp = GetOwner()->FindComponentByClass<UInputComponent>();

	if (myInputComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("myInputComp found!"));
		///lets bind action to mapped keys created in ue4 project settings/input/actions - see Summary Notes - 03_BuildingEscape Game pg 51
		myInputComp->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		myInputComp->BindAction("Grab", IE_Released, this, &UGrabber::Release);

	}
	else
	{


		UE_LOG(LogTemp, Error, TEXT("Error raised while trying invoke myInputComp with object:%s"),
			*GetOwner()->GetName());

	}
}


void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// Called every frame
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if PH attached 
		//move object


}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// Get player view point 
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewPointLocation,
		PlayerViewPointRotation

	);
	///selement note here the use of * is NOT a pointer but a de-referencing too *PlayerViewPointLocation.ToString()
	/*UE_LOG(LogTemp, Warning, TEXT("Location is %s rotation is %s"),
	*PlayerViewPointLocation.ToString(),
	*PlayerViewPointRotation.ToString() );
	*/

	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
	///draw a red trace line in the world to visualize

	/* selement don't need but leaving for future reference

	DrawDebugLine(
	GetWorld(),
	PlayerViewPointLocation,
	LineTraceEnd,
	FColor(255,0,0), //Red, green, blue
	false,
	0.0f,
	0.0f,
	2.0f //line thickness
	);
	*/

	///Setup raycast query parameters
	FCollisionQueryParams ScottsTraceParameters(FName(TEXT("")), false, GetOwner());

	///Line Trace AKA Ray cast out to calc distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		ScottsTraceParameters
	);

	///See what we hit

	AActor* HitActor = Hit.GetActor();

	if (HitActor)

	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace Hit detail is %s"),
			*(HitActor->GetName()));
	}
	return FHitResult();
}