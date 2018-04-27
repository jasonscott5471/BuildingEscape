// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	float Reach = 100.0f;
	UPhysicsHandleComponent* myPhysicsHandle = nullptr; //nullptr is memory address 0 and represents an initialization

	UInputComponent* myInputComp = nullptr; 

	//selemnt Ray-cast and grab whats in reach
	void Grab();
	void Release();
	void FindPhysicsHandleComponent();

	void SetupInputComponent();

	//return hit for first physics body (PB) in reach
	const FHitResult GetFirstPhysicsBodyInReach();


	//return current end of reach line
	FVector GetReachLine(FString ReachType);
};
