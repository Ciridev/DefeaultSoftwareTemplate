#include "pxpch.h"

#include "Entity/Component.h"

#include <glm/glm.hpp>

TransformComponent::TransformComponent(bool active) : Component(active) {}
PhysicsComponent::PhysicsComponent(bool active) : Component(active) {}
CameraComponent::CameraComponent(bool active) : Component(active) {}