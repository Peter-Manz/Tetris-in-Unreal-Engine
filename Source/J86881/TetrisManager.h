
#pragma once

#include "Cube.h"
#include "Shape.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TetrisManager.generated.h"

UCLASS()
class J86881_API ATetrisManager : public APawn
{
	GENERATED_BODY()

public:
	ATetrisManager();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;

	UPROPERTY(EditAnywhere)
	UCameraComponent* OurCamera;

	UTextRenderComponent* CountdownText;

	void MoveDown();
	void Move_Y_Right();
	void Move_Y_Left();
	void Rotate();
	void SendTetrisObject();
	void RemoveTetrisShape();

	AShape* lastShape; 

	//Start of adapted Code from (UnrealEngine, 2023)
	float CountdownTime;
	float currentDeltaTime;
	void UpdateTimerDisplay();
	void AdvanceTimer();
	void ResetTimer();
	FTimerHandle CountdownTimerHandle;
	//end of adapted Code 

	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* ScoreText;

	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* Controls;

	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* MoveLeftLabel;

	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* MoveRightLabel;

	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* MoveDownLabel;

	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* RotateLabel;

};
