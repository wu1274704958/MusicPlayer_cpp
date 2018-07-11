#include "SEPrintFFT.h"
#include "SimpleEngine\SimpleEngine.h"
#include "SimpleEngine\ShapeSE.h"
#include <iostream>
#include "SimpleEngine\MeshManager.h"

#define PI_2 3.1415926535898 * 2.0
#define PI_1F4 3.1415926535898 / 4.0
#define PI_3F4 (3.1415926535898 / 4.0) * 3.0

SimpleEngine *se = nullptr;
ShapeSE *sseV[256];

float YS[128];

bool L_BUTTON_DOWN = false;
int L_BTN_DOWN_X = 0;
int L_BTN_DOWN_Y = 0;

bool R_BUTTON_DOWN = false;
int R_BTN_DOWN_X = 0;
int R_BTN_DOWN_Y = 0;


HANDLE hand;
HANDLE mutexHand;
bool close = false;
bool autoRotateZ = false;
bool autoRotateY = false;



SEPrintFFT::SEPrintFFT() : PrintFFT()
{
	init_data();
}


void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON )
	{
		if (state == GLUT_DOWN)
		{
			L_BUTTON_DOWN = true;
			L_BTN_DOWN_X = x;
			L_BTN_DOWN_Y = y;
		}
		else if (state == GLUT_UP)
		{
			L_BUTTON_DOWN = false;
		}
	}

	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			R_BUTTON_DOWN = true;
			R_BTN_DOWN_X = x;
			R_BTN_DOWN_Y = y;
		}
		else if (state == GLUT_UP)
		{
			R_BUTTON_DOWN = false;
		}
	}

	

	if (button == 3)
	{
		se->translateView(glm::vec3(0.0f, 0.0f, 0.01f));
	}
	if (button == 4)
	{
		se->translateView(glm::vec3(0.0f, 0.0f, -0.01f));
	}
}

#define FSUB(f1,f2) abs(f1 - f2) < 0.1f

void motionFunc(int x, int y)
{
	if (L_BUTTON_DOWN)
	{
		int offset_x = x - L_BTN_DOWN_X;
		int offset_y = y - L_BTN_DOWN_Y;

		
		se->rotateView(offset_x / 100.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		
		
		se->rotateView(offset_y / 100.0f, glm::vec3(1.0f, 0.0f, 0.0f));

		L_BTN_DOWN_X = x;
		L_BTN_DOWN_Y = y;
	}

	if (R_BUTTON_DOWN)
	{
		int offset_x = x - R_BTN_DOWN_X;
		int offset_y = y - R_BTN_DOWN_Y;

		se->translateView(glm::vec3(offset_x / 100.0f,-(offset_y / 100.0f),0.0f));

		R_BTN_DOWN_X = x;
		R_BTN_DOWN_Y = y;
	}
}

void keyBoardFunc(unsigned char a, int x, int y)
{
	switch (a)
	{
	case 'l':
		for (int i = 0; i < 256; i++)
		{
			sseV[i]->setDrawMode(GL_LINE_STRIP);
		}
		break;
	case 'p':
		for (int i = 0; i < 256; i++)
		{
			sseV[i]->setDrawMode(GL_POINTS);
		}
		break;
	case 'r':
		se->resetView();
		break;
	case 'a':
		autoRotateZ = !autoRotateZ;
		break;
	case 'y':
		autoRotateY = !autoRotateY;
		break;
	case 'm':
		for (int i = 128; i < 256; i++)
		{
			sseV[i]->isVisible = !(sseV[i]->isVisible);
		}
		break;
	}
}

void update(int value);
void reSize(int w, int h);
void destory();
void display();
DWORD WINAPI ThreadProc(LPVOID lp);

SEPrintFFT::~SEPrintFFT()
{
	close = true;

	WaitForSingleObject(hand, INFINITE);
	
	
	CloseHandle(hand);
	CloseHandle(mutexHand);
	
	printf("clean up SEPrintFFT...\n");
}







inline void SEPrintFFT::init_data()
{
	mutexHand = CreateMutex(NULL, FALSE, NULL);
	if (mutexHand == 0)
	{
		std::cout << "create mutex failed" << std::endl;
		CloseHandle(mutexHand);
	}
	DWORD threadId;
	hand = CreateThread(NULL, 0, ThreadProc, NULL, 0, &threadId);
	
	if (hand == 0)
	{
		std::cout << "create thread failed" << std::endl;
		CloseHandle(hand);
	}
}

void SEPrintFFT::printFFT(float *fft, int len, float l, float h)
{
	for (int i = 12; i < 128; i++)
	{
		float hhh = sqrtf(fft[i]);

		float t = YS[i] + hhh;
		
		
		WaitForSingleObject(mutexHand, INFINITE);
		

		sseV[i]->scale(glm::vec3(t,t, l * 3.0f));

		ReleaseMutex(mutexHand);
		
		if(sseV[i + 128]->isVisible)
		{ 
			WaitForSingleObject(mutexHand, INFINITE);
			sseV[i+128]->scale(glm::vec3(t, t, h * 3.0f));
			ReleaseMutex(mutexHand);
		}
	}

}


void reSize(int w, int h)
{
	glViewport(0, 0, 800, 600);
}

void destory()
{
	SimpleEngine::freeSimpleEngine();
}

void display()
{
	if (close)
		glutLeaveMainLoop();

	if (autoRotateZ)
	{
		if (se->rot.z < PI_2)
		{
			se->rot.z += 0.1f;
		}
		else {
			se->rot.z = 0.0f;
		}
	}

	if (autoRotateY)
	{
		if (se->rot.y < PI_2)
		{
			se->rot.y += 0.1f;
		}
		else {
			se->rot.y = 0.0f;
		}
	}

	WaitForSingleObject(mutexHand, INFINITE);
	se->drawChildren();
	ReleaseMutex(mutexHand);
}

void update(int value)
{
	glutPostRedisplay();
	glutTimerFunc(30, update, 1);
}


DWORD  WINAPI ThreadProc(LPVOID lp) {

	char *music[1] = { "MusicPlayer.exe" };
	SimpleEngine::createSimpleEngine(1, music);
	se = SimpleEngine::getInstance();
	
	se->setPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

	std::cout << se << std::endl;

	GLfloat v1[] = {
		//0.0f,0.0f,0.0f,
		0.0f,0.1f,0.0f,
		0.0f,0.2f,-0.02f,
		0.0f,0.3f,-0.04f,
		0.007f,0.43f,-0.07f,
		-0.007f,0.43f,-0.07f,
		0.0f,0.58f,-0.10f,
		0.02f,0.58f,-0.10f,
		-0.02f,0.58f,-0.10f
	};

	GLfloat v2[] = {
		//0.0f,0.0f,0.0f,
		0.0f,-0.05f,0.0f,
		0.0f,-0.1f,0.0f,
		0.0f,-0.15f,0.0f,
		0.0f,-0.22f,0.0f,
		0.0f,-0.31f,0.0f,
		0.0f,-0.42,0.0f,
		0.0f,-0.55f,0.0f,
		0.0f,-0.70f,0.0f,
		0.0f,-0.87f,0.0f,
		0.0f,-1.04f,0.0f,
		0.0f,-1.20f,0.0f
	};

	MeshManager::addMesh(v1, sizeof(v1) / sizeof(float), "V1");
	//MeshManager::addMesh(v2, sizeof(v2) / sizeof(float), "V2");

	float space = PI_2 / 256.0f;
	float tmp = 1.0f / 128.0f;

	float sin = 0.0f, ssin = 0.0f;

	for (int i = 0; i < 128; i++)
	{
		ShapeSE *s = new ShapeSE();
		s->setDrawMode(GL_POINTS);
		
		s->setMeshVAO(MeshManager::getVAO("V1"));
		s->setColor(glm::vec4(0.0f + (i * (tmp / 2.0f)), 0.8f - (i * tmp), 0.5f + (i * tmp), 0.8f));

		//i * 0.01f
		//s->translate(glm::vec3(0.0f,1.5f ,0.0f ));
		s->rotate(space * i, glm::vec3(0.0f, 0.0f, 1.0f));
		
		if (i <= 70)
		{
			YS[i] = 1.0f * sinf(sin);
			sin += 0.0245436921874f;
			if (i == 70)
			{
				ssin = sinf(sin);
				sin = 4.7123889803846898576939650749193f;
			}
		}
		else {
			YS[i] = 1.0f *  (ssin + (1.0f + sinf(sin)));
			sin += 0.01225395477824044916841409977405f;
		}
	
		s->scale(glm::vec3(YS[i], YS[i], 1.0f));
		se->addChild(s);

		//¾µÏñ
		
		ShapeSE *s_mirror = new ShapeSE(*s);
		//s_mirror->isVisible = false;
		s_mirror->reset();
		s_mirror->rotate(- (space * (i + 1)) , glm::vec3(0.0f, 0.0f, 1.0f));
		//s_mirror->pos.z = -s_mirror->pos.z;
		s_mirror->scale(glm::vec3(YS[i], YS[i], 1.0f));
		se->addChild(s_mirror);
		sseV[i] = s;
		sseV[i + 128] = s_mirror;
	}

	std::cout << se->getChildNum() << std::endl;
	glPointSize(2.0f);
	glLineWidth(2.0f);

	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH, GL_NICEST);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH, GL_NICEST);

	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	se->run(display, update, reSize, destory,mouseFunc,motionFunc,keyBoardFunc);
	return 0;
}