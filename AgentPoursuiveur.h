#ifndef AGENTPOURSUIVEUR_H
#define AGENTPOURSUIVEUR_H
#pragma warning (disable:4786)

//------------------------------------------------------------------------
//
//  Name:   AgentPoursuiveur.h
//
//  Desc:   Definition of AgentPoursuiveur
//
//------------------------------------------------------------------------

#include "Vehicle.h"
#include "2d/Vector2D.h"
#include "misc/Smoother.h"
#include "AgentLeader.h"

#include <vector>
#include <list>
#include <string>


class AgentPoursuiveur : public Vehicle
{
private :
	AgentLeader* leaderToFollow;
	double triggerRadius;
	int indexInFormation;

public :
	AgentPoursuiveur(GameWorld* world,Vector2D position,double rotation,Vector2D velocity,double mass,double max_force,double max_speed,double max_turn_rate,double scale);
	~AgentPoursuiveur();
	void Update(double time_elapsed);
	void LeaderDetected(Vehicle* leader);
	void UpdateOffsetFollower();

	int GetIndexInFormation(){return indexInFormation;}
	void SetIndexInFormation(int index){ indexInFormation = index;}
	
};



#endif