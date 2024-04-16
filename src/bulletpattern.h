/***************************************************/
/*  bulletpattern.h                                */
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

#ifndef BULLET_PATTERN_H
#define BULLET_PATTERN_H

#include <godot_cpp/classes/resource.hpp>
#include "bulletsettings.h"
#include "bulletpool.h"


namespace godot {  // There's probably a better way to do this, but for now, resources are pretty good for this.
class BulletPattern : public Resource {
    GDCLASS(BulletPattern, Resource)

protected:
    static void _bind_methods();

public:
    BulletPattern();
    ~BulletPattern();

    virtual void fire(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation) {};
    virtual void fire_fixed(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation, real_t dir) {};
    virtual void fire_aimed(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation, Vector2 towards) {};
    virtual void fire_random(BulletPool* pool, Ref<BulletSettings> settings, Vector2 origin, real_t offset, real_t rotation) {};
};
}

#endif