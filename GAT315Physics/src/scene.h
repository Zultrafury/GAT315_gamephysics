#pragma once
#include "raylib.h"
#include "scene_camera.h"
#include <string>

class World;

class Scene
{
public:
	Scene(const std::string& title, int width, int height, const Color& background = BLACK);
	virtual ~Scene();

	virtual void Initialize() = 0;
	virtual void Update() = 0;

	virtual void BeginDraw();
	virtual void EndDraw();
	virtual void Draw() = 0;
	virtual void DrawGUI() = 0;

	bool IsQuit() { return WindowShouldClose(); }

	void SetCamera(SceneCamera* camera) { m_camera = camera; }
	SceneCamera* GetCamera() { return m_camera; }

	friend struct Body;
	friend struct Spring;
	
protected:
	void DrawGrid(float slices, float thickness, const Color& color) const;
	void DrawCircle(const Vector2& vec, float radius, const Color& color) const;
	void DrawLine(const Vector2& first, const Vector2& last, const Color& color) const;

	int m_width{ 0 };
	int m_height{ 0 };
	Color m_background{ WHITE };

	SceneCamera* m_camera{ nullptr };
	World* m_world{nullptr};
};
