#ifndef DANMAKU_ENGINE_REGISTER_TYPES_H
#define DANMAKU_ENGINE_REGISTER_TYPES_H

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void initialise_danmaku_engine(ModuleInitializationLevel p_level);
void uninitialise_danmaku_engine(ModuleInitializationLevel p_level);

#endif