/***************************************************/
/*  arcpattern.cpp                                 */
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

#include "arcpattern.h"

using namespace godot;


void ArcPattern::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_bullets_in_arc"), &ArcPattern::get_bullets_in_arc);
    ClassDB::bind_method(D_METHOD("set_bullets_in_arc", "p_bullets_in_arc"), &ArcPattern::set_bullets_in_arc);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "bullets_in_arc"), "set_bullets_in_arc", "get_bullets_in_arc");

    ClassDB::bind_method(D_METHOD("get_arc_angle_deg"), &ArcPattern::get_arc_angle_deg);
    ClassDB::bind_method(D_METHOD("set_arc_angle", "p_arc_angle_deg"), &ArcPattern::set_arc_angle);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "arc_angle"), "set_arc_angle", "get_arc_angle_deg");
}


void ArcPattern::fire(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation) {
    double angle_per_bullet = _get_angle_per_bullet();

    for (uint32_t i = 0; i < get_bullets_in_arc(); i++) {
        double bullet_angle = angle_per_bullet * i + rotation - (get_arc_angle() * 0.5);

        Vector2 start_pos = origin + (Vector2(cos(bullet_angle), sin(bullet_angle)) * offset);

        pool->start_bullet(settings, bullet_angle, start_pos);
    }
}


void ArcPattern::fire_fixed(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation, real_t dir) {
    double angle_per_bullet = _get_angle_per_bullet();

    for (uint32_t i = 0; i < get_bullets_in_arc(); i++) {
        double bullet_angle = angle_per_bullet * i + rotation - (get_arc_angle() * 0.5);

        Vector2 start_pos = origin + (Vector2(cos(bullet_angle), sin(bullet_angle)) * offset);

        pool->start_bullet(settings, dir, start_pos);
    }
}


void ArcPattern::fire_aimed(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation, Vector2 towards) {
    double angle_per_bullet = _get_angle_per_bullet();

    for (uint32_t i = 0; i < get_bullets_in_arc(); i++) {
        double bullet_angle = angle_per_bullet * i + rotation - (get_arc_angle() * 0.5);

        Vector2 start_pos = origin + (Vector2(cos(bullet_angle), sin(bullet_angle)) * offset);

        pool->start_bullet(settings, (towards - start_pos).angle(), start_pos);
    }
}


void ArcPattern::fire_random(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation) {
    double angle_per_bullet = _get_angle_per_bullet();

    for (uint32_t i = 0; i < get_bullets_in_arc(); i++) {
        double bullet_angle = angle_per_bullet * i + rotation - (get_arc_angle() * 0.5);

        Vector2 start_pos = origin + (Vector2(cos(bullet_angle), sin(bullet_angle)) * offset);

        pool->start_bullet(settings, UtilityFunctions::randf_range(0, 2*Math_PI), start_pos);
    }
}


double ArcPattern::_get_angle_per_bullet() {
    return arc_angle_rad / (float(bullets_in_arc) - 1.0);
}


ArcPattern::ArcPattern() {
}


ArcPattern::~ArcPattern() {
}
