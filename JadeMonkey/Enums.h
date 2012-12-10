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
	ChaseTarget,
	RunningAway,
	Idle
};

enum Behaviour
{
	BasicEnemy,
	RangedEnemy,
	HealerEnemy
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
	Heal,
	Nothing
};

enum EntityType
{
	HumanPlayer,
	Enemy,
	Projectile
};
