#pragma once

class Object;

bool ObjectAndObjectCollision(Object* object_a, Object* object_b);
void ArenaAndObjectCollision(Object* object);
void Collision_Off_Lock_And_Player(Object* obj_i, Object* obj_j);
bool DeleteUnlessPlayer(Object* object);