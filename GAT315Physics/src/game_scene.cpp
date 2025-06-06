#include "game_scene.h"
#include "mathutils.h"
#include "body.h"
#include "world.h"
#include "raygui.h"
#include "polar.h"

void GameScene::Initialize()
{
    m_camera = new SceneCamera(Vector2{static_cast<float>(m_width) / 2, static_cast<float>(m_height) / 2.0f});
    m_world = new World();
    m_world->Initialize();
    m_world->m_gravity = Vector2{0,-5};
    pbody = m_world->CreateBody(Vector2{0,0},1,0,0.15f,1.5f,WHITE);
    bossbody = m_world->CreateBody(Vector2{0,0},1,1,0.15f,0,ColorFromHSV(0,1,0.75f));
    GuiEnable();
    std::string style = "dark";
    std::string stylestring = "../raygui/styles/"+style+"/style_"+style+".rgs";
    GuiLoadStyle(stylestring.c_str());
    DisableCursor();
    m_sounds.push_back(LoadSound("hurt.mp3"));
    SetSoundVolume(m_sounds[0], 0.15f);
    m_sounds.push_back(LoadSound("laser.wav"));
    SetSoundVolume(m_sounds[1], 0.15f);
    m_sounds.push_back(LoadSound("music.mp3"));
    SetSoundVolume(m_sounds[2], 0.25f);
    PlaySound(m_sounds[2]);
    unloadedtime = GetTime();
}

void GameScene::Update()
{
    // Time variables
    const float dt = GetFrameTime();
    et = GetTime() - unloadedtime;

    // Grid offset
    if (phits > 0) gridoffset = fmodf(gridoffset + dt,1);

    // Boss movement
    const Vector2 bossoff = {sinf(et*2),2+sinf(et*6.5f)/3};
    if (phits > 0)
    {
        bossbody->pos = bosspos + bossoff;
        bossbody->size = 0.25f - bossatk/8;
    }

    //Boss attacks
    const float standardbossatk = std::max(1.5f-(et/50),0.75f);

    if (bossatk <= 0 && phits > 0)
    {
        PlaySound(m_sounds[1]);
        bossatk = standardbossatk;
        int r = injecttimes > 0 ? injectatk : static_cast<int>(randomf(0, 7));
        if (r == 0)
        {
            Body* atkbody = m_world->CreateBody(bossbody->pos,1,0,0.25f,0,RED);
            atkbody->vel = Vector2Normalize(pbody->pos - atkbody->pos) * 10;
            atkbody->exptime = 10;
        }
        else if (r == 1)
        {
            for (int i = 0; i < 5; ++i)
            {
                Body* atkbody = m_world->CreateBody(bossbody->pos,1,0,0.2f,0,RED);
                float tgtangle = Vector2Angle(pbody->pos - atkbody->pos,{0,-1});
                atkbody->vel = Vector2Normalize(Polar{((PI/6*i) - 5*PI/6) - tgtangle,10}) * 6;
                atkbody->exptime = 4;
            }
        }
        else if (r == 2) {
            Body* atkbody = m_world->CreateBody(bossbody->pos,1,2,0.5f,0,RED);
            atkbody->vel = Vector2Normalize(pbody->pos - atkbody->pos) * 3;
            atkbody->exptime = 10;
        }
        else if (r == 3)
        {
            for (int i = 0; i < 3; ++i)
            {
                Body* atkbody = m_world->CreateBody(bossbody->pos,1,2,0.11f,0,RED);
                float tgtangle = Vector2Angle(pbody->pos - atkbody->pos,{0,-1});
                atkbody->vel = Vector2Normalize(Polar{((PI/12*i) - 7*PI/12) - tgtangle,1}) * 10;
                //atkbody->vel = Polar{(PI/12*i) - 3*PI/5,10} ;
                atkbody->exptime = 1;
            }
        }
        else if (r == 4) {
            for (int i = 0; i < 30; ++i)
            {
                Body* atkbody = m_world->CreateBody(bossbody->pos,1,2,0.11f,0,RED);
                atkbody->vel = Vector2Normalize(pbody->pos - atkbody->pos) * (8-(i/4.0f));
                atkbody->exptime = 3;
            }
        }
        else if (r == 5)
        {
            for (int i = 0; i < 16; ++i)
            {
                Body* atkbody = m_world->CreateBody(bossbody->pos,1,2,0.11f,0,RED);
                //float tgtangle = Vector2Angle(pbody->pos - atkbody->pos,{0,-1});
                atkbody->vel = Vector2Normalize(Polar{(PI/8*i),1}) * 5;
                //atkbody->vel = Polar{(PI/12*i) - 3*PI/5,10} ;
                atkbody->exptime = 3;
            }
            injectatk = 5;
            bossatk = 0.01f;
            if (injecttimes == 0) injecttimes = 16;
            if (injecttimes == 1) bossatk = standardbossatk;
            injecttimes--;
        }
        else if (r == 6)
        {
            Body* atkbody = m_world->CreateBody(bossbody->pos,1,2,0.11f,0,RED);
            //float tgtangle = Vector2Angle(pbody->pos - atkbody->pos,{0,-1});
            atkbody->vel = Vector2Normalize(Polar{injecttimes/16.0f*(2*PI),1}) * 6;
            atkbody->exptime = 5;
            
            injectatk = 6;
            bossatk = 0.005f;
            if (injecttimes == 0) injecttimes = 32;
            if (injecttimes == 1) bossatk = standardbossatk;
            injecttimes--;
        }
    }
    else bossatk -= dt;

    // Player movement
    const Vector2 towardsmouse = m_camera->ScreenToWorld(GetMousePosition()) - pbody->pos;
    pbody->ApplyForce(towardsmouse*200, Body::ForceMode::Force);
    pbody->vel = Vector2Clamp(pbody->vel, {-10,-10}, {10,10});

    // Player hit detection
    Color pcol = (phits > 0) ? ColorFromHSV(0,(3*pinv)/4,1-(pinv/3)) : WHITE;
    if (pinv <= 0)
    {
        if (pbody->GetCollided())
        {
            pinv = 1;
            phits--;
            PlaySound(m_sounds[0]);
        }
        else pcol = WHITE;
    }
    else
    {
        pinv -= dt;
        pbody->SetCollided(false);
    }
    pbody->col = pcol;

    // Step simulation
    if (phits > 0) m_world->Step(dt);

    // Border reflection
    for (auto body : m_world->GetBodies())
    {
        if (body->type != Body::Type::Dynamic) continue;
        AABB aabb = m_camera->GetAABB();
        if (body->pos.y < aabb.min().y)
        {
            body->pos.y = aabb.min().y;
            body->vel.y *= -1;
        }
        if (body->pos.y > aabb.max().y)
        {
            body->pos.y = aabb.max().y;
            body->vel.y *= -1;
        }
        if (body->pos.x < aabb.min().x)
        {
            body->pos.x = aabb.min().x;
            body->vel.x *= -1;
        }
        if (body->pos.x > aabb.max().x)
        {
            body->pos.x = aabb.max().x;
            body->vel.x *= -1;
        }
    }
}

void GameScene::Draw()
{
    m_camera->BeginMode();

    const Color col = ColorFromHSV(0,1,0.1f+(0.3f*sinf(gridoffset*PI)));
    DrawGrid(20, 3, col, Vector2{gridoffset,gridoffset});

    DrawCircle(m_camera->ScreenToWorld(GetMousePosition()),0.05f,GRAY);

    m_world->Draw(*this);
    
    m_camera->EndMode();
}

void GameScene::DrawGUI()
{
    const std::string label = "Lives: "+std::to_string(phits);
    GuiLabel({m_width/16.0f, m_width/32.0f, 1000, 24}, label.c_str());
    const std::string time = "Time: "+std::to_string(et).substr(0,6);
    if (phits <= 0)
    {
        finaltime = finaltime == "" ? "Final "+time : finaltime;
        GuiLabel({m_width/2.0f + (sinf(et*4)*10) - 50, m_height/2.0f, 1000, 24}, finaltime.c_str());
    }
    else GuiLabel({m_width/16.0f, m_width*16/32.0f, 1000, 24}, time.c_str());
}
