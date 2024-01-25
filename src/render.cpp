#include <raylib.h>
#include <iostream>
#include <string>
#include <vector>
#include "render.h"
#include "gui.h"

// Function to convert the string into a vector(array) of words
std::vector<std::string> Render::stringToWords()
{
    std::vector<std::string> words;

    std::string singleWord;

    for (char c : paragraphToRender)
    {
        if (c == ' ' || c == '\n' || c == '\t')
        {
            words.push_back(singleWord);
            singleWord.clear();
        }
        else
        {
            singleWord += c;
        }
    }

    words.push_back(singleWord);
    singleWord.clear();
    return words;
}

// Function to check if the words are correct
void Render::checkWords(bool &isCorrect, std::string userInput, std::vector<std::string> &usersWords, int &numOfWord, std::vector<std::string> words)
{
    if (userInput == words[numOfWord])
    {
        usersWords.push_back(userInput);
        numOfWord++;
        isCorrect = true;
    }
    return;
}
// Funtion to get the keyboard input
void Render::getKeyboardInputs(bool &isCorrect, std::string &userInput, std::vector<std::string> &usersWords, int &numOfWord, std::vector<std::string> words)
{
    //    string userInput{};
    int keyPressed = GetKeyPressed();
    if (keyPressed != 0)
    {
        if (keyPressed == 259)
        {
            if (!userInput.empty())
            {
                userInput.erase(userInput.size() - 1);
            }
        }
        else if (keyPressed == 32)
        {
            checkWords(isCorrect, userInput, usersWords, numOfWord, words);
            userInput.clear();
        }
        else
        {
            userInput += tolower((char)keyPressed);
        }
    }
}

void Render::renderUserInputs(Font font, std::string userInput)
{
    float x = 30.0f;
    float y = 450.0f;
    DrawTextEx(font, userInput.c_str(), {x, y}, fontSize, 0, BLACK);
}

void Render::renderOnTextBox(Font font, std::vector<std::string> words)
{
    float x = 30;
    float y = 30;
    for (int i = 0; i < words.size(); i++)
    {
        // DrawText(words[i].c_str(), x, y, textSize, BLACK);
        DrawTextEx(font, words[i].c_str(), {x, y}, fontSize, 0, BLACK);
        Vector2 value = MeasureTextEx(font, words[i].c_str(), fontSize, 0);
        x += value.x + 10;
        if (!(i + 1 >= words.size()))
        {
            Vector2 value2 = MeasureTextEx(font, words[i + 1].c_str(), fontSize, 0);
            if (x + value2.x >= windowWidth - 20)
            {
                x = 30;
                y += 30;
            }
        }
    }
}

void Render::renderInTextBoxInGreen(Font font, bool isCorrect, std::vector<std::string> userWords)
{
    float x = 30;
    float y = 30;
    for (int i = 0; i < userWords.size(); i++)
    {
        // DrawText(userWords[i].c_str(), x, y, textSize, GREEN);
        DrawTextEx(font, userWords[i].c_str(), {x, y}, fontSize, 0, GREEN);
        Vector2 value = MeasureTextEx(font, userWords[i].c_str(), fontSize, 0);
        x += value.x + 10;
        if (!(i + 1 >= userWords.size()))
        {
            Vector2 value2 = MeasureTextEx(font, userWords[i + 1].c_str(), fontSize, 0);
            if (x + value2.x >= windowWidth - 20)
            {
                x = 30;
                y += 30;
            }
        }
    }
}

void Render::greyBox(Font font, bool &isCorrect, int &x, int &y, int numOfWord, std::vector<std::string> words)
{
    Vector2 value = MeasureTextEx(font, words[numOfWord].c_str(), fontSize, 0);
    if (isCorrect)
    {
        Vector2 value2 = MeasureTextEx(font, words[numOfWord - 1].c_str(), fontSize, 0);
        x += value2.x + 10;
        isCorrect = false;
    }
    DrawRectangle(x, y + 4, value.x, value.y - 5, GRAY);

    if (!(numOfWord + 1 > words.size()))
    {
        Vector2 value3 = MeasureTextEx(font, words[numOfWord].c_str(), fontSize, 0);
        if (x + value3.x >= windowWidth - 20)
        {
            x = 30;
            y += 30;
        }
    }
}

void Render::loadFonts()
{
    font = LoadFontEx("/home/steel/main/typing_game/resources/Kanit-Black.ttf", fontSize, 0, 0);
    // Check if the font was loaded successfully
    if (font.texture.id == 0)
    {
        // Handle error, e.g., print an error message
        std::cerr << "Error loading font!" << std::endl;
    }
}

void Render::drawTime(bool &timerActive, float &timer)
{
    if (IsKeyPressed(KEY_SPACE))
    {
        timerActive = true;
    }

    if (timerActive)
    {
        if (timer > 0)
        {
            timer -= GetFrameTime() * 1000; // Convert seconds to milliseconds
        }
        else
        {
            timer = 0;
            timerActive = false;
        }
    }
    // Draw the formatted time
    DrawText(TextFormat("%.0fs", timer / 1000), 650, 460, 40, BLACK);
}

void Render::allFuntionToDraw(std::vector<std::string> words, std::string &userInput, std::vector<std::string> userWords)
{
    // Outer Rectangle
    DrawRectangleLines(outerRec.x, outerRec.y, outerRec.width, outerRec.height, BLACK);

    // Inner Rectangle
    DrawRectangleLines(innerRec.x, innerRec.y, innerRec.width, innerRec.height, BLACK);

    // Correction box
    greyBox(font, isCorrect, x_box, y_box, numOfWord, words);

    // Paragraph
    renderOnTextBox(font, words);

    // Text on userBox
    renderUserInputs(font, userInput);

    // Words in green
    renderInTextBoxInGreen(font, isCorrect, userWords);

    // KeyBoard inputs
    getKeyboardInputs(isCorrect, userInput, userWords, numOfWord, words);
}

void Render::reset()
{
    timer = 6000.0f;
    isStarted = false;
    timerActive = false;
    x_box = 30;
    y_box = 30;
}

void Render::setTimer(float value)
{
    timer = value;
}

void Render::wpm(int time, int correctWords)
{
    int WPM = static_cast<int>(static_cast<double>(correctWords) / (static_cast<double>(time) / 60000.0));
    std::cout << "WPM: " << WPM << std::endl;
    // DrawText(TextFormat("WPM: %d", WPM), 400, 400, 40, YELLOW);
}
// Function to draw
void Render::draw()
{
    std::vector<std::string> words = stringToWords();
    InitWindow(windowWidth, windowHeight, "TYPING GAME");
    loadFonts();

    std::string userInput{};
    std::vector<std::string> userWords;

    Gui gui;
    int correctWords{};
    float time{};
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        BeginDrawing();
        if (timer < 0.0f)
        {
            reset();
            gui.set(false);
            userInput.clear();
            userWords.clear();
            correctWords = numOfWord;
            numOfWord = 0;
            if (correctWords != 0)
            {
                wpm(time, correctWords);
            }
        }
        if (isStarted && timer >= 0.0f)
        {
            ClearBackground(YELLOW);
            allFuntionToDraw(words, userInput, userWords);
            // Clock
            drawTime(timerActive, timer);
        }
        else
        {
            ClearBackground(BLACK);
            gui.drawGui();
            isStarted = gui.get();
            timer = gui.getTimer();
            time = timer;
        }
        EndDrawing();
    }

    UnloadFont(font);
    CloseWindow();
}