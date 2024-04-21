/***************************************************/
/*  bulletpool.cpp                                 */
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
#include <godot_cpp/classes/physics_server2d.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/world2d.hpp>
#include <assert.h>

#include "bulletpool.h"

using namespace godot;


void BulletPool::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_current_bullets"), &BulletPool::get_current_bullets);
    ClassDB::bind_method(D_METHOD("start_bullet", "settings", "angle", "init_position", "owner"), &BulletPool::start_bullet);
    ClassDB::bind_method(D_METHOD("kill_em_all"), &BulletPool::kill_em_all);
    ClassDB::bind_method(D_METHOD("remove_bullet_by_rid", "rid"), &BulletPool::remove_bullet_by_rid);

    ClassDB::bind_method(D_METHOD("get_pool_size"), &BulletPool::get_pool_size);
	ClassDB::bind_method(D_METHOD("set_pool_size", "p_pool_size"), &BulletPool::set_pool_size);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "pool_size", PROPERTY_HINT_RANGE, "100,20000,100"), "set_pool_size", "get_pool_size");

    ClassDB::bind_method(D_METHOD("get_phys_layer"), &BulletPool::get_phys_layer);
    ClassDB::bind_method(D_METHOD("set_phys_layer", "phys_layer"), &BulletPool::set_phys_layer);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "physics_layer", PROPERTY_HINT_LAYERS_2D_PHYSICS), "set_phys_layer", "get_phys_layer");
}


BulletPool::BulletPool() {
}


BulletPool::~BulletPool() {
    if (pool == nullptr) { return; }

    PhysicsServer2D* server = PhysicsServer2D::get_singleton();
    for (uint32_t i = 0; i < get_pool_size(); i++) {
        server->free_rid(pool[i].physics_body);
    }
    delete[] pool;
}


void BulletPool::_ready() {
    set_process(false);
    set_physics_process(false);

    if (Engine::get_singleton()->is_editor_hint()) { return; }

    set_physics_process(true);
    initialise_pool();
}


void BulletPool::_physics_process(double delta) {
    process_bullets(delta);
}


void BulletPool::initialise_pool() {
    pool = new Bullet[get_pool_size()];

    available_bullets = pool;

    PhysicsServer2D* server = PhysicsServer2D::get_singleton();
    RID space = get_world_2d()->get_space();

    Transform2D transform = Transform2D();

    for (int32_t i = 0; i < get_pool_size(); i++) {
        pool[i].physics_body = server->body_create();

        server->body_set_mode(pool[i].physics_body, PhysicsServer2D::BODY_MODE_KINEMATIC);
        server->body_set_space(pool[i].physics_body, space);

        server->body_set_collision_mask(pool[i].physics_body, 0);
        server->body_set_collision_layer(pool[i].physics_body, get_phys_layer());

        transform.set_origin(Vector2(0, 0));

        server->body_set_state(pool[i].physics_body, PhysicsServer2D::BODY_STATE_TRANSFORM, transform);

        rid_to_pool_pos_map[pool[i].physics_body.get_id()] = i;

        pool[i].next = &pool[i+1];
    }
    pool[get_pool_size() - 1].next = nullptr;  // I don't like how the last iteration accesses unallocated memory but hey, It Works
}


// void BulletPool::connect_bullet_clear(Callable method_to_connect_to) {  // TODO Hack this another day
//     for (uint32_t i = 0; i < get_pool_size(); i++) {
//         callable_mp(method_to_connect_to.get_object, method_to_connect_to)
//         pool[i].connect("clear", method_to_connect_to);
//     }
// }


// FIRE IN THE HOLE
void BulletPool::start_bullet(Ref<BulletSettings> settings, double angle, Vector2 init_position, Node* owner) {
    if (available_bullets == nullptr) { return; }

    Bullet* bullet = available_bullets;

    bullet->active = true;
    bullet->ttl = settings->get_ttl();
    bullet->velocity = Vector2(cos(angle), sin(angle)) * settings->get_initial_speed();
    bullet->ang_vel = Math::deg_to_rad(settings->get_ang_vel());
    bullet->acceleration = settings->get_acceleration();
    bullet->position = init_position;
    bullet->texture = settings->get_texture();
    bullet->directed_texture = settings->is_directed_texture();

    PhysicsServer2D* server = PhysicsServer2D::get_singleton();

    // if (owner != nullptr && owner->has_signal("clear_owned_bullets")) {
    //     // owner->connect("clear_owned_bullets", callable_mp(this, &Bullet2D::clear)); TODO Owned bullet clearing
    //     bullet->current_owner = owner;
    // }

    if (server->body_get_shape_count(bullet->physics_body) == 0) {
        server->body_add_shape(bullet->physics_body, settings->get_bullet_shape_rid());
    }
    else {
        server->body_set_shape(bullet->physics_body, 0, settings->get_bullet_shape_rid());
    }

    server->body_set_shape_disabled(bullet->physics_body, 0, false);

    increment_current_bullet_count();

    available_bullets = bullet->next;
}


// TODO Measure performance with tracy or something
void BulletPool::process_bullets(double delta) {  // TODO Maybe multithread this if performance still takes a hit?
    if (current_bullet_count == 0) { return; }

    Bullet* bullet;

    Transform2D transform = Transform2D();
    PhysicsServer2D* server = PhysicsServer2D::get_singleton();

    for (uint32_t i = 0; i < get_pool_size(); i++) {  // TODO Iterates over all bullets for now until I think of a good way to implement a "active bullet" array thingy
        bullet = &pool[i];
        if (!bullet->active) { continue; }

        if (bullet->ang_vel != 0.0) {
            bullet->velocity = bullet->velocity.rotated(bullet->ang_vel * delta);
        }

        bullet->velocity = bullet->velocity + (bullet->velocity.normalized() * (bullet->acceleration * delta));

        bullet->position = bullet->position + (bullet->velocity * delta);

        transform.set_origin(bullet->position);
        server->body_set_state(bullet->physics_body, PhysicsServer2D::BODY_STATE_TRANSFORM, transform);

        bullet->ttl = bullet->ttl - delta;

        if (bullet->ttl < 0.0) { disable_bullet(bullet); }
        // else if (get_world_2d()->get_direct_space_state()->intersect_shape()) {}
    }
    queue_redraw();
}


void BulletPool::kill_em_all() {
    Bullet* bullet;

    for (uint32_t i = 0; i < get_pool_size(); i++) {
        bullet = &pool[i];
        if (!bullet->active) { continue; }

        disable_bullet(bullet);
    }
    reset_current_bullet_count();
}


void BulletPool::disable_bullet(Bullet* bullet) {
    decrement_current_bullet_count();

    PhysicsServer2D::get_singleton()->call_deferred("body_set_shape_disabled", bullet->physics_body, 0, true);
    bullet->next = available_bullets;
    available_bullets = bullet;
    bullet->active = false;
}


void BulletPool::remove_bullet_by_rid(RID body) {
    if (rid_to_pool_pos_map.find(body.get_id()) == rid_to_pool_pos_map.end()) { return; }

    disable_bullet(&pool[rid_to_pool_pos_map[body.get_id()]]);
}


void BulletPool::_draw() {
    if (current_bullet_count == 0) { return; }
    Bullet* bullet;

    for (uint32_t i = 0; i < get_pool_size(); i++) {
        bullet = &pool[i];
        if (!bullet->active) { continue; }

        Vector2 offset = -bullet->texture->get_size() * 0.5;

        if (bullet->directed_texture) {
            draw_set_transform(bullet->position + offset, bullet->velocity.angle());
        }
        else {
            draw_set_transform(bullet->position + offset);
        }

        draw_texture(bullet->texture, Vector2());        
    }
}
