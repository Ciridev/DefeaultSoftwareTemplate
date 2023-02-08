#include "pxpch.h"

#include "Entity/EntityManager.h"

std::shared_ptr<EntityManager> EntityManager::s_Instance = nullptr;

 std::shared_ptr<EntityManager> EntityManager::Get()
{
	if (!s_Instance) s_Instance = std::make_shared<EntityManager>();
	return s_Instance;
}

 void EntityManager::AddEntity(const Entity& entity)
 {
	 m_EntityMap.push_back(entity);
 }

 void EntityManager::DestroyEntity(const Entity& entity)
 {
	 auto it = m_EntityMap.begin();
	 while((it++)->GetId() != entity.GetId())
	 m_EntityMap.erase(it);
 }

EntityManager::EntityManager()
{
	m_EntityMap = EntityMap();
}

