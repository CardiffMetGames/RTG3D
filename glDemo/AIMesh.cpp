
#include "AIMesh.h"
#include "TextureLoader.h"

using namespace std;
using namespace glm;


AIMesh::AIMesh(std::string filename, GLuint meshIndex) {

	const struct aiScene* scene = aiImportFile(filename.c_str(),
		aiProcess_GenSmoothNormals |
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	if (!scene) {

		return;
	}

	aiMesh* mesh = scene->mMeshes[meshIndex];

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Setup VBO for vertex position data
	glGenBuffers(1, &meshVertexPosBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, meshVertexPosBuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh->mNumVertices * sizeof(aiVector3D), mesh->mVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Setup VBO for vertex normal data
	glGenBuffers(1, &meshNormalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, meshNormalBuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh->mNumVertices * sizeof(aiVector3D), mesh->mNormals, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(3);

	// *** normal mapping *** Setup VBO for tangent and bi-tangent data
	glGenBuffers(1, &meshTangentBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, meshTangentBuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh->mNumVertices * sizeof(aiVector3D), mesh->mTangents, GL_STATIC_DRAW);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(4);

	glGenBuffers(1, &meshBiTangentBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, meshBiTangentBuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh->mNumVertices * sizeof(aiVector3D), mesh->mBitangents, GL_STATIC_DRAW);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(5);

	if (mesh->mTextureCoords && mesh->mTextureCoords[0]) {

		// Setup VBO for texture coordinate data (for now use uvw channel 0 only when accessing mesh->mTextureCoords)
		glGenBuffers(1, &meshTexCoordBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, meshTexCoordBuffer);
		glBufferData(GL_ARRAY_BUFFER, mesh->mNumVertices * sizeof(aiVector3D), mesh->mTextureCoords[0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
		glEnableVertexAttribArray(2);
	}
	
	// Setup VBO for mesh index buffer (face index array)

	m_numFaces = scene->mMeshes[meshIndex]->mNumFaces;

	// Setup contiguous array
	const GLuint numBytes = scene->mMeshes[meshIndex]->mNumFaces * 3 * sizeof(GLuint);
	GLuint* faceIndexArray = (GLuint*)malloc(numBytes);

	GLuint* dstPtr = faceIndexArray;
	for (unsigned int f = 0; f < scene->mMeshes[meshIndex]->mNumFaces; ++f, dstPtr += 3) {

		memcpy_s(dstPtr, 3 * sizeof(GLuint), scene->mMeshes[meshIndex]->mFaces[f].mIndices, 3 * sizeof(GLuint));
	}

	glGenBuffers(1, &meshFaceIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshFaceIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numBytes, faceIndexArray, GL_STATIC_DRAW);

	glBindVertexArray(0);

	// Once done, release all resources associated with this import
	aiReleaseImport(scene);
}


// Texture setup methods

void AIMesh::addTexture(GLuint textureID) {

	this->textureID = textureID;
}

void AIMesh::addTexture(std::string filename, FREE_IMAGE_FORMAT format) {

	textureID = loadTexture(filename, format);
}

// ***normal mapping*** - helper functions at add normal map image to the object
void AIMesh::addNormalMap(GLuint normalMapID) {

	this->normalMapID = normalMapID;
}

void AIMesh::addNormalMap(std::string filename, FREE_IMAGE_FORMAT format) {

	normalMapID = loadTexture(filename, format);
}


// Rendering functions

void AIMesh::setupTextures() {

	if (meshTexCoordBuffer != 0) {

		if (textureID != 0) {
			
			glEnable(GL_TEXTURE_2D);
			
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureID);

			//  *** normal mapping ***  check if normal map added - if so bind to texture unit 1
			if (normalMapID != 0) {

				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, normalMapID);

				// Restore default
				glActiveTexture(GL_TEXTURE0);
			}
		}
	}
}


void AIMesh::render() {

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, m_numFaces * 3, GL_UNSIGNED_INT, (const GLvoid*)0);
}

