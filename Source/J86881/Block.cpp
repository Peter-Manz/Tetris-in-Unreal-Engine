
#include "Block.h"

// This Class is not used, couldn't Figure out how to remove from UnrealEngine
ABlock::ABlock()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABlock::BeginPlay()
{
	Super::BeginPlay();
}

void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABlock::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
