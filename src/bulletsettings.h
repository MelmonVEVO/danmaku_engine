/***************************************************/
/*  bulletsettings.h                               */
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

#ifndef BULLETSETTINGS_H
#define BULLETSETTINGS_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/texture2d.hpp>


namespace godot {

class BulletSettings : public Resource {
    GDCLASS(BulletSettings, Resource)

private:
    Ref<Texture2D> bullet_texture;
    real_t init_speed;
    real_t acceleration;
    real_t ang_vel;
    uint32_t phys_layer;
    real_t ttl;

protected:
    static void _bind_methods();

public:
    void set_texture(Ref<Texture2D> p_texture) { bullet_texture = p_texture; };
    Ref<Texture2D> get_texture() const { return bullet_texture; };

    void set_initial_speed(real_t p_initial_speed) { init_speed = p_initial_speed; };
    real_t get_initial_speed() const { return init_speed; };

    void set_acceleration(real_t p_acceleration) { acceleration = p_acceleration; };
    real_t get_acceleration() const { return acceleration; };

    void set_ang_vel(real_t p_ang_vel) { ang_vel = p_ang_vel; };
    real_t get_ang_vel() const { return ang_vel; };

    void set_phys_layer(uint32_t p_phys_layer) { phys_layer = p_phys_layer; };
    uint32_t get_phys_layer() const { return phys_layer; };

    void set_ttl(real_t p_ttl) { ttl = p_ttl; };
    real_t get_ttl() const { return ttl; };
};

}

#endif
