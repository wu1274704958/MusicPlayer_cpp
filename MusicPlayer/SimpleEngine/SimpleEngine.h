#pragma once
#ifndef __SIMPLE_ENGINE_H__
#define __SIMPLE_ENGINE_H__

#include "ShapeSE.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

class SimpleEngine
{
public:
	glm::vec3 pos;
	glm::vec3 rot;

	static void createSimpleEngine(int arge, char **argv);
	static void freeSimpleEngine();
	static SimpleEngine *getInstance();
	
	virtual ~SimpleEngine();
	void addChild(ShapeSE *c);
	void run(void(*display)(void), void(*timerFunc)(int), void(*reShape)(int, int),void (*closeFunc)(), void(*mouseFunc)(int, int, int, int) = NULL, void(*motionFunc)(int, int) = NULL, void(*keyBoardFunc)(unsigned char, int, int) = NULL);
	void drawChildren();

	void translateView(glm::vec3 &v);
	void rotateView(float angle, glm::vec3 &v);
	void resetView();

	void setPolygonMode(GLint face, GLint mode);

	int getChildNum() { return children.size(); };
private:

	glm::mat4 projectionMat;
	glm::mat4 viewMat;

	GLint vmIndex;
	GLint pmIndex;
	GLint mmIndex;

	GLint colorIndex;

	int WIDTH;
	int HEIGHT;

	GLint polygonModeFace;
	GLint polygonModeMode;

	std::vector<ShapeSE *> children;
	
	SimpleEngine(int arge, char **argv);
	

	static bool _isError;
	static SimpleEngine *_se;

	GLuint vposition;

	GLuint program ;
};





#endif //__SIMPLE_ENGINE_H__