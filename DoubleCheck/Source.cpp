/*
 * Author		:Sangmin Kim
 * File			:Source.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Source
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */

#include "Engine.hpp"
extern int life = 3;

#if _DEBUG
int main()
{
    Engine engine;
    engine.Init();
    while (!engine.IsDone())
        engine.Update();

    engine.Delete();
    return 0;
}
#else
int WinMain()
{
    Engine engine;
    engine.Init();
    while (!engine.IsDone())
        engine.Update();

    engine.Delete();
    return 0;
}
#endif
