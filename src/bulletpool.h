/***************************************************/
/*  bulletpool.h                                   */
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

#ifndef BULLET_POOL_H
#define BULLET_POOL_H

#include <godot_cpp/classes/node2d.hpp>
#include <unordered_map>
#include "bulletsettings.h"


namespace godot {

struct Bullet {
    RID physics_body;
    Bullet* next;

    // Current bullet information
    bool active = false;
    double ttl = 0.0;
    Node* current_owner = nullptr;
    Vector2 position;
    Vector2 velocity;
    real_t ang_vel = 0.0;
    real_t acceleration = 0.0;
    real_t max_vel = INFINITY;
    real_t min_vel = -INFINITY;
    Ref<Texture2D> texture;
};

class BulletPool : public Node2D {
    GDCLASS(BulletPool, Node2D)


private:
    uint32_t pool_size = 1000;
    Bullet* pool = nullptr;
    uint32_t phys_layer = 0;

    Bullet* available_bullets = nullptr;
    uint32_t current_bullet_count = 0;


protected:
    static void _bind_methods();
    void set_current_bullets(uint32_t pool_size) { current_bullet_count = pool_size; }
    void increment_current_bullet_count() { current_bullet_count++; }
    void decrement_current_bullet_count() { current_bullet_count--; }
    void reset_current_bullet_count() { current_bullet_count = 0; }

    void process_bullets(double delta);
    void initialise_pool();

public:
    BulletPool();
    ~BulletPool();

    
    void _ready() override;
    void _physics_process(double delta) override;
    void _draw() override;
    
    void start_bullet(Ref<BulletSettings> settings, double angle, Vector2 init_position, Node* owner=nullptr);
    
    void set_pool_size(uint32_t p_pool_size) { pool_size = p_pool_size; };
    uint32_t get_pool_size() const { return pool_size; };

    void set_phys_layer(uint32_t p_phys_layer) { phys_layer = p_phys_layer; };
    uint32_t get_phys_layer() const { return phys_layer; };

    uint32_t get_current_bullets() { return current_bullet_count; };
    void kill_em_all();
};
}

#endif
