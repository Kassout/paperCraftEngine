#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>
#include <memory>

/// Integer value representing the maximum number of components allowed to be setup in an entity.
const unsigned int MAX_COMPONENTS = 32;

/// We use a bitset (1s and 0s) to keep track of which components an entity has,
/// and also helps keep track of which entities a system is interested in.
typedef std::bitset<MAX_COMPONENTS> Signature;

/// Structure containing the data representing the base information of a Component object.
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
    virtual ~IPool();
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

public:
    /// @brief Pool constructor
    /// @details A constructor of the Pool class using a size value parameter.
    /// @param size: An Integer value representing the size of the Pool data vector to instantiate.
    Pool(int size = 100) { data.resize(size); }

    /// @brief Default destructor
    /// @details A default destructor of the Pool class.
    virtual ~Pool() = default;

    /// @brief Pool empty check
    /// @details This method is responsible for checking if the Pool object is empty.
    /// @return The emptiness boolean status of the Pool object.
    bool isEmpty() const {
        return data.empty();
    }

    /// @brief Pool get data vector size
    /// @details This method is responsible for access and return the size of the data vector of the Pool object.
    /// @return An integer value representing the size of the data vector of the Pool object.
    int GetSize() const {
        return data.size();
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
    void Set(int index, T object) {
        data[index] = object;
    }

    /// @brief Pool vector get data
    /// @details This method is responsible to access the data contained at a given index of the Pool object vector.
    /// @param index: An integer value representing the index value of the Pool object vector to access.
    /// @return A "T" class object contained at the given index of the Pool object vector.
    T& Get(int index) { return static_cast<T&>(data[index]); }

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

    /// Set of entity objects awaiting creation in the next Registry update cycle.
    std::set<Entity> entitiesToBeAdded;

    /// Set of entity objects awaiting destruction in the next Registry update cycle.
    std::set<Entity> entitiesToBeKilled;

    /// Vector of component pools. Each pool contains all the data for a certain component type.
    /// @details componentPools[index = component type id]
    /// @details poolObject[index = entity id]
    std::vector<IPool*> componentPools;

    /// Vector of component signatures per entity, saying which component is turned "on" for a given entity.
    /// @details entityComponentSignatures[index = entity id]
    std::vector<Signature> entityComponentSignatures;

    /// Unordered map of active systems.
    /// @details systems[index = system typeid]
    std::unordered_map<std::type_index, System*> systems;

public:
    /// @brief Default constructor
    /// @details A default constructor of the Registry class.
    Registry() = default;

    /// @brief Registry (World objects) update method
    /// @details The registry update method finally processes the entities that are waiting to be added/killed in the scene.
    void Update();

    /// @brief Create entity method
    /// @details This method is responsible to create a new entity, giving it a new unique id and adding to entities list of the system.
    /// @return The Entity object created by the system.
    Entity CreateEntity();

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

    /// @brief Add entity to systems method
    /// @details This method is responsible for subscribing entity to the different systems that could be interested, regarding the entity components signature.
    /// @param entity: The Entity class object to add to the different systems of the registry.
    void AddEntityToSystems(Entity entity);
};

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
        Pool<TComponent>* newComponentPool = new Pool<TComponent>();
        componentPools[componentId] = newComponentPool;
    }

    // Get the pool of component values for that component type
    Pool<TComponent>* componentPool = static_cast<Pool<TComponent>>(componentPools[componentId]);

    // If the entity id is greater than the current size of the component pool, then resize the pool
    if (entityId >= componentPool->GetSize()) {
            componentPool->Resize(numEntities);
    }

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

    entityComponentSignatures[entityId].set(componentId, false);
}

template <typename TComponent>
bool Registry::HasComponent(Entity entity) const {
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();

    return entityComponentSignatures[entityId].test(componentId);
}

template <typename TSystem, typename ...TArgs>
void Registry::AddSystem(TArgs&& ...args) {
    TSystem* newSystem(new TSystem(std::forward<TArgs>(args)...));
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
