// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere) //MACRO FROM UE4 ENGINE THAT DOES PRECOMPILE STUFF - https://wiki.unrealengine.com/UPROPERTY
	float OpenAngle = 90.0f;

	UPROPERTY(EditAnywhere) //selement var injects into UE4 but need to set to TriggerVolume
		ATriggerVolume* PressurePlate;

	//UPROPERTY(EditAnywhere) //selement var injects into UE4 but need to be able to choose which actor will TriggerVolume
		AActor* ActorThatOpensDoor; //selement remember pawn inherents from actor
	
	
};
