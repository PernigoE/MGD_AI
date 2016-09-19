#ifndef STEERINGBEHAVIORS_H
#define STEERINGBEHAVIORS_H

#include "Vector2.h"
#include <vector>

class Agent;
class Place;

class SteeringBehaviors
{

public:
	SteeringBehaviors(Agent* bp);
	~SteeringBehaviors();

	Vector2 GetTarget()const{ return m_target; }
	
	void SetTarget(const Vector2 target);
	void SetEvader(Agent* evader);

	void SetNeighbors(std::vector<Agent*> nNeighbors) { m_neighbors = nNeighbors; }
	void SetObstacles(std::vector<Place*> nObstacles) { m_obstacles = nObstacles; }

	
	Vector2 GetForce()const { return m_steering; }

	void Calculate();

	inline void SeekOn()				{ m_iFlags |= seek; }
	inline void ArriveOn()				{ m_iFlags |= arrive; }
	inline void FleeOn()				{ m_iFlags |= flee; }
	inline void PursuitOn()				{ m_iFlags |= pursuit; }
	inline void EvadeOn()				{ m_iFlags |= evade; }
	inline void WanderOn()				{ m_iFlags |= wander; }
	inline void ObstacleAvoidanceOn()	{ m_iFlags |= obstaclesAvoidance; }
	inline void WallAvoidanceOn()		{ m_iFlags |= wallAvoidance; }
	inline void InterposeOn()			{ m_iFlags |= interpose; }
	inline void SeparationOn()			{ m_iFlags |= separation; }
	inline void CohesionOn()			{ m_iFlags |= cohesion; }
	inline void AlignmentOn()			{ m_iFlags |= alignment; }

	inline void SeekOff()				{ if(SeekIsOn()) m_iFlags ^= seek; }
	inline void ArriveOff()				{ if(ArriveIsOn()) m_iFlags ^= arrive; }
	inline void FleeOff()				{ if(FleeIsOn()) m_iFlags ^= flee; }
	inline void PursuitOff()			{ if(PursuitIsOn()) m_iFlags ^= pursuit; }
	inline void EvadeOff()				{ if(EvadeIsOn()) m_iFlags ^= evade; }
	inline void WanderOff()				{ if(WanderIsOn()) m_iFlags ^= wander; }
	inline void ObstacleAvoidanceOff()	{ if(ObstacleAvoidanceIsOn()) m_iFlags ^= obstaclesAvoidance; }
	inline void WallAvoidanceOff()		{ if(WallAvoidanceIsOn()) m_iFlags ^= wallAvoidance; }
	inline void InterposeOff()			{ if(InterposeIsOn()) m_iFlags ^= interpose; }
	inline void SeparationOff()			{ if(SeparationIsOn()) m_iFlags ^= separation; }
	inline void CohesionOff()			{ if(CohesionIsOn()) m_iFlags ^= cohesion; }
	inline void AlignmentOff()			{ if(AlignmentIsOn()) m_iFlags ^= alignment; }

	inline bool SeekIsOn()				{ return On(seek); }
	inline bool ArriveIsOn()			{ return On(arrive); }
	inline bool FleeIsOn()				{ return On(flee); }
	inline bool PursuitIsOn()			{ return On(pursuit); }
	inline bool EvadeIsOn()				{ return On(evade); }
	inline bool WanderIsOn()			{ return On(wander); }
	inline bool ObstacleAvoidanceIsOn()	{ return On(obstaclesAvoidance); }
	inline bool WallAvoidanceIsOn()		{ return On(wallAvoidance); }
	inline bool InterposeIsOn()			{ return On(interpose); }
	inline bool SeparationIsOn()		{ return On(separation); }
	inline bool CohesionIsOn()			{ return On(cohesion); }
	inline bool AlignmentIsOn()			{ return On(alignment); }


private:
	
	Agent*				m_agent;

	std::vector<Agent*>		m_neighbors;
	std::vector<Place*>		m_obstacles;

	Vector2			m_steering;
	Vector2			m_target;
	
	float			m_thetaValue;

	int				m_iFlags;

	enum Behaviors
	{
		none				= 0x0000,
		seek				= 0x0001,
		arrive				= 0x0002,
		flee				= 0x0004,
		pursuit				= 0x0008,
		evade				= 0x0010,
		wander				= 0x0020,
		obstaclesAvoidance	= 0x0040,
		wallAvoidance		= 0x0080,
		interpose			= 0x0100,
		separation			= 0x0200,
		cohesion			= 0x0400,
		alignment			= 0x0800,

	};

	bool	On(Behaviors bt){return ((m_iFlags & bt) == bt);}

	void SumForces();

	Vector2 Seek(const Vector2& target);
	Vector2 Flee(const Vector2& target);
	Vector2 Arrive(const Vector2& target);
	Vector2 Pursuit(const Agent* target);
	Vector2 Evade(const Agent* target);
	Vector2 Wander();
	Vector2 ObstacleAvoidance();
	Vector2 WallAvoidance(const Vector2& target);
	Vector2 Interpose(const Vector2& target);

	//group
	Vector2 Separation(const std::vector<Agent*>& neighbors);
	Vector2 Cohesion(const std::vector<Agent*>& neighbors);
	Vector2 Alignment(const Vector2& target);

};

#endif