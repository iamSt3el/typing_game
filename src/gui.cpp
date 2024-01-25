#include "gui.h"
#include <raylib.h>
#include <cctype>
#include <iostream>
#include "render.h"

bool Gui::collision(Rectangle position, Vector2 mousePosition)
{
    return CheckCollisionPointRec(mousePosition, position) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

bool Gui::get()
{
    return isCollide;
}

void Gui::set(bool value)
{
    isCollide = value;
} 

float Gui::getTimer()
{
    return timer;
}
void Gui::drawGui()
{
    DrawText("WELCOME TO TYPE-TYPE", 150, 30, 40, YELLOW);

        for (auto rect : rects)
        {
            DrawRectangle(rect.x, rect.y, rect.width, rect.height, BLUE);
        }

        for (int i = 0; i < textPosition.size(); i++)
        {
            DrawText(text[i].c_str(), textPosition[i].x, textPosition[i].y, textFontSize, YELLOW);
        }

        for (int i = 0; i < rects.size(); i++)
        {
            if (collision(rects[i], GetMousePosition()))
            {
                isCollide = true;
                std::cout << "Collide" << std::endl;
                if(i == 0)
                {
                    timer = 15000.0f;
                }   
                else
                {
                    timer = 30000.0f;
                }
                return;
                
            }
        }
}
