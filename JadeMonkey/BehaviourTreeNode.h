#pragma once
#include <vector>
#include "GameEntity.h"
#include "Enums.h"

class BehaviourComponent;

using namespace std;

class BehaviourTreeNode
{
public:
	BehaviourTreeNode(BehaviourComponent* behaviourComponent, BehaviourTreeNodeType type);
	BehaviourTreeNode(BehaviourComponent* behaviourComponent, string name, BehaviourTreeNodeType type);
	virtual bool Update(void) = 0;
	void AddChild(BehaviourTreeNode* node);
	BehaviourTreeNodeState GetState(void);
	void SetState(BehaviourTreeNodeState state);
	BehaviourTreeNodeType GetType(void);
	vector<BehaviourTreeNode*> GetChildren(void);

protected:
	vector<BehaviourTreeNode*> _children;
	BehaviourTreeNodeState _state;
	BehaviourTreeNodeType _type;
	BehaviourTreeNode* _runningNode;
	BehaviourComponent* _behaviourComponent;
	string _name;
};