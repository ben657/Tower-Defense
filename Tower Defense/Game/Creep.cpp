#include "Creep.h"

Creep::~Creep()
{
}

void Creep::Update(float delta)
{
	
}

void Creep::FixedUpdate()
{
	Vec2 direction = pathPoint_ - position_;
	direction.Normalise();

	position_ += direction * speed_;

	float dist2 = (pathPoint_ - position_).Length2();

	if (dist2 < .4f)
	{
		position_ = pathPoint_;

		//TODO: Creep manager so this stuff will work nicely
		//pathPoint_ = scene->NextPoint(path, pathIndex_);
		//pathIndex_++;
	}
}