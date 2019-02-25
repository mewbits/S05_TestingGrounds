// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrollingGuard.h" // TODO, remove later
#include "AIController.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (!Cast<APatrollingGuard>(OwnerComp.GetAIOwner()->GetPawn())) return EBTNodeResult::Failed;

	SetupWaypointArray(OwnerComp);

	if (!Waypoints[Index] || Waypoints[Index] == Cast<AActor>(ControlledPawn)) return EBTNodeResult::Failed;
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
	UE_LOG(LogTemp, Warning, TEXT("Index number : %i percent %i"), Index++, Waypoints.Num());
	Index = (Index++) % Waypoints.Num();
	UE_LOG(LogTemp, Warning, TEXT("is %i"), Index);
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index);
}