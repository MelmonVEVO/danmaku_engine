/***************************************************/
/*  emitter2d.cpp                                  */
/***************************************************/
/* This file is a part of Danmaku Engine, a Godot  */
/* plugin by MELMON PROJECT.                       */
/*                                                 */
/* Copyright (c) 2024-present MELMON PROJECT.      */
/*                                                 */
/* Danmaku Engine is released under the MIT        */
/* Licence You should have received a copy of the  */
/* licence with the source code.                   */
/*                                                 */
/* THIS SOFTWARE IS PROVIDED "AS IS" WITH NO       */
/* WARRANTY OF ANY KIND. FOR DETAILS, CHECK THE    */
/* PROVIDED LICENSE FILE.                          */
/***************************************************/

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

#include "emitter2d.h"

using namespace godot;


void Emitter2D::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_settings"), &Emitter2D::get_settings);
    ClassDB::bind_method(D_METHOD("set_settings", "p_settings"), &Emitter2D::set_settings);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "bullet_settings", PROPERTY_HINT_RESOURCE_TYPE, "BulletSettings"), "set_settings", "get_settings");
    
    ClassDB::bind_method(D_METHOD("get_usable_pool"), &Emitter2D::get_usable_pool);
    ClassDB::bind_method(D_METHOD("set_usable_pool", "p_usable_pool"), &Emitter2D::set_usable_pool);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "bullet_pool_to_use", PROPERTY_HINT_NODE_TYPE, "BulletPool"), "set_usable_pool", "get_usable_pool");
    
    ClassDB::bind_method(D_METHOD("get_bullets_per_volley"), &Emitter2D::get_bullets_per_volley);
    ClassDB::bind_method(D_METHOD("set_bullets_per_volley", "p_bullets_per_volley"), &Emitter2D::set_bullets_per_volley);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "bullets_per_volley", PROPERTY_HINT_RANGE, "1,200,1,or_greater"), "set_bullets_per_volley", "get_bullets_per_volley");
 
    ClassDB::bind_method(D_METHOD("is_spawn_on_start"), &Emitter2D::is_spawn_on_start);
    ClassDB::bind_method(D_METHOD("set_spawn_on_start", "p_spawn_on_start"), &Emitter2D::set_spawn_on_start);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "spawn_on_start"), "set_spawn_on_start", "is_spawn_on_start");
    
    ClassDB::bind_method(D_METHOD("get_spawn_rate"), &Emitter2D::get_spawn_rate);
    ClassDB::bind_method(D_METHOD("set_spawn_rate", "p_spawn_rate"), &Emitter2D::set_spawn_rate);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spawn_rate", PROPERTY_HINT_RANGE, "0.1,100,0.1"), "set_spawn_rate", "get_spawn_rate");

    ADD_SIGNAL(MethodInfo("clear"));
    ADD_SIGNAL(MethodInfo("volley"));
    ADD_SIGNAL(MethodInfo("finished_spawning"));
}


Emitter2D::Emitter2D() {
}


Emitter2D::~Emitter2D() {
}


void Emitter2D::_ready() {
    if (!Engine::get_singleton()->is_editor_hint()) {
        spawning = spawn_on_start;
        time_to_wait = 1 / get_spawn_rate();
        current_timer = time_to_wait;
        angle_per_bullet = (2 * Math_PI) / get_bullets_per_volley();
    }
}


void Emitter2D::_process(double delta) {
    if (!Engine::get_singleton()->is_editor_hint()) {
        if (spawning) {
            current_timer = current_timer - delta;
            if (current_timer <= 0) {
                current_timer = time_to_wait;
                for (uint32_t i = 0; i < bullets_per_volley; i++) {
                    double bullet_angle = angle_per_bullet * i;
                    Bullet2D* bullet = usable_pool->get_bullet();
                    if (bullet != nullptr) {  // pool returns nullptr if no bullets left.
                        bullet->start(get_settings(), bullet_angle, get_position(), this);
                    }
                }
            }
        }
    }
}


PackedStringArray Emitter2D::_get_configuration_warnings() const {
    PackedStringArray to_return = PackedStringArray();
    if (get_usable_pool() == nullptr) {
        to_return.append("This node cannot function without being assigned a BulletPool.");
    }
    if (get_settings().is_null()) {
        to_return.append("Please provide some BulletSettings.");
    }
    return to_return;
}
