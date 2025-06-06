#pragma once
#include "scene.h"

class GameScene : public Scene
{
public:
    GameScene(const std::string& title, int width, int height, const Color& background = BLACK) :
        Scene(title, width, height, background) {}
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void DrawGUI() override;
private:
    float gridoffset = 0;
    Body* bossbody = nullptr;
    Vector2 bosspos = {0,0};
    Body* pbody = nullptr;
    float pinv = 0;
    int phits = 5;
    float bossatk = 10;
    int injectatk = -1;
    int injecttimes = 0;
    float et = 0;
    std::string finaltime = "";
    float unloadedtime = 0;
};
