#ifndef GUI_H
#define GUI_H
#include <raylib.h>
#include <vector>
#include <string>

class Gui
{
private:
    std::vector<Rectangle> rects = {
        {200, 250, 80, 50},
        {330, 250, 80, 50}};

    std::vector<Vector2> textPosition ={
        {205, 265},
        {335, 265},
    };

    int textFontSize = 20;

    std::vector<std::string> text = {
        "15 SEC",
        "30 SEC"
    };

    bool isCollide = false;
    float timer{};

public:
    //bool isCollide = false;
    bool get();
    void set(bool value);
    void drawGui();
    bool collision(Rectangle position, Vector2 mousePosition);
    float getTimer();
};

#endif
