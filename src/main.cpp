#include <iostream>
#include <SDL2/SDL.h>
#include "Core/DapperCore.h"
#include "UI/Button.h"
#include "UI/Registrar.h"
#include "UI/Checkbox.h"
#include "UI/TextBox.h"
#include <unistd.h>

#include "UI/ProgressBar.h"

using namespace std;

bool DapperCore::running = true;

bool isCheck1On = false;

int main()
{
    DapperCore app(1000, 1000, "Dapper Test");

    const auto check1 = CreateUIElement<Checkbox>(200,200, 25, 2);
    check1->modifyShadow(3,3,0,0,0,128);
    check1->assignBoolean(&isCheck1On);

    const auto button1 = CreateUIElement<Button>(25,25,125,50);
    button1->modifyShadow(4, 4, 0, 0, 0, 200);
    button1->setText(0,0,"Button 1",24);
    button1->onClick = []() { std::cout << "Button clicked!\n"; };

    const auto button2 = CreateUIElement<Button>(25,100,125,50);
    button2->modifyShadow(4, 4, 0, 0, 0, 200);

    const auto button3 = CreateUIElement<Button>(25,175, 125,50);
    button3->modifyShadow(4, 4, 0, 255, 0, 50);
    button3->setText(0,0,"This is a button",24);
    button3->modifyOutline(2,0,0,0,255);

    const auto textBox1 = CreateUIElement<TextBox>(300,300, 300, 300,2);
	textBox1->setText(0,0,"Yellow black, yellow black, yellow black, yellow black, "
                       "ooo black and yellow lets shake it up a little. Barry Breakfast is ready! Coming Ma, *Ring Ring*, "
                       "Barry? Adam? Can you beleive this is happening? I cant ill pick you up. Looking sharp. Barry what "
                       "have i told you about flying in the house your father paid good money for those stairs. Theres our "
                       "son perfect report card! All B's.",24);
    textBox1->setBackGroundColor(255,255,255,255);

    const auto progressBar = CreateUIElement<ProgressBar>(50,800, 750, 50, 3);
    progressBar->setProgressColor(0,255,0,255);

    button2->onClick = [progressBar]() { progressBar->increaseByIntpercent(1); };
    button3->onClick = [progressBar]() { progressBar->increaseByIntpercent(5); };

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

