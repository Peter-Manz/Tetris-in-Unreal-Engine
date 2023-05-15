
#pragma once

#include "Engine.h"
#include "Cube.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shape.generated.h"


UCLASS()
class J86881_API AShape : public AActor
{
	GENERATED_BODY()
	
public:	
	AShape();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void MoveDown();
	void Move_Y_Right();
	void Move_Y_Left();
	void Rotate();

	void SendTetrisObject();
	void RemoveTetrisShape();

	TArray<ACube*> tetrisShapes;
	ACube* cubeA;
	ACube* cubeB;
	ACube* cubeC;
	ACube* cubeD;
	ACube* lowestCube;

	float step;
	int currentShapeCode;

	ACube* FindLowestCube();
	float floorMinHeight;
	FVector paramOne, paramTwo, paramThree, paramFour;

	bool CheckLeftMove();
	bool CheckRightMove();
	bool CheckDownMove();
	float currentDeltaTime;

};
