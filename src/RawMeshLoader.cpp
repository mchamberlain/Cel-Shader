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

#include <string>
#include <iostream>
#include <fstream>

#include "RawMeshLoader.h"

RawMeshLoader::RawMeshLoader() {
	vertexArray = NULL;
	normalArray = NULL;
	colourArray = NULL;
	uvArray = NULL;
	size = 0;
}

RawMeshLoader::~RawMeshLoader() {
	releaseArrays();
}

unsigned int RawMeshLoader::load(const std::string& path) {
	std::ifstream inFile(path.c_str(), std::ios_base::in | std::ios_base::binary);
	unsigned int i;
	unsigned int entrySize;
	unsigned int uvSize;

	if (!inFile.good()) {
		return 0;
	}

	releaseArrays();

	size = 0;
	inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
	vertexArray = new GLfloat[size * 3];
	normalArray = new GLfloat[size * 3];
	colourArray = new GLfloat[size * 3];
	uvArray = new GLfloat[size * 2];

	entrySize = 3 * sizeof(GLfloat);
	uvSize = 2 * sizeof(GLfloat);
	i = 0;
	while (inFile.good()) {
		inFile.read(reinterpret_cast<char*>(vertexArray) + i * entrySize, entrySize);
		if (inFile.good()) {
			inFile.read(reinterpret_cast<char*>(normalArray) + i * entrySize, entrySize);
			if (inFile.good()) {
				inFile.read(reinterpret_cast<char*>(colourArray) + i * entrySize, entrySize);
				if (inFile.good()) {
					inFile.read(reinterpret_cast<char*>(uvArray) + i * uvSize, uvSize);
				}
			}
		}
		i++;
	}
	inFile.close();

	return i;
}

const GLvoid* RawMeshLoader::getVertexArray() const {
	return vertexArray;
}

const GLvoid* RawMeshLoader::getNormalArray() const {
	return normalArray;
}

const GLvoid* RawMeshLoader::getColourArray() const {
	return colourArray;
}

const GLvoid* RawMeshLoader::getUVArray() const {
	return uvArray;
}

const unsigned int RawMeshLoader::getSize() const {
	return size;
}

void RawMeshLoader::releaseArrays() {
	if (vertexArray != NULL) {
		delete [] static_cast<GLfloat*>(vertexArray);
		vertexArray = NULL;
	}

	if (normalArray != NULL) {
		delete [] static_cast<GLfloat*>(normalArray);
		normalArray = NULL;
	}

	if (colourArray != NULL) {
		delete [] static_cast<GLfloat*>(colourArray);
		colourArray = NULL;
	}

	if (uvArray != NULL) {
		delete [] static_cast<GLfloat*>(uvArray);
		uvArray = NULL;
	}
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
