/***************************************************/
/*  emitter2d.h                                    */
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

#ifndef EMITTER2D_H
#define EMITTER2D_H

#include <godot_cpp/classes/marker2d.hpp>

#include "bulletsettings.h"
#include "bulletpool.h"


namespace godot {

class Emitter2D : public Marker2D {
    GDCLASS(Emitter2D, Marker2D)

public:
    // enum SpawnType {
    //     POINT,
    //     DIRECTIONAL,
    //     RING,
    //     ARC
    // };
    // enum RotationOption {
    //     CONTINUOUS,
    //     RANDOMISE,
    //     AIMED
    // };

private:
    Ref<BulletSettings> settings;
    BulletPool* usable_pool = nullptr;

    // Spawning properties
    // SpawnType spawn_type;
    int32_t bullets_per_volley = 1;  // For the ring spawner
    //int32_t stack_count;
    //real_t time_between_stacks;
    bool spawn_on_start = false;
    real_t volley_rate = 2.0;
    real_t spawn_offset = 0.0;  // How far in game units to spawn away from the emitter.
    //int32_t volley_count;  // How many volleys to do after emitter starts spawning. Infinite if -1.
    //real_t rotation_rate_deg;  // Rotation rate of the emitter
    //RotationOption rotation_option;

    // Logic variables
    bool spawning;
    double time_to_wait;
    double current_timer;
    double angle_per_bullet;
    //real_t current_added_rotation;
    //int32_t current_volley;

protected:
    static void _bind_methods();


public:
    Emitter2D();
    ~Emitter2D();

    void _ready() override;
    void _process(double delta) override;
    PackedStringArray _get_configuration_warnings() const override;
    // void clear_owned_bullets();
    void do_volley();

    
    // Setters and getters. My word!
    void set_settings(Ref<BulletSettings> p_settings) { settings = p_settings; };
    Ref<BulletSettings> get_settings() const { return settings; };

    void set_usable_pool(BulletPool* p_usable_pool) { usable_pool = p_usable_pool; };
    BulletPool* get_usable_pool() const { return usable_pool; };

    void set_bullets_per_volley(int32_t p_bullets_per_volley) { bullets_per_volley = p_bullets_per_volley; };
    int32_t get_bullets_per_volley() const { return bullets_per_volley; };

    void set_spawn_on_start(bool p_spawn_on_start) { spawn_on_start = p_spawn_on_start; };
    bool is_spawn_on_start() const { return spawn_on_start; };

    void set_volley_rate(real_t p_volley_rate) { volley_rate = p_volley_rate; };
    real_t get_volley_rate() const { return volley_rate; };

    void set_spawn_offset(real_t p_spawn_offset) { spawn_offset = p_spawn_offset; };
    real_t get_spawn_offset() const { return spawn_offset; };
};
}

#endif
