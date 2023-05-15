
#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cube.generated.h"

UCLASS()
class J86881_API ACube : public AActor
{
	GENERATED_BODY()

private:
	UStaticMeshComponent* visualComponent;
public:	
	ACube();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	//Start of adapted Code from (Unrealcpp, 2018)
	UPROPERTY(EditAnywhere)
	class UMaterial* RedMaterial;

	UPROPERTY(EditAnywhere)
	class UMaterial* GreenMaterial;

	UPROPERTY(EditAnywhere)
	class UMaterial* BlueMaterial;

	UPROPERTY(EditAnywhere)
	class UMaterial* YellowMaterial;

	UPROPERTY(EditAnywhere)
	class UMaterial* colorMaterials[3];
	//end of adapted Code 

	void BlowUp();

	void SetParameters(FVector& position);
	void AssignColors();
	void SetShapeColor(int& randomNum);

	float currentDeltaTime;
	float floorMinHeight;
	float leftWall;
	float rightWall;
	void MoveAxis(FVector& currentLoc);

	bool CanMoveLeft();
	bool CanMoveRight();

	void SetMoveableFalse();
	bool GetMoveable();
	bool moveable;
	bool CheckForNextMove();
	float GetFloorMinHeight();

};
