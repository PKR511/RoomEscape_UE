// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
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
	// ...
	UE_LOG(LogTemp, Warning, TEXT("Grabber Reporting"));
	FindPhysicHandleComponent();
	SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// if physic handle is attached
	if (PhysicHandle->GrabbedComponent) {
		PhysicHandle->SetTargetLocation(GetReachLineEndLocation());
	}
	
}

void UGrabber:: FindPhysicHandleComponent() {
	PhysicHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("%s missing physic handle component "), *GetOwner()->GetName());
	}

}
void UGrabber::SetupInputComponent() {

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Input Component Found"));
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing input component "), *GetOwner()->GetName());
	}
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab Called"));
	
	/// Line Trace and check if we hit any actor with physic body collision set.	
	auto HitResult=GetFirstPhysicBodyInReach();
	auto ComponenetToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();
	if (PhysicHandle == nullptr)
		return;
	///if we hit somethig then attach physic handle.
	if (ActorHit) {
		PhysicHandle->GrabComponent
		(
			ComponenetToGrab,
			NAME_None,//No Bone Name Needed.
			ComponenetToGrab->GetOwner()->GetActorLocation(),
			true
		);
	}
}
void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Release Called"));
	if (PhysicHandle == nullptr)
		return;
	PhysicHandle->ReleaseComponent();
}

const FHitResult  UGrabber::GetFirstPhysicBodyInReach()
{		
	FHitResult HitResult;
	///Creating collisionqueryparam
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	///Doing Ray Trace here
	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		GetReachLineStartLocation(),
		GetReachLineEndLocation(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	//AActor* Actor = HitResult.GetActor();
	//if (Actor) {
	//	UE_LOG(LogTemp, Warning, TEXT("Hit Object: %s "), *(Actor->GetName()));
	//}
	return HitResult;
}
FVector UGrabber::GetReachLineStartLocation() {
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s & Rotation: %s"),*PlayerLocation.ToString(),*PlayerRotation.ToString());

	return PlayerLocation ;

	
}
FVector UGrabber::GetReachLineEndLocation() {
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s & Rotation: %s"),*PlayerLocation.ToString(),*PlayerRotation.ToString());

	FVector LineEndLocation = PlayerLocation + PlayerRotation.Vector() * Reach;

	/*DrawDebugLine(
		GetWorld(),
		PlayerLocation,
		LineEndLocation,
		FColor(255, 0, 0),
		false,
		0.0f,
		0.0f,
		5.0f

	);*/
	return LineEndLocation;
}