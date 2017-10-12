#include "AgentPoursuiveur.h"
#include "SteeringBehaviors.h"
#include "GameWorld.h"
#include "iostream"


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
	triggerRadius = 100;
	leaderToFollow = nullptr;
	SetIsLeader(false);
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
	leaderToFollow = (AgentLeader*)leader;
	leaderToFollow->AddFollower(this);
}

void AgentPoursuiveur::Update(double time_elapsed)
{    
	if (!isActivated)
		return;

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

	if(!isFollowingLeader){
		//A modifier
		//	gdi->GreenPen();
		//	gdi->Circle(Pos(), triggerRadius); 
		this->World()->CellSpace()->CalculateNeighbors(Pos(), triggerRadius);

		for (Vehicle* cur_Vehicle = this->World()->CellSpace()->begin();
			!this->World()->CellSpace()->end();     
			cur_Vehicle = this->World()->CellSpace()->next())
		{
			if(cur_Vehicle->GetIsLeader() == true && cur_Vehicle->GetIsActivated())
			{
				LeaderDetected(cur_Vehicle);
				break;
			}
		}
	}else{// On update l'offset de l'offset poursuit
		UpdateOffsetFollower();		
	}
}

void AgentPoursuiveur::UpdateOffsetFollower(){
	switch(leaderToFollow->GetFormation())
	{
	case(Line):
		//Steering()->SetOffset(leaderToFollow->GetDistBetweenFollowers()*Vec2DNormalize(leaderToFollow->Heading()));
		Steering()->SetOffset(Vector2D(-10, 0));
		break;		
	case(V):
		if(indexInFormation%2 == 0){
			Steering()->SetOffset(Vector2D(-10, 8));
		}else{
			Steering()->SetOffset(Vector2D(-10, -8));
		}
		break;

	default:
		break;
	}
}