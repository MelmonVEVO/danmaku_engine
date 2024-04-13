/***************************************************/
/*  bullet2d.cpp                                   */
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

#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/world2d.hpp>
#include <godot_cpp/classes/physics_server2d.hpp>
#include <godot_cpp/variant/string_name.hpp>

#include "bullet2d.h"

using namespace godot;


void Bullet2D::_bind_methods() {
    ClassDB::bind_method(D_METHOD("clear"), &Bullet2D::clear);
    ClassDB::bind_method(D_METHOD("start"), &Bullet2D::start);
    ClassDB::bind_method(D_METHOD("standby"), &Bullet2D::standby);

    ADD_SIGNAL(MethodInfo("standby", PropertyInfo(Variant::OBJECT, "target", PROPERTY_HINT_RESOURCE_TYPE, "Bullet2D")));
    ADD_SIGNAL(MethodInfo("cleared"));
}


Bullet2D::Bullet2D() {
}


void Bullet2D::_ready() {
    set_process(false);
    set_physics_process(false);

    PhysicsServer2D* server = PhysicsServer2D::get_singleton();
    physics_body = server->body_create();

    server->body_set_mode(physics_body, PhysicsServer2D::BODY_MODE_RIGID);

    server->body_set_collision_mask(physics_body, 0);

    server->body_set_state(physics_body, PhysicsServer2D::BODY_STATE_TRANSFORM, get_global_transform());

    server->body_set_space(physics_body, get_world_2d()->get_space());

    next = nullptr;

    hide();
}


// TODO measure performance with tracy or something
void Bullet2D::_physics_process(double delta) {  // maybe multithread this if performance still takes a hit?
    PhysicsServer2D* server = PhysicsServer2D::get_singleton();

    if (ang_vel != 0.0) {
        velocity = velocity.rotated(ang_vel * delta);
    }
    set_position(get_position() + (velocity * delta));
    server->body_set_state(physics_body, PhysicsServer2D::BODY_STATE_TRANSFORM, get_global_transform());
    ttl = ttl - delta;
    if (ttl < 0.0) {
        standby();
    }
}


// Starts the processing of the bullet.
void Bullet2D::start(Ref<BulletSettings> settings, double angle, Vector2 init_position, Node* owner) {
    set_position(init_position);

    ttl = settings->get_ttl();
    velocity = Vector2(cos(angle), sin(angle)) * settings->get_initial_speed();
    ang_vel = settings->get_ang_vel();
    acceleration = settings->get_acceleration();

    PhysicsServer2D* server = PhysicsServer2D::get_singleton();

    server->body_set_collision_layer(physics_body, settings->get_phys_layer());

    if (owner != nullptr && owner->has_signal("clear_owned_bullets")) {
        // owner->connect("clear_owned_bullets", callable_mp(this, &Bullet2D::clear));
        current_owner = owner;
    }

    set_texture(settings->get_texture());

    if (server->body_get_shape_count(physics_body) == 0) {
        server->body_add_shape(physics_body, settings->get_bullet_shape_rid());
    }
    else {
        server->body_set_shape(physics_body, 0, settings->get_bullet_shape_rid());
    }

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
    PhysicsServer2D* server = PhysicsServer2D::get_singleton();

    emit_signal("standby", this);
    server->body_set_shape_disabled(physics_body, 0, true);
    set_physics_process(false);
    hide();
    if (current_owner != nullptr && current_owner->has_signal("clear_owned_bullets")) {
        current_owner->disconnect("clear_owned_bullets", callable_mp(this, &Bullet2D::clear));
    }
}


// Cleanup.
Bullet2D::~Bullet2D() {
    PhysicsServer2D* server = PhysicsServer2D::get_singleton();
    server->free_rid(physics_body);
}
