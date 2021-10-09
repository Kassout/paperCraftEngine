#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>

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
        static audo id = nextId++;
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
    virtual ~System() = default;

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

/// Class responsible for managing the different game systems.
/// @file ECS.h
/// @author Maxime Héliot
/// @version 0.1.0 08/10/2021
class Registry {
    // TODO: ...
};

// Implementation of the function template
template <typename TComponent>
void System::RequireComponent() {
    const auto componentId = Component<TComponent>::GetId();
    componentSignature.set(componentId);
}

#endif /* ECS_H */
