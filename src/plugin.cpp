#include "reframework/API.hpp"
#include <sol/sol.hpp>

using API = reframework::API;
lua_State *g_lua{nullptr};

template <typename T> T &read_memory(uintptr_t ptr) {
    return *reinterpret_cast<T *>(ptr);
}

template <typename T> void write_memory(uintptr_t ptr, const T &value) {
    *reinterpret_cast<T *>(ptr) = value;
}

void on_lua_state_created(lua_State *l) {
    API::LuaLock _{};
    g_lua = l;
    sol::state_view lua{g_lua};

    auto fes_util = lua.create_table();
    fes_util["write_byte"] = write_memory<uint8_t>;
    fes_util["write_short"] = write_memory<uint16_t>;
    fes_util["write_dword"] = write_memory<uint32_t>;
    fes_util["write_qword"] = write_memory<int64_t>;
    fes_util["write_float"] = write_memory<float>;
    fes_util["write_double"] = write_memory<double>;
    fes_util["read_byte"] = read_memory<uint8_t>;
    fes_util["read_short"] = read_memory<uint16_t>;
    fes_util["read_dword"] = read_memory<uint32_t>;
    fes_util["read_qword"] = read_memory<int64_t>;
    fes_util["read_float"] = read_memory<float>;
    fes_util["read_double"] = read_memory<double>;
    lua["fes_util"] = fes_util;
}

void on_lua_state_destroyed(lua_State *l) {
    API::LuaLock _{};
    g_lua = nullptr;
}

extern "C" __declspec(dllexport) bool
reframework_plugin_initialize(const REFrameworkPluginInitializeParam *param) {
    API::initialize(param);

    const auto functions = param->functions;
    functions->on_lua_state_created(on_lua_state_created);
    functions->on_lua_state_destroyed(on_lua_state_destroyed);

    return true;
}
