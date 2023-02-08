#include "pxpch.h"

#include "Entity/Entity.h"
#include "Entity/EntityManager.h"

static const char* idCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!?@_$";

Entity::Entity(std::string name)
{
	this->name = name;
	this->id = "";

	this->name.reserve(25);
}

void Entity::SetName(const std::string& name)
{
	this->name = name;
}

bool Entity::operator!=(const Entity& other)
{
	return this->name != other.name || this->id != other.id;
}

Entity& Entity::CreateEntity(std::string name)
{
	Entity entity = Entity(name);

	for (int i = 0; i < 16; i++) entity.id += idCharacters[std::rand() % 67];

	EntityManager::Get()->AddEntity(entity);
	return entity;
}
