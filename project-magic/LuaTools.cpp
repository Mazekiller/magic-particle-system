#include "LuaTools.hpp"
#include <stdexcept>

LuaStateHandle::LuaStateHandle()
  :L(luaL_newstate())
{ luaL_openlibs(L); }

LuaStateHandle::~LuaStateHandle()
{ ClearLuaState(); }

LuaStateHandle::LuaStateHandle(LuaStateHandle&& LH)
  :L(std::move(LH.L))
{}

LuaStateHandle::LuaStateHandle(const LuaStateHandle& LH)
  :L(LH.L)
{}

const float LuaStateHandle::RunEmitterFormulaScript(const std::string& pathToScript, const float angleIndex)
{
    float result;

    luaL_dofile(L, pathToScript.c_str());
    lua_getglobal(L, "emit");
    lua_pushnumber(L, angleIndex);
    lua_pcall(L, 1, 1, 0);

    if(!lua_isnil(L, -1))
    { result = lua_tonumber(L, -1); }
    else
    {
        ///Error in script format.
        throw std::runtime_error(std::string("There was an error with the script file in this path: " +
                                             pathToScript +
                                             "\n" +
                                             "Please check that the name of the function variable is \"emit\""));
    }

    lua_pop(L, -1);

    return result;
}

void LuaStateHandle::ClearLuaState()
{ lua_close(L); }
