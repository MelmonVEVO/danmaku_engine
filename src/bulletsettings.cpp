/***************************************************/
/*  bulletsettings.cpp                             */
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
#include <godot_cpp/classes/physics_server2d.hpp>

#include "bulletsettings.h"

using namespace godot;


void BulletSettings::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_texture"), &BulletSettings::get_texture);
    ClassDB::bind_method(D_METHOD("set_texture", "p_texture"), &BulletSettings::set_texture);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "bullet_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_texture", "get_texture");

    ClassDB::bind_method(D_METHOD("is_directed_texture"), &BulletSettings::is_directed_texture);
    ClassDB::bind_method(D_METHOD("set_directed_texture", "p_directed_texture"), &BulletSettings::set_directed_texture);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "directed_texture"), "set_directed_texture", "is_directed_texture");

    ClassDB::bind_method(D_METHOD("get_initial_speed"), &BulletSettings::get_initial_speed);
    ClassDB::bind_method(D_METHOD("set_initial_speed", "p_initial_speed"), &BulletSettings::set_initial_speed);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "initial_speed"), "set_initial_speed", "get_initial_speed");

    ClassDB::bind_method(D_METHOD("get_acceleration"), &BulletSettings::get_acceleration);
    ClassDB::bind_method(D_METHOD("set_acceleration", "p_acceleration"), &BulletSettings::set_acceleration);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "acceleration"), "set_acceleration", "get_acceleration");

    ClassDB::bind_method(D_METHOD("get_ang_vel"), &BulletSettings::get_ang_vel);
    ClassDB::bind_method(D_METHOD("set_ang_vel", "p_ang_vel"), &BulletSettings::set_ang_vel);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_velocity"), "set_ang_vel", "get_ang_vel");

    ClassDB::bind_method(D_METHOD("get_ttl"), &BulletSettings::get_ttl);
    ClassDB::bind_method(D_METHOD("set_ttl", "p_ttl"), &BulletSettings::set_ttl);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "ttl"), "set_ttl", "get_ttl");

    ClassDB::bind_method(D_METHOD("get_radius"), &BulletSettings::get_radius);
    ClassDB::bind_method(D_METHOD("set_radius", "p_radius"), &BulletSettings::set_radius);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "bullet_hitbox_radius"), "set_radius", "get_radius");

    ClassDB::bind_method(D_METHOD("get_max_speed"), &BulletSettings::get_max_speed);
    ClassDB::bind_method(D_METHOD("set_max_speed", "p_max_speed"), &BulletSettings::set_max_speed);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_speed"), "set_max_speed", "get_max_speed");

    ClassDB::bind_method(D_METHOD("get_min_speed"), &BulletSettings::get_min_speed);
    ClassDB::bind_method(D_METHOD("set_min_speed", "p_min_speed"), &BulletSettings::set_min_speed);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "min_speed"), "set_min_speed", "get_min_speed");

    ClassDB::bind_method(D_METHOD("get_bullet_shape_rid"), &BulletSettings::get_bullet_shape_rid);
}


RID BulletSettings::get_bullet_shape_rid() {
    if (bullet_shape.get_id() == 0) {
        PhysicsServer2D* server = PhysicsServer2D::get_singleton();

        bullet_shape = server->circle_shape_create();
        server->shape_set_data(bullet_shape, get_radius());
    }
    return bullet_shape;
}


BulletSettings::BulletSettings() {
}


BulletSettings::~BulletSettings() {
    if (bullet_shape.get_id() != 0) {
        PhysicsServer2D::get_singleton()->free_rid(bullet_shape);
    }
}
