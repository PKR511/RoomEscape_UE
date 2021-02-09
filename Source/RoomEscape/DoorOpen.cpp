// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpen.h"

// Sets default values for this component's properties
UDoorOpen::UDoorOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpen::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//Finding Player Object  From World 
	//(i.e fetching player controller from unreal world and getting pawn (body that hold controller).
	//ActorThatOpensDoor = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	Owner = GetOwner();//getting ref of owern of the component.
	if (PressurePlate == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("%s Object is missing pressure plate"), *Owner->GetName());
	}
	
}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//cheking if trigger volume is getting triggered
	if (GetTotalMassOfActorsOnPressurePlate()>=TriggerMass) {
		OnOpenRequest.Broadcast();
	}
	else {
		OnCloseRequest.Broadcast();
	}
	
		
	
}



float UDoorOpen::GetTotalMassOfActorsOnPressurePlate()
{
	float TotalMass = 0.0f;
	TArray<AActor*> OverlappingActors;
	if (PressurePlate == nullptr) {
		return TotalMass;
	}
	PressurePlate->GetOverlappingActors(OverlappingActors);
	for (const auto &Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s Object is on pressureplate "),  *Actor->GetName());
	}

	return TotalMass;
}

