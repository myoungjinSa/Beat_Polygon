#include "stdafx.h"
#include "Framework.h"
#include "Camera.h"
#include "Cube.h"
#include "Light.h"
#include "WallManager.h"

GLvoid DrawScene();
void KeyInput(unsigned char key, int x, int y);
void SpecialKeyUp(int key, int x, int y);
void ProcessMouseEvent(int button, int state, int x, int y);

Framework framework;

int main(int argc,char** argv)
{
	
	framework.Init(argc,argv);

	glutDisplayFunc(DrawScene);
	glutIdleFunc(DrawScene);
	glutKeyboardFunc(KeyInput);	
	glutMouseFunc(ProcessMouseEvent);
	glutSpecialUpFunc(SpecialKeyUp);
	
	glutMainLoop();
}

void KeyInput(unsigned char key, int x, int y)
{
	switch (key)
	{

#ifdef WRITE_MUSIC
	case 'm':
	case 'M':
		framework.pWallManager->WriteMusicInfo(framework.timer.GetTimeElapsed());
		break;
#endif
	default:
		std::cout << "정의 되지 않은 키" << std::endl;
		break;
	}
}

void SpecialKeyUp(int key, int x, int y)
{
	framework.EndDash();

}

GLvoid DrawScene()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	framework.Draw();
	
	glutSwapBuffers();
}

void ProcessMouseEvent(int button,int state,int x,int y)
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
	
		if (framework.gameState == Framework::GAME_STATE::INTRO)
		{
			if (x >= 492 && y >= 630 && x <= 730 && y <= 680)
			{
				framework.ChangeGameState(true);
			}
		}
	}


	glutPostRedisplay();
}