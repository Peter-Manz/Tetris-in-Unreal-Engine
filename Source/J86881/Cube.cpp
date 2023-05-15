
#include "Cube.h"
// Sets default values
ACube::ACube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	visualComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	visualComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> visualComponentAsset(TEXT("/Engine/BasicShapes/Cube.cube"));
	AssignColors();

	if (visualComponentAsset.Succeeded())
	{
		visualComponent->SetStaticMesh(visualComponentAsset.Object);
		visualComponent->SetRelativeLocation(FVector(0.0f, 100.0f, 500.0f));
		visualComponent->SetWorldScale3D(FVector(0.2f));
		visualComponent->SetMaterial(0, RedMaterial);
	}
	moveable = true;
	currentDeltaTime = 1.0;
}

void ACube::BeginPlay()
{
	Super::BeginPlay();
	FVector origin, bounds;
	float floorTop = 0.0f;
	leftWall = 0.0f;
	rightWall = 180.0f;

	for (TObjectIterator<AStaticMeshActor> act; act; ++act)
	{
		FString actorName = act->GetName();

		if (actorName.Contains("Floor"))
		{
			act->GetActorBounds(true, origin, bounds);
			floorTop = origin.Z + bounds.Z;
			break;
		}
	}
	floorMinHeight = floorTop + 60.0f;
	
}

void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
float ACube::GetFloorMinHeight() 
{
	return floorMinHeight;
}

void ACube::MoveAxis(FVector& currentLoc)
{
	SetActorLocation(currentLoc);
}
void ACube::SetMoveableFalse()
{
	moveable = false;
	FVector NewLocation = GetActorLocation();
	SetActorLocation(NewLocation);
}
bool ACube::GetMoveable()
{
	return moveable;
}
void ACube::BlowUp() 
{
	this->Destroy();
}
bool ACube::CheckForNextMove() 
{
	FVector currentLocation = GetActorLocation();
	float distanceToFloor, distanceToCube;

	FVector origin,bounds,otherCube;

	for (TObjectIterator<ACube> act; act; ++act) {
		if (act->GetWorld() != this->GetWorld())
		{
			continue;
		}
		
		if (!act->GetMoveable()) {
			act->GetActorBounds(true, origin, bounds);
			float currentLocZ = origin.Z + 20.0f ;
			float currentLocY = origin.Y;
			distanceToCube = currentLocation.Z - currentLocZ;
			if (currentLocY == currentLocation.Y) {
				if (distanceToCube <= 0.5f)
				{
					return false;
				}
			}
		}
	}

	distanceToFloor = (currentLocation.Z - floorMinHeight);
	
	if (distanceToFloor >= 19.0f)
	{
		return true;
	}
	else {
		return false;
	}

}
bool ACube::CanMoveLeft() {

	float distanceToLeftWall;
	FVector currentLocation = GetActorLocation();
	distanceToLeftWall = (currentLocation.Y);

	if (distanceToLeftWall >= 20.0f) {
		return true;
	}
	else {
		return false;
	}

}

bool ACube::CanMoveRight() {
	float distanceToRightWall; 
	FVector currentLocation = GetActorLocation();
	distanceToRightWall = (rightWall - currentLocation.Y);
	if (distanceToRightWall >= 20.0f) {
		return true;
	}
	else {
		return false;
	}
}

void ACube::SetParameters(FVector& position)
{
	visualComponent->SetRelativeLocation(position);
}

//Start of adapted Code from (Unrealcpp, 2018)
void ACube::AssignColors()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> yellowMaterial(TEXT("'/Game/Materials/Yellow.Yellow'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> redMaterial(TEXT("'/Game/Materials/Red.Red'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> blueMaterial(TEXT("'/Game/Materials/Blue.Blue'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> greenMaterial(TEXT("'/Game/Materials/Green.Green'"));

	RedMaterial = redMaterial.Object;
	BlueMaterial = blueMaterial.Object;
	GreenMaterial = greenMaterial.Object;
	YellowMaterial = yellowMaterial.Object;

	colorMaterials[0] = RedMaterial; 
	colorMaterials[1] = BlueMaterial;
	colorMaterials[2] = GreenMaterial;
	colorMaterials[3] = YellowMaterial;
}
void ACube::SetShapeColor(int& randomNum)
{
	if (randomNum == NULL){
		randomNum = 0;
		visualComponent->SetMaterial(1, colorMaterials[randomNum]);
	}
	else {
		visualComponent->SetMaterial(1, colorMaterials[randomNum]);
	}
}
//end of adapted Code


