#include "ShapeSE.h"
#include <iostream>
ShapeSE::ShapeSE()
{

	pos = glm::vec3(0.0f, 0.0f, 0.0f);
	rot = glm::vec3(0.0f, 0.0f, 0.0f);
	sca = glm::vec3(1.0f, 1.0f, 1.0f);

	color = glm::vec4(0.0f, 1.0f, 0.0f,1.0f);

	drawMode = GL_TRIANGLES;
	drawUnitNum = 3;
	isVisible = true;
}

ShapeSE::ShapeSE(const ShapeSE &shape)
{
	pos = shape.pos;
	rot = shape.rot;
	sca = shape.sca;

	color = shape.color;
	drawMode = shape.drawMode;
	drawUnitNum = shape.drawUnitNum;
	isVisible = shape.isVisible;

	meshVao = shape.meshVao;
}

ShapeSE::ShapeSE(ShapeSE && shape)
{
	pos = shape.pos;
	rot = shape.rot;
	sca = shape.sca;

	color = shape.color;
	drawMode = shape.drawMode;
	drawUnitNum = shape.drawUnitNum;
	isVisible = shape.isVisible;

	meshVao = std::move(shape.meshVao);
}

ShapeSE::~ShapeSE()
{
	
}

void ShapeSE::setMeshVAO(const MeshVAO& mv)
{
	meshVao = mv;
}

int ShapeSE::getArrayLength()
{
	return meshVao.VNum;
}



void ShapeSE::draw(GLint mmIndex, GLint colorIndex)
{
	if(isVisible)
	{
		modelMat = glm::mat4();
		modelMat = glm::translate(modelMat, pos);
		modelMat = glm::rotate(modelMat, rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
		modelMat = glm::rotate(modelMat, rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
		modelMat = glm::rotate(modelMat, rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
		modelMat = glm::scale(modelMat, sca);

		glUniform4f(colorIndex, color.x, color.y, color.z, color.w);

		glUniformMatrix4fv(mmIndex, 1, GL_FALSE, glm::value_ptr(modelMat));
		//std::cout << "draw Shape" << _array.size() / 3 << std::endl;
		glBindVertexArray(meshVao.VAO);


		glDrawArrays(drawMode, 0, meshVao.VNum/ drawUnitNum);
	}
}

void ShapeSE::translate(glm::vec3 &v)
{
	pos += v;
}

void ShapeSE::rotate(float angle, glm::vec3 &v)
{
	rot.x += v.x * angle;
	rot.y += v.y * angle;
	rot.z += v.z * angle;
}

void ShapeSE::scale(glm::vec3 &v)
{
	sca = v;
}

void ShapeSE::reset()
{
	pos = glm::vec3(0.0f, 0.0f, 0.0f);
	rot = glm::vec3(0.0f, 0.0f, 0.0f);
	sca = glm::vec3(1.0f, 1.0f, 1.0f);
}

void ShapeSE::setColor(glm::vec4 &v)
{
	color = v;
}


void ShapeSE::setDrawMode(GLint mode, int unitNum)
{
	drawMode = mode;
	drawUnitNum = unitNum;
}