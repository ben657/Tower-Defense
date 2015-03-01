#pragma once

#include <vector>
#include <World/Entity.h>

class Scene
{
protected:	
	std::vector<Entity*> entities_;

public:
	Scene();
	virtual ~Scene();
	
	virtual void SwitchedTo(const std::string& from){};
	virtual void SwitchedFrom(const std::string& to){};

	int AddEntity(Entity* entity);

	virtual void Update(float delta);
	virtual void FixedUpdate();
	virtual void Draw(float interp);
};