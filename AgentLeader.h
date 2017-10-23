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

static enum Formation 
{ 
	Line=1,
	V=2,
	X=4,
	Cercle=5
};

class AgentLeader : public Vehicle
{
protected : 
	Formation formation;
	std::vector<Vehicle*> followers;
	float distBetweenFollowers;

public :
	AgentLeader(GameWorld* world,Vector2D position,double rotation,Vector2D velocity,double mass,double max_force,double max_speed,double max_turn_rate,double scale);
	~AgentLeader();
	void Update(double time_elapsed);
	void AddFollower(Vehicle* follower);

	Formation GetFormation(){return formation;}
	void SetFormation(Formation form);

	float GetDistBetweenFollowers(){return distBetweenFollowers;}
	void SetDistBetweenFollowers(float dist){distBetweenFollowers=dist;}

private : 	
	void RecalculateOffsetLine();
	void RecalculateOffsetV();
	void RecalculateOffsetX();
	void RecalculateOffsetCercle();
};



#endif