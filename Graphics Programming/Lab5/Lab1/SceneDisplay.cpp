#include "SceneDisplay.h"


SceneDisplay::SceneDisplay()
{
	SceneSdlWindow = nullptr; //initialise to generate null access violation for debugging. 
	screenWidth = 1024.0f;
	screenHeight = 768.0f; 
}

void SceneDisplay::createDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initalise everything

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Min no of bits used to diplay colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);// set up z-buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // set up double buffer   

	SceneSdlWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)screenWidth, (int)screenHeight, SDL_WINDOW_OPENGL); // create window

	if (SceneSdlWindow == nullptr)
	{
		returnErrorMessage("window failed to create");
	}

	SceneGlContext = SDL_GL_CreateContext(SceneSdlWindow);

	if (SceneGlContext == nullptr)
	{
		returnErrorMessage("SDL_GL context failed to create");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		returnErrorMessage("GLEW failed to initialise");
	}

	glEnable(GL_DEPTH_TEST); //enable z-buffering 
	glEnable(GL_CULL_FACE); //dont draw faces that are not pointing at the camera

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
}

SceneDisplay::~SceneDisplay()
{
	SDL_GL_DeleteContext(SceneGlContext); // delete context
	SDL_DestroyWindow(SceneSdlWindow); // detete window 
	SDL_Quit();
}

float SceneDisplay::getDisplayWidth() { return screenWidth; } //getters
float SceneDisplay::getDisplayHeight() { return screenHeight; }



void SceneDisplay::changeBuffers()
{
	SDL_GL_SwapWindow(SceneSdlWindow); //swap buffers
}

void SceneDisplay::clearScreenDisplay(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear colour and depth buffer - set colour to colour defined in glClearColor
}

void SceneDisplay::returnErrorMessage(std::string errorString)  //returns an error message if one occurs
{
	std::cout << errorString << std::endl;
	std::cout << "press any  key to quit...";
	int in;
	std::cin >> in;
	SDL_Quit();
}

