#include "stdafx.h"

// General
#include "GameState_InWorld.h"

// Additional
#include "World.h"

bool GameState_InWorld::Init()
{
    GameState::Init();

    enableFreeCamera = false;
    cameraSprint = false;

    minimapActive = false;

    return true;
}

void GameState_InWorld::Destroy()
{
    GameState::Destroy();
}

bool GameState_InWorld::Set()
{
    GameState::Set();

    return true;
}

void GameState_InWorld::Unset()
{
    GameState::Unset();
}

void GameState_InWorld::Input(double t, double dt)
{
    float speed = 4.5f;

    if (cameraSlow)
        speed *= 0.2f;

    if (cameraSprint)
        speed *= 3.0f;

    if (Modules::input().IsKeyPressed(OW_KEY_W))
        _Render->mainCamera->ProcessKeyboard(FORWARD, speed);

    if (Modules::input().IsKeyPressed(OW_KEY_S))
        _Render->mainCamera->ProcessKeyboard(BACKWARD, speed);

    if (Modules::input().IsKeyPressed(OW_KEY_A))
        _Render->mainCamera->ProcessKeyboard(LEFT, speed);

    if (Modules::input().IsKeyPressed(OW_KEY_D))
        _Render->mainCamera->ProcessKeyboard(RIGHT, speed);
}

void GameState_InWorld::Update(double t, double dt)
{
    _EnvironmentManager->animtime += (dt * 1000.0f);
    _EnvironmentManager->globalTime = (int)_EnvironmentManager->animtime;

    _World->tick(dt);
}

void GameState_InWorld::Render(double t, double dt)
{
    if (!minimapActive)
    {
        _World->Render();
    }
}

void GameState_InWorld::RenderUI()
{
    //if (_World->loading)
    //{
    //	_Render->RenderText(vec2(_Render->GetWindowSize().x / 2, 200), _World->GetMap()->IsOutOfBounds() ? "Out of bounds" : "Loading...");
    //}

    if (minimapActive)
    {
        int basex = 200;
        int basey = 0;

        if (_Map->GetMinimap() != 0)
        {
            const int len = 768;

            _Render->RenderTexture(vec2(basex, basey), _Map->GetMinimap(), vec2(len, len));

            // Player position
            /*glBegin(GL_LINES);
            float fx, fz;
            fx = basex + _World->mainCamera->Position.x / C_TileSize * 12.0f;
            fz = basey + _World->mainCamera->Position.z / C_TileSize * 12.0f;
            glVertex2f(fx, fz);
            glColor4f(1, 1, 1, 0);
            glVertex2f(fx + 10.0f * cosf(degToRad(_World->mainCamera->Roll)), fz + 10.0f * sinf(degToRad(_World->mainCamera->Roll)));
            glEnd();*/

            return;
        }
    }

    // HUD
        // Skyname
        //char* sn = _World->skies->getSkyName();
        //if(sn)
        //	_Render->RenderText(vec2(200, 0), string(sn));

        // Area and region




        // Area
    DB�_AreaTableRecord* areaRecord = nullptr;
    string areaName = "<unknown>";

    areaRecord = DB�_AreaTable[_Map->getAreaID()];
    if (areaRecord != nullptr)
    {
        areaName = areaRecord->Get_Name();
    }

    // Region
    DB�_AreaTableRecord* regionRecord = nullptr;
    string regionName = "<unknown>";

    if (areaRecord != nullptr)
    {
        regionRecord = areaRecord->Get_ParentAreaID();
        if (regionRecord != nullptr)
        {
            regionName = regionRecord->Get_Name();
        }
    }


    //
    // DEBUG
    //
    _Render->RenderTexture(vec2(Modules::config().windowSizeX * 2.0 / 3.0, Modules::config().windowSizeY * 2.0 / 3.0), _Render->r->getRenderBufferTex(_World->rb2, 2), vec2(Modules::config().windowSizeX / 3, Modules::config().windowSizeY / 3));


    //


    /*_Render->RenderText(vec2(5, 20), "Area: [" + areaName + "] [Area id = " + std::to_string(_Map->getAreaID()) + "]");
    _Render->RenderText(vec2(5, 40), "Region: [" + regionName + "]");
    _Render->RenderText(vec2(5, 60), "CURRX: " + to_string(_Map->GetCurrentX()) + ", CURRZ " + to_string(_Map->GetCurrentZ()));*/


    ///

    _Perfomance->Draw(vec2(5, 100));

    /*_Render->RenderText(vec2(5, Modules::config().windowSizeY - 66), "REAL CamPos: [" + to_string(_World->mainCamera->Position.x) + "], [" + to_string(_World->mainCamera->Position.y) + "], [" + to_string(_World->mainCamera->Position.z) + "]");
    _Render->RenderText(vec2(5, Modules::config().windowSizeY - 44), "CamPos: [" + to_string(-(_World->mainCamera->Position.x - C_ZeroPoint)) + "], [" + to_string(-(_World->mainCamera->Position.z - C_ZeroPoint)) + "], [" + to_string(_World->mainCamera->Position.y) + "]");
    _Render->RenderText(vec2(5, Modules::config().windowSizeY - 22), "CamRot: [" + to_string(_World->mainCamera->Direction.x) + "], [" + to_string(_World->mainCamera->Direction.y) + "], [" + to_string(_World->mainCamera->Direction.z) + "]");

    // Time
    _Render->RenderText(vec2(Modules::config().windowSizeX - 150, 0), "TIME [" + to_string(_EnvironmentManager->m_GameTime.GetHour()) + "." + to_string(_EnvironmentManager->m_GameTime.GetMinute()) + "]");
    char buff[256];

    // Ambient

    sprintf(buff, "Amb[c=[%0.2f %0.2f %0.2f] i=[%f]]",
    _EnvironmentManager->dayNightPhase.ambientColor.x, _EnvironmentManager->dayNightPhase.ambientColor.y, _EnvironmentManager->dayNightPhase.ambientColor.z,
    _EnvironmentManager->dayNightPhase.ambientIntensity
    );
    _Render->RenderText(vec2(Modules::config().windowSizeX - 400, 20), buff);

    // Day

    sprintf(buff, "Day[c=[%0.2f %0.2f %0.2f] i=[%f] d=[%0.2f %0.2f %0.2f]]",
    _EnvironmentManager->dayNightPhase.dayColor.x, _EnvironmentManager->dayNightPhase.dayColor.y, _EnvironmentManager->dayNightPhase.dayColor.z,
    _EnvironmentManager->dayNightPhase.dayIntensity,
    _EnvironmentManager->dayNightPhase.dayDir.x, _EnvironmentManager->dayNightPhase.dayDir.y, _EnvironmentManager->dayNightPhase.dayDir.z
    );
    _Render->RenderText(vec2(Modules::config().windowSizeX - 400, 40), buff);

    // Night

    sprintf(buff, "Nig[c=[%0.2f %0.2f %0.2f] i=[%f] d=[%0.2f %0.2f %0.2f]]\0",
    _EnvironmentManager->dayNightPhase.nightColor.x, _EnvironmentManager->dayNightPhase.nightColor.y, _EnvironmentManager->dayNightPhase.nightColor.z,
    _EnvironmentManager->dayNightPhase.nightIntensity,
    _EnvironmentManager->dayNightPhase.nightDir.x, _EnvironmentManager->dayNightPhase.nightDir.y, _EnvironmentManager->dayNightPhase.nightDir.z
    );
    _Render->RenderText(vec2(Modules::config().windowSizeX - 400, 60), buff);*/
}

//

#pragma region Input functional

On_Mouse_Moved(GameState_InWorld)
{
    if (enableFreeCamera)
    {
        vec2 mouseDelta = (_mousePos - lastMousePos) / Modules::config().GetWindowSize();

        _Render->mainCamera->ProcessMouseMovement(mouseDelta.x, -mouseDelta.y);

        _Engine->GetAdapter()->SetMousePosition(lastMousePos);
    }
}

On_Mouse_Pressed(GameState_InWorld)
{
    if (_button == OW_MOUSE_BUTTON_LEFT)
    {
        enableFreeCamera = true;
        lastMousePos = _mousePos;
        _Engine->GetAdapter()->HideCursor();
        return true;
    }

    return false;
}

On_Mouse_Released(GameState_InWorld)
{
    if (_button == OW_MOUSE_BUTTON_LEFT)
    {
        enableFreeCamera = false;
        lastMousePos = VECTOR_ZERO;
        _Engine->GetAdapter()->ShowCursor();
        return true;
    }

    return false;
}

On_Mouse_WScrolled(GameState_InWorld)
{
    return false;
}

On_Keyboard_Pressed(GameState_InWorld)
{
    if (_key == OW_KEY_ESCAPE)
    {
        GameStateManager::SetGameState(GameStatesNames::GAME_STATE_MENU);
        return true;
    }

    if (_key == OW_KEY_X)
    {
        cameraSprint = true;
        return true;
    }

    if (_key == OW_KEY_Z)
    {
        cameraSlow = true;
        return true;
    }

    if (_key == OW_KEY_KP_1)
    {
        Modules::config().draw_map_chunk = !Modules::config().draw_map_chunk;
        return true;
    }
    if (_key == OW_KEY_KP_2)
    {
        Modules::config().draw_map_wmo = !Modules::config().draw_map_wmo;
        return true;
    }
    if (_key == OW_KEY_KP_3)
    {
        Modules::config().draw_map_wmo_doodads = !Modules::config().draw_map_wmo_doodads;
        return true;
    }

    if (_key == OW_KEY_KP_4)
    {
        Modules::config().draw_map_mdx = !Modules::config().draw_map_mdx;
        return true;
    }


    if (_key == OW_KEY_C)
    {
        Modules::config().enableMCCV = !Modules::config().enableMCCV;
        return true;
    }

    if (_key == OW_KEY_V)
    {
        Modules::config().enableMCLV = !Modules::config().enableMCLV;
        return true;
    }

    if (_key == OW_KEY_H)
    {
        Modules::config().drawhighres = !Modules::config().drawhighres;
        return true;
    }

    if (_key == OW_KEY_F)
    {
        Modules::config().drawfog = !Modules::config().drawfog;
        return true;
    }

    // minimap
    if (_key == OW_KEY_M)
    {
        minimapActive = !minimapActive;
        return true;
    }

    return false;
}

On_Keyboard_Released(GameState_InWorld)
{
    if (_key == OW_KEY_X)
    {
        cameraSprint = false;
        return true;
    }

    if (_key == OW_KEY_Z)
    {
        cameraSlow = false;
        return true;
    }

    return false;
}

#pragma endregion