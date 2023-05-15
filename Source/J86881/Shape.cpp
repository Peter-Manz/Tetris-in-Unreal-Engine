
#include "Shape.h"

AShape::AShape()
{
	PrimaryActorTick.bCanEverTick = true;
	currentDeltaTime = 1.0f;
	currentShapeCode = 0;
	step = 20.0f;
}

void AShape::BeginPlay()
{
	Super::BeginPlay();
	lowestCube = NULL;
	SendTetrisObject();
	floorMinHeight = cubeA->GetFloorMinHeight();
}

// Called every frame
void AShape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	currentDeltaTime -= (1.0f * DeltaTime);

	lowestCube = FindLowestCube();
	FVector bottomLocation = lowestCube->GetActorLocation();

	paramOne = cubeA->GetActorLocation();
	paramTwo = cubeB->GetActorLocation();
	paramThree = cubeC->GetActorLocation();
	paramFour = cubeD->GetActorLocation();
	
	if (bottomLocation.Z <= floorMinHeight || (!CheckDownMove()))
	{
		lowestCube->SetMoveableFalse();
		cubeA->SetMoveableFalse();
		cubeB->SetMoveableFalse();
		cubeC->SetMoveableFalse();
		cubeD->SetMoveableFalse();

		if (!lowestCube->GetMoveable())
		{
			SendTetrisObject();
		}
		lowestCube = NULL;
	}
	if (currentDeltaTime <= 0.03f) {
		currentDeltaTime = 1.0f;
		MoveDown();
	}
}

void AShape::SendTetrisObject() {

	currentShapeCode = FMath::RandRange(1, 8);
	int randomNum = FMath::RandRange(0, 3);
	cubeA = (ACube*)GWorld->SpawnActor(ACube::StaticClass());
	cubeB = (ACube*)GWorld->SpawnActor(ACube::StaticClass());
	cubeC = (ACube*)GWorld->SpawnActor(ACube::StaticClass());
	cubeD = (ACube*)GWorld->SpawnActor(ACube::StaticClass());

	switch (currentShapeCode) {
	case 1:
		paramOne = FVector(100.0f, 100.0f, 500.0f);
		paramTwo = FVector(100.0f, 120.0f, 500.0f);
		paramThree = FVector(100.0f, 140.0f, 500.0f);
		paramFour = FVector(100.0f, 160.0f, 500.0f);
		break;
	case 2:
		paramOne = FVector(100.0f, 100.0f, 500.0f);
		paramTwo = FVector(100.0f, 120.0f, 500.0f);
		paramThree = FVector(100.0f, 100.0f, 520.0f);
		paramFour = FVector(100.0f, 120.0f, 520.0f);
		break;
	case 3:
		paramOne = FVector(100.0f, 100.0f, 500.0f);
		paramTwo = FVector(100.0f, 120.0f, 500.0f);
		paramThree = FVector(100.0f, 120.0f, 480.0f);
		paramFour = FVector(100.0f, 140.0f, 480.0f);
		break;
	case 4:
		paramOne = FVector(100.0f, 100.0f, 500.0f);
		paramTwo = FVector(100.0f, 100.0f, 520.0f);
		paramThree = FVector(100.0f, 100.0f, 540.0f);
		paramFour = FVector(100.0f, 100.0f, 480.0f);
		break;
	case 5:
		paramOne = FVector(100.0f, 100.0f, 500.0f);
		paramTwo = FVector(100.0f, 100.0f, 520.0f);
		paramThree = FVector(100.0f, 100.0f, 540.0f);
		paramFour = FVector(100.0f, 120.0f, 500.0f);
		break;
	case 6:
		paramOne = FVector(100.0f, 140.0f, 520.0f);
		paramTwo = FVector(100.0f, 120.0f, 520.0f);
		paramThree = FVector(100.0f, 120.0f, 500.0f);
		paramFour = FVector(100.0f, 100.0f, 500.0f);
		break;
	case 7:
		paramOne = FVector(100.0f, 100.0f, 500.0f);
		paramTwo = FVector(100.0f, 100.0f, 520.0f);
		paramThree = FVector(100.0f, 100.0f, 540.0f);
		paramFour = FVector(100.0f, 80.0f, 500.0f);
		break;
	case 8: 
		paramOne = FVector(100.0f, 80.0f, 500.0f);
		paramTwo = FVector(100.0f, 100.0f, 500.0f);
		paramThree = FVector(100.0f, 120.0f, 500.0f);
		paramFour = FVector(100.0f, 100.0f, 480.0f);
		break;
	default:
		paramOne = FVector(100.0f, 100.0f, 500.0f);
		paramTwo = FVector(100.0f, 120.0f, 500.0f);
		paramThree = FVector(100.0f, 100.0f, 520.0f);
		paramFour = FVector(100.0f, 120.0f, 520.0f);
		break;
	}
	cubeA->SetParameters(paramOne);
	//cubeA->SetShapeColor(randomNum);
	cubeB->SetParameters(paramTwo);
	//cubeB->SetShapeColor(randomNum);
	cubeC->SetParameters(paramThree);
	//cubeC->SetShapeColor(randomNum);
	cubeD->SetParameters(paramFour);
	//cubeD->SetShapeColor(randomNum);
	tetrisShapes.Add(cubeA);
	tetrisShapes.Add(cubeB);
	tetrisShapes.Add(cubeC);
	tetrisShapes.Add(cubeD);

}
void AShape::MoveDown()
{
	if (CheckDownMove()) {
		for (TObjectIterator<ACube> act; act; ++act) {
			if (act->GetWorld() != this->GetWorld())
			{
				continue;
			}
			if (act->GetMoveable()) {
				FVector currentLoc = act->GetActorLocation();
				currentLoc.Z -= step;
				act->MoveAxis(currentLoc);
			}
		}
	}
}

void AShape::Move_Y_Right() 
{
	if (CheckRightMove()) {
		for (TObjectIterator<ACube> act; act; ++act) {
			if (act->GetWorld() != this->GetWorld())
			{
				continue;
			}
			if (act->GetMoveable()) {
				FVector currentLoc = act->GetActorLocation();
				currentLoc.Y += step;
				act->MoveAxis(currentLoc);
			}
		}
	}
}
void AShape::Move_Y_Left() {

	if (CheckLeftMove()) {
		for (TObjectIterator<ACube> act; act; ++act) {
			if (act->GetWorld() != this->GetWorld())
			{
				continue;
			}
			if (act->GetMoveable()) {
				FVector currentLoc = act->GetActorLocation();
				currentLoc.Y -= step;
				act->MoveAxis(currentLoc);
			}
		}
	}
}
bool AShape::CheckDownMove() 
{
	int truthCounter = 0;
	for (TObjectIterator<ACube> act; act; ++act) {
		if (act->GetWorld() != this->GetWorld())
		{
			continue;
		}
		if (act->GetMoveable()) {
			if (act->CheckForNextMove()) {
				truthCounter += 1;
				if (truthCounter == 4) {
					return true;
				}
			}
		}
	}
	return false;
}
bool AShape::CheckRightMove()
{
	int truthCounter = 0;
	for (TObjectIterator<ACube> act; act; ++act) {
		if (act->GetWorld() != this->GetWorld())
		{
			continue;
		}
		if (act->GetMoveable()) {
			if (act->CanMoveRight()) {
				truthCounter += 1;
				if (truthCounter == 4) {
					return true;
				}
			}
		}
	}
	return false;
}
bool AShape::CheckLeftMove()
{
	int truthCounter = 0;
	for (TObjectIterator<ACube> act; act; ++act) {
		if (act->GetWorld() != this->GetWorld())
		{
			continue;
		}
		if (act->GetMoveable()) {
			FVector currentLoc = act->GetActorLocation();

			if (act->CanMoveLeft()) {
				truthCounter += 1;
				if (truthCounter == 4) {
					return true;
				}
			}
		}
	}
	return false;
}
void AShape::Rotate()
{
	//Start of adapted code from (Stackoverflow, 2021)
	paramOne = cubeA->GetActorLocation();
	paramTwo = cubeB->GetActorLocation();
	paramThree = cubeC->GetActorLocation();
	paramFour = cubeD->GetActorLocation();

	switch (currentShapeCode) {
	case 1:
		paramOne = FVector(paramTwo.X, paramTwo.Y, paramTwo.Z - step);
		paramTwo = paramTwo;
		paramThree = FVector(paramTwo.X, paramTwo.Y, paramTwo.Z + step);
		paramFour = FVector(paramTwo.X, paramTwo.Y, paramTwo.Z + (step + step));
		currentShapeCode = 4;
		break;
	case 2:
		paramOne = paramOne;
		paramTwo = paramTwo;
		paramThree = paramThree;
		paramFour = paramFour;
		currentShapeCode = 2;
		break;
	case 3:
		paramOne = FVector(paramThree.X, paramThree.Y, paramThree.Z - step);
		paramTwo = FVector(paramTwo.X, paramTwo.Y + step, paramTwo.Z);
		paramThree = paramThree;
		paramFour = paramFour;
		currentShapeCode = 16;
		break;
	case 4:
		paramOne = FVector(paramTwo.X, paramTwo.Y - step, paramTwo.Z);
		paramTwo = paramTwo;
		paramThree = FVector(paramTwo.X, paramTwo.Y + step, paramTwo.Z);
		paramFour = FVector(paramTwo.X, paramTwo.Y + (step + step), paramTwo.Z);
		currentShapeCode = 1;
		break;
	case 5:
		paramOne = FVector(paramTwo.X, paramTwo.Y - step, paramTwo.Z);
		paramTwo = paramTwo;
		paramThree = FVector(paramTwo.X, paramTwo.Y + step, paramTwo.Z);
		paramFour = FVector(paramTwo.X, paramTwo.Y - step, paramTwo.Z - step);
		currentShapeCode = 9;
		break;
	case 6:
		paramOne = FVector(paramFour.X, paramFour.Y, paramFour.Z + step);
		paramTwo = FVector(paramThree.X, paramThree.Y, paramThree.Z - step);
		paramThree = paramThree;
		paramFour = paramFour;
		currentShapeCode = 10;
		break;
	case 7:
		paramOne = FVector(paramFour.X, paramFour.Y + (step + step), paramFour.Z);
		paramTwo = FVector(paramFour.X, paramFour.Y, paramFour.Z + step);
		paramThree = FVector(paramFour.X, paramFour.Y + step, paramFour.Z);
		paramFour = paramFour;
		currentShapeCode = 11;
		break;
	case 8:
		paramOne = FVector(paramTwo.X, paramTwo.Y, paramTwo.Z - step);
		paramTwo = paramTwo;
		paramThree = FVector(paramTwo.X, paramTwo.Y, paramTwo.Z + step);
		paramFour = FVector(paramTwo.X, paramTwo.Y - step, paramTwo.Z );
		currentShapeCode = 17;
		break;
	case 9:
		paramOne = FVector(paramTwo.X, paramTwo.Y, paramTwo.Z + step);
		paramTwo = paramTwo;
		paramThree = FVector(paramTwo.X, paramTwo.Y - step, paramTwo.Z + step);
		paramFour = FVector(paramTwo.X, paramTwo.Y , paramTwo.Z - step);
		currentShapeCode = 14;
		break;
	case 10:
		paramOne = FVector(paramThree.X, paramThree.Y, paramThree.Z + step);
		paramTwo = FVector(paramThree.X, paramThree.Y + step, paramThree.Z + step);
		paramThree = paramThree;
		paramFour = paramFour;
		currentShapeCode = 6;
		break;
	case 11:
		paramOne = FVector(paramFour.X, paramFour.Y + step, paramFour.Z);
		paramTwo = FVector(paramFour.X, paramFour.Y, paramFour.Z - step);
		paramThree = FVector(paramFour.X, paramFour.Y, paramFour.Z - (step + step));
		paramFour = paramFour;
		currentShapeCode = 12;
		break;
	case 12:
		paramOne = FVector(paramFour.X, paramFour.Y - (step + step), paramFour.Z);
		paramTwo = FVector(paramFour.X, paramFour.Y - step, paramFour.Z);
		paramThree = FVector(paramFour.X, paramFour.Y, paramFour.Z - step);
		paramFour = paramFour;
		currentShapeCode = 13;
		break;
	case 13: 
		paramOne = FVector(paramFour.X, paramFour.Y , paramFour.Z + (step + step));
		paramTwo = FVector(paramFour.X, paramFour.Y - step, paramFour.Z);
		paramThree = FVector(paramFour.X, paramFour.Y, paramFour.Z + step);
		paramFour = paramFour; 
		currentShapeCode = 7; 
		break;
	case 14: 
		paramOne = FVector(paramTwo.X, paramTwo.Y + step, paramTwo.Z + step);
		paramTwo = paramTwo;
		paramThree = FVector(paramTwo.X, paramTwo.Y - step, paramTwo.Z);
		paramFour = FVector(paramTwo.X, paramTwo.Y + step, paramTwo.Z);
		currentShapeCode = 15;
		break;
	case 15: 
		paramOne = FVector(paramTwo.X, paramTwo.Y, paramTwo.Z + step);
		paramTwo = paramTwo;
		paramThree = FVector(paramTwo.X, paramTwo.Y, paramTwo.Z - step);
		paramFour = FVector(paramTwo.X, paramTwo.Y + step, paramTwo.Z - step);
		currentShapeCode = 5;
		break;
	case 16:
		paramOne = FVector(paramThree.X, paramThree.Y - step, paramThree.Z + step);
		paramTwo = FVector(paramThree.X, paramThree.Y, paramThree.Z + step);
		paramThree = paramThree;
		paramFour = paramFour;
		currentShapeCode = 3;
		break;
	case 17: 
		paramOne = FVector(paramTwo.X, paramTwo.Y + step, paramTwo.Z);
		paramTwo = paramTwo;
		paramThree = FVector(paramTwo.X, paramTwo.Y, paramTwo.Z + step);
		paramFour = FVector(paramTwo.X, paramTwo.Y - step, paramTwo.Z);
		currentShapeCode = 18;
		break;
	case 18:
		paramOne = FVector(paramTwo.X, paramTwo.Y, paramTwo.Z - step);
		paramTwo = paramTwo;
		paramThree = FVector(paramTwo.X, paramTwo.Y, paramTwo.Z + step);
		paramFour = FVector(paramTwo.X, paramTwo.Y + step, paramTwo.Z);
		currentShapeCode = 19;
		break;
	case 19:
		paramOne = FVector(paramTwo.X, paramTwo.Y, paramTwo.Z - step);
		paramTwo = paramTwo;
		paramThree = FVector(paramTwo.X, paramTwo.Y - step, paramTwo.Z);
		paramFour = FVector(paramTwo.X, paramTwo.Y + step, paramTwo.Z);
		currentShapeCode = 8;
		break;
	//end of adapted code
	default:
		paramOne = FVector(100.0f, 100.0f, 500.0f);
		paramTwo = FVector(100.0f, 120.0f, 500.0f);
		paramThree = FVector(100.0f, 100.0f, 520.0f);
		paramFour = FVector(100.0f, 120.0f, 520.0f);
		break;
	}
	cubeA->SetParameters(paramOne);
	cubeB->SetParameters(paramTwo);
	cubeC->SetParameters(paramThree);
	cubeD->SetParameters(paramFour);

	
}
void AShape::RemoveTetrisShape() 
{
	for (auto i : tetrisShapes) {
		i->Destroy();
	}
}

ACube* AShape::FindLowestCube()
{
	float lowestDistanceSqr = (float)1e10;

	for (TObjectIterator<ACube> act; act; ++act)
	{
		if (act->GetWorld() != this->GetWorld())
		{
			continue;
		}
		if (act->GetMoveable()) {
			FVector distanceToTarget = (act->GetActorLocation() - floorMinHeight);

			if (distanceToTarget.SizeSquared() < lowestDistanceSqr)
			{
				lowestDistanceSqr = distanceToTarget.SizeSquared();
				lowestCube = *act;
			}
		}
	}
	return lowestCube;
}

