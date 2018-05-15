#include "MainScene.h"
#include "SceneCamera.h"
#include <iostream>
#include <string>


ModelTransform modelTransform;

MainScene::MainScene()
{
	_sceneState = sceneState::Active;  //sets the state od the scene to active
	SceneDisplay* _sceneDisplay = new SceneDisplay(); //creates new display
	//creates objects for models and shaders
    ObjectMesh* model1();
	ObjectMesh* model2();
	ObjectMesh* model3();
	ObjectMesh* model4();
	ObjectMesh* model5();
	ShaderClass* adsShader();
	ShaderClass* blobShader();
	ShaderClass* toonShader();
	ShaderClass* rimLightShader();
	ShaderClass* toonRimShader();
	ShaderClass* toonRimFogShader();
}

MainScene::~MainScene() 
{
}

void MainScene::runProgram()  //runs the program
{
	initalise(); //calls the method to initalise everything
	mainLoop();  //runs the main loop of the program
}

void MainScene::initalise()
{
	//initalizes the display
	_sceneDisplay.createDisplay(); 

	//loading models and shaders from their external files
	blobShader.InitaliseShader("..\\res\\shaderBlob.vert", "..\\res\\shaderBlob.frag");
	toonShader.InitaliseShader("..\\res\\shaderToon.vert", "..\\res\\shaderToon.frag");
	rimLightShader.InitaliseShader("..\\res\\shaderRim.vert", "..\\res\\shaderRim.frag");
	toonRimShader.InitaliseShader("..\\res\\shaderToonRim.vert", "..\\res\\shaderToonRim.frag");
	toonRimFogShader.InitaliseShader("..\\res\\shaderToonRimFog.vert", "..\\res\\shaderToonRimFog.frag");

	model1.loadModelFromFile("..\\res\\cone.obj");
	model2.loadModelFromFile("..\\res\\monkey3.obj");
	model3.loadModelFromFile("..\\res\\box.obj");
	model4.loadModelFromFile("..\\res\\ring.obj");
	model5.loadModelFromFile("..\\res\\sphere.obj");
	
	//creates a camera
	sceneCamera.createCamera(glm::vec3(0, 0, -10.0), 70.0f, (float)_sceneDisplay.getDisplayWidth()/_sceneDisplay.getDisplayHeight(), 0.01f, 1000.0f);

	//initalises the timer
	timer = 1.0f;
}

void MainScene::mainLoop()  //runst the main loop of the program
{
	while (_sceneState != sceneState::Close) //runs while the state is active
	{
		QuitFunction();    //checks if the state has changed to close
		drawScene();   //draws the models to the screen
		timer = timer + 0.01f;  //advances the timer
	}
}

void MainScene::QuitFunction() //checks if the state has changed to close
{
	SDL_Event Event;

	while(SDL_PollEvent(&Event)) //get and process events
	{
		switch (Event.type)
		{
			case SDL_QUIT:
				_sceneState = sceneState::Close;  //if SDL has quit, changes the state to Close
				break;
		}
	}
	
}

void MainScene::toonLighting()  //sends the light direction to the toon shader
{
	toonShader.setVec3("lightDirection", glm::vec3(0.5, 0.5, 0.5));
}

void MainScene::rimShader()  //sends the view and projection matricies to the rim shader
{
	rimLightShader.setMat4("u_vm", sceneCamera.GetView());
	rimLightShader.setMat4("u_pm", sceneCamera.GetProjection());
}

void MainScene::toonRimLighting()  // sends light direction, view martix, and projection matrix 
{
	toonRimShader.setVec3("lightDir", glm::vec3(0.5, 0.5, 0.5));
	toonRimShader.setMat4("u_vm", sceneCamera.GetView());
	toonRimShader.setMat4("u_pm", sceneCamera.GetProjection());
}

void MainScene::ToonRimFog()  //sends the light direction, view martix, projection matrix, zvalue, fog color, fog minimun and maximum distance
{
	toonRimFogShader.setVec3("lightDir", glm::vec3(0.8, 0.8, 0.8)); 
	toonRimFogShader.setFloat("zValue", modelTransform.GetPosition()->z);
	toonRimFogShader.setMat4("u_vm", sceneCamera.GetView());
	toonRimFogShader.setMat4("u_pm", sceneCamera.GetProjection());

	toonRimFogShader.setVec3("fogColor", glm::vec3(0.2, 0.2, 0.2));
	toonRimFogShader.setFloat("minDistance", -5.0f);
	toonRimFogShader.setFloat("maxDistance", 5.0f);
}

void MainScene::blobLighting()  //sends the inner and outer color and radiuses to the blob shader
{
	blobShader.setVec4("innerColor", glm::vec4(1.0f, 1.0f, 0.75f, 1.0f));
	blobShader.setVec4("outerColor", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	blobShader.setFloat("innerRadius", 0.0f);
	blobShader.setFloat("outerRadius", 0.75f);
}

void MainScene::drawScene()  //draws the scene to the screen
{
	_sceneDisplay.clearScreenDisplay(0.2f, 0.2f, 0.2f, 1.0f);  //clears the screen


//sends values to shaders and draws the models
	modelDraw(1);
	model1.drawModel();
	
	modelDraw(2);
	model2.drawModel();

	modelDraw(3);
	model3.drawModel();

	modelDraw(4);
	model4.drawModel();

	modelDraw(5);
	model5.drawModel();

	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	//swaps the buffers
	_sceneDisplay.changeBuffers();
} 

void MainScene::modelDraw(int Index)  //called from the draw method, updates shaders and model positions depending on what index it recieves
{
	switch (Index)
	{
		case(1):
		{
			modelTransform.SetPosition(glm::vec3(4.0, -sinf(timer),0));
			modelTransform.SetRotation(glm::vec3(270, timer * 5, 0));
			modelTransform.SetScale(glm::vec3(0.6, 0.6, 0.6));

			toonRimShader.BindShader();
			toonRimLighting();
			toonRimShader.Update(modelTransform, sceneCamera);
		}
		break;

		case(2):
		{
			modelTransform.SetPosition(glm::vec3(0.0, -1.0, -sinf(timer) * 5));
			modelTransform.SetRotation(glm::vec3(0.0, 90, 0.0));
			modelTransform.SetScale(glm::vec3(0.6, 0.6, 0.6));

			toonRimFogShader.BindShader();
			ToonRimFog();
			toonRimFogShader.Update(modelTransform, sceneCamera);
			cout << modelTransform.GetPosition()->z << std::endl;
		}
		break;
		
		case(3):
		{
			modelTransform.SetPosition(glm::vec3(-4.0, -sinf(timer), 0.0));
			modelTransform.SetRotation(glm::vec3(270, timer * 5, 0));
			modelTransform.SetScale(glm::vec3(0.6, 0.6, 0.6));

			blobShader.BindShader();
			blobLighting();
			blobShader.Update(modelTransform, sceneCamera);
		}
		break;		

		case(4):
		{
			modelTransform.SetPosition(glm::vec3(0.0, -sinf(timer), 0.0));
			modelTransform.SetRotation(glm::vec3(timer * 5, 0.0, -sinf(timer)));
			modelTransform.SetScale(glm::vec3(0.2, 0.2, 0.2));

			toonShader.BindShader();
			toonLighting();
			toonShader.Update(modelTransform, sceneCamera);
		}
		break;

		case(5):
		{
			modelTransform.SetPosition(glm::vec3(sinf(timer), 0.5, 0.0));
			modelTransform.SetRotation(glm::vec3(timer * 5, timer * 5, 0.0));
			modelTransform.SetScale(glm::vec3(0.6, 0.6, 0.6));

			rimLightShader.BindShader();
			rimShader();
			rimLightShader.Update(modelTransform, sceneCamera);
		}
		break;
	}
}