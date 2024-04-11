/***************************************************/
/*  bulletsettings.cpp                             */
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

#include <godot_cpp/core/class_db.hpp>

#include "bulletsettings.h"

using namespace godot;


void BulletSettings::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_texture"), &BulletSettings::get_texture);
    ClassDB::bind_method(D_METHOD("set_texture", "p_texture"), &BulletSettings::set_texture);

    ClassDB::bind_method(D_METHOD("get_initial_speed"), &BulletSettings::get_initial_speed);
    ClassDB::bind_method(D_METHOD("set_initial_speed", "p_initial_speed"), &BulletSettings::set_initial_speed);

    ClassDB::bind_method(D_METHOD("get_acceleration"), &BulletSettings::get_acceleration);
    ClassDB::bind_method(D_METHOD("set_acceleration", "p_acceleration"), &BulletSettings::set_acceleration);

    ClassDB::bind_method(D_METHOD("get_ang_vel"), &BulletSettings::get_ang_vel);
    ClassDB::bind_method(D_METHOD("set_ang_vel", "p_ang_vel"), &BulletSettings::set_ang_vel);

    ClassDB::bind_method(D_METHOD("get_phys_layer"), &BulletSettings::get_phys_layer);
    ClassDB::bind_method(D_METHOD("set_phys_layer", "phys_layer"), &BulletSettings::set_phys_layer);

    ClassDB::bind_method(D_METHOD("get_ttl"), &BulletSettings::get_ttl);
    ClassDB::bind_method(D_METHOD("set_ttl", "p_ttl"), &BulletSettings::set_ttl);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "bullet_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_texture", "get_texture");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "initial_speed"), "set_initial_speed", "get_initial_speed");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "acceleration"), "set_acceleration", "get_acceleration");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "ang_vel", PROPERTY_HINT_RANGE, "-360,360"), "set_ang_vel", "get_ang_vel");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "phys_layer", PROPERTY_HINT_LAYERS_2D_PHYSICS), "set_phys_layer", "get_phys_layer");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "ttl"), "set_ttl", "get_ttl");
}