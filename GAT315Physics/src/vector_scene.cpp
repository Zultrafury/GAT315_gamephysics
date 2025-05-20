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
}

void VectorScene::Update()
{
    float dt = GetFrameTime();

    if (IsMouseButtonPressed(0))
    {
        Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
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

void VectorScene::Draw()
{
    m_camera->BeginMode();
    DrawGrid(10, 2, DARKGRAY);

    Vector2 Anchor = m_camera->ScreenToWorld(Vector2{ static_cast<float>(m_width) / -2, static_cast<float>(m_height) / -2 });            // ANCHOR ID:1
    
    // Define controls variables
    float MassSliderValue = 0.0f;            // SliderBar: MassSlider
    float SizeSliderValue = 0.0f;            // SliderBar: SizeSlider
    bool TypeDropdownEditMode = false;
    int TypeDropdownActive = 0;            // DropdownBox: TypeDropdown
    float DampingSliderValue = 0.0f;            // SliderBar: DampingSlider
    float GravitySliderValue = 0.0f;            // SliderBar: GravitySlider
    float PullSliderValue = 0.0f;            // SliderBar: PullSlider

    // Main game loop
    if (TypeDropdownEditMode) GuiLock();

    GuiGroupBox(m_camera->ScreenToWorld({ Anchor.x + 0, Anchor.y + -152, 264, 152 }), "Simulation Controls");
    GuiSliderBar(m_camera->ScreenToWorld({ Anchor.x + 56, Anchor.y + -144, 208, 24 }), nullptr, nullptr, &MassSliderValue, 0, 100);
    GuiSliderBar(m_camera->ScreenToWorld({ Anchor.x + 56, Anchor.y + -120, 208, 24 }), nullptr, nullptr, &SizeSliderValue, 0, 100);
    GuiSliderBar(m_camera->ScreenToWorld({ Anchor.x + 56, Anchor.y + -96, 208, 24 }), nullptr, nullptr, &DampingSliderValue, 0, 100);
    GuiSliderBar(m_camera->ScreenToWorld({ Anchor.x + 56, Anchor.y + -48, 208, 24 }), nullptr, nullptr, &GravitySliderValue, 0, 100);
    GuiLabel(m_camera->ScreenToWorld({ Anchor.x + 0, Anchor.y + -72, 48, 24 }), "Type");
    GuiLabel(m_camera->ScreenToWorld({ Anchor.x + 0, Anchor.y + -96, 48, 24 }), "Damping");
    GuiLabel(m_camera->ScreenToWorld({ Anchor.x + 0, Anchor.y + -120, 48, 24 }), "Size");
    GuiLabel(m_camera->ScreenToWorld({ Anchor.x + 0, Anchor.y + -144, 48, 24 }), "Mass");
    GuiLabel(m_camera->ScreenToWorld({ Anchor.x + 0, Anchor.y + -48, 48, 24 }), "Gravity");
    GuiLabel(m_camera->ScreenToWorld({ Anchor.x + 0, Anchor.y + -24, 48, 24 }), "Pull");
    GuiSliderBar({ Anchor.x + 56, Anchor.y + -24, 208, 24 }, nullptr, nullptr, &PullSliderValue, 0, 100);
    if (GuiDropdownBox({ Anchor.x + 56, Anchor.y + -72, 120, 24 }, "Dynamic;Static;Kinematic", &TypeDropdownActive, TypeDropdownEditMode)) TypeDropdownEditMode = !TypeDropdownEditMode;
    
    GuiUnlock();

    m_world->Draw(*this);
    
    m_camera->EndMode();
}

void VectorScene::DrawGUI()
{
}
