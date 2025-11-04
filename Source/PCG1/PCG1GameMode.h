// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PCG1GameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class APCG1GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	APCG1GameMode();
};



