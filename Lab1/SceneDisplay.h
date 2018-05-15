#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class SceneDisplay
{
public:
	SceneDisplay();
	~SceneDisplay();
	void createDisplay();
	void changeBuffers();
	void clearScreenDisplay(float r, float g, float b, float a);

	float getDisplayWidth();
	float getDisplayHeight();

private:

	void returnErrorMessage(std::string errorMessage);
	
	SDL_GLContext SceneGlContext; //global variable to hold the context
	SDL_Window* SceneSdlWindow; //holds pointer to out window
	float screenWidth;
	float screenHeight;
};

