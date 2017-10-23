#include "AgentLeader.h"
#include "AgentPoursuiveur.h"
#include "SteeringBehaviors.h"
#include "GameWorld.h"
#include <math.h> 
#include <iostream> 


//----------------------------- ctor -------------------------------------
//------------------------------------------------------------------------
AgentLeader::AgentLeader(GameWorld* world,
	Vector2D position,
	double    rotation,
	Vector2D velocity,
	double    mass,
	double    max_force,
	double    max_speed,
	double    max_turn_rate,
	double    scale): Vehicle(world, position, rotation, velocity, mass, max_force,max_speed, max_turn_rate, scale)
{
	distBetweenFollowers=10;
	formation = Line;
	SetIsLeader(true);
	// On lance la recherche de Leader
	Steering()->WanderOn();
}

//----------------------------- dtor -------------------------------------
//------------------------------------------------------------------------
AgentLeader::~AgentLeader()
{

}

void AgentLeader::Update(double time_elapsed)
{    
	if (!isActivated) {
		for (std::vector<Vehicle*>::iterator f = followers.begin(); f != followers.end() && followers.size(); f++) {
			(*f)->Steering()->WanderOn();
			(*f)->Steering()->OffsetPursuitOff();
			(*f)->SetIsFollowingLeader(false);
		}

		followers.clear();
		return;
	}

	//update the time elapsed
	m_dTimeElapsed = time_elapsed;

	//keep a record of its old position so we can update its cell later
	//in this method
	Vector2D OldPos = Pos();


	Vector2D SteeringForce;

	//calculate the combined force from each steering behavior in the 
	//vehicle's list
	SteeringForce = m_pSteering->Calculate();

	//Acceleration = Force/Mass
	Vector2D acceleration = SteeringForce / m_dMass;

	//update velocity
	m_vVelocity += acceleration * time_elapsed; 

	//make sure vehicle does not exceed maximum velocity
	m_vVelocity.Truncate(m_dMaxSpeed);

	//update the position
	m_vPos += m_vVelocity * time_elapsed;

	//update the heading if the vehicle has a non zero velocity
	if (m_vVelocity.LengthSq() > 0.00000001)
	{    
		m_vHeading = Vec2DNormalize(m_vVelocity);

		m_vSide = m_vHeading.Perp();
	}

	//EnforceNonPenetrationConstraint(this, World()->Agents());

	//treat the screen as a toroid
	WrapAround(m_vPos, m_pWorld->cxClient(), m_pWorld->cyClient());

	//update the vehicle's current cell if space partitioning is turned on
	if (Steering()->isSpacePartitioningOn())
	{
		World()->CellSpace()->UpdateEntity(this, OldPos);
	}

	if (isSmoothingOn())
	{
		m_vSmoothedHeading = m_pHeadingSmoother->Update(Heading());
	}
}

void AgentLeader::AddFollower(Vehicle* follower){	
	//On stop la recherche 
	follower->Steering()->WanderOff();
	double anglefin=0;float angle;
	//On donne au follower l'offset poursuite que le Leader a choisi
	switch(formation){
	case Line:
		if(followers.size() == 0){
			follower->Steering()->OffsetPursuitOn(this, Vector2D(-10, 0));
		}else{
			follower->Steering()->OffsetPursuitOn(followers[followers.size()-1], Vector2D(-10, 0));
		}
		break;

	case V:
		if(followers.size() == 0){
			follower->Steering()->OffsetPursuitOn(this, Vector2D(-10,10));
		}else if(followers.size() == 1){
			follower->Steering()->OffsetPursuitOn(this, Vector2D(10,10));
		}else if((followers.size()%2) == 0){ 
			follower->Steering()->OffsetPursuitOn(followers[followers.size()-2], Vector2D(-10,10));
		}else{
			follower->Steering()->OffsetPursuitOn(followers[followers.size()-2], Vector2D(10,10));
		}
		break;
	case X:
		if(followers.size() == 0){
			follower->Steering()->OffsetPursuitOn(this, Vector2D(10,10));
		}
		if(followers.size() == 1){
			follower->Steering()->OffsetPursuitOn(this, Vector2D(-10,10));
		}
		if(followers.size() == 2){
			follower->Steering()->OffsetPursuitOn(this, Vector2D(-10,-10));
		}
		if(followers.size() == 3){
			follower->Steering()->OffsetPursuitOn(this, Vector2D(10,-10));
		}
		if(followers.size() > 3){
			if(followers.size()%4 == 0){ 
				follower->Steering()->OffsetPursuitOn(followers[followers.size()-4], Vector2D(10,10));
			}else if(followers.size()%4 == 1){
				follower->Steering()->OffsetPursuitOn(followers[followers.size()-4], Vector2D(-10,10));
			}else if(followers.size()%4 == 2){
				follower->Steering()->OffsetPursuitOn(followers[followers.size()-4], Vector2D(-10,-10));
			}else if(followers.size()%4 == 3){
				follower->Steering()->OffsetPursuitOn(followers[followers.size()-4], Vector2D(10,-10));
			}
		}
		break;
	case(Cercle):
		angle = 360/Prm.NumAgents;
		anglefin=angle*followers.size();
		follower->Steering()->OffsetPursuitOn(this,Vector2D(20+cos(anglefin)*50,sin(anglefin)*50));
		break;
	default:
		break;
	}
	follower->SetIsFollowingLeader(true);
	((AgentPoursuiveur*)follower)->SetIndexInFormation(followers.size());
	followers.push_back(follower);
}

void AgentLeader::SetFormation(Formation form){
	formation = form;
	switch(formation)
	{
	case(Line):
		RecalculateOffsetLine();
		break;
	case(V):
		RecalculateOffsetV();
		break;
	case(X):
		RecalculateOffsetX();
		break;
	case(Cercle):
		RecalculateOffsetCercle();
		break;
	default:
		break;
	}
}

void AgentLeader::RecalculateOffsetLine(){
	if(followers.size() != 0){
		followers[0]->Steering()->OffsetPursuitOn(this, Vector2D(-10, 0));
		for(unsigned int i =1; i<followers.size(); i++){
			followers[i]->Steering()->OffsetPursuitOn(followers[i-1], Vector2D(-10, 0));
		}
	}
}

void AgentLeader::RecalculateOffsetV(){
	if(followers.size() > 0){
		followers[0]->Steering()->OffsetPursuitOn(this, Vector2D(-10,10));
	}
	if(followers.size() > 1){
		followers[1]->Steering()->OffsetPursuitOn(this, Vector2D(10,10));
	}
	if(followers.size() > 2){
		for(unsigned int i =2; i<followers.size(); i++){
			if(i%2 == 0){ 
				followers[i]->Steering()->OffsetPursuitOn(followers[i-2], Vector2D(-10,10));
			}else{
				followers[i]->Steering()->OffsetPursuitOn(followers[i-2], Vector2D(10,10));
			}
		}
	}
}


void AgentLeader::RecalculateOffsetX(){
	if(followers.size() > 0){
		followers[0]->Steering()->OffsetPursuitOn(this, Vector2D(10,10));
	}
	if(followers.size() > 1){
		followers[1]->Steering()->OffsetPursuitOn(this, Vector2D(-10,10));
	}
	if(followers.size() > 2){
		followers[2]->Steering()->OffsetPursuitOn(this, Vector2D(-10,-10));
	}
	if(followers.size() > 3){
		followers[3]->Steering()->OffsetPursuitOn(this, Vector2D(10,-10));
	}
	if(followers.size() > 4){
		for(unsigned int i = 4; i<followers.size(); i++){
			if(i%4 == 0){ 
				followers[i]->Steering()->OffsetPursuitOn(followers[i-4], Vector2D(10,10));
			}else if(i%4 == 1){
				followers[i]->Steering()->OffsetPursuitOn(followers[i-4], Vector2D(-10,10));
			}else if(i%4 == 2){
				followers[i]->Steering()->OffsetPursuitOn(followers[i-4], Vector2D(-10,-10));
			}else if(i%4 == 3){
				followers[i]->Steering()->OffsetPursuitOn(followers[i-4], Vector2D(10,-10));
			}
		}
	}
}

void AgentLeader::RecalculateOffsetCercle(){
	double angle,anglefin;angle = 360/Prm.NumAgents;anglefin = 0;
		for(unsigned int i = 0; i<followers.size(); i++){
			followers[i]->Steering()->OffsetPursuitOn(this, Vector2D(20+cos(anglefin)*50,sin(anglefin)*50));
			anglefin+= angle;
		}
}
