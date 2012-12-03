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
	BasicEnemy
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