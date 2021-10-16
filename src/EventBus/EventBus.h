#ifndef EVENTBUS_H
#define EVENTBUS_H

#include <map>
#include <typeindex>
#include <list>
#include <functional>
#include "Event.h"

/// Interface class laying the foundation of every EventCallBack subclass type.
/// @file EventBus.h
/// @author Maxime Héliot
/// @version 0.1.0 16/10/2021
class IEventCallback {
private:
    /// @brief Abstract call event method
    /// @details Abstract method responsible to call the given event reference.
    /// @param e: Event object class reference to be called by the method.
    virtual void Call(Event& e) = 0;

public:
    /// @brief Abstract IEventCallback destructor
    /// @details Base abstract destructor of the IEventCallback class.
    virtual ~IEventCallback() = default;

    /// @brief Execute event method
    /// @details Method responsible to execute the given event's call method.
    /// @param e: Event object class reference to be executed by the method.
    void Execute(Event& a) {
        Call(a);
    }
};

/// Template class responsible for performing events type object invocation.
/// @file EventBus.h
/// @author Maxime Héliot
/// @version 0.1.0 16/10/2021
template <typename TOwner, typename TEvent>
class EventCallback: public IEventCallback {
private:
    /// CallbackFunction type definition.
    typedef void (TOwner::*CallbackFunction)(TEvent&);

    /// Class type container the definition of the callback function.
    TOwner* ownerInstance;

    /// CallbackFunction object representing the function to invoke on event trigger.
    CallbackFunction callbackFunction;

    /// @brief Call event method
    /// @details Method responsible to call the given event type reference.
    /// @param e: Event object class reference to be called by the method.
    void Call(Event& e) override {
        std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(e));
    }

public:
    /// @brief Default EventCallback constructor
    /// @details Base constructor of the EventCallback class.
    EventCallback(TOwner* ownerInstance, CallbackFunction callbackFunction): ownerInstance(ownerInstance), callbackFunction(callbackFunction) {}

    /// @brief Default EventCallback destructor
    /// @details Base destructor of the EventCallback class.
    virtual ~EventCallback() override = default;
};

/// HandlerList type definition.
typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

/// Class responsible for managing events system subscription and trigger notifications.
/// @file EventBus.h
/// @author Maxime Héliot
/// @version 0.1.0 16/10/2021
class EventBus {
private:
    /// Map of subscribers object containing event callback methods linked by event notification type index.
    std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;

public:
    /// @brief Default EventBus constructor
    /// @details Base constructor of the EventBus class.
    EventBus() = default;

    /// @brief Default EventBus destructor
    /// @details Base destructor of the EventBus class.
    ~EventBus() = default;

    // Clears the subscribers list
    /// @brief Subscribers clearer method.
    /// @details This method is responsible for clearing the subscribers container.
    void Reset() {
        subscribers.clear();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Subscribe to an event of type <T>
    // In out implementation, a listener subscribes to an event
    // Example: eventBus->SubscribeEvent<CollisionEvent>(this, &Game::onCollision);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /// @brief Subscribe event method
    /// @details Template method responsible for subscribing a class to an event
    /// by adding its callback function to the subscribers map by the linked event awaiting notification.
    /// @param callbackFunction: The class type *TOwner* function to call when the event triggers.
    /// @param ownerInstance: The object class subscribing to the event.
    template <typename TEvent, typename TOwner>
    void SubscribeEvent(TOwner* ownerInstance, void (TOwner::*callbackFunction)(TEvent&)) {
        if (!subscribers[typeid(TEvent)].get()) {
            subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
        }
        auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(ownerInstance, callbackFunction) ;
        subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Emit an event of type <T>
    // In out implementation, as soon as something emits an
    // event we go ahead and execute all the listener callback functions
    // Example: eventBus->EmitEvent<CollisionEvent>(player, enemy);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /// @brief Emit event method
    /// @details Template method responsible for emitting a notification of the triggered event therefore calling for the subscribers callback functions.
    template<typename TEvent, typename ...TArgs>
    void EmitEvent(TArgs&& ...args) {
        auto handlers = subscribers[typeid(TEvent)].get();
        if (handlers) {
            for (auto i = handlers->begin(); i != handlers->end(); i++) {
                auto handler = i->get();
                TEvent event(std::forward<TArgs>(args)...);
                handler->Execute(event);
            }
        }
    }
};

#endif // EVENTBUS_H //
