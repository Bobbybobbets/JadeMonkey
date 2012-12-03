#pragma once

enum AStarNeighbourDirection
{
	Top,
	TopRight,
	Right,
	DownRight,
	Down,
	DownLeft,
	Left,
	TopLeft
};

enum BehaviourState
{
	Attack,
	Patrol,
	Move,
	ChasePlayer,
	Idle
};

enum Behaviour
{
	BasicEnemy,
	RangedEnemy
};

enum BehaviourTreeNodeState
{
	Ready,
	Running
};

enum BehaviourTreeNodeType
{
	PrioritySelector,
	ConcurrentSelector,
	SequenceSelector,
	Condition,
	Action
};

enum CollisionGroup
{
	Player,
	Enemies
};

enum CollisionConsequence
{
	MinusSize,
	MinusLife,
	Kill,
	Nothing
};

enum EntityType
{
	HumanPlayer,
	Enemy,
	Projectile
};
