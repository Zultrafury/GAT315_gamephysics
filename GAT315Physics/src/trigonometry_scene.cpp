#include "trigonometry_scene.h"

#include <cmath>

#include "raymath.h"

void TrigonometryScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, m_height / 2.0f });
}

void TrigonometryScene::Update()
{
}

float DegToRad(float degrees)
{
	return degrees * (PI / 180.0f);
}

float RadToDeg(float radians)
{
	return radians * (180.0f / PI);
}

/*
float Vector2Length(const Vector2& v)
{
	return std::sqrt((v.x * v.x) + (v.y * v.y));
}
*/

/*
Vector2 Vector2Normalize(const Vector2& v)
{
	float l = Vector2Length(v);
	return Vector2{v.x / l, v.y / l};
}
*/

void TrigonometryScene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, WHITE);
	//DrawCircleV(m_camera->WorldToScreen(Vector2{ 0, 0 }), m_camera->WorldToScreen(1), RED);

	float radius = 3;
	float rate = 1.2f;
	float time = GetTime() * rate;

	// circle
	int steps = 10;
	for (int i = 0; i < steps; i++)
	{
		float theta = time + (i/static_cast<float>(steps)) * (2 * PI);
		float x = cos(theta) * radius;
		float y = sin(theta) * radius;

		DrawCircle(Vector2{x,y}, 0.1f, GREEN);
	}

	// sin/ cos
	for (float f = -9.0f; f < 9; f += 0.2f)
	{
		float theta = time + (f/6) * (2* PI);
		float c = cos(theta) * radius;

		DrawCircle(Vector2{f,c}, 0.1f, BLUE);
	}

	// speedy circle
	Vector2 coords = Vector2{cosf(-3 * time) * radius,sinf(-3 * time) * radius};
	DrawCircle(coords, 0.25f, PURPLE);

	float angle = atan2(coords.y,coords.x);
	DrawCircle(Vector2Normalize(coords),angle,WHITE);

	m_camera->EndMode();
}

void TrigonometryScene::DrawGUI()
{
}
