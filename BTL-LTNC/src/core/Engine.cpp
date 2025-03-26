#include "Engine.h"
#include <iostream>

using namespace std;

Engine* Engine::s_Instance = nullptr;

bool Engine::Init()
{
    m_Isrunning = true;
}

bool Engine::Clean()
{

}

void Engine::Quit()
{

}

void Engine::Update()
{
    cout << "updating...." << endl;
}

void Engine::Render()
{

}


