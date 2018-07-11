#include <iostream>
#include "SimpleEngine.h"

#include "LoadShaders.h"
#include <GL\freeglut.h>

SimpleEngine *SimpleEngine::_se = nullptr;
bool SimpleEngine::_isError = false;




SimpleEngine::SimpleEngine(int arge, char **argv)
{
	WIDTH = 800;
	HEIGHT = 600;

	program = 0;
	vposition = 0;

	pos = glm::vec3(0.0f, 0.0f, -3.0f);
	rot = glm::vec3(0.0f, 0.0f, 0.0f);

	glutInit(&arge, argv);
	glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutCreateWindow("SEPrintFFT");

	if (glewInit())
	{
		_isError = true;
		std::cout << "unable to initialize glew" << std::endl;	
	}

	projectionMat = glm::perspective(45.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	//viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));
	polygonModeFace = GL_FRONT_AND_BACK;
	polygonModeMode = GL_LINE;
}

void SimpleEngine::createSimpleEngine(int arge, char **argv)
{
	if (_se == nullptr)
	{
		_se = new SimpleEngine(arge, argv);
	}
}


void SimpleEngine::freeSimpleEngine()
{
	if (_se != nullptr)
	{
		delete _se;
		_se = nullptr;
	}
	printf("clean up SimpleEngine ...\n");
}

SimpleEngine *SimpleEngine::getInstance()
{
	if (_se == nullptr || _isError)
	{
		return nullptr;
	}
	else {
		return _se;
	}
}

SimpleEngine::~SimpleEngine()
{
	for (int i = 0; i < children.size(); i++)
	{
		delete (children.at(i));
	}
}

void SimpleEngine::addChild(ShapeSE *c)
{
	children.push_back(c);
}


void SimpleEngine::run(void(*display)(void), void(*timerFunc)(int), void(*reShape)(int, int),void(*closeFunc)(),void(*mouseFunc)(int,int,int,int),void(*motionFunc)(int,int),void(*keyBoardFunc)(unsigned char,int,int))
{

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(polygonModeFace, polygonModeMode);

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER,"triangles.vert" },
		{ GL_FRAGMENT_SHADER,"triangles.frag" },
		{ GL_NONE,NULL }
	};

	program = LoadShaders(shaders);
	glUseProgram(program);

	

	mmIndex = glGetUniformLocation(program, "model");
	vmIndex = glGetUniformLocation(program, "view");
	pmIndex = glGetUniformLocation(program, "projection");

	colorIndex = glGetUniformLocation(program, "Color");


	glUniformMatrix4fv(pmIndex, 1, GL_FALSE, glm::value_ptr(projectionMat));

	glutDisplayFunc(display);
	glutTimerFunc(33, timerFunc, 1);

	glutReshapeFunc(reShape);
	glutCloseFunc(closeFunc);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(motionFunc);
	glutKeyboardFunc(keyBoardFunc);

	glutMainLoop();
}

void SimpleEngine::drawChildren()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewMat = glm::mat4();
	viewMat = glm::translate(viewMat, pos);
	viewMat = glm::rotate(viewMat,rot.x ,glm::vec3(1.0f,0.0f,0.0f));
	viewMat = glm::rotate(viewMat, rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
	viewMat = glm::rotate(viewMat, rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
	
	glUniformMatrix4fv(vmIndex, 1, GL_FALSE, glm::value_ptr(viewMat));

	glUseProgram(program);

	
	//std::cout << children.size() << std::endl;
	for (int i = 0; i < children.size(); i++)
	{
		children.at(i)->draw(mmIndex,colorIndex);
		
	}
	glFlush();
	
}

void SimpleEngine::translateView(glm::vec3 &v)
{
	pos += v;
}

void SimpleEngine::rotateView(float angle, glm::vec3 &v)
{
	rot.x += v.x * angle;
	rot.y += v.y * angle;
	rot.z += v.z * angle;
}

void SimpleEngine::resetView()
{
	pos = glm::vec3(0.0f, 0.0f, -3.0f);
	rot = glm::vec3(0.0f, 0.0f, 0.0f);
}

void SimpleEngine::setPolygonMode(GLint face, GLint mode)
{
	polygonModeFace = face;
	polygonModeMode = mode;
}


