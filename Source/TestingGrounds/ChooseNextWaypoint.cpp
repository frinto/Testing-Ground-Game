// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingGuard.h" // TODO remove coupling


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//TODO protect against empty patrol routes

	// Get the patrol points
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	auto PatrolledPoints = PatrollingGuard->PatrolPointsCPP;

	//set next waypoint
	auto Blackboardcomp = OwnerComp.GetBlackboardComponent();
	auto Index = Blackboardcomp->GetValueAsInt(IndexKey.SelectedKeyName);
	Blackboardcomp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolledPoints[Index]);

	//cycle the index

	auto NextIndex = (Index + 1) % PatrolledPoints.Num();
	Blackboardcomp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
	
	return EBTNodeResult::Succeeded;

}

