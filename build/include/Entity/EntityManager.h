#pragma once

#include "Entity/Entity.h"

using EntityMap = std::vector<Entity>;
using EntityMapIterator = EntityMap::iterator;

class EntityManager
{
public:
	static std::shared_ptr<EntityManager> Get();

	const EntityMap& GetEntityMap() const { return m_EntityMap; }

	const Entity& GetEntityAtLocation(unsigned int where) const { return m_EntityMap[where]; }
	Entity& GetEntityAtLocation(unsigned int where) { return m_EntityMap[where]; }

	void AddEntity(const Entity& entity);
	void DestroyEntity(const Entity& entity);

	EntityManager();
	~EntityManager() = default;

private:

	static std::shared_ptr<EntityManager> s_Instance;
	EntityMap m_EntityMap;
};