#include "vector_scene.h"
#include <random>
#include "body.h"
#include "mathutils.h"
#include "world.h"
#include "raymath.h"
#define RAYGUI_IMPLEMENTATION

#include "raygui.h"

void VectorScene::Initialize()
{
    m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, static_cast<float>(m_height) / 2.0f });
    m_world = new World();
    m_world->Initialize();
    GuiEnable();
    GuiLoadStyle("../raygui/styles/terminal/style_terminal.rgs");
}

void VectorScene::Update()
{
    float dt = GetFrameTime();

    m_world->m_gravity = Vector2{0,-GravitySliderValue};
    if (IsMouseButtonPressed(1))
    {
        Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
        Body* body = m_world->CreateBody(position, MassSliderValue, TypeDropdownActive, SizeSliderValue, DampingSliderValue, WHITE);
        
        /**
        for (int i = 0; i < 100; ++i)
        {
            float rvel = randomf(1,6);
            Color col = ColorFromHSV(150, 1.0, (rvel/6)-1);
            Body* body = m_world->CreateBody(position, 0.05f, col);
            float theta = randomf(0,360);
            float x = cos(theta);
            float y = sin(theta);
            body->vel = Vector2Normalize(Vector2{ x, y }) * rvel;
        }
        **/
    }
    
    m_world->Step(dt);

    for (auto body : m_world->GetBodies())
    {
        if (body->pos.y < -5)
        {
            body->pos.y = -5;
            body->vel.y *= -1;
        }
        if (body->pos.y > 5)
        {
            body->pos.y = 5;
            body->vel.y *= -1;
        }
    }
}

void VectorScene::DrawGUI()
{
    Vector2 Anchor = Vector2{0,20};
    
    if (TypeDropdownEditMode) GuiLock();

    GuiGroupBox({ Anchor.x + 0, Anchor.y - 10, 351, 191 }, "Simulation Controls");
    GuiSliderBar({ Anchor.x + 60, Anchor.y + 0, 290, 30 }, nullptr, nullptr, &SizeSliderValue, 0, 1);
    GuiLabel({ Anchor.x + 10, Anchor.y + 0, 48, 24 }, "Size");
    GuiSliderBar({ Anchor.x + 60, Anchor.y + 30, 290, 30 }, nullptr, nullptr, &MassSliderValue, 0, 10);
    GuiLabel({ Anchor.x + 10, Anchor.y + 30, 48, 24 }, "Mass");
    GuiSliderBar({ Anchor.x + 60, Anchor.y + 60, 290, 30 }, nullptr, nullptr, &DampingSliderValue, 0, 2);
    GuiLabel({ Anchor.x + 10, Anchor.y + 60, 48, 24 }, "Damping");
    GuiSliderBar({ Anchor.x + 60, Anchor.y + 90, 290, 30 }, nullptr, nullptr, &GravitySliderValue, 0, 50);
    GuiLabel({ Anchor.x + 10, Anchor.y + 90, 48, 24 }, "Gravity");
    GuiSliderBar({ Anchor.x + 60, Anchor.y + 120, 290, 30 }, nullptr, nullptr, &PullSliderValue, 0, 100);
    GuiLabel({ Anchor.x + 10, Anchor.y + 120, 48, 24 }, "Pull");
    if (GuiDropdownBox({ Anchor.x + 60, Anchor.y + 150, 290, 30 }, "Dynamic;Static;Kinematic", &TypeDropdownActive, TypeDropdownEditMode)) TypeDropdownEditMode = !TypeDropdownEditMode;
    GuiLabel({ Anchor.x + 10, Anchor.y + 150, 48, 24 }, "Type");
    
    GuiUnlock();
}

void VectorScene::Draw()
{    
    m_camera->BeginMode();

    DrawGrid(10, 2, DARKGRAY);
    
    m_world->Draw(*this);
    
    m_camera->EndMode();
}
