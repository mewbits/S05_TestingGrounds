// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRoute.generated.h"

/**
 * A Route card to help AI choose their next waypoint. Pick actors from the level for your patrol points
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class S05_TESTINGGROUNDS_API UPatrolRoute : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditInstanceOnly, Category = "Patrol Route")
	TArray <AActor *> PatrolPoints;

	UFUNCTION(BlueprintPure, Category = "Patrol Route")
	TArray <AActor *> GetPatrolPoints() const;
};
