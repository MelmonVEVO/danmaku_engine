/***************************************************/
/*  bulletpool.h                                   */
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


#ifndef BULLET_POOL_H
#define BULLET_POOL_H

#include <godot_cpp/classes/node.hpp>
#include "bullet2d.h"

namespace godot {


class BulletPool : public Node {
    GDCLASS(BulletPool, Node)


private:
    uint32_t pool_size;
    Bullet2D* pool;

    Bullet2D* first_available;  // unused bullet

protected:
    static void _bind_methods();


public:
    BulletPool();
    ~BulletPool();

    void initialise_pool(uint32_t p_pool_size=-1);
    void _ready() override;
    Bullet2D* get_bullet();
    void return_bullet(Bullet2D* bullet);
    
    void set_pool_size(uint32_t p_pool_size) { pool_size = p_pool_size; }
    uint32_t get_pool_size() const { return pool_size; }
};
}

#endif
