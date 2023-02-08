#pragma once

#include <glm/glm.hpp>

enum class ComponentType : int
{
	Unknown = -1,
	Transform = 0,
	Camera = 1,
	Physics = 2, // Mechanics? 
};

class Component
{
public: 
	virtual const char* GetComponentName() const = 0;
	virtual std::string GetComponentNameStr() const = 0;
	virtual ComponentType GetComponentType() const = 0;

protected:
	Component(bool active) : isActive(active) {}

	bool isActive;
};

class TransformComponent : public Component
{
public:
	TransformComponent(bool active = true);

	virtual const char* GetComponentName() const override		{ return "Transform"; };
	virtual std::string GetComponentNameStr() const override	{ return "Transform"; };
	virtual ComponentType GetComponentType() const override		{ return ComponentType::Transform; };
	static ComponentType GetStaticComponentType()				{ return ComponentType::Transform; };

private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
};

class CameraComponent : public Component
{
public:
	CameraComponent(bool active = true);

	virtual const char* GetComponentName() const override		{ return "Camera"; };
	virtual std::string GetComponentNameStr() const override	{ return "Camera"; };
	virtual ComponentType GetComponentType() const override		{ return ComponentType::Camera; };
	static ComponentType GetStaticComponentType()				{ return ComponentType::Camera; };

private:
	glm::mat4 m_ViewProjectionMatrix;
};

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(bool active = true);

	virtual const char* GetComponentName() const override		{ return "Physics"; };
	virtual std::string GetComponentNameStr() const override	{ return "Physics"; };
	virtual ComponentType GetComponentType() const override		{ return ComponentType::Physics; };
	static ComponentType GetStaticComponentType()				{ return ComponentType::Physics; };

private:
	float m_Mass;
	glm::vec3 m_Acceleration;
	glm::vec3 m_Velocity;
	glm::vec3 m_AngularAcceleration; // Not in the short term
	glm::vec3 m_AngularVelocity; // Not in the short term
	glm::vec3 m_CMPosition;
};
