#pragma once
#include "CondPlayerProximityBehaviourNode.h"
#include "PrioritySelectorBehaviourNode.h"
#include "BehaviourComponent.h"
#include "SequenceSelectorBehaviourNode.h"
#include "Enums.h"
#include "AStarPathfindingComponent.h"
#include "ActionMoveToPlayerBehaviourNode.h"
#include "FireboltSkillComponent.h"
#include "ActionShootFireboltBehaviourNode.h"


class BehaviourBuilder
{
public:
	static BehaviourTreeNode* BuildBasicEnemy(BehaviourComponent* behaviourComponent, GameEntity* player, AStarPathfindingComponent* pathfinding)
	{
		PrioritySelectorBehaviourNode* root = new PrioritySelectorBehaviourNode(behaviourComponent, "root");
		SequenceSelectorBehaviourNode* aggro = new SequenceSelectorBehaviourNode(behaviourComponent, "aggro");
		CondPlayerProximityBehaviourNode* proximityBehaviour  = new CondPlayerProximityBehaviourNode(behaviourComponent, player, 300, "aggro distance");
		ActionMoveToPlayerBehaviourNode* actionMoveToPlayer = new ActionMoveToPlayerBehaviourNode(behaviourComponent, player, pathfinding, "move to player");

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
		CondPlayerProximityBehaviourNode* proximityBehaviourAggro  = new CondPlayerProximityBehaviourNode(behaviourComponent, player, 400, "aggro distance");
		CondPlayerProximityBehaviourNode* proximityBehaviourFireball  = new CondPlayerProximityBehaviourNode(behaviourComponent, player, 300, "attack distance");
		ActionMoveToPlayerBehaviourNode* actionMoveToPlayer = new ActionMoveToPlayerBehaviourNode(behaviourComponent, player, pathfinding, "move to player");
		ActionShootFireboltBehaviourNode* actionShootFireball = new ActionShootFireboltBehaviourNode(behaviourComponent, player, firebolt, "attack player");

		root->AddChild(attack);
		attack->AddChild(proximityBehaviourFireball);
		attack->AddChild(actionShootFireball);
		root->AddChild(aggro);
		aggro->AddChild(proximityBehaviourAggro);
		aggro->AddChild(actionMoveToPlayer);

		return root;
	}
};