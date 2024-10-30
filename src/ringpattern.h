/***************************************************/
/*  ringpattern.h                                  */
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

#ifndef RING_PATTERN_H
#define RING_PATTERN_H

#include "bulletpattern.h"


namespace godot {

class RingPattern : public BulletPattern {
    GDCLASS(RingPattern, BulletPattern)

private:
    uint32_t bullets_in_ring = 2;
    double angle_per_bullet = 0.0;

protected:
    static void _bind_methods();

public:
    RingPattern();
    ~RingPattern();

    void fire(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation) override;
    void fire_fixed(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation, real_t dir) override;
    void fire_aimed(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation, Vector2 towards) override;
    void fire_random(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation) override;

    void set_bullets_in_ring(uint32_t p_bullets_in_ring) {
        bullets_in_ring = p_bullets_in_ring;
        angle_per_bullet = (2.0 * Math_PI) / ((double) get_bullets_in_ring());
    };
    uint32_t get_bullets_in_ring() const { return bullets_in_ring; };
};


}

#endif
