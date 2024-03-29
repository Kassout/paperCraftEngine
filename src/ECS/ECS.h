#ifndef ECS_H
#define ECS_H

#include "../Logger/Logger.h"
#include <vector>
#include <bitset>
#include <set>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <deque>

/// Integer value representing the maximum number of components allowed to be setup in an entity.
const unsigned int MAX_COMPONENTS = 32;

/// We use a bitset (1s and 0s) to keep track of which components an entity has,
/// and also helps keep track of which entities a system is interested in.
typedef std::bitset<MAX_COMPONENTS> Signature;

/// Structure interface containing the data representing the base information of a Component object.
struct IComponent {
protected:
    /// Integer value representing the id of the next instantiated Component object.
    static int nextId;
};

/// Class responsible for containing the game data a certain System object is using to process game actions.
/// @file ECS.h
/// @author Maxime Héliot
/// @version 0.1.0 08/10/2021
template <typename T>
class Component : public IComponent {
public:
    /// @brief Get the component id.
    /// @details Return the unique id of Component<T>
    /// @return Integer value representing the Component object id.
    static int GetId() {
        static auto id = nextId++;
        return id;
    }
};

/// Class responsible of representing a game object under a unique id.
/// @file ECS.h
/// @author Maxime Héliot
/// @version 0.1.0 08/10/2021
class Entity {
private:
    /// Entity id integer value.
    int id;

public:
    /// Pointer to the registry of the game, owner of the entity.
    class Registry* registry;

    /// @brief Entity constructor
    /// @details A constructor of the Entity class using an id value parameter.
    /// @param id: An Integer value representing the id of the Entity to instantiate.
    Entity(int id): id(id) {};

    /// @brief Entity constructor
    /// @details A constructor of the Entity class using another Entity object as parameter.
    /// @param entity: An Entity object representing the Entity to instantiate.
    Entity(const Entity& entity) = default;

    /// @brief Get the entity id
    /// @details Return the unique id of the Entity.
    /// @return Integer value representing the Entity object id.
    int GetId() const;

    /// @brief Remove the entity
    /// @details Remove the entity from the game.
    void Kill();

    // Manage entity tags and groups
    /// @brief Add tag to entity
    /// @details This method is responsible to add a given string tag to an entity.
    /// @param tag: The string tag to rely the entity on.
    void Tag(const std::string& tag);

    /// @brief Check tag of entity
    /// @details This method is responsible to check if an entity is linked to a given string tag.
    /// @param: tag: The string tag to check the entity reliability of.
    /// @return A boolean value representing the entity reliability status of the given tag.
    bool HasTag(const std::string& tag) const;

    /// @brief Add group to entity
    /// @details This method is responsible to add the entity to a given group.
    /// @param group: The string group to rely the entity on.
    void Group(const std::string& group);

    /// @brief Check group of entity
    /// @details This method is responsible to check if an entity is linked to a given group.
    /// @param: group: The string group to check the entity reliability of.
    /// @return A boolean value representing the entity reliability status of the given group.
    bool BelongsToGroup(const std::string& group) const;

    /// @brief Add component to entity method
    /// @details This method is responsible to add a new component to the entity and it components pool.
    /// @param args: The arguments of the Component type class.
    template <typename TComponent, typename ...TArgs>
    void AddComponent(TArgs&& ...args);

    /// @brief Remove component from entity method
    /// @details This method is responsible to remove a component from the entity and it components pool.
    template<typename TComponent>
    void RemoveComponent();

    /// @brief Check component attendance in entity method
    /// @details This method is responsible for checking the attendance of a component type inside the entity.
    /// @return A boolean value representing the attendance status of the component type inside the entity.
    template<typename TComponent>
    bool HasComponent() const;

    /// @brief Component getter method
    /// @details This method is responsible to get the given component type from the entity components list.
    /// @return The instance of the found component type class.
    template<typename TComponent>
    TComponent& GetComponent() const;

    /// @brief Assignment operator overloading
    Entity& operator = (const Entity& other) = default;
    /// @brief Equal comparison operator overloading
    bool operator == (const Entity& other) const { return id == other.id; }
    /// @brief Unequal comparison operator overloading
    bool operator != (const Entity& other) const { return id != other.id; }
    /// @brief Greater than comparison operator overloading
    bool operator > (const Entity& other) const { return id > other.id; }
    /// @brief Less than comparison operator overloading
    bool operator < (const Entity& other) const { return id < other.id; }
};

/// Class responsible for processes entities that contain a specific components signature.
/// @file ECS.h
/// @author Maxime Héliot
/// @version 0.1.0 08/10/2021
class System {
private:
    /// Signature object representing a bitset of components our entities is required to have for the system to consider them.
    Signature componentSignature;
    /// Vector object representing the list of entities the system is interested in process.
    std::vector<Entity> entities;

public:
    /// @brief Default constructor
    /// @details A default constructor of the System class.
    System() = default;

    /// @brief Default destructor
    /// @details A default destructor of the System class.
    ~System() = default;

    /// @brief Add an entity to the system
    /// @details This method is responsible to add an entity object to the list of ones to consider by the system object.
    /// @param entity: An Entity object to add the list of entity to be considered by the system.
    void AddEntityToSystem(Entity entity);

    /// @brief Remove an entity from the system
    /// @details This method is responsible to remove an entity object of the list of ones to consider by the system object.
    /// @param entity: An Entity object to remove from the list of entity to be considered by the system.
    void RemoveEntityFromSystem(Entity entity);

    /// @brief System entities accessor
    /// @details This method is responsible to access the list of entities contained in the system object.
    /// @return The list of system's entities.
    std::vector<Entity> GetSystemEntities() const;

    /// @brief System signature accessor
    /// @details This method is responsible to access the signature of the system object.
    /// @return The system's signature
    const Signature& GetComponentSignature() const;

    /// @brief System entity required component setter
    /// @details This method is responsible to set the entity required component to be considered by the system.
    template <typename TComponent>
    void RequireComponent();
};

/// Interface of the Pool<T> class.
/// @file ECS.h
/// @author Maxime Héliot
/// @version 0.1.0 09/10/2021
class IPool {
public:
    /// @brief Default destructor
    /// @details A default destructor of the IPool class.
    virtual ~IPool() = default;
    /// @brief Remove entity from pool method
    /// @details This method is responsible of removing a given entity from the pool object of components.
    /// @param entityId: Integer value representing the id of the given entity to remove from the pool.
    virtual void RemoveEntityFromPool(int entityId) = 0;
};

/// Class responsible for containing objects of type T.
/// @file ECS.h
/// @author Maxime Héliot
/// @version 0.1.0 09/10/2021
template <typename T>
class Pool: public IPool {
private:
    /// Vector (contiguous data) of objects of type T.
    std::vector<T> data;
    /// Integer value representing the pool size of components.
    int size;

    // Maps to keep track of entity ids per index so the vector is always packed
    /// Map of entity associated by index;
    std::unordered_map<int, int> entityIdToIndex;
    /// Map of index associated to entity;
    std::unordered_map<int, int> indexToEntityId;

public:
    /// @brief Pool constructor
    /// @details A constructor of the Pool class using a size value parameter.
    /// @param size: An Integer value representing the size of the Pool data vector to instantiate.
    Pool(int capacity = 100) {
        size = 0;
        data.resize(capacity);
    }

    /// @brief Default destructor
    /// @details A default destructor of the Pool class.
    virtual ~Pool() = default;

    /// @brief Pool empty check
    /// @details This method is responsible for checking if the Pool object is empty.
    /// @return The emptiness boolean status of the Pool object.
    bool IsEmpty() const {
        return size == 0;
    }

    /// @brief Pool get data vector size
    /// @details This method is responsible for access and return the size of the data vector of the Pool object.
    /// @return An integer value representing the size of the data vector of the Pool object.
    int GetSize() const {
        return size;
    }

    /// @brief Pool resize data vector
    /// @details This method is responsible for resizing the Pool object data vector to the target value.
    /// @param n: An integer value representing the desired new size of the Pool object data vector.
    void Resize(int n) {
        data.resize(n);
    }

    /// @brief Pool data vector clear
    /// @details This method is responsible to clear all the data contained in the Pool object vector.
    void Clear() {
        data.clear();
        size = 0;
    }

    /// @brief Pool vector add data
    /// @details This method is responsible to add data to the Pool object vector.
    /// @param object: A "T" class object to add to the Pool object vector.
    void Add(T object) {
        data.push_back(object);
    }

    /// @brief Pool vector set data
    /// @details This method is responsible to access the data contained at a given index of the Pool object vector and, set it to a new data value.
    /// @param index: An integer value representing the index value of the Pool object vector to set the new data value in.
    /// @param object: A "T" class object to add to the Pool object vector at the given index.
    void Set(int entityId, T object) {
        if (entityIdToIndex.find(entityId) != entityIdToIndex.end()) {
            // If the element already exists, simply replace the component object
            int index = entityIdToIndex[entityId];
            data[index] = object;
        } else {
            // When adding a new object, we keep track of the entity ids and their vector index
            int index = size;
            entityIdToIndex.template emplace(entityId, index);
            indexToEntityId.template emplace(index, entityId);
            if (index >= data.capacity()) {
                // If necessary, we resize by always doubling the current capacity
                data.resize(size * 2);
            }
            data[index] = object;
            size++;
        }
    }

    /// @brief Remove entity from pool
    /// @details This method is responsible to remove the given entity from the pool object of components.
    /// @param entityId: Integer value representing the id of the given entity to remove from the pool.
    void Remove(int entityId) {
        // Copy the last element to the deleted position to keep the array packed
        int indexOfRemoved = entityIdToIndex[entityId];
        int indexOfLast = size - 1;
        data[indexOfRemoved] = data[indexOfLast];

        // Update the index-entity maps to point to the correct elements
        int entityIdOfLastElement = indexToEntityId[indexOfLast];
        entityIdToIndex[entityIdOfLastElement] = indexOfRemoved;
        indexToEntityId[indexOfRemoved] = entityIdOfLastElement;

        entityIdToIndex.erase(entityId);
        indexToEntityId.erase(indexOfLast);

        size--;
    }

    /// @brief Remove entity from pool
    /// @details This method is responsible to remove the given entity from the pool object of components.
    /// @param entityId: Integer value representing the id of the given entity to remove from the pool.
    void RemoveEntityFromPool(int entityId) override {
        if (entityIdToIndex.find(entityId) != entityIdToIndex.end()) {
            Remove(entityId);
        }
    }

    /// @brief Pool vector get data
    /// @details This method is responsible to access the data contained at a given index of the Pool object vector.
    /// @param index: An integer value representing the index value of the Pool object vector to access.
    /// @return A "T" class object contained at the given index of the Pool object vector.
    T& Get(int entityId) {
        int index = entityIdToIndex[entityId];
        return static_cast<T&>(data[index]);
    }

    /// @brief Subscript operator overloading
    T& operator [](unsigned int index) { return data[index]; }
};

/// Class responsible for managing the creation and destruction of entities, add systems and components.
/// @file ECS.h
/// @author Maxime Héliot
/// @version 0.1.0 08/10/2021
class Registry {
private:
    /// Integer value representing the number of entity added to the scene.
    int numEntities = 0;
    /// Vector of component pools. Each pool contains all the data for a certain component type.
    /// @details componentPools[index = component type id]
    /// @details poolObject[index = entity id]
    std::vector<std::shared_ptr<IPool>> componentPools;
    /// Vector of component signatures per entity, saying which component is turned "on" for a given entity.
    /// @details entityComponentSignatures[index = entity id]
    std::vector<Signature> entityComponentSignatures;
    /// Unordered map of active systems.
    /// @details systems[index = system typeid]
    std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
    /// Set of entity objects awaiting creation in the next Registry update cycle.
    std::set<Entity> entitiesToBeAdded;
    /// Set of entity objects awaiting destruction in the next Registry update cycle.
    std::set<Entity> entitiesToBeKilled;
    // Entity tags (one tag name per entity)
    /// Map of entities associated by tag.
    std::unordered_map<std::string, Entity> entityPerTag;
    /// Map of tags associated by entity id.
    std::unordered_map<int, std::string> tagPerEntity;
    // Entity groups (a set of entities per group name)
    /// Map of entities associated by group.
    std::unordered_map<std::string, std::set<Entity>> entitiesPerGroup;
    /// Map of groups associated by entity.
    std::unordered_map<int, std::string> groupPerEntity;
    /// Double-ended queue containing the ids of the killed entities.
    std::deque<int> freeIds;

public:
    /// @brief Default constructor
    /// @details A default constructor of the Registry class.
    Registry() = default;

    /// @brief Default destructor
    /// @details A default constructor of the Registry class.
    ~Registry() = default;

    /// @brief Registry (World objects) update method
    /// @details The registry update method finally processes the entities that are waiting to be added/killed in the scene.
    void Update();

    /// @brief Create entity method
    /// @details This method is responsible to create a new entity, giving it a new unique id and adding to entities list of the system.
    /// @return The Entity object created by the system.
    Entity CreateEntity();

    /// @brief Remove entity method
    /// @details This method is responsible to kill an entity, removing it from entities list of the system.
    /// @param entity: The Entity object to remove from the system.
    void KillEntity(Entity entity);

    /// @brief Add entity to systems method
    /// @details This method is responsible for subscribing entity to the different systems that could be interested, regarding the entity components signature.
    /// @param entity: The Entity class object to add to the different systems of the registry.
    void AddEntityToSystems(Entity entity);

    /// @brief Remove entity from systems method
    /// @details This method is responsible for removing entity from the different systems that it was linked to, regarding the entity components signature.
    /// @param entity: The Entity class object to remove from the different systems of the registry.
    void RemoveEntityFromSystems(Entity entity);

    // Tag management
    /// @brief Add tag to entity
    /// @details This method is responsible to add a given string tag to the given entity.
    /// @param entity: Entity object to add the tag on.
    /// @param tag: String tag to rely the entity on.
    void TagEntity(Entity entity, const std::string& tag);

    /// @brief Check tag of entity
    /// @details This method is responsible to check the given entity reliability to a given string tag.
    /// @param entity: Entity object to check the tag on.
    /// @param tag: String tag to check for the entity reliability.
    /// @return Boolean value representing the entity reliability status of the given tag.
    bool EntityHasTag(Entity entity, const std::string& tag) const;

    /// @brief Get entity by tag
    /// @details This method is responsible to get the entity associate to the given tag.
    /// @param tag: String tag associate to an entity.
    /// @return Entity object associate to the given tag.
    Entity GetEntityByTag(const std::string& tag) const;

    /// @brief Remove the entity tag
    /// @details This method is responsible to remove the tag associate to the given entity.
    /// @param entity: Entity object to remove the tag from.
    void RemoveEntityTag(Entity entity);

    /// @brief Add group to entity
    /// @details This method is responsible to add a given string group to the given entity.
    /// @param entity: Entity object to add the group on.
    /// @param group: String group to rely the entity on.
    void GroupEntity(Entity entity, const std::string& group);

    /// @brief Check group of entity
    /// @details This method is responsible to check the given entity reliability to a given group.
    /// @param entity: Entity object to check the group on.
    /// @param group: String tag to check for the entity reliability.
    /// @return Boolean value representing the entity reliability status of the given group.
    bool EntityBelongsToGroup(Entity entity, const std::string& group) const;

    /// @brief Get entities by group
    /// @details This method is responsible to get entities associate to the given group.
    /// @param group: String group associate to entities.
    /// @return Vector of entity objects associate to the given group.
    std::vector<Entity> GetEntitiesByGroup(const std::string& group) const;

    /// @brief Remove the entity group
    /// @details This method is responsible to remove the group associate to the given entity.
    /// @param entity: Entity object to remove the group from.
    void RemoveEntityGroup(Entity entity);

    /// @brief Add system method
    /// @details This method is responsible to add a new system type to the registry.
    /// @param args: The arguments of the System type class.
    template <typename TSystem, typename ...TArgs>
    void AddSystem(TArgs&& ...args);

    /// @brief Remove system method
    /// @details This method is responsible to remove a system type from the registry.
    template <typename TSystem>
    void RemoveSystem();

    /// @brief Check system attendance method
    /// @details This method is responsible for checking the attendance of a system type inside the registry.
    /// @return A boolean value representing the attendance status of the system type inside the registry.
    template <typename TSystem>
    bool HasSystem() const;

    /// @brief System getter method
    /// @details This method is responsible to get the given system type from the registry systems list.
    /// @return The instance of the found system type class.
    template<typename TSystem>
    TSystem& GetSystem() const;

    /// @brief Add component method
    /// @details This method is responsible to add a new component to a given entity and it components pool.
    /// @param entity: The Entity class object to which add the new T type component.
    /// @param args: The arguments of the Component type class.
    template <typename TComponent, typename ...TArgs>
    void AddComponent(Entity entity, TArgs&& ...args);

    /// @brief Remove component method
    /// @details This method is responsible to remove a component from an entity and it components pool.
    /// @param entity: The Entity class object to which remove the T type component.
    template<typename TComponent>
    void RemoveComponent(Entity entity);

    /// @brief Check component attendance method
    /// @details This method is responsible for checking the attendance of a component type inside an entity.
    /// @param entity: The Entity class object to which check the component type attendance.
    /// @return A boolean value representing the attendance status of the component type inside the given entity.
    template<typename TComponent>
    bool HasComponent(Entity entity) const;

    /// @brief Component getter method
    /// @details This method is responsible to get the given component type from a given entity components list.
    /// @param entity: The Entity class object from which getting the component type.
    /// @return The instance of the found component type class.
    template<typename TComponent>
    TComponent& GetComponent(Entity entity) const;
};

template <typename TComponent, typename ...TArgs>
void Entity::AddComponent(TArgs&& ...args) {
    registry->AddComponent<TComponent>(*this, std::forward<TArgs>(args)...);
}

template <typename TComponent>
void Entity::RemoveComponent() {
    registry->RemoveComponent<TComponent>(*this);
}

template <typename TComponent>
bool Entity::HasComponent() const {
    return registry->HasComponent<TComponent>(*this);
}

template<typename TComponent>
TComponent& Entity::GetComponent() const {
    return registry->GetComponent<TComponent>(*this);
}

template <typename TComponent>
void System::RequireComponent() {
    const auto componentId = Component<TComponent>::GetId();
    componentSignature.set(componentId);
}

template <typename TComponent, typename ...TArgs>
void Registry::AddComponent(Entity entity, TArgs&& ...args) {
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();

    // If the component id is greater than the current size of the componentPools, then resize the vector
    if (componentId >= componentPools.size()) {
        componentPools.resize(componentId + 1, nullptr);
    }

    // If we still don't have a Pool for that component type
    if (!componentPools[componentId])
    {
        std::shared_ptr<Pool<TComponent>> newComponentPool = std::make_shared<Pool<TComponent>>();
        componentPools[componentId] = newComponentPool;
    }

    // Get the pool of component values for that component type
    std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentId]);

    // Create a new Component object of the type T, and forward the various parameters to the constructor
    // use "forward" to pass all the arguments of the T component sub-class to the constructor of that same sub-class
    TComponent newComponent(std::forward<TArgs>(args)...);

    // Add the new component to the component pool list, using the entity id as index
    componentPool->Set(entityId, newComponent);

    // Finally, change the component signature of the entity and set the component id on the bitset to 1
    entityComponentSignatures[entityId].set(componentId);
}

template <typename TComponent>
void Registry::RemoveComponent(Entity entity) {
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();

    // Get the pool of component values for that component type
    std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentId]);
    componentPool->Remove(entityId);

    // Set this component signature for that entity to false
    entityComponentSignatures[entityId].set(componentId, false);
}

template <typename TComponent>
bool Registry::HasComponent(Entity entity) const {
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();

    return entityComponentSignatures[entityId].test(componentId);
}

template<typename TComponent>
TComponent& Registry::GetComponent(Entity entity) const {
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();

    auto componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentId]);
    return componentPool->Get(entityId);
}

template <typename TSystem, typename ...TArgs>
void Registry::AddSystem(TArgs&& ...args) {
    // Shared smart pointers
    std::shared_ptr<TSystem> newSystem = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
    systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template <typename TSystem>
void Registry::RemoveSystem() {
    auto system = systems.find(std::type_index(typeid(TSystem)));
    systems.erase(system);
}

template <typename TSystem>
bool Registry::HasSystem() const {
    return systems.find(std::type_index(typeid(TSystem))) != systems.end();
}

template <typename TSystem>
TSystem& Registry::GetSystem() const {
    auto system = systems.find(std::type_index(typeid(TSystem)));
    return *(std::static_pointer_cast<TSystem>(system->second));
}

#endif /* ECS_H */