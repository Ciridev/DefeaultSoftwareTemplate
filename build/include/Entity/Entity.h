#pragma once

class Entity
{
public: 
	static Entity& CreateEntity(std::string name = "Entity");
	
	const std::string& GetName() const { return name; }
	const std::string& GetId() const { return id; }

	void SetName(const std::string& name);

	Entity(std::string name = "Entity");

	bool operator !=(const Entity& other);

private:
	std::string name;
	std::string id;
	bool active;
};