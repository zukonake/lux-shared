#pragma once

#include <lua.hpp>

namespace data
{

class LuaEngine
{
    public:
    LuaEngine();
    ~LuaEngine();

    //used like this: lua_engine.call(&lua_copy, -1, -2);
    template<typename T, typename ...Args>
    T call(T (*f)(lua_State *, Args...), Args... args);
    private:
    lua_State *state;
};

template<typename T, typename ...Args>
T LuaEngine::call(T (*f)(lua_State *, Args...), Args... args)
{
    (*f)(state, args...);
}

}
