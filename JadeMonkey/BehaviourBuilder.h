#pragma once
#include "CondPlayerProximityBehaviourNode.h"
#include "PrioritySelectorBehaviourNode.h"
#include "BehaviourComponent.h"
#include "SequenceSelectorBehaviourNode.h"
#include "Enums.h"
#include "AStarPathfindingComponent.h"
#include "ActionMoveToPlayerBehaviourNode.h"
#include "FireboltSkillComponent.h"


class BehaviourBuilder
{
public:
	static BehaviourTreeNode* BuildBasicEnemy(BehaviourComponent* behaviourComponent, GameEntity* player, AStarPathfindingComponent* pathfinding)
	{
		PrioritySelectorBehaviourNode* root = new PrioritySelectorBehaviourNode(behaviourComponent);
		SequenceSelectorBehaviourNode* aggro = new SequenceSelectorBehaviourNode(behaviourComponent);
		CondPlayerProximityBehaviourNode* proximityBehaviour  = new CondPlayerProximityBehaviourNode(behaviourComponent, player, 150);
		ActionMoveToPlayerBehaviourNode* actionMoveToPlayer = new ActionMoveToPlayerBehaviourNode(behaviourComponent, player, pathfinding);

		root->AddChild(aggro);
		aggro->AddChild(proximityBehaviour);
		aggro->AddChild(actionMoveToPlayer);

		return root;
	}

	static BehaviourTreeNode* BuildRangedEnemy(BehaviourComponent* behaviourComponent, GameEntity* player, AStarPathfindingComponent* pathfinding, FireboltSkillComponent* firebolt)
	{
	}
};