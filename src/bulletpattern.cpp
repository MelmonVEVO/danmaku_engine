/***************************************************/
/*  bulletpattern.cpp                              */
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

#include "bulletpattern.h"

using namespace godot;


void BulletPattern::_bind_methods() {
    ClassDB::bind_method(D_METHOD("fire", "pool", "settings", "origin", "offset", "rotation"), &BulletPattern::fire);
    ClassDB::bind_method(D_METHOD("fire_fixed", "pool", "settings", "origin", "offset", "rotation", "dir"), &BulletPattern::fire_fixed);
    ClassDB::bind_method(D_METHOD("fire_aimed", "pool", "settings", "origin", "offset", "rotation", "towards"), &BulletPattern::fire_aimed);
    ClassDB::bind_method(D_METHOD("fire_random", "pool", "settings", "origin", "offset", "rotation"), &BulletPattern::fire_random);
}


BulletPattern::BulletPattern() {
}


BulletPattern::~BulletPattern() {
}
