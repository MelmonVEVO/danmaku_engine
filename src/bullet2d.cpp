/***************************************************/
/*  bullet2d.cpp                                   */
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


#include "bullet2d.h"
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/world2d.hpp>
#include <godot_cpp/classes/physics_server2d.hpp>
#include <godot_cpp/variant/string_name.hpp>

using namespace godot;


void Bullet2D::_bind_methods() {
    ADD_SIGNAL(MethodInfo("standby", PropertyInfo(Variant::OBJECT, "target", PROPERTY_HINT_RESOURCE_TYPE, "Bullet2D")));
    ADD_SIGNAL(MethodInfo("cleared"));
}


Bullet2D::Bullet2D() {
    server = PhysicsServer2D::get_singleton();
    current_owner = NULL;

    physics_body = server->body_create();
    server->body_set_mode(physics_body, PhysicsServer2D::BODY_MODE_RIGID);
    physics_shape = server->circle_shape_create();
    server->shape_set_data(physics_shape, 4);

    server->body_add_shape(physics_body, physics_shape);
    server->body_set_space(physics_body, get_world_2d()->get_space());
    server->body_add_shape(physics_body, physics_shape);
    server->body_set_collision_mask(physics_body, 0);

    server->body_set_state(physics_body, PhysicsServer2D::BODY_STATE_TRANSFORM, get_global_transform());

    initialise(0.0, 0.0, 0, 0.0, 0);

    server->body_set_shape_disabled(physics_body, 0, true);

    set_process(false);
    set_physics_process(false);
    hide();
}


// Updates the properties of a bullet.
void Bullet2D::initialise(real_t angle, real_t init_speed, uint32_t p_layer, double init_ttl, real_t hitbox_radius, real_t accel, real_t angular_velocity, Node* owner) {
    ttl = init_ttl;
    velocity = Vector2(cos(angle), sin(angle)) * init_speed;
    ang_vel = angular_velocity;
    acceleration = accel;

    server->shape_set_data(physics_shape, hitbox_radius);
    server->body_set_collision_layer(physics_body, p_layer);
    
    server->body_set_collision_layer(physics_body, p_layer);
    if (owner && owner->has_signal("clear_owned_bullets")) {
        owner->connect("clear_owned_bullets", callable_mp(this, &Bullet2D::clear));
        current_owner = owner;
    }
}


void Bullet2D::_physics_process(double delta) {  // maybe multithread this if performance still takes a hit?
    if (ang_vel != 0.0) {
        velocity = velocity.rotated(ang_vel * delta);
    }
    set_position(get_position() + (velocity * delta));
    server->body_set_state(physics_body, PhysicsServer2D::BODY_STATE_TRANSFORM, get_global_transform());
}


void Bullet2D::_process(double delta) {
    ttl = ttl - delta;
    if (ttl < 0.0) {
        standby();
    }
}


// Starts the processing of the single bullet.
void Bullet2D::start() {
    set_physics_process(true);
    server->body_set_shape_disabled(physics_body, 0, false);
    show();
}


// Makes the bullet emit the cleared signal, then stands by.
void Bullet2D::clear() {
    emit_signal("cleared");
    standby();
}


// This makes the bullet return to the bullet pool and stands by.
// Mostly used by itself if a bullet times out. clear() may be more appropriate for manually clearing bullets.
void Bullet2D::standby() {
    emit_signal("standby", *this);
    server->body_set_shape_disabled(physics_body, 0, true);
    set_physics_process(false);
    hide();
    if (current_owner) {
        current_owner->disconnect("clear_owned_bullets", callable_mp(this, &Bullet2D::clear));
    }
}


// Cleanup.
Bullet2D::~Bullet2D() {
    server->free_rid(physics_shape);
    server->free_rid(physics_body);
}
