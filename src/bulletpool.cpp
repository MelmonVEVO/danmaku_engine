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


#include "bulletpool.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


void BulletPool::_bind_methods() {
    ADD_SIGNAL(MethodInfo("clear_all_bullets"));

    ADD_PROPERTY(PropertyInfo(Variant::INT, "current_pool_size"), "set_current_pool_size", "get_current_pool_size");
}


BulletPool::BulletPool() {
}


BulletPool::~BulletPool() {  // free the memory of pooled objects
}


void BulletPool::_ready() {

}


void BulletPool::initialise_pool(uint32_t pool_size) {
    if (bullet_pool) {
        memdelete_arr(bullet_pool);
    }

    if (pool_size < 0) {
        bullet_pool = memnew_arr(Bullet2D, get_current_pool_size());
    }
    else {
        bullet_pool = memnew_arr(Bullet2D, pool_size);
        set_current_pool_size(pool_size);
    }
}


Bullet2D* BulletPool::get_bullet() {}


void BulletPool::set_current_pool_size(uint32_t p_pool_size) {}


void BulletPool::return_bullet(Bullet2D* bullet) {}
