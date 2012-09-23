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

#ifndef __CEL_SHADER_H__
#define __CEL_SHADER_H__

#include <string>

#include "MiscGL.h"
#include "RawMeshLoader.h"

class CelShader {
	public:
		/**
		 * Constructor.
		 * @param windowWidth The width of the window.
		 * @param windowHeight The height of the window.
		 */
		CelShader(int windowWidth, int windowHeight);

		/**
		 * Destructor.
		 */
		~CelShader();

		/**
		 * Exists the program.
		 */
		void quit();

		/**
		 * Loads a shader file.
		 * @param path The path of the file.
		 * @param source An array of char* pointers. The source will be placed in the first element of the
		 * array.
		 * @return true if successfull, false otherwise.
		 */
		bool loadShader(const std::string& path, char** source);

		/**
		 * Print the info log for the specified shader.
		 * @param shader The shader to print the info log for.
		 */
		void printShaderInfoLog(GLuint shader);

		/**
		 * Creates the shader objects, compiles them and attaches them to the program.
		 * @param vertexShaderSource The path to the vertex shader source file.
		 * @param fragmentShaderSource The path to the fragment shader source file.
		 * @return true if the shader was compiled and linked successfully, false otherwise.
		 */
		bool setupShaders(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

		/**
		 * Resizes the objects to fit tightly into the new window size.
		 * @param windowWidth The new window width.
		 * @param windowHeight The new window height.
		 */
		void reshapeWindow(int windowWidth, int windowHeight);

		/**
		 * Handles keyboard events.
		 * @param key The key that was pressed.
		 * @param x The mouse x coordinate when the key was pressed.
		 * @param y The mouse y coordinate when the key was pressed.
		 */
		void keyboardHandler(int key, int x, int y);

		/**
		 * Handles key releases.
		 * @param key The key that was released.
		 * @param x The mouse x coordinate when the key was pressed.
		 * @param y The mouse y coordinate when the key was pressed.
		 */
		void keyboardUpHandler(unsigned char key, int x, int y);

		/**
		 * Handles mouse button events.
		 * @param button One of GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON or GLUT_RIGHT_BUTTON.
		 * @param state One of GLUT_UP (button released) or GLUT_DOWN (button pressed).
		 * @param x The mouse x coordinate when the key was pressed.
		 * @param y The mouse y coordinate when the key was pressed.
		 */
		void mouseButtonHandler(int button, int state, int x, int y);

		/**
		 * Handles mouse motion events.
		 * @param x The mouse x coordinate.
		 * @param y The mouse y coordinate.
		 */
		void mouseMotionHandler(int x, int y);

		/**
		 * This method draws the scene.
		 */
		void draw();

		/**
		 * Update the parameter controlling the light's position, based on the time that has passed since
		 * the last invocation.
		 */
		void step();

		/**
		 * Renders the basic scene, only a torus.
		 */
		void renderBasicScene();

		/**
		 * Renders a more complex scene, containing a cube, a cone, a teapot and a plane.
		 */
		void renderMoreComplexScene();

		/**
		 * Renders a model imported from Blender.
		 */
		void renderComplexScene();

	private:
		/** The total window width */
		int windowWidth;
		/** The total window height */
		int windowHeight;
		/** The program object used with the shaders */
		GLuint celShaderProg;
		/** The light's position */
		GLVector4f lightPos;
		/** Parameter controlling light position */
		float angle;
		/** Time variable used to calculate time difference between frames */
		unsigned long prevTime;
		/** Variable indicating the scene to be displayed */
		unsigned char scene;
		/** The model loader to use */
		RawMeshLoader meshLoader;
		/** time delta */
		float dT;
		/** mouse previous position */
		GLVector2i mousePrev;
		/** View angle */
		float viewAngleXZ;
		/** View pitch */
		float pitch;
		/** Camera distance */
		float camDistance;
};

#endif

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
