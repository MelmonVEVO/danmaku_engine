/***************************************************/
/*  bulletsettings.h                               */
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

#ifndef BULLETSETTINGS_H
#define BULLETSETTINGS_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/texture2d.hpp>


namespace godot {

class BulletSettings : public Resource {
    GDCLASS(BulletSettings, Resource)

private:
    Ref<Texture2D> bullet_texture;
    bool directed_texture = false;
    real_t init_speed = 0.0;
    real_t acceleration = 0.0;
    real_t ang_vel = 0.0;
    real_t ttl = 5.0;
    uint32_t radius = 2;
    real_t max_speed = INFINITY;  // TODO max and min speed
    real_t min_speed = -INFINITY;
    uint32_t phys_mask = 0;

    RID bullet_shape;

protected:
    static void _bind_methods();

public:
    BulletSettings();
    ~BulletSettings();

    void set_texture(Ref<Texture2D> p_texture) { bullet_texture = p_texture; };
    Ref<Texture2D> get_texture() const { return bullet_texture; };

    void set_directed_texture(bool p_directed_texture) { directed_texture = p_directed_texture; };
    bool is_directed_texture() const { return directed_texture; };

    void set_initial_speed(real_t p_initial_speed) { init_speed = p_initial_speed; };
    real_t get_initial_speed() const { return init_speed; };

    void set_acceleration(real_t p_acceleration) { acceleration = p_acceleration; };
    real_t get_acceleration() const { return acceleration; };

    void set_ang_vel(real_t p_ang_vel) { ang_vel = p_ang_vel; };
    real_t get_ang_vel() const { return ang_vel; };

    void set_ttl(real_t p_ttl) { ttl = p_ttl; };
    real_t get_ttl() const { return ttl; };

    void set_radius(uint32_t p_radius) { radius = p_radius; };
    uint32_t get_radius() const { return radius; };

    void set_max_speed(real_t p_max_speed) { max_speed = p_max_speed; };
    real_t get_max_speed() const { return max_speed; };
    
    void set_min_speed(real_t p_min_speed) { min_speed = p_min_speed; };
    real_t get_min_speed() const { return min_speed; };

    void set_phys_mask(uint32_t p_phys_mask) { phys_mask = p_phys_mask; };
    uint32_t get_phys_mask() const { return phys_mask; };

    RID get_bullet_shape_rid();
};

}

#endif
