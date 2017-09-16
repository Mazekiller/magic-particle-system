#pragma once

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <string>

///This simple class handles the main calls to the C API for Lua embedding.
class LuaStateHandle
{
    public:
        LuaStateHandle();  ///Creates a new Lua state and charges the library modules.
        ~LuaStateHandle(); ///Destroys the values for the stack on the Lua state.

        LuaStateHandle(const LuaStateHandle& LH);
        LuaStateHandle(LuaStateHandle&& LH);

        ///Basic function for emitter math, if another one is needed, it can be added.
        const float RunEmitterFormulaScript(const std::string& pathToScript, const float angleIndex);

        ///Clears the lua state from all data, including libs.
        void ClearLuaState();

    private:
        lua_State *L;

        LuaStateHandle& operator=(const LuaStateHandle& LH) = delete;
        LuaStateHandle& operator=(LuaStateHandle&& LH) = delete;

};





