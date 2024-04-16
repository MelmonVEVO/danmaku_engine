/***************************************************/
/*  pointpattern.cpp                               */
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

#include <godot_cpp/variant/utility_functions.hpp>
#include "pointpattern.h"

using namespace godot;


void PointPattern::fire(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation) {
    Bullet2D* bullet = pool->get_bullet();
    if (bullet == nullptr) { return; }

    Vector2 start_pos = origin + (Vector2(cos(rotation), sin(rotation)) * offset);

    if (bullet != nullptr) {
        bullet->start(settings, rotation, start_pos);  // TODO ownership
    }
}


void PointPattern::fire_fixed(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation, real_t dir) {
    Bullet2D* bullet = pool->get_bullet();
    if (bullet == nullptr) { return; }

    Vector2 start_pos = origin + (Vector2(cos(rotation), sin(rotation)) * offset);

    if (bullet != nullptr) {
        bullet->start(settings, dir, start_pos);
    }
}


void PointPattern::fire_aimed(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation, Vector2 towards) {
    Bullet2D* bullet = pool->get_bullet();
    if (bullet == nullptr) { return; }

    Vector2 start_pos = origin + (Vector2(cos(rotation), sin(rotation)) * offset);

    if (bullet != nullptr) {
        bullet->start(settings, (towards - start_pos).angle(), start_pos);
    }
}


void PointPattern::fire_random(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation) {
    Bullet2D* bullet = pool->get_bullet();
    if (bullet == nullptr) { return; }

    Vector2 start_pos = origin + (Vector2(cos(rotation), sin(rotation)) * offset);

    if (bullet != nullptr) {
        bullet->start(settings, UtilityFunctions::randf_range(0, 2*Math_PI), start_pos);
    }
}


PointPattern::PointPattern() {
}


PointPattern::~PointPattern() {
}
