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

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <fstream>

#include "CelShader.h"
#include "MiscGL.h"
#include "RawMeshLoader.h"

#ifndef M_PI
#	define M_PI 3.14159265358979323846264338327
#endif

#define WHEEL_UP 3
#define WHEEL_DOWN 4

#define DRAW_GRID_ROWS 10
#define DRAW_GRID_COLS 10

CelShader::CelShader(int windowWidth, int windowHeight)
	: windowWidth(windowWidth),
	  windowHeight(windowHeight),
	  celShaderProg(0),
	  lightPos(10.0f, 5.0f, 0.0f, 1.0f),
	  angle(0),
	  viewAngleXZ(0.0f),
	  pitch(0.0f),
	  camDistance(35.0f),
	  prevTime(clock()),
	  scene(0),
	  dT(0)
{
}

CelShader::~CelShader() {
	meshLoader.releaseArrays();
}

bool CelShader::loadShader(const std::string& path, GLchar** source) {
	std::ifstream *inFile;
	std::streamoff len;
	unsigned int i;

	inFile = new std::ifstream(path.c_str(), std::ios::in);

	if (inFile->good() == false) {
		delete inFile;

		return false;
	}

	// Get the file size
	inFile->seekg(0, std::ios::end);
	len = inFile->tellg();
	inFile->seekg(std::ios::beg);

	if (len == 0) {
		return false;
	}

	*source = new GLchar[static_cast<unsigned int>(len) + 1];

	// Read the shader source from the file
	i = 0;
	while (inFile->good()) {
		(*source)[i] = inFile->get();
		if (!inFile->eof()) {
			i++;
		}
	}

	// Null terminate the string
	(*source)[i] = '\0';

	inFile->close();
	delete inFile;

	return true;
}

void CelShader::printShaderInfoLog(GLuint shader) {
	int infologLen = 0;
	int charsWritten = 0;
	GLchar *infoLog;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLen);

	if (infologLen > 0) {
		infoLog = new GLchar[infologLen];
		if (infoLog == NULL) {
			std::cerr << "ERROR: Could not allocate InfoLog buffer" << std::endl;
		}

		glGetShaderInfoLog(shader, infologLen, &charsWritten, infoLog);
		std::cerr << "InfoLog:" << std::endl << infoLog << std::endl << std::endl;

		delete [] infoLog;
	}
}

bool CelShader::setupShaders(const std::string& vertexShaderSourcePath, const std::string& fragmentShaderSourcePath) {
	GLuint vertexShader;
	GLuint fragmentShader;
	GLint vertCompiled;
	GLint fragCompiled;
	GLint linked;
	GLchar* vertexShaderSource;
	GLchar* fragmentShaderSource;

	if ((!loadShader(vertexShaderSourcePath, &vertexShaderSource)) || (!loadShader(fragmentShaderSourcePath, &fragmentShaderSource))) {
		return false;
	}

	// Create shader objects
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Associate the shaders with their source files
	glShaderSource(vertexShader, 1, const_cast<const GLchar**>(&vertexShaderSource), NULL);
	glShaderSource(fragmentShader, 1, const_cast<const GLchar**>(&fragmentShaderSource), NULL);

	// glShaderSource copies the source arrays, so we can delete them now
	delete[] vertexShaderSource;
	delete[] fragmentShaderSource;

	//Compile the vertex shader
	glCompileShader(vertexShader);
// 	printOpenGLError();
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertCompiled);
	printShaderInfoLog(vertexShader);

	//Compile the fragment shader
	glCompileShader(fragmentShader);
// 	printOpenGLError();
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragCompiled);
	printShaderInfoLog(fragmentShader);

	if ((!vertCompiled) || (!fragCompiled)) {
		std::cout << "compile error " << vertCompiled << " " << fragCompiled << std::endl;
		return false;
	}

	// Create a program object to attach the shaders too
	celShaderProg = glCreateProgram();
	glAttachShader(celShaderProg, vertexShader);
	glAttachShader(celShaderProg, fragmentShader);

	// Link the program
	glLinkProgram(celShaderProg);
// 	printOpenGLError();
	glGetProgramiv(celShaderProg, GL_LINK_STATUS, &linked);
// 	printProgramInfoLog(celShaderProg);

	if (!linked) {
		return false;
	}

	glUseProgram(celShaderProg);

	return true;
}

void CelShader::reshapeWindow(int windowWidth, int windowHeight) {
	GLfloat ratio;

	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	ratio = static_cast<GLfloat>(windowWidth) / static_cast<GLfloat>(windowHeight);

	/* Change to the projection matrix and set the viewing volume */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/* Set the perspective */
 	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	/* Setup the viewport */
	glViewport(0, 0, static_cast<GLsizei>(windowWidth), static_cast<GLsizei>(windowHeight));

	/* Switch to model view */
	glMatrixMode(GL_MODELVIEW);

	/* Reset The View */
	glLoadIdentity();
}

void CelShader::quit() {
	meshLoader.releaseArrays();
	exit(0);
}

void CelShader::keyboardHandler(int key, int x, int y) {
	switch (key) {
		case 27: //Escape
			quit();
			break;
		case GLUT_KEY_LEFT:
			viewAngleXZ -= 0.1f;

			if (viewAngleXZ < 0.0f) {
				viewAngleXZ += 2.0f * M_PI;
			}
			break;
		case GLUT_KEY_RIGHT:
			viewAngleXZ += 0.1f;

			if (viewAngleXZ > 2.0f * M_PI) {
				viewAngleXZ -= 2.0f * M_PI;
			}
			break;
		case GLUT_KEY_UP:
			pitch -= 0.1f;

			if (pitch < 0.0f) {
				pitch += 2.0f * M_PI;
			}
			break;
		case GLUT_KEY_DOWN:
			pitch += 0.1f;

			if (pitch > 2.0f * M_PI) {
				pitch -= 2.0f * M_PI;
			}
			break;
		case '+':
			camDistance *= 0.9f;
			break;
		case '-':
			camDistance *= 1.1f;
			break;
		default:
			pitch = 0.0f;
			viewAngleXZ = 0.0f;
			camDistance = 35.0f;
			scene = (scene + 1) % 3;
	}

}

void CelShader::keyboardUpHandler(unsigned char key, int x, int y) {
}

void CelShader::mouseButtonHandler(int button, int state, int x, int y) {
}

void CelShader::mouseMotionHandler(int x, int y) {
}

void CelShader::step() {
	dT = ((double) (clock() - prevTime)) / (double) CLOCKS_PER_SEC;
	prevTime = clock();

	// Increase the parameter for the movement of the light
	angle += dT * 0.5f;

	if (angle > 2.0f * M_PI) {
		angle -= 2.0f * M_PI;
	}

	// Set the light's position
	lightPos[0] = 10.0f * cosf(angle);
	lightPos[2] = 10.0f * sinf(angle);

	draw();
}

void CelShader::renderBasicScene() {
	glPushMatrix();

	glRotatef(115, 1.0f, 0.0f, 0.0f);

	// Render the back faces only, in wireframe first with thick black lines is a strict < test in the
	// depth buffer
 	glLineWidth(6.0f);
 	glPolygonMode(GL_BACK, GL_LINE);
	glDepthFunc(GL_LESS);
	glCullFace(GL_FRONT);
 	glColor3f(0.0f, 0.0f, 0.0f);
	// Don't use the shader when rendering the wireframe back faces
	glUseProgram(0);
 	glutSolidTorus(2.0f, 5.0f, 20, 40);

	// Render the front faces, filled, using the depth buffer test of <= so that we can render over anything
	// that is deeper or at the same depth. Thus only the thick outlines of the first render remain
 	glLineWidth(1.0f);
 	glPolygonMode(GL_FRONT, GL_FILL);
	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_BACK);
 	glColor3f(0.0f, 1.0f, 0.0f);
	// Use the cel shader when rendering
	glUseProgram(celShaderProg);
/*	glColor3f(0.0f, 1.0f, 0.0f);*/
 	glutSolidTorus(2.0f, 5.0f, 20, 40);

	glPopMatrix();
}

void CelShader::renderMoreComplexScene() {
	// Render the cube
	glPushMatrix();
	glRotatef(45, 0.0f, 1.0f, 0.0f);

	// Render the back faces only, in wireframe first with thick black lines is a strict < test in the
	// depth buffer
 	glLineWidth(6.0f);
 	glPolygonMode(GL_BACK, GL_LINE);
	glDepthFunc(GL_LESS);
	glCullFace(GL_FRONT);
 	glColor3f(0.0f, 0.0f, 0.0f);
	glUseProgram(0);
	glutSolidCube(4.0f);

	// Render the front faces, filled, using the depth buffer test of <= so that we can render over anything
	// that is deeper or at the same depth. Thus only the thick outlines of the first render remain
 	glLineWidth(1.0f);
 	glPolygonMode(GL_FRONT, GL_FILL);
	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_BACK);
 	glColor3f(1.0f, 0.0f, 0.0f);
	glUseProgram(celShaderProg);
/*	glColor3f(0.0f, 1.0f, 0.0f);*/
	glutSolidCube(4.0f);

	glPopMatrix();

	// Render a sphere
	glPushMatrix();
	glTranslatef(-10.0f, 0.0f, 0.0f);
// 	glFrontFace(GL_CW);

	// Render the back faces only, in wireframe first with thick black lines is a strict < test in the
	// depth buffer
 	glLineWidth(6.0f);
 	glPolygonMode(GL_BACK, GL_LINE);
	glDepthFunc(GL_LESS);
	glCullFace(GL_FRONT);
 	glColor3f(0.0f, 0.0f, 0.0f);
	glUseProgram(0);
	glutSolidSphere(3.0f, 80, 40);

	// Render the front faces, filled, using the depth buffer test of <= so that we can render over anything
	// that is deeper or at the same depth. Thus only the thick outlines of the first render remain
 	glLineWidth(1.0f);
 	glPolygonMode(GL_FRONT, GL_FILL);
	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_BACK);
 	glColor3f(0.0f, 1.0f, 0.0f);
	glUseProgram(celShaderProg);
/*	glColor3f(0.0f, 1.0f, 0.0f);*/
	glutSolidSphere(3.0f, 80, 40);

// 	glFrontFace(GL_CCW);
	glPopMatrix();

	// Render the cone
	glPushMatrix();
	glTranslatef(10.0f, -5.0f, 0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);

	// Render the back faces only, in wireframe first with thick black lines is a strict < test in the
	// depth buffer
 	glLineWidth(6.0f);
 	glPolygonMode(GL_BACK, GL_LINE);
	glDepthFunc(GL_LESS);
	glCullFace(GL_FRONT);
 	glColor3f(0.0f, 0.0f, 0.0f);
	glUseProgram(0);
	glutSolidCone(5.0, 8.0, 20, 20);

	// Render the front faces, filled, using the depth buffer test of <= so that we can render over anything
	// that is deeper or at the same depth. Thus only the thick outlines of the first render remain
 	glLineWidth(1.0f);
 	glPolygonMode(GL_FRONT, GL_FILL);
	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_BACK);
 	glColor3f(0.75f, 0.5f, 0.0f);
	glUseProgram(celShaderProg);
/*	glColor3f(0.0f, 1.0f, 0.0f);*/
	glutSolidCone(5.0, 8.0, 20, 20);

	glPopMatrix();

	// Render the plane
	glPushMatrix();
	glTranslatef(-5.0f, -10.0f, 0.0f);
 	glRotatef(-45, 1.0f, 0.0f, 0.0f);

	// Render the back faces only, in wireframe first with thick black lines is a strict < test in the
	// depth buffer
 	glLineWidth(6.0f);
 	glPolygonMode(GL_BACK, GL_LINE);
	glDepthFunc(GL_LESS);
	glCullFace(GL_FRONT);
	glUseProgram(0);
	glBegin(GL_QUADS);
	 	glColor3f(0.0f, 0.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(5.0f, 5.0f, 0.0f);
		glVertex3f(-5.0f, 5.0f, 0.0f);
		glVertex3f(-5.0f, -5.0f, 0.0f);
		glVertex3f(5.0f, -5.0f, 0.0f);

		// Have to render a back face, CW order
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(5.0f, -5.0f, 0.0f);
		glVertex3f(-5.0f, -5.0f, 0.0f);
		glVertex3f(-5.0f, 5.0f, 0.0f);
		glVertex3f(5.0f, 5.0f, 0.0f);
	glEnd();

	// Render the front faces, filled, using the depth buffer test of <= so that we can render over anything
	// that is deeper or at the same depth. Thus only the thick outlines of the first render remain
 	glLineWidth(1.0f);
 	glPolygonMode(GL_FRONT, GL_FILL);
	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_BACK);
	glUseProgram(celShaderProg);
	glBegin(GL_QUADS);
	 	glColor3f(0.0f, 0.5f, 0.75f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(5.0f, 5.0f, 0.0f);
		glVertex3f(-5.0f, 5.0f, 0.0f);
		glVertex3f(-5.0f, -5.0f, 0.0f);
		glVertex3f(5.0f, -5.0f, 0.0f);

		// Have to render a back face, CW order
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(5.0f, -5.0f, 0.0f);
		glVertex3f(-5.0f, -5.0f, 0.0f);
		glVertex3f(-5.0f, 5.0f, 0.0f);
		glVertex3f(5.0f, 5.0f, 0.0f);
	glEnd();

	glPopMatrix();
}

void CelShader::renderComplexScene() {

	// Load the mesh from file if it hasn't been loaded yet
	if (meshLoader.getSize() == 0) {
		std::cout << "Loading concept-sedan-02-sport.raw... (this may take a couple of seconds)" << std::endl;
		std::cout << "Vertices = " << meshLoader.load("models/concept-sedan-02-sport.raw") << std::endl;
	}

	glPushMatrix();
 	//glScalef(2.5f, 2.5f, 2.5f);
 	//glRotatef(45, 0.0f, 1.0f, 0.0f);
 	//glRotatef(-90, 1.0f, 0.0f, 0.0f);

	// Render the back faces only, in wireframe first with thick black lines is a strict < test in the
	// depth buffer
 	glLineWidth(6.0f);
 	glPolygonMode(GL_BACK, GL_LINE);
	glDepthFunc(GL_LESS);
	glCullFace(GL_FRONT);
	glUseProgram(0);

	// Disable the color array for glDrawArrays, as we want to use black at every vertex
	glDisableClientState(GL_COLOR_ARRAY);
	// Load the normal and vertex arrays from the mesh
	glNormalPointer(GL_FLOAT, 0, meshLoader.getNormalArray());
	glVertexPointer(3, GL_FLOAT, 0, meshLoader.getVertexArray());
	glColor3f(0.0f, 0.0f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 0, meshLoader.getSize());

	// Render the front faces, filled, using the depth buffer test of <= so that we can render over anything
	// that is deeper or at the same depth. Thus only the thick outlines of the first render remain
 	glLineWidth(1.0f);
 	glPolygonMode(GL_FRONT, GL_FILL);
	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_BACK);
	glUseProgram(celShaderProg);

	// Enable the color array
	glEnableClientState(GL_COLOR_ARRAY);
	// Load the colour array from the mesh
	glColorPointer(3, GL_FLOAT, 0, meshLoader.getColourArray());
	glNormalPointer(GL_FLOAT, 0, meshLoader.getNormalArray());
	glVertexPointer(3, GL_FLOAT, 0, meshLoader.getVertexArray());
	glDrawArrays(GL_TRIANGLES, 0, meshLoader.getSize());

	glPopMatrix();
}

void CelShader::draw() {
	GLfloat lightPosArray[4];

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.4f, 0.4f, 1.0f);
 	glLineWidth(1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -camDistance);
	glRotatef(pitch * 180 / M_PI, 1.0f, 0.0f, 0.0f);
	glRotatef(viewAngleXZ * 180 / M_PI, 0.0f, 1.0f, 0.0f);

	// Position the light source
	lightPos.copyTo(lightPosArray);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosArray);

	// Draw the light as a sphere
 	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(0.75f, 0.75f, 0.0f);
	glPushMatrix();
	glTranslatef(lightPosArray[0], lightPosArray[1], lightPosArray[2]);
	// Don't use the shader when rendering the light sphere
	glUseProgram(0);
	glutSolidSphere(1.0, 20, 10);
	glPopMatrix();

	// Render the selected scene
	if (scene == 0) {
		renderBasicScene();
	}
	else if (scene == 1) {
		renderMoreComplexScene();
	}
	else {
		renderComplexScene();
	}


	glFlush();
	glutSwapBuffers();
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
