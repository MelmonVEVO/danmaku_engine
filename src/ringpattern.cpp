/***************************************************/
/*  ringpattern.cpp                                */
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
#include "ringpattern.h"

using namespace godot;


void RingPattern::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_bullets_in_ring"), &RingPattern::get_bullets_in_ring);
    ClassDB::bind_method(D_METHOD("set_bullets_in_ring", "p_bullets_in_ring"), &RingPattern::set_bullets_in_ring);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "bullets_in_ring"), "set_bullets_in_ring", "get_bullets_in_ring");

}


void RingPattern::fire(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation) {
    double angle_per_bullet = (2.0 * Math_PI) / ((double) get_bullets_in_ring());

    for (uint32_t i = 0; i < get_bullets_in_ring(); i++) {
        double bullet_angle = angle_per_bullet * i + rotation;

        Bullet2D* bullet = pool->get_bullet();

        if (bullet == nullptr) { return; }

        Vector2 start_pos = origin + (Vector2(cos(bullet_angle), sin(bullet_angle)) * offset);

        bullet->start(settings, bullet_angle, start_pos);
    }
}


void RingPattern::fire_fixed(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation, real_t dir) {
    double angle_per_bullet = (2.0 * Math_PI) / ((double) get_bullets_in_ring());

    for (uint32_t i = 0; i < get_bullets_in_ring(); i++) {
        double bullet_angle = angle_per_bullet * i + rotation;

        Bullet2D* bullet = pool->get_bullet();

        if (bullet == nullptr) { return; }

        Vector2 start_pos = origin + (Vector2(cos(bullet_angle), sin(bullet_angle)) * offset);

        bullet->start(settings, dir, start_pos);
    }
}


void RingPattern::fire_aimed(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation, Vector2 towards) {
    double angle_per_bullet = (2.0 * Math_PI) / ((double) get_bullets_in_ring());

    for (uint32_t i = 0; i < get_bullets_in_ring(); i++) {
        double bullet_angle = angle_per_bullet * i + rotation;

        Bullet2D* bullet = pool->get_bullet();

        if (bullet == nullptr) { return; }

        Vector2 start_pos = origin + (Vector2(cos(bullet_angle), sin(bullet_angle)) * offset);

        bullet->start(settings, (towards - start_pos).angle(), start_pos);
    }
}


void RingPattern::fire_random(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation) {
    double angle_per_bullet = (2.0 * Math_PI) / ((double) get_bullets_in_ring());

    for (uint32_t i = 0; i < get_bullets_in_ring(); i++) {
        double bullet_angle = angle_per_bullet * i + rotation;

        Bullet2D* bullet = pool->get_bullet();

        if (bullet == nullptr) { return; }

        Vector2 start_pos = origin + (Vector2(cos(bullet_angle), sin(bullet_angle)) * offset);

        bullet->start(settings, UtilityFunctions::randf_range(0, 2*Math_PI), start_pos);
    }
}


RingPattern::RingPattern() {
}


RingPattern::~RingPattern() {
}
