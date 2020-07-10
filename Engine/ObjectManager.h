/*
 * Author		:Sangmin Kim
 * File			:ObjectManager.h
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for Object Manager
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#pragma once
#include <vector>
#include "Object.h"
#include <memory>
#include <unordered_map>

class ObjectManager
{
public:
    static ObjectManager* GetObjectManager();

    void Init();
    void Update(float dt);
    void Delete();
    void Clear();

    void AddObject(Object* obj);
	void Add_Object_Instancing(Object* obj);
    void DeleteObject(std::shared_ptr<Object> obj);
    void DivideObjectByState();
    std::vector<Object*> Find_Objects_By_Tag(std::string tag);
    Object* Find_Object_By_Name(std::string name);

    std::vector<std::shared_ptr<Object>>& GetObjectManagerContainer()
    {
        return objects;
    }
    std::vector<std::shared_ptr<Object>> GetObjectManagerContainer_Value()
    {
        return objects;
    }
    std::vector<std::shared_ptr<Object>>& Get_Objects()
    {
        return objects;
    }


	void Instancing_Update(float dt);
    void ObjectCollision();
    void ArenaCollision();
    void DivideObjectByStateOnce();
private:
    static ObjectManager* object_manager;
    std::vector<std::shared_ptr<Object>> objects{};
	std::vector<std::shared_ptr<Object>> objects_instancing{};
    std::vector<std::shared_ptr<Object>> delete_obj{};
    std::vector<std::shared_ptr<Object>> objects_by_state;
};