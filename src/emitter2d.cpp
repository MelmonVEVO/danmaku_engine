/***************************************************/
/*  emitter2d.cpp                                  */
/***************************************************/
/* This file is a part of Danmaku Engine, a Godot  */
/* plugin by MELMON PROJECT.                       */
/*                                                 */
/* Copyright (c) 2024-present MELMON PROJECT.      */
/*                                                 */
/* Danmaku Engine is released under the GNU GPL    */
/* Public Licence v3.0. You should have received a */
/* copy of the licence with the source code.       */
/*                                                 */
/* THIS SOFTWARE IS PROVIDED "AS IS" WITH NO       */
/* WARRANTY OF ANY KIND. FOR DETAILS, CHECK THE    */
/* PROVIDED LICENSE FILE.                          */
/***************************************************/


#include "emitter2d.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


void Emitter2D::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_texture"), &Emitter2D::get_texture);
    ClassDB::bind_method(D_METHOD("set_texture", "p_texture"), &Emitter2D::set_texture);

    ClassDB::bind_method(D_METHOD("get_initial_speed"), &Emitter2D::get_initial_speed);
    ClassDB::bind_method(D_METHOD("set_initial_speed", "p_initial_speed"), &Emitter2D::set_initial_speed);

    ClassDB::bind_method(D_METHOD("get_acceleration"), &Emitter2D::get_acceleration);
    ClassDB::bind_method(D_METHOD("set_acceleration", "p_acceleration"), &Emitter2D::set_acceleration);

    ClassDB::bind_method(D_METHOD("get_ang_vel"), &Emitter2D::get_ang_vel);
    ClassDB::bind_method(D_METHOD("set_ang_vel", "p_ang_vel"), &Emitter2D::set_ang_vel);

    ClassDB::bind_method(D_METHOD("get_p_layer"), &Emitter2D::get_phys_layer);
    ClassDB::bind_method(D_METHOD("set_p_layer", "p_layer"), &Emitter2D::set_phys_layer);

    ClassDB::bind_method(D_METHOD("get_ttl"), &Emitter2D::get_ttl);
    ClassDB::bind_method(D_METHOD("set_ttl", "p_ttl"), &Emitter2D::set_ttl);

    ClassDB::bind_method(D_METHOD("get_spawn_type"), &Emitter2D::get_spawn_type);
    ClassDB::bind_method(D_METHOD("set_spawn_type", "p_spawn_type"), &Emitter2D::set_spawn_type);

    ClassDB::bind_method(D_METHOD("get_bullets_per_volley"), &Emitter2D::get_bullets_per_volley);
    ClassDB::bind_method(D_METHOD("set_bullets_per_volley", "p_bullets_per_volley"), &Emitter2D::set_bullets_per_volley);

    ClassDB::bind_method(D_METHOD("get_stack_count"), &Emitter2D::get_stack_count);
    ClassDB::bind_method(D_METHOD("set_stack_count", "p_stack_count"), &Emitter2D::set_stack_count);

    ClassDB::bind_method(D_METHOD("is_spawning"), &Emitter2D::is_spawning);
    ClassDB::bind_method(D_METHOD("set_spawning", "p_spawning"), &Emitter2D::set_spawning);

    ClassDB::bind_method(D_METHOD("get_spawn_rate"), &Emitter2D::get_spawn_rate);
    ClassDB::bind_method(D_METHOD("set_spawn_rate", "p_spawn_rate"), &Emitter2D::set_spawn_rate);

    ClassDB::bind_method(D_METHOD("get_volley_count"), &Emitter2D::get_volley_count);
    ClassDB::bind_method(D_METHOD("set_volley_count", "p_volley_count"), &Emitter2D::set_volley_count);

    ClassDB::bind_method(D_METHOD("get_spawn_offset"), &Emitter2D::get_spawn_offset);
    ClassDB::bind_method(D_METHOD("set_spawn_offset", "p_spawn_offset"), &Emitter2D::set_spawn_offset);

    ClassDB::bind_method(D_METHOD("get_rotation_rate"), &Emitter2D::get_rotation_rate);
    ClassDB::bind_method(D_METHOD("set_rotation_rate", "p_rotation_rate"), &Emitter2D::set_rotation_rate);

    ClassDB::bind_method(D_METHOD("get_rotation_option"), &Emitter2D::get_rotation_option);
    ClassDB::bind_method(D_METHOD("set_rotation_option", "p_rotation_option"), &Emitter2D::set_rotation_option);

    ADD_SIGNAL(MethodInfo("clear"));
    ADD_SIGNAL(MethodInfo("volley_timeout"));
    ADD_SIGNAL(MethodInfo("finished_spawning"));

    ADD_GROUP("Bullet Settings", "bullet_settings_");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "bullet_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_texture", "get_texture");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "initial_speed"), "set_initial_speed", "get_initial_speed");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "acceleration"), "set_acceleration", "get_acceleration");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "ang_vel", PROPERTY_HINT_RANGE, "-360,360"), "set_ang_vel", "get_ang_vel");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "phys_layer", PROPERTY_HINT_LAYERS_2D_PHYSICS), "set_phys_layer", "get_phys_layer");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "ttl"), "set_ttl", "get_ttl");
    
    ADD_GROUP("Spawner Settings", "spawner_settings_");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "spawn_type", PROPERTY_HINT_ENUM, "Directional,Ring,Arc"), "set_spawn_type", "get_spawn_type");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "bullets_per_volley", PROPERTY_HINT_RANGE, "1,200,1,or_greater"), "set_bullets_per_volley", "get_bullets_per_volley");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "stack_count", PROPERTY_HINT_RANGE, "1,50,1,or_greater"), "set_stack_count", "get_stack_count");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "spawning"), "set_spawning", "is_spawning");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spawn_rate"), "set_spawn_rate", "get_spawn_rate");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "volley_count"), "set_volley_count", "get_volley_count");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spawn_offset"), "set_spawn_offset", "get_spawn_offset");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rotation_rate", PROPERTY_HINT_RANGE, "-360,360,0"), "set_rotation_rate", "get_rotation_rate");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "rotation_option", PROPERTY_HINT_ENUM, "Continuous,Randomise,Aimed"), "set_rotation_option", "get_rotation_option");
}

