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
    m_camera = new SceneCamera(Vector2{static_cast<float>(m_width) / 2, static_cast<float>(m_height) / 2.0f});
    m_world = new World();
    m_world->Initialize();
    GuiEnable();
    GuiLoadStyle("../raygui/styles/terminal/style_terminal.rgs");
}

void VectorScene::Update()
{
    float dt = GetFrameTime();

    m_world->m_gravity = Vector2{0, -GravitySliderValue};
    if (IsMouseButtonPressed(1))
    {
        Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
        Color col = ColorFromHSV(330*(MassSliderValue/10),1-(RestitutionSliderValue/4),1-(DampingSliderValue/4));
        Body* body = m_world->CreateBody(position, MassSliderValue, TypeDropdownActive, SizeSliderValue,
                                         DampingSliderValue, col, RestitutionSliderValue);
        if (TypeDropdownActive == 2) { body->vel = Vector2Negate(Vector2{randomf(-1,1), randomf(-1,1)}); }
        
        if (springhead != nullptr && SpringAttachMode)
        {
            float dist = Vector2Length(springhead->pos - body->pos);
            Spring* spring = m_world->CreateSpring(springhead, body, dist, SpringStiffSliderValue,
                                                   SpringDampSliderValue);
        }

        springhead = body;
    }

    if (!SimulationPaused) m_world->Step(dt);

    for (auto body : m_world->GetBodies())
    {
        /*if (body->pos.y < -5)
        {
            body->pos.y = -5;
            body->vel.y *= -1;
        }
        if (body->pos.y > 5)
        {
            body->pos.y = 5;
            body->vel.y *= -1;
        }*/

        AABB aabb = body->GetAABB();
        AABB worldAABB = m_camera->GetAABB();		
				
        if ((aabb.min().y) < worldAABB.min().y)
        {
            float overlap = (worldAABB.min().y - aabb.min().y); // calculate how far the body has penetrated beyond the world boundary
            body->pos.y += 2 * overlap; // move the body back inside the world bounds
            body->vel.y *= -body->damping; // multiple by -restituion to scale and flip velocity
        }
        else if ((aabb.max().y) > worldAABB.max().y)
        {
            float overlap = (worldAABB.max().y - aabb.max().y);  // calculate how far the body has penetrated beyond the world boundary
            body->pos.y += 2 * overlap; // move the body back inside the world bounds
            body->vel.y *= -body->damping; // multiple by -restituion to scale and flip velocity
        }

        if ((aabb.min().x) < worldAABB.min().x)
        {
            float overlap = (worldAABB.min().x - aabb.min().x); // calculate how far the body has penetrated beyond the world boundary
            body->pos.x += 2 * overlap; // move the body back inside the world bounds
            body->vel.x *= -body->damping; // multiple by -restituion to scale and flip velocity
        }
        else if ((aabb.max().x) > worldAABB.max().x)
        {
            float overlap = (worldAABB.max().x - aabb.max().x);  // calculate how far the body has penetrated beyond the world boundary
            body->pos.x += 2 * overlap; // move the body back inside the world bounds
            body->vel.x *= -body->damping; // multiple by -restituion to scale and flip velocity
        }
    }
}

void VectorScene::DrawGUI()
{
    // Bodies
    if (TypeDropdownEditMode) GuiLock();
    Vector2 Anchor = Vector2{0, 20};

    GuiGroupBox({Anchor.x + 0, Anchor.y - 10, 251, 191}, "Simulation Controls");
    GuiSliderBar({Anchor.x + 60, Anchor.y + 5, 185, 20}, nullptr, nullptr, &SizeSliderValue, 0, 1);
    GuiLabel({Anchor.x + 5, Anchor.y + 2.5f, 50, 24}, "Size");
    GuiSliderBar({Anchor.x + 60, Anchor.y + 35, 185, 20}, nullptr, nullptr, &MassSliderValue, 0, 10);
    GuiLabel({Anchor.x + 5, Anchor.y + 32.5f, 50, 24}, "Mass");
    GuiSliderBar({Anchor.x + 60, Anchor.y + 65, 185, 20}, nullptr, nullptr, &DampingSliderValue, 0, 2);
    GuiLabel({Anchor.x + 5, Anchor.y + 62.5f, 50, 24}, "Damping");
    GuiSliderBar({Anchor.x + 60, Anchor.y + 95, 185, 20}, nullptr, nullptr, &RestitutionSliderValue, 0, 2);
    GuiLabel({Anchor.x + 5, Anchor.y + 92.5f, 50, 24}, "Bounce");
    GuiSliderBar({Anchor.x + 60, Anchor.y + 125, 185, 20}, nullptr, nullptr, &GravitySliderValue, 0, 50);
    GuiLabel({Anchor.x + 5, Anchor.y + 122.5f, 50, 24}, "Gravity");
    //GuiSliderBar({ Anchor.x + 60, Anchor.y + 125, 285, 20 }, nullptr, nullptr, &PullSliderValue, 0, 100);
    //GuiLabel({ Anchor.x + 5, Anchor.y + 122.5f, 50, 24 }, "Pull");
    if (GuiDropdownBox({Anchor.x + 60, Anchor.y + 155, 185, 20}, "Dynamic;Static;Kinematic", &TypeDropdownActive,
                       TypeDropdownEditMode)) TypeDropdownEditMode = !TypeDropdownEditMode;
    GuiLabel({Anchor.x + 5, Anchor.y + 152.5f, 50, 24}, "Type");

    // Springs
    Anchor += Vector2{250, 0};

    GuiGroupBox({Anchor.x + 0, Anchor.y - 10, 251, 71}, "Spring Controls");
    GuiSliderBar({Anchor.x + 60, Anchor.y + 5, 185, 20}, nullptr, nullptr, &SpringDampSliderValue, 0, 10);
    GuiLabel({Anchor.x + 5, Anchor.y + 2.5f, 50, 24}, "Damping");
    GuiSliderBar({Anchor.x + 60, Anchor.y + 35, 185, 20}, nullptr, nullptr, &SpringStiffSliderValue, 0, 10);
    GuiLabel({Anchor.x + 5, Anchor.y + 32.5f, 50, 24}, "Stiff");
    if (GuiButton({Anchor.x + 0, Anchor.y + 61, 120, 30}, "Clear"))
    {
        m_world->DestroyAll();
        m_world = new World();
        springhead = nullptr;
    }
    if (GuiButton({Anchor.x + 0, Anchor.y + 91, 120, 30}, "Default"))
    {
        TypeDropdownActive = 0; // DropdownBox: TypeDropdown
        MassSliderValue = 1; // SliderBar: MassSlider
        SizeSliderValue = 0.1f; // SliderBar: SizeSlider
        DampingSliderValue = 0.5f; // SliderBar: DampingSlider
        RestitutionSliderValue = 0; // SliderBar: DampingSlider
        GravitySliderValue = 9.81f; // SliderBar: GravitySlider
        PullSliderValue = 0.0f; // SliderBar: PullSlider
        SpringDampSliderValue = 0.5f;
        SpringStiffSliderValue = 1.0f;
        SpringAttachMode = false;
        SimulationPaused = false;
    }
    GuiCheckBox({Anchor.x + 121, Anchor.y + 61, 15, 15}, "Attach",&SpringAttachMode);
    GuiCheckBox({Anchor.x + 121, Anchor.y + 76, 15, 15}, "Pause",&SimulationPaused);

    GuiUnlock();
}

void VectorScene::Draw()
{
    m_camera->BeginMode();

    DrawGrid(10, 2, DARKGRAY);

    m_world->Draw(*this);

    m_camera->EndMode();
}
