#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "SceneDisplay.h" 
#include "ShaderClass.h"
#include "ObjectMesh.h"
#include "ModelTransform.h"


enum class sceneState{Active, Close};

class MainScene
{
public:
	MainScene();
	~MainScene();

	void runProgram();

private:

	void initalise();
	void drawScene();
	void rimShader();
	void toonRimLighting();
	void ToonRimFog();
	void blobLighting();
	void toonLighting();
	void QuitFunction();
	void mainLoop();
	void modelDraw(int Index);

	SceneDisplay _sceneDisplay;
	sceneState _sceneState;	
	ShaderClass blobShader;
	ShaderClass toonShader;
	ShaderClass rimLightShader;
	ShaderClass toonRimShader;
	ShaderClass toonRimFogShader;
	ObjectMesh model1;
	ObjectMesh model2;
	ObjectMesh model3;
	ObjectMesh model4;
	ObjectMesh model5;
	SceneCamera sceneCamera;
	float timer;
};

