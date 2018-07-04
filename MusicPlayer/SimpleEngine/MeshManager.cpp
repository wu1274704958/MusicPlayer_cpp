#include "MeshManager.h"
#include <GL\glew.h>
#include <GL/gl.h>
#include <GL\freeglut.h>

std::map<std::string, MeshVAO> MeshManager:: _MVS;

void MeshManager::addMesh(float *d, int len, const char *name)
{
	GLuint vao = 0;
	GLuint vbo = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, len * sizeof(float), d, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(0);

	MeshVAO mv( vao,vbo ,len);

	_MVS.insert(std::pair<std::string,MeshVAO>(std::move(std::string(name)), std::move(mv))); 
}

const MeshVAO& MeshManager::getVAO(const char *name)
{
	return _MVS[std::string(name)];
}