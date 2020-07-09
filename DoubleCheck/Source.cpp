/*
 * Author		:Sangmin.kim
 * File			:Source.cpp
 * Term			:2019 Fall
 * Class		:GAM200
 * Project		:GAM200 Project
 * Date			:2019/12/11
 * Description	:Containing the main function of our engine.
 *
 * copyright   All content ?2019 DigiPen (USA) Corporation, all rights reserved
 */

#include "Engine.hpp"

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
