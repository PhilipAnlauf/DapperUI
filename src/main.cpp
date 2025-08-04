#include <iostream>
#include <SDL2/SDL.h>
#include "Core/DapperCore.h"
#include "UI/Button.h"
#include "UI/Registrar.h"
#include "UI/Checkbox.h"
#include "UI/TextBox.h"
#include <unistd.h>

using namespace std;

bool DapperCore::running = true;

bool isCheck1On = false;

int main()
{
    DapperCore app(1000, 1000, "Dapper Test");

    auto button1 = CreateUIElement<Button>(25,25,125,50);
    auto button2 = CreateUIElement<Button>(25,100,125,50, 15);
    auto button3 = CreateUIElement<Button>(25,175, 125,50,25);
    auto check1 = CreateUIElement<Checkbox>(200,200, 25, 5, 0);
	auto textBox1 = CreateUIElement<TextBox>(300,300, 300, 300,2);
    check1->assignBoolean(&isCheck1On);

    button1->modifyShadow(4, 4, 0, 0, 0, 200);
    button2->modifyShadow(4, 4, 0, 0, 0, 200);
    button3->modifyShadow(4, 4, 0, 255, 0, 50);
    button1->setText(0,0,"Button 1",24);
    button3->setText(0,0,"This is a button",24);
	textBox1->setText(0,0,"Wow, did this textbox actually work?",24);
    textBox1->setBackGroundColor(255,0,0,255);

    button1->onClick = []() { std::cout << "Button clicked!\n"; };
    button2->onClick = []() { std::cout << "Button2 clicked!\n"; };
    button3->onClick = []() { std::cout << "Button3 clicked!\n"; };

    Uint32 lastTime = SDL_GetTicks();
    while (DapperCore::running)
    {
        //std::cout << "Check1 status: " << isCheck1On << endl;
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 500.0f;
        lastTime = currentTime;

        app.update(deltaTime);
    }

    return 0;
}

