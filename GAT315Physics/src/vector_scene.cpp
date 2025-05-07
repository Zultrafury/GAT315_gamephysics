#include "vector_scene.h"
#include <random>

#include "body.h"
#include "raymath.h"

float randomf(float min, float max)
{
    static std::default_random_engine generator(time(0));
    std::uniform_real_distribution distribution(min, max);
    return distribution(generator);
}

void VectorScene::Initialize()
{
    m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, m_height / 2.0f });
    Body* body = new Body(Vector2{0,0},Vector2{0,0},0.25f);
    m_head = body;
    player = body;

    for (int i = 0; i < 100; ++i)
    {
        body->next = new Body(Vector2{randomf(-9,9),randomf(-5,5)},
            Vector2{randomf(-100,100)/100,randomf(-100,100)/100},
            GREEN);
        body->next->prev = body;
        body = body->next;
    }
}

void VectorScene::Update()
{
    float dt = GetFrameTime();
    
    Vector2 input{ 0,0 };
    if (IsKeyDown(KEY_W)) input.y = 1;
    if (IsKeyDown(KEY_S)) input.y = -1;
    if (IsKeyDown(KEY_A)) input.x = -1;
    if (IsKeyDown(KEY_D)) input.x = 1;
    input = Vector2Normalize(input);
    Body* body = m_head;
    while (body)
    {
        if (body == player)
        {
            body->vel = input;
            body = body->next;
            continue;
        }

        Vector2 direction = player->pos - body->pos;
        direction = Vector2Normalize(direction);
        body->vel = direction;
        body->Step(dt);
        body = body->next;
    }
}

void VectorScene::Draw()
{
    m_camera->BeginMode();
    DrawGrid(10, 5, WHITE);

    Body* body = m_head;
    while (body)
    {
        body->Draw(*this);
        body = body->next;
    }
    
    m_camera->EndMode();
}

void VectorScene::DrawGUI()
{
}
