#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include <sol/sol.hpp>

/// TODO: comments
struct ScriptComponent {
    /// TODO: comments
    sol::function func;

    /// TODO: comments
    ScriptComponent(sol::function func = sol::lua_nil): func(func) {}
};

#endif // SCRIPTCOMPONENT_H //
