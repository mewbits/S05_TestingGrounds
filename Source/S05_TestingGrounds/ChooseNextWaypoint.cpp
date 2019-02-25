// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrollingGuard.h" // TODO, remove coupling later
#include "AIController.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (!Cast<APatrollingGuard>(OwnerComp.GetAIOwner()->GetPawn())) return EBTNodeResult::Failed;
	SetupWaypointArray(OwnerComp);

	if (!Waypoints[Index]) return EBTNodeResult::Failed;
	SetWaypoint();

	CycleIndex();

	return EBTNodeResult::Succeeded;
}

void UChooseNextWaypoint::SetupWaypointArray(UBehaviorTreeComponent& OwnerComp)
{
	Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	Waypoints = Cast<APatrollingGuard>(ControlledPawn)->PatrolPoints;
}

void UChooseNextWaypoint::SetWaypoint()
{
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, Waypoints[Index]);
}

void UChooseNextWaypoint::CycleIndex()
{
	int32 NextIndex = (Index + 1) % Waypoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
}