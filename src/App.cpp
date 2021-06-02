#include "App.h"
#include<sstream>

App::App(const wchar_t* gameName) 
    :mainWnd(gameName)
{

}

int App::Run()
{

    while(true)
    {
        if (const auto quit = mainWnd.WindowLoop())
        {
            return quit.value();
        }

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
