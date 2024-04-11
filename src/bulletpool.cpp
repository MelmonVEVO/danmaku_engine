/***************************************************/
/*  bulletpool.cpp                                 */
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
#include <godot_cpp/classes/physics_server2d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <assert.h>

#include "bulletpool.h"
#include "bullet2d.h"


using namespace godot;


void BulletPool::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_current_bullets"), &BulletPool::get_current_bullets);

    ADD_SIGNAL(MethodInfo("clear_all_bullets"));

    ClassDB::bind_method(D_METHOD("get_pool_size"), &BulletPool::get_pool_size);
	ClassDB::bind_method(D_METHOD("set_pool_size", "p_pool_size"), &BulletPool::set_pool_size);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "pool_size", PROPERTY_HINT_RANGE, "100,20000,100"), "set_pool_size", "get_pool_size");
}


BulletPool::BulletPool() {
}


BulletPool::~BulletPool() {
    if (pool != nullptr) {
        for (uint32_t i = 0; i < get_pool_size(); i++) {
            memdelete(&pool[i]);
        }
        memdelete_arr(pool);
    }

    PhysicsServer2D::get_singleton()->free_rid(bullet_shape);
}


void BulletPool::_ready() {
    set_process(false);
    set_physics_process(false);
    if (!Engine::get_singleton()->is_editor_hint()) {  // make sure _ready only runs in game
        PhysicsServer2D* server = PhysicsServer2D::get_singleton();
        bullet_shape = server->circle_shape_create();
        server->shape_set_data(bullet_shape, 2);

        initialise_pool();
    }
}


void BulletPool::initialise_pool() {
    pool = (Bullet2D*) memalloc(sizeof(Bullet2D) * get_pool_size());

    for (int32_t i = 0; i < get_pool_size(); i++) {
        memnew_placement(&pool[i], Bullet2D);
        add_child(&pool[i]);
        pool[i].connect("standby", callable_mp(this, &BulletPool::return_bullet));
    }

    first_available = pool;  // set up the free list of available bullets

    for (int32_t i = 0; i < get_pool_size() - 1; i++) {
        pool[i].set_next(&pool[i+1]);
    }

    pool[get_pool_size() - 1].set_next(nullptr);
}


Bullet2D* BulletPool::get_bullet() {
    if (first_available != nullptr) {
        Bullet2D* to_return = first_available;
        first_available = to_return->get_next();
        increment_current_bullets();
        return to_return;
    }
    return nullptr;
}


void BulletPool::return_bullet(Bullet2D* bullet) {
    if (!first_available) {
        first_available = bullet;
    }
    else {
        bullet->set_next(first_available);
        first_available = bullet;
    }
    decrement_current_bullets();
}
