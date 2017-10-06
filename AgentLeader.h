#ifndef AGENTLEADER_H
#define AGENTLEADER_H
#pragma warning (disable:4786)

//------------------------------------------------------------------------
//
//  Name:   AgentLeader.h
//
//  Desc:   Definition of AgentPoursuiveur
//
//------------------------------------------------------------------------

#include "Vehicle.h"
#include "2d/Vector2D.h"
#include "misc/Smoother.h"

#include <vector>
#include <list>
#include <string>


class AgentLeader : public Vehicle
{

public :
	AgentLeader(GameWorld* world,Vector2D position,double rotation,Vector2D velocity,double mass,double max_force,double max_speed,double max_turn_rate,double scale);
	~AgentLeader();

};



#endif