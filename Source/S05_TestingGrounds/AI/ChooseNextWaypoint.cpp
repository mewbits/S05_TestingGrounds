// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "PatrolRoute.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	BlackboardComp = OwnerComp.GetBlackboardComponent();
	ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (!ControlledPawn) return EBTNodeResult::Failed;

	PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();


	if (!PatrolRoute) return EBTNodeResult::Failed;
	
	SetupWaypointArray(OwnerComp);
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("A Guard is missing Patrol Points!"));
		return EBTNodeResult::Failed;
	}
	
	SetWaypoint();

	CycleIndex();

	return EBTNodeResult::Succeeded;
}

void UChooseNextWaypoint::SetupWaypointArray(UBehaviorTreeComponent& OwnerComp)
{
	Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	
	PatrolPoints = PatrolRoute->GetPatrolPoints();
}

void UChooseNextWaypoint::SetWaypoint()
{
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
}

void UChooseNextWaypoint::CycleIndex()
{
	int32 NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
}