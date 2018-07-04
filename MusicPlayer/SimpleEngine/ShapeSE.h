#pragma once

#ifndef __SHAPE_SE_H__
#define __SHAPE_SE_H__


#include <GL\glew.h>
#include <GL/gl.h>
#include <GL\freeglut.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include <vector>
#include "MeshVAO.h"

class SimpleEngine;

class ShapeSE {
	friend class SimpleEngine;
public:

	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 sca;

	bool isVisible;

	glm::vec4 color;

	ShapeSE();
	ShapeSE(const ShapeSE &shape);
	ShapeSE(ShapeSE &&shape);
	virtual ~ShapeSE();

	virtual void setMeshVAO(const MeshVAO &mv);
	virtual int getArrayLength();
	

	void translate(glm::vec3 &v);
	void rotate(float angle, glm::vec3 &v);
	void scale(glm::vec3 &v);
	void setColor(glm::vec4 &v);
	void reset();
	void setDrawMode(GLint mode, int unitNum = 3);
private:

	virtual void draw(GLint mmIndex, GLint colorIndex);

	glm::mat4 modelMat;
	MeshVAO meshVao;
	
	GLint drawMode;
	int drawUnitNum;
};


#endif //__SHAPE_SE_H__



