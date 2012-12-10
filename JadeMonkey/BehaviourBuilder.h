#pragma once
#include "CondEntityProximityBehaviourNode.h"
#include "PrioritySelectorBehaviourNode.h"
#include "BehaviourComponent.h"
#include "SequenceSelectorBehaviourNode.h"
#include "Enums.h"
#include "AStarPathfindingComponent.h"
#include "ActionMoveToPlayerBehaviourNode.h"
#include "FireboltSkillComponent.h"
#include "ActionShootFireboltBehaviourNode.h"
#include "HealSkillComponent.h"
#include "ActionHealAllyBehaviourNode.h"
#include "CondTargetProximityBehaviourNode.h"
#include "CondAllyHealthLowBehaviourNode.h"
#include "ActionMoveAwayBehaviourNode.h"
#include "ActionStopMovingBehaviourNode.h"
#include "ActionMoveToTargetBehaviourNode.h"
#include "CondHealthMonitorBehaviourNode.h"


class BehaviourBuilder
{
public:
	static BehaviourTreeNode* BuildBasicEnemy(BehaviourComponent* behaviourComponent, GameEntity* player, AStarPathfindingComponent* pathfinding)
	{
		PrioritySelectorBehaviourNode* root = new PrioritySelectorBehaviourNode(
			behaviourComponent, 
			"root");
		SequenceSelectorBehaviourNode* aggro = new SequenceSelectorBehaviourNode(
			behaviourComponent, 
			"aggro");
		SequenceSelectorBehaviourNode* runAway = new SequenceSelectorBehaviourNode(
			behaviourComponent,
			"runAway");
		SequenceSelectorBehaviourNode* idle = new SequenceSelectorBehaviourNode(
			behaviourComponent,
			"idle");
		CondEntityProximityBehaviourNode* runAwayProximity = new CondEntityProximityBehaviourNode(
			behaviourComponent,
			player,
			150,
			"runAwayProximity");
		CondEntityProximityBehaviourNode* proximityBehaviour  = new CondEntityProximityBehaviourNode(
			behaviourComponent, 
			player, 
			300, 
			"aggro distance");
		ActionMoveToPlayerBehaviourNode* actionMoveToPlayer = new ActionMoveToPlayerBehaviourNode(
			behaviourComponent, 
			player, 
			pathfinding, 
			"move to player");
		ActionStopMovingBehaviourNode* actionStopMoving = new ActionStopMovingBehaviourNode(
			behaviourComponent,
			pathfinding);

		ActionMoveAwayBehaviourNode* moveAway = new ActionMoveAwayBehaviourNode(
			behaviourComponent, 
			player, 
			pathfinding);
		CondHealthMonitorBehaviourNode* healthMonitor = new CondHealthMonitorBehaviourNode(
			behaviourComponent,
			75);

		root->AddChild(runAway);
		runAway->AddChild(healthMonitor);
		runAway->AddChild(runAwayProximity);
		runAway->AddChild(moveAway);

		root->AddChild(idle);
		idle->AddChild(healthMonitor);
		idle->AddChild(actionStopMoving);

		root->AddChild(aggro);
		aggro->AddChild(proximityBehaviour);
		aggro->AddChild(actionMoveToPlayer);

		return root;
	}

	static BehaviourTreeNode* BuildRangedEnemy(BehaviourComponent* behaviourComponent, GameEntity* player, AStarPathfindingComponent* pathfinding, FireboltSkillComponent* firebolt)
	{
		PrioritySelectorBehaviourNode* root = new PrioritySelectorBehaviourNode(behaviourComponent, "root");
		SequenceSelectorBehaviourNode* aggro = new SequenceSelectorBehaviourNode(behaviourComponent, "aggro");
		SequenceSelectorBehaviourNode* attack = new SequenceSelectorBehaviourNode(behaviourComponent, "attack");

		SequenceSelectorBehaviourNode* selectorMoveAway = new SequenceSelectorBehaviourNode(behaviourComponent, "moveaway");

		CondEntityProximityBehaviourNode* proximityBehaviourAggro  = new CondEntityProximityBehaviourNode(
			behaviourComponent, 
			player, 
			400, 
			"aggro distance");

		CondEntityProximityBehaviourNode* proximityBehaviourFireball  = new CondEntityProximityBehaviourNode(
			behaviourComponent, 
			player, 
			300,
			"attack distance");

		CondEntityProximityBehaviourNode* playerProximity = new CondEntityProximityBehaviourNode(
			behaviourComponent, 
			player, 
			100, 
			"playerProximity");
		
		ActionMoveToPlayerBehaviourNode* actionMoveToPlayer = new ActionMoveToPlayerBehaviourNode(
			behaviourComponent, 
			player, 
			pathfinding, 
			"move to player");

		ActionShootFireboltBehaviourNode* actionShootFireball = new ActionShootFireboltBehaviourNode(
			behaviourComponent, 
			player, 
			firebolt, 
			"attack player");

		ActionStopMovingBehaviourNode* actionStopMoving = new ActionStopMovingBehaviourNode(
			behaviourComponent,
			pathfinding);

		ActionMoveAwayBehaviourNode* moveAway = new ActionMoveAwayBehaviourNode(
			behaviourComponent, 
			player, 
			pathfinding);

		root->AddChild(selectorMoveAway);
		selectorMoveAway->AddChild(playerProximity);
		selectorMoveAway->AddChild(moveAway);
		root->AddChild(attack);
		attack->AddChild(proximityBehaviourFireball);
		attack->AddChild(actionStopMoving);
		attack->AddChild(actionShootFireball);
		root->AddChild(aggro);
		aggro->AddChild(proximityBehaviourAggro);
		aggro->AddChild(actionMoveToPlayer);

		return root;
	}

	static BehaviourTreeNode* BuildHealerEnemy(BehaviourComponent* behaviourComponent, GameEntity* player, AStarPathfindingComponent* pathfinding, HealSkillComponent* healSkill)
	{
		PrioritySelectorBehaviourNode* root = new PrioritySelectorBehaviourNode(behaviourComponent, "root");
		SequenceSelectorBehaviourNode* runAway = new SequenceSelectorBehaviourNode(behaviourComponent, "runAway");
		SequenceSelectorBehaviourNode* heal = new SequenceSelectorBehaviourNode(behaviourComponent, "heal");
		SequenceSelectorBehaviourNode* moveToAlly = new SequenceSelectorBehaviourNode(behaviourComponent, "moveToAlly");
		
		CondAllyHealthLowBehaviourNode* allyHealthLow = new CondAllyHealthLowBehaviourNode(
			behaviourComponent, 
			75);
		CondEntityProximityBehaviourNode* playerProximity = new CondEntityProximityBehaviourNode(
			behaviourComponent, 
			player, 
			100, 
			"playerProximity");
		CondTargetProximityBehaviourNode* targetProximity = new CondTargetProximityBehaviourNode(
			behaviourComponent,
			healSkill->GetRange());
		ActionHealAllyBehaviourNode* healAlly = new ActionHealAllyBehaviourNode(
			behaviourComponent, 
			healSkill,
			"heal ally");
		ActionMoveAwayBehaviourNode* moveAway = new ActionMoveAwayBehaviourNode(
			behaviourComponent, 
			player, 
			pathfinding);
		ActionMoveToTargetBehaviourNode* moveToTarget = new ActionMoveToTargetBehaviourNode(
			behaviourComponent,
			pathfinding);
	
		ActionStopMovingBehaviourNode* actionStopMoving = new ActionStopMovingBehaviourNode(
			behaviourComponent,
			pathfinding);

		root->AddChild(runAway);
		runAway->AddChild(playerProximity);
		runAway->AddChild(moveAway);
		
		root->AddChild(heal);
		heal->AddChild(allyHealthLow);
		heal->AddChild(targetProximity);
		heal->AddChild(actionStopMoving);
		heal->AddChild(healAlly);

		root->AddChild(moveToAlly);
		moveToAlly->AddChild(moveToTarget);
		//CondTargetProximityBehaviourNode* targetProximity = new CondTargetProximityBehaviourNode(behaviourComponent, healSkill->GetRange());

		return root;
	}
};