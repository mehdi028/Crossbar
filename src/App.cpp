#include "App.h"
#include<sstream>
#include <ctime>
App::App(const wchar_t* gameName) 
    :mainWnd(gameName)
{
    // main plate 
    main_plate = std::make_unique<Plate>(*(mainWnd.pgfx));
    Limit_Bar = std::make_unique<LimitLine>(*(mainWnd.pgfx));
    //Draw_eliments.push_back(std::make_unique<LimitLine>(*(mainWnd.pgfx)));
    
    int i = 0;
    while (i < 10)
    {
        Draw_eliments.push_back(std::make_unique<Enemy>(*(mainWnd.pgfx)));
        i++;
    }

}

int App::Run()
{
    MyTimer timr;
    float angle = 0;
    float x = 0.f;
    float y = 0.f;
    while(true)
    {
        
        if (const auto quit = mainWnd.WindowLoop())
        {
            return quit.value();
        }
        //mainWnd.pgfx->ClearRendered();
        /*auto  key = mainWnd.kb.GetKeysEvent();
        if (key.eventType == Keyboard::Event::Type::Key_Pressed && key.Unicode == VK_UP)
        {
            y += 10.f;
        }
        else if (key.eventType == Keyboard::Event::Type::Key_Pressed && key.Unicode == VK_DOWN)
        {
            y -= 10.f;
        }
        
        else if (key.eventType == Keyboard::Event::Type::Key_Pressed && key.Unicode == VK_LEFT)
        {
            x -= 10.f;
        }
        else if (key.eventType == Keyboard::Event::Type::Key_Pressed && key.Unicode == VK_RIGHT)
        {
            x += 10.f;
        }*/
        DrawFrame();
        
        std::string a = std::to_string( sin(timr.Peek()));
        OutputDebugStringA(a.c_str());
       // mainWnd.pgfx->DrawTriangle((float) sin(timr.Peek()), 0.02f, 1.f);
        mainWnd.pgfx->PresentFrame();
        mainWnd.pgfx->ClearRendered();
        
    }
    return -1;
    
   /* std::ostringstream ss;


    MSG msg;
    bool move = false;
    BOOL id;
    while ((id = GetMessage(&msg, NULL, 0, 0)) > 0) {
        auto ev = mainWnd.kb.GetCharEvent();
        auto mouse_event = mainWnd.mouse.GetMouseEvent();
        if (mouse_event.EventType == Mouse::Event::Type::MouseMove)
        {
            move = true;
            ss.str("");
            ss << "(" << mouse_event.coordinate.first << "," << mouse_event.coordinate.second << ")";
            SetWindowTextA(mainWnd.hwnd, ss.str().c_str());
            
        }
        else if (ev.eventType == Keyboard::Event::Type::Key_Char)
        {
            if (move == true)
            {
                ss.str("");
                move = false;
            }
            ss << ev.Unicode;
            SetWindowTextA(mainWnd.hwnd, ss.str().c_str());
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        
    }
    return msg.wParam;*/
}

void App::DrawFrame()
{
    /*static float move_plate_val = 0.f;
    auto kb_event = mainWnd.kb.GetKeysEvent();
    if (kb_event.Unicode == VK_RIGHT) {

        move_plate_val += 0.05f;
        main_plate->UpdatePos(move_plate_val, Limit_Bar->getLimitX());
    }
    else if (kb_event.Unicode == VK_LEFT)
    {
        move_plate_val -= 0.05f;
        main_plate->UpdatePos(move_plate_val, Limit_Bar->getLimitX() );

    }*/
    main_plate->MovePlate(mainWnd, Limit_Bar->getLimitX());
    Limit_Bar->Draw();
    main_plate->Draw();
    
    for (auto& eliment : Draw_eliments)
    {
        eliment->Draw();
    }
}


