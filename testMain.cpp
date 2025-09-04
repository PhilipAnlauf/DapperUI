#include <iostream>
#include "DapperUI.h"

using namespace std;

bool isCheck1On = false;

int main()
{
    DapperUI::DapperCore app(1000, 1000, "Dapper Test");

    const auto check1 = DapperUI::CreateUIElement<DapperUI::Checkbox>(200,200, 25, 2);
    check1->modifyShadow(3,3,0,0,0,128);
    check1->assignBoolean(&isCheck1On);

    const auto button1 = DapperUI::CreateUIElement<DapperUI::Button>(25,25,125,50);
    button1->modifyShadow(4, 4, 0, 0, 0, 200);
    button1->setText(0,0,"Button 1",24);

    const auto button2 = DapperUI::CreateUIElement<DapperUI::Button>(25,100,125,50);
    button2->modifyShadow(4, 4, 0, 0, 0, 200);

    const auto button3 = DapperUI::CreateUIElement<DapperUI::Button>(25,175, 125,50);
    button3->modifyShadow(4, 4, 0, 255, 0, 50);
    button3->setText(0,0,"This is a button",24);
    button3->modifyOutline(2,0,0,0,255);

    const auto textBox1 = DapperUI::CreateUIElement<DapperUI::TextBox>(300,300, 300, 300,2);
    textBox1->setText(0,0,"Yellow black, yellow black, yellow black...",24);
    textBox1->setBackGroundColor(255,255,255,255);

    const auto progressBar = DapperUI::CreateUIElement<DapperUI::ProgressBar>(50,800, 750, 50, 3);
    progressBar->setProgressColor(0,255,0,255);

    button2->onClick = [progressBar]() { progressBar->increaseByIntPercent(1); };
    button3->onClick = [progressBar]() { progressBar->increaseByIntPercent(5); };
    button1->onClick = [textBox1]() { std::cout << "Button clicked!\n"; textBox1->setText(0,0,"Button 1 was clicked", 24); };

    Uint32 lastTime = SDL_GetTicks();
    while (app.running)
    {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 500.0f;
        lastTime = currentTime;

        app.update(deltaTime);
    }

    return 0;
}
