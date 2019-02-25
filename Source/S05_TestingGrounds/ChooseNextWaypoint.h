// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChooseNextWaypoint.generated.h"

class UBlackboardComponent;
/**
 * 
 */
UCLASS()
class S05_TESTINGGROUNDS_API UChooseNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector WaypointKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector IndexKey;

private:

	UPROPERTY()
	TArray <AActor *> Waypoints;

	int32 Index;

	APawn * ControlledPawn;

	UBlackboardComponent * BlackboardComp;

	void SetupWaypointArray(UBehaviorTreeComponent& OwnerComp);

	void SetWaypoint();

	void CycleIndex();
	
};
