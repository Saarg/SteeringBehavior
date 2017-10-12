#include "AgentPlayer.h"
#include "AgentPoursuiveur.h"
#include "SteeringBehaviors.h"
#include "GameWorld.h"


AgentPlayer::AgentPlayer(GameWorld* world,
	Vector2D position,
	double    rotation,
	Vector2D velocity,
	double    mass,
	double    max_force,
	double    max_speed,
	double    max_turn_rate,
	double    scale): AgentLeader(world, position, rotation, velocity, mass, max_force,max_speed, max_turn_rate, scale)
{
	isPlayer = true;
}


AgentPlayer::~AgentPlayer(void)
{
}

void AgentPlayer::Update(double time_elapsed)
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