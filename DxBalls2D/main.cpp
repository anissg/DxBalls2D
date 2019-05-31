#include "stdafx.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    PhysicsSim engine;

    // Engine configuration
    // Config config;
    // Ui configuration

    engine.Initialize(/*config*/hInstance, L"TinyDXEngine", L"TDXEClass", 1280, 720);
    engine.Run();

    return 0;
}