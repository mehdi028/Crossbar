#include "App.h"
#include<sstream>

App::App(const wchar_t* gameName) 
    :mainWnd(gameName)
{

}

int App::Run()
{
    std::ostringstream ss;


    MSG msg;
    BOOL id;
    while ((id = GetMessage(&msg, NULL, 0, 0)) > 0) {
        auto ev = mainWnd.kb.GetCharEvent();
        if (ev.eventType == Keyboard::Event::Type::Key_Char)
        {
            ss << ev.Unicode;
            SetWindowTextA(mainWnd.hwnd, ss.str().c_str());
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        
    }
    return msg.wParam;
}
