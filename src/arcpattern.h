/***************************************************/
/*  arcpattern.h                                   */
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

#ifndef ARC_PATTERN_H
#define ARC_PATTERN_H

#include "bulletpattern.h"


namespace godot {

class ArcPattern : public BulletPattern {
    GDCLASS(ArcPattern, BulletPattern)

private:
    uint32_t bullets_in_arc = 2;
    real_t arc_angle_deg = 30.0;

    double arc_angle_rad = Math_PI / 6.0;

protected:
    static void _bind_methods();

public:
    ArcPattern();
    ~ArcPattern();

    void fire(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation) override;
    void fire_fixed(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation, real_t dir) override;
    void fire_aimed(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation, Vector2 towards) override;
    void fire_random(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation) override;

    void set_bullets_in_arc(uint32_t p_bullets_in_arc) { bullets_in_arc = p_bullets_in_arc; };
    uint32_t get_bullets_in_arc() const { return bullets_in_arc; };

    void set_arc_angle(real_t p_arc_angle_deg) {
        arc_angle_deg = p_arc_angle_deg;
        arc_angle_rad = Math::deg_to_rad(p_arc_angle_deg);
    };
    real_t get_arc_angle_deg() const { return arc_angle_deg; };
    double get_arc_angle() const { return arc_angle_rad; };
};


}

#endif
