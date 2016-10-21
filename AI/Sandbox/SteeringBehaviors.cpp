#include "SteeringBehaviors.h"
#include <chrono>

Vector2 SteeringBehaviors::Seek(const Vector2 & target)
{
	Vector2 Vel = target - m_agent->pos;
	Vel.Truncate(m_agent->maxVel);

	return Vel;
}

Vector2 SteeringBehaviors::Flee(const Vector2 & target)
{
	//return -Seek();
	//escape always at max vel
	Vector2 Vel = target - m_agent->pos;
	Vel.Normalize();
	Vel *= -m_agent->maxVel;

	return Vel;
}

Vector2 SteeringBehaviors::Arrive(const Vector2 & target)
{
	Vector2 Vel = Vector2();

	Vector2 vDist = target - m_agent->pos;
	float dist = vDist.Length();

	if(dist <= m_agent->arriveLimit)
	{
		dist /= m_agent->arriveLimit;	
		vDist.Normalize();
		Vel = vDist * m_agent->maxVel * dist;
	}
	return Vel;
}

Vector2 SteeringBehaviors::Pursuit(const Agent * target)
{
	//distance beetween agent and target 
	float dist = (target->pos - m_agent->pos).Length();

	float time = (dist / m_agent->maxVel) + target->currVel.Length();
	Vector2 targetPos = target->pos + target->currVel * time;

	return targetPos;
}

Vector2 SteeringBehaviors::Evade(const Agent * target)
{
	Vector2 targetPos = Pursuit(target);
	targetPos.Set(-targetPos.x, -targetPos.y);
	return targetPos;
}


Vector2 RandInCircum(Vector2& center, float radius)
{
	int rand = std::rand() % 360;
	Vector2 circumPos = center;
	circumPos.x += cos(rand) * radius;
	circumPos.y += sin(rand) * radius;
	return circumPos - center;
}

Vector2 SteeringBehaviors::Wander()
{
	//std::chrono::high_resolution_clock::now();
	//Vector2 targetpos = RandInCircum(m_agent->pos + m_agent->currVel,5);
	//Vector2 targetpos = m_agent->pos + m_agent->currVel;
	return Vector2();
}
