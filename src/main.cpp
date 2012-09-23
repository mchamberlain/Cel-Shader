// Copyright (c) 2012, ME Chamberlain
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
// 	- Redistributions of source code must retain the above copyright notice, this
// 	  list of conditions and the following disclaimer.
// 	- Redistributions in binary form must reproduce the above copyright notice,
// 	  this list of conditions and the following disclaimer in the documentation 
// 	  and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
// SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
// TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
// BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
// WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <assert.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>

#include "MiscGL.h"
#include "CelShader.h"

#define DEFAULT_WINDOW_MAX_X 800.0f
#define DEFAULT_WINDOW_MAX_Y 600.0f
#define ASPECT_RATIO 4.0f / 3.0f
#define INITIAL_VIEWPORT_WIDTH 800
#define INITIAL_VIEWPORT_HEIGHT 600
#define BOUNDARY 0.05f

/*#ifndef DEBUG_CELSHADER
#define PRINTD(str,...)
#else
#define PRINTD(str,...) { printf("[%s]: ",__FUNCTION__); printf(str, ##__VA_ARGS__); }
#endif
*/

/** The main instance for the program */
CelShader* csInstance;

/** Display callback */
void display() {
	csInstance->draw();
}

/**
 * The window resize callback.
 * @param width The new width for the window
 * @param height The new height for the window.
 */
void reshapeFunc(int width, int height) {
	csInstance->reshapeWindow(width, height);
}

/**
 * Mouse button event callback.
 * @param button The button that was pressed or released.
 * @param state Indicates if the button was pressed or released.
 * @param x The x-coordinate of the cursor (window coordinates) when the event occured.
 * @param y The y-coordinate of the curosr (window coordinates) when the event occured.
 */
void mouseButtonHanlder(int button, int state, int x, int y) {
	csInstance->mouseButtonHandler(button, state, x, y);
}

/**
 * Mouse motion callback. Called when the mouse is moved while a button is down.
 * @param x The x-coordinate of the cursor (window coordinates) when the event occured.
 * @param y The y-coordinate of the curosr (window coordinates) when the event occured.
 */
void mouseMotionHandler(int x, int y) {
	csInstance->mouseMotionHandler(x, y);
}

/**
 * Keyboard event callback. Called when a key is pressed.
 * @param key The key that was pressed.
 * @param x The x-coordinate of the cursor (window coordinates) when the event occured.
 * @param y The y-coordinate of the curosr (window coordinates) when the event occured.
 */
void keyboardHandler(unsigned char key, int x, int y) {
	csInstance->keyboardHandler(key, x, y);
}

/**
 * The keyboard event callback for special keys (F1, F2, arrows, etc).
 * @param key The key that was pressed.
 * @param x The x-coordinate of the cursor (window coordinates) when the event occured.
 * @param y The y-coordinate of the curosr (window coordinates) when the event occured.
 */
void keyboardHandler2(int key, int x, int y) {
	csInstance->keyboardHandler(key, x, y);
}

/**
 * Keyboard event callback. Called when a key is released.
 * @param key The key that was released.
 * @param x The x-coordinate of the cursor (window coordinates) when the event occured.
 * @param y The y-coordinate of the curosr (window coordinates) when the event occured.
 */
void keyboardUpHandler(unsigned char key, int x, int y) {
	csInstance->keyboardUpHandler(key, x, y);
}

/**
 * Called once every iteration of the main loop if there are no other events.
 */
void idleFunc() {
	csInstance->step();
}

/**
 * Main method.
 * @param argc The number of command line arguments.
 * @param argv An array of strings containing the command line arguments.
 * @return 0 on successful termination, otherwise some error code.
 */
int main(int argc, char **argv) {
	int mainWindow;
	// Define the light source and it's properties
	GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat light_position[] = { 0.0f, 10.0f, 10.0f, 0.0f };

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(INITIAL_VIEWPORT_WIDTH, INITIAL_VIEWPORT_HEIGHT);
	glutInitWindowPosition(10, 10);
	mainWindow = glutCreateWindow("Cel Shader");

	// If the window could not be created, print an error message.
	if (mainWindow <= 0) {
		std::cout << "Error creating window. Check your OpenGL, and GLUT installations." << std::endl;
		exit(1);
	}

	// Initialize GLEW so that all openGL 2.0 extensions are supported
	GLenum err = glewInit();
	if (err != GLEW_OK)
    {
        std::cout << "Failed to initialise glew: " << glewGetErrorString(err) << std::endl;
        exit(2);
    }

	csInstance = new CelShader(INITIAL_VIEWPORT_WIDTH, INITIAL_VIEWPORT_HEIGHT);
	std::cout << "Setting up shaders: " << csInstance->setupShaders("shaders/celShader.vs", "shaders/celShader.frag") << std::endl;

	// Set the background to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Depth buffer setup
	glClearDepth(1.0f);

	// Enables Depth Testing
	glEnable(GL_DEPTH_TEST);

	// The Type Of Depth Test To Do
	glDepthFunc(GL_LEQUAL);

	// Really Nice Perspective Calculations
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// Setup the light source
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	// Do not enable OpenGL's built-in lighting
 	glDisable(GL_LIGHTING);
//  	glEnable(GL_LIGHT0);

	// Disable blending
	glDisable(GL_BLEND);

	// Enable back face culling
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	// Enable the use of vertex, normal and colour arrays in renedering
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	// Setup the glut callbacks
	glutReshapeFunc(reshapeFunc);
	glutKeyboardFunc(keyboardHandler);
	glutSpecialFunc(keyboardHandler2);
	glutMouseFunc(mouseButtonHanlder);
	glutDisplayFunc(display);
	glutKeyboardUpFunc(keyboardUpHandler);
 	glutMotionFunc(mouseMotionHandler);
	glutPassiveMotionFunc(mouseMotionHandler);
	glutIdleFunc(idleFunc);

	glutMainLoop();

	return 0;
}

// Copyright (c) 2012, ME Chamberlain
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
// 	- Redistributions of source code must retain the above copyright notice, this
// 	  list of conditions and the following disclaimer.
// 	- Redistributions in binary form must reproduce the above copyright notice,
// 	  this list of conditions and the following disclaimer in the documentation 
// 	  and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
// SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
// TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
// BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
// WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
