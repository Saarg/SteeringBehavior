#ifndef AGENTPLAYER_H
#define AGENTPLAYER_H
#pragma warning (disable:4786)

#include "AgentLeader.h"

class AgentPlayer : public AgentLeader
{
public:
	AgentPlayer(GameWorld* world,Vector2D position,double rotation,Vector2D velocity,double mass,double max_force,double max_speed,double max_turn_rate,double scale);
	~AgentPlayer(void);

	void Update(double time_elapsed);

	Vector2D SteeringForce;
};

#endif
