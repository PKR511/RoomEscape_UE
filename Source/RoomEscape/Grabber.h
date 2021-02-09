// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <PhysicsEngine/PhysicsHandleComponent.h>
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOMESCAPE_API UGrabber : public UActorComponent
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
	float Reach = 150.0f;
	UPhysicsHandleComponent* PhysicHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	//method get invoked on key press event for 'Grab' input event.
	//this method grabs any physic object it can.
	void Grab();
	//method get invoked on key released event for 'Grab' input event.
	//this method released any physic object that is in hold.
	void Release();

	//finds the physichandlecomponent attached to this object.
	void FindPhysicHandleComponent();
	//find the inputcomponent attached to this object.
	void SetupInputComponent();

	//return hitresult of first body it hits.
	const FHitResult GetFirstPhysicBodyInReach() ;
	
	//return the start of line reach.
	FVector GetReachLineStartLocation();
	//return the end of line reach.
	FVector GetReachLineEndLocation();
};
