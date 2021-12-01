#include "Animator.h"

Node::Node(float NodeStart, Vec3f startPosition, Vec3f startRotoation) :
mNodeStart(NodeStart),
mNodeEnd(0.f),
mStartPosition(startPosition),
deltaTime(0.f),
NodeLenght(0.f)
{
}

/*
Animator::Animator()
{
	timeNot = 5;
}
*/