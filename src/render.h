#ifndef RENDER_H
#define RENDER_H
#include <raylib.h>
#include <string>
#include <vector>
#include <iostream>

class Render
{
private:
    bool isStarted{};
    int windowWidth{};
    int windowHeight{};
    Rectangle outerRec{};
    Rectangle innerRec{};
    std::string paragraphToRender{};
    float fontSize{};
    Font font{};
    bool isCorrect{};

    int x_box{};
    int y_box{};

    int numOfWord{};

    bool timerActive = false;
    float timer{};

public:
    Render() : timerActive(false),
               isStarted(false),
               windowWidth(800),
               windowHeight(600),
               fontSize(48.0f),
               isCorrect(false),
               x_box(30),
               y_box(30),
               outerRec({20, 20, 760, 400}), innerRec({20, 430, 760, 100}),
               paragraphToRender("the sun sets behind the mountains casting a warm glow across the tranquil valley a\n"
                                 "gentle breeze rustles through the leaves of the trees creating a soothing melody the\n"
                                 "air is filled with the sweet scent of wildflowers and the world seems to slow down as\n")
    {
    }

    void allFuntionToDraw(std::vector<std::string> words, std::string &userInput, std::vector<std::string> userWords);
    void draw();
    std::vector<std::string> stringToWords();
    void loadFonts();
    void getKeyboardInputs(bool &isCorrect, std::string &userInput, std::vector<std::string> &usersWords, int &numOfWord, std::vector<std::string> words);
    void checkWords(bool &isCorrect, std::string userInput, std::vector<std::string> &usersWords, int &numOfWord, std::vector<std::string> words);
    void renderUserInputs(Font font, std::string userInput);
    void renderOnTextBox(Font font, std::vector<std::string> words);
    void renderInTextBoxInGreen(Font font, bool isCorrect, std::vector<std::string> userWords);
    void greyBox(Font font, bool &isCorrect, int &x, int &y, int numOfWord, std::vector<std::string> words);
    void drawTime(bool &timerActive, float &timer);
    void reset();
    void setTimer(float value);
    void wpm(int time, int correctWords);
};
#endif