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
#include <godot_cpp/variant/utility_functions.hpp>

#include "emitter2d.h"

using namespace godot;


void Emitter2D::_bind_methods() {
    ClassDB::bind_method(D_METHOD("start_emitting"), &Emitter2D::start_emitting);
    ClassDB::bind_method(D_METHOD("stop_emitting"), &Emitter2D::stop_emitting);

    ADD_GROUP("Core", "emitter_core_");
    ClassDB::bind_method(D_METHOD("is_spawn_on_start"), &Emitter2D::is_spawn_on_start);
    ClassDB::bind_method(D_METHOD("set_spawn_on_start", "p_spawn_on_start"), &Emitter2D::set_spawn_on_start);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "spawn_on_start"), "set_spawn_on_start", "is_spawn_on_start");

    ClassDB::bind_method(D_METHOD("get_offset_time"), &Emitter2D::get_offset_time);
    ClassDB::bind_method(D_METHOD("set_offset_time", "p_offset_time"), &Emitter2D::set_offset_time);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "offset_time"), "set_offset_time", "get_offset_time");

    ClassDB::bind_method(D_METHOD("get_settings"), &Emitter2D::get_settings);
    ClassDB::bind_method(D_METHOD("set_settings", "p_settings"), &Emitter2D::set_settings);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "bullet_settings", PROPERTY_HINT_RESOURCE_TYPE, "BulletSettings"), "set_settings", "get_settings");
    
    ClassDB::bind_method(D_METHOD("get_usable_pool"), &Emitter2D::get_usable_pool);
    ClassDB::bind_method(D_METHOD("set_usable_pool", "p_usable_pool"), &Emitter2D::set_usable_pool);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "bullet_pool_to_use", PROPERTY_HINT_NODE_TYPE, "BulletPool"), "set_usable_pool", "get_usable_pool");
    
    ClassDB::bind_method(D_METHOD("get_pattern"), &Emitter2D::get_pattern);
    ClassDB::bind_method(D_METHOD("set_pattern", "p_pattern"), &Emitter2D::set_pattern);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "bullet_pattern", PROPERTY_HINT_RESOURCE_TYPE, "BulletPattern"), "set_pattern", "get_pattern");

    ClassDB::bind_method(D_METHOD("get_volley_rate"), &Emitter2D::get_volley_rate);
    ClassDB::bind_method(D_METHOD("set_volley_rate", "p_volley_rate"), &Emitter2D::set_volley_rate);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "volley_rate"), "set_volley_rate", "get_volley_rate");

    ClassDB::bind_method(D_METHOD("get_number_of_volleys"), &Emitter2D::get_number_of_volleys);
    ClassDB::bind_method(D_METHOD("set_number_of_volleys", "p_number_of_volleys"), &Emitter2D::set_number_of_volleys);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "number_of_volleys"), "set_number_of_volleys", "get_number_of_volleys");

    ADD_GROUP("Trajectory", "emitter_trajectory_");
    ClassDB::bind_method(D_METHOD("get_trajectory"), &Emitter2D::get_trajectory);
    ClassDB::bind_method(D_METHOD("set_trajectory", "p_trajectory"), &Emitter2D::set_trajectory);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "trajectory", PROPERTY_HINT_ENUM, "DEFAULT,FIXED,AIMED,RANDOM"), "set_trajectory", "get_trajectory");

    ClassDB::bind_method(D_METHOD("get_towards"), &Emitter2D::get_towards);
    ClassDB::bind_method(D_METHOD("set_towards", "p_towards"), &Emitter2D::set_towards);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aimed_towards", PROPERTY_HINT_NODE_TYPE, "Node2D"), "set_towards", "get_towards");

    ADD_GROUP("Rotation", "emitter_rotation_");
    ClassDB::bind_method(D_METHOD("get_rotation_option"), &Emitter2D::get_rotation_option);
    ClassDB::bind_method(D_METHOD("set_rotation_option", "p_rotation_option"), &Emitter2D::set_rotation_option);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "rotation_option", PROPERTY_HINT_ENUM, "NONE,CONTINUOUS,BOUNCE,RANDOMISE"), "set_rotation_option", "get_rotation_option");

    ClassDB::bind_method(D_METHOD("get_start_rotation"), &Emitter2D::get_start_rotation);
    ClassDB::bind_method(D_METHOD("set_start_rotation", "p_start_rotation"), &Emitter2D::set_start_rotation);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "start_rotation"), "set_start_rotation", "get_start_rotation");

    ClassDB::bind_method(D_METHOD("get_rot_range_deg"), &Emitter2D::get_rot_range_deg);
    ClassDB::bind_method(D_METHOD("set_rot_range", "p_rot_range_deg"), &Emitter2D::set_rot_range);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rotation_range"), "set_rot_range", "get_rot_range_deg");

    ClassDB::bind_method(D_METHOD("get_rotation_speed_deg"), &Emitter2D::get_rotation_speed_deg);
    ClassDB::bind_method(D_METHOD("set_rotation_speed", "p_rotation_speed"), &Emitter2D::set_rotation_speed);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rotation_speed"), "set_rotation_speed", "get_rotation_speed_deg");

    ClassDB::bind_method(D_METHOD("get_spawn_offset"), &Emitter2D::get_spawn_offset);
    ClassDB::bind_method(D_METHOD("set_spawn_offset", "p_spawn_offset"), &Emitter2D::set_spawn_offset);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spawn_offset"), "set_spawn_offset", "get_spawn_offset");

    ADD_SIGNAL(MethodInfo("volley"));
    ADD_SIGNAL(MethodInfo("finished_emitting"));

    BIND_ENUM_CONSTANT(Trajectory::DEFAULT);
    BIND_ENUM_CONSTANT(Trajectory::FIXED);
    BIND_ENUM_CONSTANT(Trajectory::AIMED);
    BIND_ENUM_CONSTANT(Trajectory::RANDOM);
    BIND_ENUM_CONSTANT(RotationOption::NONE);
    BIND_ENUM_CONSTANT(RotationOption::CONTINUOUS);
    BIND_ENUM_CONSTANT(RotationOption::BOUNCE);
    BIND_ENUM_CONSTANT(RotationOption::RANDOMISE);
}


Emitter2D::Emitter2D() {
}


Emitter2D::~Emitter2D() {
}


void Emitter2D::_ready() {
    if (!Engine::get_singleton()->is_editor_hint()) {
        time_to_wait = 1 / get_volley_rate();
        current_timer = time_to_wait;
        current_rotation = Math::deg_to_rad(get_start_rotation());
        if (is_spawn_on_start()) {
            start_emitting();
        }
    }
}


void Emitter2D::start_emitting() {
    spawning = true;
    if (get_number_of_volleys() > 0) {
        volleys_left = get_number_of_volleys();
    }
}


void Emitter2D::stop_emitting() {
    spawning = false;
}


void Emitter2D::_process(double delta) {
    if (!Engine::get_singleton()->is_editor_hint()) {
        if (spawning) {
            current_timer = current_timer - delta;
            if (current_timer <= 0) {
                current_timer = time_to_wait;
                do_volley();
            }
            rotate(delta);
        }
    }
}


void Emitter2D::do_volley() {
    switch (get_trajectory()) {
        case DEFAULT:
            pattern->fire(get_usable_pool(), get_settings(), get_global_position(), get_spawn_offset(), current_rotation);
            break;
        case FIXED:
            pattern->fire_fixed(get_usable_pool(), get_settings(), get_global_position(), get_spawn_offset(), current_rotation, current_rotation);
            break;
        case AIMED:
            pattern->fire_aimed(get_usable_pool(), get_settings(), get_global_position(), get_spawn_offset(), current_rotation, towards->get_global_position());
            break;
        case RANDOM:
            pattern->fire_random(get_usable_pool(), get_settings(), get_global_position(), get_spawn_offset(), current_rotation);
            break;
    }

    if (get_number_of_volleys() > 0) {
        volleys_left -= 1;
        if (volleys_left == 0) {
            stop_emitting();
        }
    }
}


PackedStringArray Emitter2D::_get_configuration_warnings() const {  // Saving me from myself.
    PackedStringArray to_return = PackedStringArray();
    if (get_usable_pool() == nullptr) {
        to_return.append("This node cannot function without being assigned a BulletPool.");
    }
    if (get_settings().is_null()) {
        to_return.append("Please provide some BulletSettings.");
    }
    if (get_trajectory() == AIMED && get_towards() == nullptr) {
        to_return.append("The emitter's trajectory is set to Aimed. Please assign aimed_towards.");
    }
    return to_return;
}


void Emitter2D::rotate(double delta) {
    if (get_rotation_option() == NONE) { return; }

    double init_r = Math::deg_to_rad(get_start_rotation());

    if (get_rotation_option() == RANDOMISE) {
        current_rotation = UtilityFunctions::randf_range(init_r, init_r + get_rot_range());
        return;
    }

    current_rotation += get_rotation_speed() * delta;

    if (
        (get_rot_range() >= 0 && (current_rotation > get_rot_range() + init_r || current_rotation < init_r))  // range is positive (clockwise)
        || (get_rot_range() < 0 && (current_rotation < get_rot_range() + init_r || current_rotation > init_r))  // range is negative (anticlockwise)
    ) {
        switch (get_rotation_option()) {
            case CONTINUOUS:
                if (current_rotation > 0) { current_rotation -= get_rot_range(); }
                else { current_rotation += get_rot_range(); }
                break;
            case BOUNCE:
                set_rotation_speed(-get_rotation_speed_deg());
                break;
        }
    }
}
