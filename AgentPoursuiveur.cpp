#include "AgentPoursuiveur.h"
#include "SteeringBehaviors.h"


//----------------------------- ctor -------------------------------------
//------------------------------------------------------------------------
AgentPoursuiveur::AgentPoursuiveur(GameWorld* world,
	Vector2D position,
	double    rotation,
	Vector2D velocity,
	double    mass,
	double    max_force,
	double    max_speed,
	double    max_turn_rate,
	double    scale): Vehicle(world, position, rotation, velocity, mass, max_force,max_speed, max_turn_rate, scale)
{
	// On lance la recherche de Leader
	Steering()->WanderOn();
}

//----------------------------- dtor -------------------------------------
//------------------------------------------------------------------------
AgentPoursuiveur::~AgentPoursuiveur()
{

}

void AgentPoursuiveur::LeaderDetected(Vehicle* leader)
{
	//Update Leader
	leaderToFollow = leader;
	//On stop la recherche et ...
	Steering()->WanderOff();
	//On commence � follow
	Steering()->OffsetPursuitOn(leaderToFollow, offset);
}