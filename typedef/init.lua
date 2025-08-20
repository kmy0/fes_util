---@meta

---@class fes_util
---@field write_byte fun(ptr: integer, value: integer): boolean
---@field write_short fun(ptr: integer, value: integer): boolean
---@field write_dword fun(ptr: integer, value: integer): boolean
---@field write_qword fun(ptr: integer, value: integer): boolean
---@field write_float fun(ptr: integer, value: number): boolean
---@field write_double fun(ptr: integer, value: number): boolean
---@field read_byte fun(ptr: integer): integer
---@field read_short fun(ptr: integer): integer
---@field read_dword fun(ptr: integer): integer
---@field read_qword fun(ptr: integer): integer
---@field read_float fun(ptr: integer): number
---@field read_double fun(ptr: integer): number

---@class fes_util
fes_util = {}
