#include "App.h"
#include "..\Headers\App.h"

App::App(const wchar_t* gameName) 
    :mainWnd(gameName)
{
}

int App::Run()
{
    MSG msg;
    BOOL id;
    while ((id = GetMessage(&msg, NULL, 0, 0)) > 0) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
        
    }
    return msg.wParam;
}
