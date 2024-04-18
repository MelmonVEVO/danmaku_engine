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
#include <godot_cpp/classes/node2d.hpp>

#include "bulletsettings.h"
#include "bulletpool.h"
#include "bulletpattern.h"


namespace godot {

class Emitter2D : public Marker2D {
    GDCLASS(Emitter2D, Marker2D)

public:
    enum Trajectory {  // The direction the bullets move.
        DEFAULT = 0,  // No change. Bullets move as they normally do.
        FIXED = 1,  // Every bullet moves in the *same* direction.
        AIMED = 2,  // Every bullet moves towards a certain Node2D, normally the player.
        RANDOM = 3  // Every bullet has a random trajectory.
    };
    enum RotationOption {  // The rate the emitter's direction spins
        NONE = 0,  // No rotation
        CONTINUOUS = 1,  // Goes from start to end of the rot_range
        BOUNCE = 2,  // Bounces between the rot_range range
        RANDOMISE = 3  // Picks a random direction within the rot_range
    };

private:
    Ref<BulletSettings> settings;
    Ref<BulletPattern> pattern;
    BulletPool* usable_pool = nullptr;

    // =+ Spawning properties += //
    Emitter2D::Trajectory trajectory = DEFAULT;
    bool spawn_on_start = false;
    real_t volley_rate = 2.0;
    int32_t number_of_volleys = -1;
    real_t spawn_offset = 0.0;  // How far in game units to spawn away from the emitter.
    Node2D* towards = nullptr;
    Emitter2D::RotationOption rotation_option = NONE;
    real_t start_rotation = 0.0;
    real_t rot_range_deg = 360.0;
    real_t rotation_speed_deg = 0.0;
    uint64_t seed = 0;

    // =+ Logic variables += //
    bool spawning = false;

    double current_rotation;  // in radians
    double rot_range = 2 * Math_PI;  // in radians
    double rotation_speed;

    double time_to_wait;
    double current_timer;
    int32_t volleys_left;

    double time_between_stacks;
    
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

    void set_spawn_on_start(bool p_spawn_on_start) {
        spawn_on_start = p_spawn_on_start;
        if (get_number_of_volleys() > -1 && p_spawn_on_start) {
            volleys_left = get_number_of_volleys();
        }
    };
    bool is_spawn_on_start() const { return spawn_on_start; };

    void set_volley_rate(real_t p_volley_rate) { volley_rate = p_volley_rate; };
    real_t get_volley_rate() const { return volley_rate; };

    void set_spawn_offset(real_t p_spawn_offset) { spawn_offset = p_spawn_offset; };
    real_t get_spawn_offset() const { return spawn_offset; };

    void set_number_of_volleys(real_t p_number_of_volleys) { number_of_volleys = p_number_of_volleys; };
    real_t get_number_of_volleys() const { return number_of_volleys; };

    void set_trajectory(Emitter2D::Trajectory p_trajectory) { trajectory = p_trajectory; };
    Emitter2D::Trajectory get_trajectory() const { return trajectory; };

    void set_towards(Node2D* p_towards) { towards = p_towards; };
    Node2D* get_towards() const { return towards; };

    void set_rotation_option(Emitter2D::RotationOption p_rotation_option) { rotation_option = p_rotation_option; };
    Emitter2D::RotationOption get_rotation_option() const { return rotation_option; };

    void set_start_rotation(real_t p_start_rotation) { start_rotation = p_start_rotation; };
    real_t get_start_rotation() const { return start_rotation; };

    void set_rot_range(real_t p_rot_range_deg) {
        rot_range_deg = p_rot_range_deg;
        rot_range = Math::deg_to_rad(p_rot_range_deg);
    };
    real_t get_rot_range_deg() const { return rot_range_deg; };
    real_t get_rot_range() const { return rot_range; };

    void set_rotation_speed(real_t p_rotation_speed) {
        rotation_speed_deg = p_rotation_speed;
        rotation_speed = Math::deg_to_rad(p_rotation_speed);
    };
    real_t get_rotation_speed_deg() const { return rotation_speed_deg; };
    real_t get_rotation_speed() const { return rotation_speed; }

    void set_seed(uint64_t p_seed) { seed = p_seed; };
    uint64_t get_seed() const { return seed; };

    void set_pattern(Ref<BulletPattern> p_pattern) { pattern = p_pattern; };
    Ref<BulletPattern> get_pattern() const { return pattern; };

    void start_emitting();

    void stop_emitting();

    void rotate(double delta);
};
}

VARIANT_ENUM_CAST(Emitter2D::Trajectory);
VARIANT_ENUM_CAST(Emitter2D::RotationOption);

#endif
