/***************************************************/
/*  bullet2d.h                                     */
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

#ifndef BULLET2D_H
#define BULLET2D_H

#include <godot_cpp/classes/sprite2d.hpp>

#include "bulletsettings.h"


namespace godot {

class Bullet2D : public Sprite2D {
    GDCLASS(Bullet2D, Sprite2D)

private:
    RID physics_body;

    // Physics stuff
    uint32_t collision_layer = 1;

    // Current bullet information
    double ttl = 0.0;
    Node* current_owner = nullptr;
    Vector2 velocity;
    real_t ang_vel = 0.0;
    real_t acceleration = 0.0;

    Bullet2D* next = nullptr;

protected:
    static void _bind_methods();

public:
    Bullet2D();
    ~Bullet2D();
    void _ready() override;
    void _physics_process(double delta) override;
    void clear();
    void start(Ref<BulletSettings> settings, double angle, Vector2 init_position, RID shape, Node* owner=nullptr);
    void set_bullet_shape(RID shape);
    void standby();

    Bullet2D* get_next() const { return next; }
    void set_next(Bullet2D* nextup) { next = nextup; }
};
}

#endif
