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


namespace godot {

class Bullet2D : public Sprite2D {
    GDCLASS(Bullet2D, Sprite2D)


private:
    // Physics stuff
    PhysicsServer2D* server;
    uint32_t collision_layer = 1;
    RID physics_body;
    RID physics_shape;

    // Bullet information
    double ttl;
    Node* current_owner;
    Vector2 velocity;
    real_t ang_vel;
    real_t acceleration;
    uint32_t phys_layer;

    bool in_use;


protected:
    static void _bind_methods();


public:
    Bullet2D();
    ~Bullet2D();

    void _physics_process(double delta) override;
    void _process(double delta) override;
    void clear();
    void initialise(real_t angle, real_t init_speed, uint32_t p_layer, double init_ttl, real_t hitbox_radius, real_t accel=0, real_t angular_velocity=0, Node* owner=NULL);
    void start();
    void standby();

    bool being_used() const { return in_use; }


};
}

#endif //BULLET2D_H
