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

    ClassDB::bind_method(D_METHOD("get_pool_size"), &BulletPool::get_pool_size);
	ClassDB::bind_method(D_METHOD("set_pool_size", "p_pool_size"), &BulletPool::set_pool_size);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "pool_size", PROPERTY_HINT_RANGE, "100,20000,100"), "set_pool_size", "get_pool_size");
    
    ADD_SIGNAL(MethodInfo("collision", PropertyInfo(Variant::DICTIONARY, "collider")));
}


BulletPool::BulletPool() {
}


BulletPool::~BulletPool() {
    if (pool == nullptr) { return; }

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
    pool = memnew_arr(Bullet, get_pool_size());

    available_bullets = pool;
    space_state = get_world_2d()->get_direct_space_state();

    PhysicsServer2D* server = PhysicsServer2D::get_singleton();
    RID space = get_world_2d()->get_space();

    Transform2D transform = Transform2D();

    for (int32_t i = 0; i < get_pool_size(); i++) {
        pool[i].query->set_collide_with_areas(true);

        pool[i].next = &pool[i+1];  // I don't like how the last iteration accesses unallocated memory but hey, It Works
    }
    pool[get_pool_size() - 1].next = nullptr;
}


// FIRE IN THE HOLE
void BulletPool::start_bullet(Ref<BulletSettings> settings, double angle, Vector2 init_position, Node* owner) {
    if (available_bullets == nullptr) { return; }

    Bullet* bullet = available_bullets;

    bullet->ttl = settings->get_ttl();
    bullet->velocity = Vector2(cos(angle), sin(angle)) * settings->get_initial_speed();
    bullet->ang_vel = Math::deg_to_rad(settings->get_ang_vel());
    bullet->acceleration = settings->get_acceleration();
    bullet->position = init_position;
    bullet->texture = settings->get_texture();

    bullet->query->set_shape_rid(settings->get_bullet_shape_rid());
    bullet->query->set_collision_mask(settings->get_phys_mask());

    increment_current_bullet_count();

    available_bullets = bullet->next;
    active_bullets.push_back(*bullet);
}


// TODO Measure performance with tracy or something
void BulletPool::process_bullets(double delta) {  // TODO Maybe multithread this if performance still takes a hit?
    if (current_bullet_count == 0) { return; }

    Bullet* bullet;
    Transform2D transform = Transform2D();

    for (auto & bul : active_bullets) {
        Bullet* bullet = &bul;
        
        // Physics value calculation
        if (bullet->ang_vel != 0.0) {
            bullet->velocity = bullet->velocity.rotated(bullet->ang_vel * delta);
        }
        bullet->velocity = bullet->velocity + (bullet->velocity.normalized() * (bullet->acceleration * delta));
        bullet->position = bullet->position + (bullet->velocity * delta);
        transform.set_origin(bullet->position);
        bullet->query->set_transform(transform);

        // Colliding
        TypedArray<Dictionary> result = space_state->intersect_shape(bullet->query, 1);
        if (!result.is_empty()) {
            emit_signal("collision", result[0]);
            bool tmp = false;
            if (result[0].get_named("collider", tmp).has_method("hit")) {
                result[0].get_named("collider", tmp).call("hit");
            }
            disable_bullet(bullet);
            active_bullets.
            return;
        }

        bullet->ttl = bullet->ttl - delta;
        if (bullet->ttl < 0.0) { disable_bullet(bullet); }
    }
    queue_redraw();
}


void BulletPool::kill_em_all() {
    for (auto & bul : active_bullets) {
        disable_bullet(&bul);
    }
    reset_current_bullet_count();
    active_bullets.clear();
}


void BulletPool::disable_bullet(Bullet* bullet) {
    decrement_current_bullet_count();
    bullet->next = available_bullets;
    available_bullets = bullet;
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
