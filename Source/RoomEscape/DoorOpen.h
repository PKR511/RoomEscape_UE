// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <Runtime/Engine/Classes/Engine/TriggerVolume.h>
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorOpen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOMESCAPE_API UDoorOpen : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpen();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FOnDoorRequest OnOpenRequest;
	UPROPERTY(BlueprintAssignable)
	FOnDoorRequest OnCloseRequest;

private:	
	UPROPERTY(VisibleAnywhere)
	float TriggerMass = 50.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate =nullptr;
	
	AActor* Owner;
		
	//return total mass(kg) of actors that are on pressureplate.
	float GetTotalMassOfActorsOnPressurePlate();
};
