/*
 * Author		:Chulseung Lee
 * File			:Collision.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Collision
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once

class Object;

bool ObjectAndObjectCollision(Object* object_a, Object* object_b);
void ArenaAndObjectCollision(Object* object);
void Collision_Off_Lock_And_Player(Object* obj_i, Object* obj_j);
bool DeleteUnlessPlayer(Object* object);