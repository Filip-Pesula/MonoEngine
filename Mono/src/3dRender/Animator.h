#pragma once
#include <chrono>
#include <vector>
#include "GR_Object.h"
class Animator {
	std::vector<Object*> objects;
	Animator();
	void addAnimaton(Object* obj)
	{

	}
};
class Node
{
public:
	float mNodeStart;
	float mNodeEnd;

	float deltaTime;
	float NodeLenght;
	Vec3f mStartPosition;
	Vec3f mEndPosition;
	Node(float NodeStart, Vec3f startPosition, Vec3f startRotoation);
	void addPosition(float timeS, Vec3f end)
	{
		NodeLenght = timeS;
		mNodeEnd = timeS + mNodeStart;
		mEndPosition = end;
	}
	void addRotation(float timeS, Vec3f end)
	{

	}
	void calcualte(float time, Object* obj)
	{
		if (time < mNodeStart || time > mNodeEnd)
		{
			return;
		}
		deltaTime = time - mNodeStart;
		if (deltaTime < 0)
		{
			deltaTime = 0;
		}
		float deltaframe = deltaTime / NodeLenght;
		Vec3f keyframe = mStartPosition * deltaframe + mEndPosition * (1 - deltaframe);
		obj->Position = keyframe;
	}
};
class Animate {
public:
	Object* object;
	std::chrono::steady_clock::time_point startFrame;
	std::chrono::steady_clock::time_point LastItteration;
	float deltaTime;
	float AnimateLenght;
	Vec3f mStartPosition;
	Vec3f mEndPosition;
	std::vector<Node> Keyframes;
	Animate() {};
	Animate(Object* obj, Vec3f startPosition, Vec3f startRotoation)
	{
		object = obj;
		mStartPosition = startPosition;
		startFrame = std::chrono::high_resolution_clock::now();
	}
	void addPosition(float timeS, Vec3f end)
	{
		float lastNodeTime;
		Vec3f lastPosition;
		if (Keyframes.size() == 0)
		{
			lastNodeTime = 0;
			lastPosition = mStartPosition;
		}
		else
		{
			lastNodeTime = Keyframes.back().mNodeEnd;
			lastPosition = Keyframes.back().mEndPosition;
		}
		Keyframes.push_back(Node(lastNodeTime, lastPosition, Vec3f(0,0,0)));
		Keyframes.back().addPosition(timeS, end);
		AnimateLenght = timeS + lastNodeTime;
		mEndPosition = end;
	}
	void addRotation(float timeS, Vec3f end)
	{

	}
	void calcualte()
	{
		std::chrono::steady_clock::time_point timeNow;
		timeNow = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = timeNow - startFrame;
		deltaTime = duration.count();
		for (Node node : Keyframes)
		{
			node.calcualte(deltaTime, object);
		}
		if (deltaTime > AnimateLenght)
		{
			startFrame = std::chrono::high_resolution_clock::now();
		}
	}
};
