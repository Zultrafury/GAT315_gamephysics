#include "polar_scene.h"
#include "polar.h"

void PolarScene::Initialize()
{
    m_camera = new SceneCamera(Vector2{static_cast<float>(m_width) / 2, m_height / 2.0f});
}

void PolarScene::Update()
{
}

void PolarScene::Draw()
{
    m_camera->BeginMode();

    DrawGrid(10, 5, WHITE);

    float radius = 1;
    float rate = -0.1f;
    float time = GetTime() * rate;

    float steps = 100;
    Vector2 last = Vector2{0, 0};
    /* // ARCHIMEDEAN
    for (float i = 0; i < steps; i += 0.1f)
    {
        float theta = (i/static_cast<float>(steps)) * (4 * PI);
        float r = i/steps * radius;
        Polar coords = Polar{i+time,r};
        Color col = ColorFromHSV(r*50, 1.0, 1.0);
        
        DrawCircle(coords, coords.radius/40, col);
        DrawLine(last,coords,col);
        last = coords;
    }
    */

    /* // CARDIOID
    for (float i = 0; i < steps; i += 0.1f)
    {
        float theta = i/steps;
        float r = radius * (1 + cos(i));
        Polar coords = Polar{i+time,r};
        Color col = ColorFromHSV(r*50, 1.0, 1.0);
        
        DrawCircle(coords, coords.radius/40, col);
        DrawLine(last,coords,col);
        last = coords;
    }
    */

    /* // LIMACON
    for (float i = 0; i < steps; i += 0.1f)
    {
        float theta = i/steps;
        float r = radius + ((radius * sin(time)) + cos(i));
        Polar coords = Polar{i,r * 2};
        Color col = ColorFromHSV(r*50, 1.0, 1.0);
        
        DrawCircle(coords, 0.1f, col);
        DrawLine(last,coords,col);
        last = coords;
    }
    */

    /* // ROSE CURVE
    for (float i = 0; i < steps; i += 0.1f)
    {
        float r = radius * cos(5*i);
        Polar coords = Polar{i+time,r};
        Color col = ColorFromHSV(r*80, 1.0, 1.0);
        
        DrawCircle(coords, coords.radius/20, col);
        //DrawLine(last,coords,col);
        last = coords;
    }
    */

    time += -1;
    for (float i = 0; i < steps; i += 0.1f)
    {
        float r = (time * time) / i;
        Polar coords = Polar{i * time, r};
        Color col = ColorFromHSV(r * 80, 1.0, 1.0);

        DrawCircle(coords, coords.radius / 20, col);
        DrawLine(last, coords, col);
        last = coords;
    }

    m_camera->EndMode();
}

void PolarScene::DrawGUI()
{
}
