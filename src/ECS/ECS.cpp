#include "ECS.h"
#include "../Logger/Logger.h"
#include <algorithm>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMPONENT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int IComponent::nextId = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ENTITY
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Entity::GetId() const {
    return id;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SYSTEM
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void System::AddEntityToSystem(Entity entity) {
    entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity) {
    // Modern C++ way to erase something in a vector.
    entities.erase(std::remove_if(entities.begin(), entities.end(), [&entity](Entity other) {
        return entity == other;
    }), entities.end());
}

std::vector<Entity> System::GetSystemEntities() const {
    return entities;
}

const Signature& System::GetComponentSignature() const {
    return componentSignature;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// REGISTRY
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Entity Registry::CreateEntity() {
    int entityId = numEntities++;
    if (entityId >= entityComponentSignatures.size())
    {
        entityComponentSignatures.resize(entityId + 1);
    }
    Entity entity(entityId);
    entitiesToBeAdded.insert(entity);

    Logger::Log("Entity created with id = " + std::to_string(entityId));

    return entity;
}

void Registry::AddEntityToSystems(Entity entity) {
    const auto entityId = entity.GetId();
    const auto& entityComponentSignature = entityComponentSignatures[entityId];

    // Loop all the systems
    for (auto& system : systems)
    {
        const auto& systemComponentSignature = system.second->GetComponentSignature();

        bool isInterested = (entityComponentSignature & systemComponentSignature) == systemComponentSignature;

        if (isInterested)
        {
            system.second->AddEntityToSystem(entity);
        }
    }
}

void Registry::Update() {
    // Here is where we actually insert/delete the entities that are waiting to be added/removed
    // We do this because we don't want to confuse our Systems by adding/removing entities in the middle
    // of the frame logic. Therefore, we wait until the end of the frame to update and perform

    // TODO: Add the entities that are waiting to be created to the
}