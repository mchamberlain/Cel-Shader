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

#ifndef __MISC_GL_H__
#define __MISC_GL_H__

#include <GL/glew.h>

#include "VectorN.h"

/** A 2-dimensional GLfloat vector type */
typedef VectorN<GLfloat,2>    GLVector2f;
/** A 2-dimensional GLdouble vector type */
typedef VectorN<GLdouble,2>   GLVector2d;
/** A 2-dimensional GLinteger vector type */
typedef VectorN<GLint,2>      GLVector2i;

/** A 3-dimensional GLfloat vector type */
typedef VectorN<GLfloat,3>    GLVector3f;
/** A 3-dimensional GLdouble vector type */
typedef VectorN<GLdouble,3>   GLVector3d;
/** A 3-dimensional GLinteger vector type */
typedef VectorN<GLint,3>      GLVector3i;

/** A 4-dimensional GLfloat vector type */
typedef VectorN<GLfloat,4>    GLVector4f;
/** A 4-dimensional GLdouble vector type */
typedef VectorN<GLdouble,4>   GLVector4d;
/** A 4-dimensional GLinteger vector type */
typedef VectorN<GLint,4>      GLVector4i;

class MiscGL {
	public:
		/**
		* Sets the position and the width and height of the default window.
		* @param x0 The bottom left x of window in world coordinates.
		* @param y0 The bottom left y of window in world coordinates.
		* @param x1 The top right x of window in world coordinates.
		* @param y2 The top right y of window in world coordinates.
		* @param boundary Adds boundary (where boundary is the %) in each dimension to the window.
		*								 In other words the window is enlarged by boundary% in each dimension.
		*/
		static void setWindow(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, float boundary);
		
		/**
		* Sets the position and the width and height of the default viewport.
		* @param x The x coordinate of the bottom left corner of the viewport.
		* @param y The y cooridnate of the bottom left corner of the viewport.
		* @param width The width of the viewport.
		* @param height The height of the viewport.
		* @param boundary Adds boundary (where boundary is the %) in each dimension to the viewport.
		*								 In other words the viewport is enlarged by boundary% in each dimension.
		*/
		static void setViewport(GLint x, GLint y, GLfloat width, GLfloat height, float boundary);
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
