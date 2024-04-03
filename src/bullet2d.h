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
    RID physics_body;

    // static struct PhysicsShapeStruct {  // single physics shape hack
    //     RID shape;
    //     PhysicsShapeStruct() {
    //         PhysicsServer2D* server = PhysicsServer2D::get_singleton();

    //         shape = server->circle_shape_create();
    //         server->shape_set_data(shape, 2);
    //     }
    //     ~PhysicsShapeStruct() {
    //         PhysicsServer2D* server = PhysicsServer2D::get_singleton();

    //         server->free_rid(shape);
    //     }
    // } physics_shape;

    union BulletState {
        struct {
            // Physics stuff
            uint32_t collision_layer = 1;

            // Bullet information
            double ttl;
            Node* current_owner;
            Vector2 velocity;
            real_t ang_vel;
            real_t acceleration;
        } live;

        Bullet2D* next;

        BulletState() {}
    } bullet_state;


protected:
    static void _bind_methods();
    

public:
    Bullet2D();
    ~Bullet2D();
    void _physics_process(double delta) override;
    void _process(double delta) override;
    void clear();
    void initialise(real_t angle, real_t init_speed, uint32_t p_layer, double init_ttl, real_t accel=0, real_t angular_velocity=0, Node* owner=NULL);
    void start();
    void standby();

    Bullet2D* get_next() const { return bullet_state.next; }
    void set_next(Bullet2D* next) { bullet_state.next = next; }


};
}

#endif
