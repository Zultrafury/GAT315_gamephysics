#include "scene.h"
#include "world.h"

Scene::Scene(const std::string& title, int width, int height, const Color& background) :
	m_width{ width },
	m_height{ height },
	m_background{ background }
{
	InitWindow(width, height, title.c_str());
}

Scene::~Scene()
{
	CloseWindow();
}

void Scene::BeginDraw()
{
	BeginDrawing();
	ClearBackground(m_background);
}

void Scene::EndDraw()
{
	EndDrawing();
}

void Scene::DrawGrid(float slices, float thickness, const Color& color) const
{
	for (float i = -slices; i <= slices; i++)
	{
		DrawLineEx(m_camera->WorldToScreen(Vector2{ -slices, i }), m_camera->WorldToScreen(Vector2{ slices, i }), thickness, color);
		DrawLineEx(m_camera->WorldToScreen(Vector2{ i, -slices }), m_camera->WorldToScreen(Vector2{ i, slices }), thickness, color);
	}
}

void Scene::DrawCircle(const Vector2& vec, float radius, const Color& color) const
{
	DrawCircleV(m_camera->WorldToScreen(vec), m_camera->WorldToScreen(radius), color);
}

void Scene::DrawLine(const Vector2& first, const Vector2& last, const Color& color) const
{
	DrawLineV(m_camera->WorldToScreen(first), m_camera->WorldToScreen(last), color);
}
