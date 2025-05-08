#include "vector_scene.h"
#include <random>
#include "body.h"
#include "mathutils.h"
#include "world.h"
#include "raymath.h"

void VectorScene::Initialize()
{
    m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, m_height / 2.0f });
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
}

void VectorScene::Draw()
{
    m_camera->BeginMode();
    DrawGrid(10, 2, DARKGRAY);

   m_world->Draw(*this);
    
    m_camera->EndMode();
}

void VectorScene::DrawGUI()
{
}
