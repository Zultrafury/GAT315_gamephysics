#pragma once
#include "scene.h"

struct Body;

class VectorScene : public Scene
{
public:
    VectorScene(const std::string& title, int width, int height, const Color& background = BLACK) :
        Scene(title, width, height, background)
    {
        //
    }
    
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void DrawGUI() override;

private:
    Body* springhead = nullptr;

    // GUI vars
    bool TypeDropdownEditMode = false;
    int TypeDropdownActive = 0;            // DropdownBox: TypeDropdown
    float MassSliderValue = 1;            // SliderBar: MassSlider
    float SizeSliderValue = 0.1f;            // SliderBar: SizeSlider
    float DampingSliderValue = 0.5f;            // SliderBar: DampingSlider
    float GravitySliderValue = 9.81f;            // SliderBar: GravitySlider
    float PullSliderValue = 0.0f;            // SliderBar: PullSlider
    float SpringDampSliderValue = 0.5f;
    float SpringStiffSliderValue = 1.0f;
};
