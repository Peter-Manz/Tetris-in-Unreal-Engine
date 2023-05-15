
#include "TetrisManager.h"
#include "Cube.h"

ATetrisManager::ATetrisManager()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-500.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	OurVisibleComponent->SetupAttachment(RootComponent);

	FString controls, moveLeft, moveRight, moveDown, rotate;
	controls = FString(ANSI_TO_TCHAR("Game Controls"));
	moveLeft = FString(ANSI_TO_TCHAR("Move Left: A or Left-Arrow"));
	moveRight = FString(ANSI_TO_TCHAR("Move Right: D or Right-Arrow"));
	moveDown = FString(ANSI_TO_TCHAR("Move Down: S or Down-Arrow"));
	rotate = FString(ANSI_TO_TCHAR("Rotate: R "));

	Controls = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Controls"));
	Controls->SetRelativeLocation(FVector(200.f, -170.f, 50.f));
	Controls->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	Controls->SetWorldSize(12.0f);
	Controls->SetupAttachment(OurCamera);
	Controls->SetText(FText::FromString(controls));

	MoveLeftLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("MoveLeftLabel"));
	MoveLeftLabel->SetRelativeLocation(FVector(200.f, -170.f, 40.f));
	MoveLeftLabel->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	MoveLeftLabel->SetWorldSize(9.0f);
	MoveLeftLabel->SetupAttachment(OurCamera);
	MoveLeftLabel->SetText(FText::FromString(moveLeft));

	MoveRightLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("MoveRightLabel"));
	MoveRightLabel->SetRelativeLocation(FVector(200.f, -170.f, 30.f));
	MoveRightLabel->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	MoveRightLabel->SetWorldSize(9.0f);
	MoveRightLabel->SetupAttachment(OurCamera);
	MoveRightLabel->SetText(FText::FromString(moveRight));


	MoveDownLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("MoveDownLabel"));
	MoveDownLabel->SetRelativeLocation(FVector(200.f, -170.f, 20.f));
	MoveDownLabel->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	MoveDownLabel->SetWorldSize(9.0f);
	MoveDownLabel->SetupAttachment(OurCamera);
	MoveDownLabel->SetText(FText::FromString(moveDown));

	RotateLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("RotateLabel"));
	RotateLabel->SetRelativeLocation(FVector(200.f, -170.f, 10.f));
	RotateLabel->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	RotateLabel->SetWorldSize(9.0f);
	RotateLabel->SetupAttachment(OurCamera);
	RotateLabel->SetText(FText::FromString(rotate));

	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText"));
	ScoreText->SetRelativeLocation(FVector(200.f, 50.f, 50.f));
	ScoreText->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	ScoreText->SetWorldSize(15.0f);
	ScoreText->SetupAttachment(OurCamera);

	CountdownTime = 60.0f;
	currentDeltaTime = 1.0f;
}

void ATetrisManager::BeginPlay()
{
	Super::BeginPlay();
	SendTetrisObject();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ATetrisManager::AdvanceTimer, 1.0f, true);
}

void ATetrisManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	currentDeltaTime -= (1.0f * DeltaTime);
	UpdateTimerDisplay();
}

void ATetrisManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("Move_Y_Right", IE_Pressed, this, &ATetrisManager::Move_Y_Right);
	InputComponent->BindAction("Move_Y_Left", IE_Pressed, this, &ATetrisManager::Move_Y_Left);
	InputComponent->BindAction("MoveDown", IE_Pressed, this, &ATetrisManager::MoveDown);
	InputComponent->BindAction("Rotate", IE_Pressed, this, &ATetrisManager::Rotate);
}
void ATetrisManager::Rotate() 
{
	lastShape->Rotate();
}

void ATetrisManager::SendTetrisObject()
{
	lastShape = (AShape*)GWorld->SpawnActor(AShape::StaticClass());
}
void ATetrisManager::MoveDown() 
{
	lastShape->MoveDown();
}

void ATetrisManager::Move_Y_Right()
{
	lastShape->Move_Y_Right();	
}
void ATetrisManager::Move_Y_Left() 
{
	lastShape->Move_Y_Left();
}

void ATetrisManager::RemoveTetrisShape() 
{
	lastShape->RemoveTetrisShape();
}

//Start of Adapted Code from (UnrealEngine, 2023)

void ATetrisManager::UpdateTimerDisplay() 
{
	ScoreText->SetText(FString::FromInt(FMath::Max(int(CountdownTime), 0)));
}

void ATetrisManager::AdvanceTimer()
{

	if (--CountdownTime <= 0)
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		ResetTimer();
		//SendTetrisObject();
	}
}

void ATetrisManager::ResetTimer()
{
	ScoreText->SetText(TEXT("Round Over"));
	CountdownTime = 60; 
	//RemoveTetrisShape();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ATetrisManager::AdvanceTimer, 1.0f, true);
}
// end of adapted code
