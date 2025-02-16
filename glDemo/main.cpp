
#include "core.h"
#include "TextureLoader.h"
#include "ArcballCamera.h"
#include "GUClock.h"
#include "PrincipleAxes.h"
#include "shader_setup.h"
#include "helper.h"
#include "AIMesh.h"
#include "Cube.h"
#include "Scene.h"


using namespace std;
using namespace glm;


#pragma region Global variables

GUClock* gameClock = nullptr;

// Mouse tracking
bool				mouseDown = false;
double				prevMouseX, prevMouseY;

// Global Example objects
// shouldn't really be anything in here for the final submission
ArcballCamera* mainCamera = nullptr;
CGPrincipleAxes* principleAxes = nullptr;
Cube* cube = nullptr;

GLuint flatColourShader;

GLuint texDirLightShader; 
vec3 DLdirection = vec3(0.0f, 1.0f, 0.0f);
vec3 DLcolour = vec3(1.0f, 1.0f, 1.0f);

AIMesh* creatureMesh = nullptr;
vec3 beastPos = vec3(2.0f, 0.0f, 0.0f);
float beastRotation = 0.0f;
AIMesh* planetMesh = nullptr;

int g_showing = 0;
int g_NumExamples = 3;

//Global Game Object
Scene* g_Scene = nullptr;

// Window size
const unsigned int initWidth = 512;
const unsigned int initHeight = 512;

#pragma endregion


// Function prototypes
void renderScene();
void updateScene();
void resizeWindow(GLFWwindow* window, int width, int height);
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseMoveHandler(GLFWwindow* window, double xpos, double ypos);
void mouseButtonHandler(GLFWwindow* window, int button, int action, int mods);
void mouseScrollHandler(GLFWwindow* window, double xoffset, double yoffset);
void mouseEnterHandler(GLFWwindow* window, int entered);


int main() {

	//
	// 1. Initialisation
	//
	
	gameClock = new GUClock();

#pragma region OpenGL and window setup

	// Initialise glfw and setup window
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_TRUE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);

	GLFWwindow* window = glfwCreateWindow(initWidth, initHeight, "GDV5001", NULL, NULL);

	// Check window was created successfully
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	

	// Set callback functions to handle different events
	glfwSetFramebufferSizeCallback(window, resizeWindow); // resize window callback
	glfwSetKeyCallback(window, keyboardHandler); // Keyboard input callback
	glfwSetCursorPosCallback(window, mouseMoveHandler);
	glfwSetMouseButtonCallback(window, mouseButtonHandler);
	glfwSetScrollCallback(window, mouseScrollHandler);
	glfwSetCursorEnterCallback(window, mouseEnterHandler);

	// Initialise glew
	glewInit();

	
	// Setup window's initial size
	resizeWindow(window, initWidth, initHeight);

#pragma endregion


	// Initialise scene - geometry and shaders etc
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // setup background colour to be black
	glClearDepth(1.0f);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//
	// Setup the Example Objects
	//

	texDirLightShader = setupShaders(string("Assets\\Shaders\\texture-directional.vert"), string("Assets\\Shaders\\texture-directional.frag"));
	flatColourShader = setupShaders(string("Assets\\Shaders\\flatColour.vert"), string("Assets\\Shaders\\flatColour.frag"));

	mainCamera = new ArcballCamera(0.0f, 0.0f, 1.98595f, 55.0f, 1.0f, 0.1f, 500.0f);
	
	principleAxes = new CGPrincipleAxes();

	cube = new Cube();

	creatureMesh = new AIMesh(string("Assets\\beast\\beast.obj"));
	if (creatureMesh) {
		creatureMesh->addTexture(string("Assets\\beast\\beast_texture.bmp"), FIF_BMP);
	}


	planetMesh = new AIMesh(string("Assets\\gsphere.obj"));
	if (planetMesh) {
		planetMesh->addTexture(string("Assets\\Textures\\Hodges_G_MountainRock1.jpg"), FIF_JPEG);
	}

	//
	//Set up Game class
	//

	g_Scene = new Scene();

	ifstream manifest;
	manifest.open("manifest.txt");

	g_Scene->Load(manifest);
	g_Scene->Init();

	manifest.close();


	//
	// Main loop
	// 

	while (!glfwWindowShouldClose(window)) {

		updateScene();
		renderScene();						// Render into the current buffer
		glfwSwapBuffers(window);			// Displays what was just rendered (using double buffering).

		glfwPollEvents();					// Use this version when animating as fast as possible
	
		// update window title
		char timingString[256];
		sprintf_s(timingString, 256, "CIS5013: Average fps: %.0f; Average spf: %f", gameClock->averageFPS(), gameClock->averageSPF() / 1000.0f);
		glfwSetWindowTitle(window, timingString);
	}

	glfwTerminate();

	if (gameClock) {

		gameClock->stop();
		gameClock->reportTimingData();
	}

	return 0;
}


// renderScene - function to render the current scene
void renderScene()
{
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mat4 cameraTransform = mainCamera->projectionTransform() * mainCamera->viewTransform();

	mat4 cameraProjection = mainCamera->projectionTransform();
	mat4 cameraView = mainCamera->viewTransform() * translate(identity<mat4>(), -beastPos);

#// Render principle axes - no modelling transforms so just use cameraTransform
	if (true) {

		{
			// Render cube 
			glUseProgram(flatColourShader);
			GLint pLocation;
			Helper::SetUniformLocation(flatColourShader, "viewMatrix", &pLocation);
			glUniformMatrix4fv(pLocation, 1, GL_FALSE, (GLfloat*)&cameraView);
			Helper::SetUniformLocation(flatColourShader, "projMatrix", &pLocation);
			glUniformMatrix4fv(pLocation, 1, GL_FALSE, (GLfloat*)&cameraProjection);
			Helper::SetUniformLocation(flatColourShader, "modelMatrix", &pLocation);
			mat4 modelTransform = identity<mat4>();
			glUniformMatrix4fv(pLocation, 1, GL_FALSE, (GLfloat*)&modelTransform);

			principleAxes->render();
		}
	}

	switch (g_showing)
	{
	case 0:
	{
		glUseProgram(texDirLightShader);

		GLint pLocation;
		Helper::SetUniformLocation(texDirLightShader, "viewMatrix", &pLocation);
		glUniformMatrix4fv(pLocation, 1, GL_FALSE, (GLfloat*)&cameraView);
		Helper::SetUniformLocation(texDirLightShader, "projMatrix", &pLocation);
		glUniformMatrix4fv(pLocation, 1, GL_FALSE, (GLfloat*)&cameraProjection);
		Helper::SetUniformLocation(texDirLightShader, "texture", &pLocation);
		glUniform1i(pLocation, 0); // set to point to texture unit 0 for AIMeshes
		Helper::SetUniformLocation(texDirLightShader, "lightDirection", &pLocation);
		glUniform3fv(pLocation, 1, (GLfloat*)&DLdirection);
		Helper::SetUniformLocation(texDirLightShader, "lightColour", &pLocation);
		glUniform3fv(pLocation, 1, (GLfloat*)&DLcolour);

		if (creatureMesh) {

			// Setup transforms
			Helper::SetUniformLocation(texDirLightShader, "modelMatrix", &pLocation);
			mat4 modelTransform = glm::translate(identity<mat4>(), beastPos) * eulerAngleY<float>(glm::radians<float>(beastRotation));
			glUniformMatrix4fv(pLocation, 1, GL_FALSE, (GLfloat*)&modelTransform);

			creatureMesh->setupTextures();
			creatureMesh->render();
		}

		if (planetMesh) {

			// Setup transforms
			Helper::SetUniformLocation(texDirLightShader, "modelMatrix", &pLocation);
			mat4 modelTransform = glm::translate(identity<mat4>(), vec3(4.0,4.0,4.0));
			glUniformMatrix4fv(pLocation, 1, GL_FALSE, (GLfloat*)&modelTransform);

			planetMesh->setupTextures();
			planetMesh->render();
		}
	}
		break;

	case 1:
	{
		// Render cube 
		glUseProgram(flatColourShader);
		GLint pLocation;
		Helper::SetUniformLocation(flatColourShader, "viewMatrix", &pLocation);
		glUniformMatrix4fv(pLocation, 1, GL_FALSE, (GLfloat*)&cameraView);
		Helper::SetUniformLocation(flatColourShader, "projMatrix", &pLocation);
		glUniformMatrix4fv(pLocation, 1, GL_FALSE, (GLfloat*)&cameraProjection);
		Helper::SetUniformLocation(flatColourShader, "modelMatrix", &pLocation);
		mat4 modelTransform = glm::translate(identity<mat4>(), vec3(2.0, 0.0, 2.0));
		glUniformMatrix4fv(pLocation, 1, GL_FALSE, (GLfloat*)&modelTransform);

		cube->render();
		break;
	}
	case 2:
		g_Scene->Render();
	}

}


// Function called to animate elements in the scene
void updateScene() {

	float tDelta = 0.0f;

	if (gameClock) {

		gameClock->tick();
		tDelta = (float)gameClock->gameTimeDelta();
	}

	g_Scene->Update(tDelta);
}


#pragma region Event handler functions
//none of this is currently passed to the Game object
//probably a good idea to do that

// Function to call when window resized
void resizeWindow(GLFWwindow* window, int width, int height)
{
	if (mainCamera) {

		mainCamera->setAspect((float)width / (float)height);
	}

	glViewport(0, 0, width, height);		// Draw into entire window
}


// Function to call to handle keyboard input
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {

		// check which key was pressed...
		switch (key)
		{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, true);
				break;

			case GLFW_KEY_SPACE:
				g_showing++;
				g_showing= g_showing %g_NumExamples;

			default:
			{
			}
		}
	}
	else if (action == GLFW_RELEASE) {
		// handle key release events
		switch (key)
		{
			default:
			{
			}
		}
	}
}


void mouseMoveHandler(GLFWwindow* window, double xpos, double ypos) {

	if (mouseDown) {

		//float tDelta = gameClock->gameTimeDelta();

		float dx = float(xpos - prevMouseX);// *360.0f * tDelta;
		float dy = float(ypos - prevMouseY);// *360.0f * tDelta;

		if (mainCamera)
			mainCamera->rotateCamera(-dy, -dx);

		prevMouseX = xpos;
		prevMouseY = ypos;
	}

}

void mouseButtonHandler(GLFWwindow* window, int button, int action, int mods) {

	if (button == GLFW_MOUSE_BUTTON_LEFT) {

		if (action == GLFW_PRESS) {

			mouseDown = true;
			glfwGetCursorPos(window, &prevMouseX, &prevMouseY);
		}
		else if (action == GLFW_RELEASE) {

			mouseDown = false;
		}
	}
}

void mouseScrollHandler(GLFWwindow* window, double xoffset, double yoffset) {

	if (mainCamera) {

		if (yoffset < 0.0)
			mainCamera->scaleRadius(1.1f);
		else if (yoffset > 0.0)
			mainCamera->scaleRadius(0.9f);
	}
}

void mouseEnterHandler(GLFWwindow* window, int entered) {
}

#pragma endregion