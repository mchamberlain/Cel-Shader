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

#ifndef __RAW_MESH_LOADER_H__
#define __RAW_MESH_LOADER_H__

#include <string>
#include <GL/glew.h>

#include "RawMeshLoader.h"

class RawMeshLoader {
	public:
		/**
		* Constructor.
		*/
		RawMeshLoader();

		/**
		* Destructor.
		*/
		~RawMeshLoader();

		/**
		 * Loads a mesh from the specified file. When it loads the mesh it sets up a multi element
		 * array containing the vertices, normals and colours of earch vertex, if it is indeed in the
		 * specified file.
		 * @param path The file to load the mesh from.
		 * @return the number of vertices that was loaded, 0 if there was an error.
		 */
		unsigned int load(const std::string& path);

		/**
		 * Gets the current vertex array.
		 * @return a const pointer to the vertex array.
		 */
		const GLvoid* getVertexArray() const;

		/**
		 * Gets the current normal array.
		 * @return a const pointer to the normal array.
		 */
		const GLvoid* getNormalArray() const;

		/**
		 * Gets the current colour array.
		 * @return a const pointer to the colour array.
		 */
		const GLvoid* getColourArray() const;

		/**
		 * Gets the current vertex UV.
		 * @return a const pointer to the UV array.
		 */
		const GLvoid* getUVArray() const;

		/**
		 * Gets the number of elements stored in the arrays.
		 */
		const unsigned int getSize() const;

		/**
		 * Free's the current element arrays.
		 */
		void releaseArrays();

	private:
		/** The element array */
		GLvoid *vertexArray;
		/** The element array */
		GLvoid *normalArray;
		/** The element array */
		GLvoid *colourArray;
		/** The element array */
		GLvoid *uvArray;
		/** The number of vertices in the element array */
		unsigned int size;
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
