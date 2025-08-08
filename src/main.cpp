#include "ofMain.h"
#include "ofApp.h"

#ifdef TARGET_WIN32
#include "../resource.h"
//========================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    ofSetupOpenGL(1024, 768, OF_WINDOW);            // <-------- setup the GL context
    HWND hwnd = ofGetWin32Window();
    HICON hMyIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MAIN_ICON));
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hMyIcon);
#else
//========================================================================
int main()
{
    ofSetupOpenGL(1024, 768, OF_WINDOW);            // <-------- setup the GL context
#endif

    //    ofSetDataPathRoot("../Resources/data/");

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());

}
