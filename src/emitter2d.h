/***************************************************/
/*  emitter2d.h                                    */
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

    // for now only get ring spawner working
    // SpawnType spawn_type;
    int32_t bullets_per_volley;
    //int32_t stack_count;              // Wanna stack bullets?
    //real_t time_between_stacks;
    bool spawn_on_start;
    real_t spawn_rate;
    //real_t spawn_offset;              // How far in game units to spawn away from the emitter.
    //int32_t volley_count;             // How many volleys to do after emitter starts spawning. Infinite if -1.
    //real_t rotation_rate;             // Rotation rate of the emitter in radians.
    //RotationOption rotation_option;

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
    // void clear_owned_bullets();
    // void start_spawning();
    // void do_volley();                 // A volley is a single spawn of a group of bullets.

    
    // Setters and getters. My word!
    void set_settings(Ref<BulletSettings> p_settings) { settings = p_settings; };
    Ref<BulletSettings> get_settings() const { return settings; };

    void set_usable_pool(BulletPool* p_usable_pool) { usable_pool = p_usable_pool; };
    BulletPool* get_usable_pool() const { return usable_pool; };

    // void set_spawn_type(SpawnType p_spawn_type);
    // SpawnType get_spawn_type() const;

    void set_bullets_per_volley(int32_t p_bullets_per_volley) { bullets_per_volley = p_bullets_per_volley; };
    int32_t get_bullets_per_volley() const { return bullets_per_volley; };

    // void set_stack_count(int32_t p_stack_count);
    // int32_t get_stack_count() const;

    void set_spawn_on_start(bool p_spawn_on_start) { spawn_on_start = p_spawn_on_start; };
    bool is_spawn_on_start() const { return spawn_on_start; };

    void set_spawn_rate(real_t p_spawn_rate) { spawn_rate = p_spawn_rate; };
    real_t get_spawn_rate() const { return spawn_rate; };

    // void set_volley_count(int32_t p_volley_count);
    // int32_t get_volley_count() const;

    // void set_spawn_offset(real_t p_spawn_offset);
    // real_t get_spawn_offset() const;

    // void set_rotation_rate(real_t p_rotation_rate);
    // real_t get_rotation_rate() const;

    // void set_rotation_option(RotationOption p_rotation_option);
    // RotationOption get_rotation_option() const;
};
}

#endif
