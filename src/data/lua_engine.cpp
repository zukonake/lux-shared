#include <stdexcept>
//
#include <lua.hpp>
//
#include "lua_engine.hpp"

namespace data
{

LuaEngine::LuaEngine() :
    state(luaL_newstate())
{
    if(state == NULL)
    {
        throw std::runtime_error("couldn't create lua state");
    }
    call(luaL_openlibs);

    call(luaL_loadstring, "package.path = package.path .. \";data/?.lua\"");
    call(lua_call, 0, 0);
}

LuaEngine::~LuaEngine()
{
    call(lua_close);
}

}
