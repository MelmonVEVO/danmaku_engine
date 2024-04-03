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
#include <assert.h>

#include "bulletpool.h"
#include "bullet2d.h"


using namespace godot;


void BulletPool::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_pool_size"), &BulletPool::get_pool_size);
	ClassDB::bind_method(D_METHOD("set_pool_size", "p_pool_size"), &BulletPool::set_pool_size);

    ADD_SIGNAL(MethodInfo("clear_all_bullets"));

    //ADD_PROPERTY(PropertyInfo(Variant::INT, "pool_size", PROPERTY_HINT_RANGE, "5000,20000,100"), "set_pool_size", "get_pool_size");
}


BulletPool::BulletPool() {
    set_pool_size(100);
}


BulletPool::~BulletPool() {  // free the memory of pooled objects
    if (pool) {
        memdelete_arr(pool);
    }
}


void BulletPool::_ready() {
    initialise_pool();
}


void BulletPool::initialise_pool(uint32_t p_pool_size) {
    if (pool) {
        memdelete_arr(pool);  // destroy existing pool if exists
    }

    if (p_pool_size < 0) {  // default p_pool_size = -1, use previous pool size
        pool = memnew_arr(Bullet2D, get_pool_size());
    }
    else {
        pool = memnew_arr(Bullet2D, p_pool_size);
        set_pool_size(p_pool_size);
    }

    first_available = pool;  // set up the free list of available bullets

    for (int32_t i = 0; i < get_pool_size() - 1; i++) {
        pool[i].set_next(&pool[i+1]);
    }

    pool[get_pool_size() - 1].set_next(NULL);
}


Bullet2D* BulletPool::get_bullet() {
    if (first_available) {
        Bullet2D* to_return = first_available;
        first_available = to_return->get_next();
        return to_return;
    }
    else {
        return NULL;
    }
}


void BulletPool::return_bullet(Bullet2D* bullet) {
    if (!first_available) {
        first_available = bullet;
    }
    else {
        bullet->set_next(first_available);
        first_available = bullet;
    }
}
