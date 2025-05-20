/*******************************************************************************************
*
*   LayoutName v1.0.0 - Tool Description
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "layout_name");

    // layout_name: controls initialization
    //----------------------------------------------------------------------------------
    // Define anchors
    Vector2 Anchor = { 224, 384 };            // ANCHOR ID:1
    
    // Define controls variables
    float MassSliderValue = 0.0f;            // SliderBar: MassSlider
    float SizeSliderValue = 0.0f;            // SliderBar: SizeSlider
    bool TypeDropdownEditMode = false;
    int TypeDropdownActive = 0;            // DropdownBox: TypeDropdown
    float DampingSliderValue = 0.0f;            // SliderBar: DampingSlider
    float GravitySliderValue = 0.0f;            // SliderBar: GravitySlider
    float PullSliderValue = 0.0f;            // SliderBar: PullSlider
    //----------------------------------------------------------------------------------

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 

            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            // Draw controls
            if (TypeDropdownEditMode) GuiLock();

            GuiGroupBox((Rectangle){ Anchor.x + 0, Anchor.y + -152, 264, 152 }, "Simulation Controls");
            GuiSliderBar((Rectangle){ Anchor.x + 56, Anchor.y + -144, 208, 24 }, NULL, NULL, &MassSliderValue, 0, 100);
            GuiSliderBar((Rectangle){ Anchor.x + 56, Anchor.y + -120, 208, 24 }, NULL, NULL, &SizeSliderValue, 0, 100);
            GuiSliderBar((Rectangle){ Anchor.x + 56, Anchor.y + -96, 208, 24 }, NULL, NULL, &DampingSliderValue, 0, 100);
            GuiLabel((Rectangle){ Anchor.x + 0, Anchor.y + -72, 48, 24 }, "Type");
            GuiLabel((Rectangle){ Anchor.x + 0, Anchor.y + -96, 48, 24 }, "Damping");
            GuiLabel((Rectangle){ Anchor.x + 0, Anchor.y + -120, 48, 24 }, "Size");
            GuiLabel((Rectangle){ Anchor.x + 0, Anchor.y + -144, 48, 24 }, "Mass");
            GuiSliderBar((Rectangle){ Anchor.x + 56, Anchor.y + -48, 208, 24 }, NULL, NULL, &GravitySliderValue, 0, 100);
            GuiLabel((Rectangle){ Anchor.x + 0, Anchor.y + -48, 48, 24 }, "Gravity");
            GuiLabel((Rectangle){ Anchor.x + 0, Anchor.y + -24, 48, 24 }, "Pull");
            GuiSliderBar((Rectangle){ Anchor.x + 56, Anchor.y + -24, 208, 24 }, NULL, NULL, &PullSliderValue, 0, 100);
            if (GuiDropdownBox((Rectangle){ Anchor.x + 56, Anchor.y + -72, 120, 24 }, "Dynamic;Static;Kinematic", &TypeDropdownActive, TypeDropdownEditMode)) TypeDropdownEditMode = !TypeDropdownEditMode;
            
            GuiUnlock();
            //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------

