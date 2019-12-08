#include "stdafx.h"
#include "Framework.h"
#include "Camera.h"
#include "Cube.h"
#include "Light.h"

GLvoid DrawScene();
void KeyInput(unsigned char key, int x, int y);
void SpecialKey(int key, int x, int y);
void SpecialKeyUp(int key, int x, int y);
void ProcessMouseEvent(int button, int state, int x, int y);

Framework framework;

int main(int argc,char** argv)
{
	
	framework.Init(argc,argv);

	glutDisplayFunc(DrawScene);
	glutIdleFunc(DrawScene);
	glutKeyboardFunc(KeyInput);	
	//glutSpecialFunc(SpecialKey);
	glutMouseFunc(ProcessMouseEvent);
	glutSpecialUpFunc(SpecialKeyUp);
	//glutMotionFunc(DragMouseFunc);

	glutMainLoop();
}

void KeyInput(unsigned char key, int x, int y)
{
	switch(key)
	{
	
	case 'z':
	{
		glm::vec3 pos = framework.pCamera->GetCameraPos();
		pos.z -= 0.1f;
		framework.pCamera->SetPosition(pos);
	}
		break;
	case 'Z':
	{
		glm::vec3 pos = framework.pCamera->GetCameraPos();
		pos.z += 0.1f;
		framework.pCamera->SetPosition(pos);
	}	
	break;
	case 'x':
	{
		glm::vec3 pos = framework.pCamera->GetCameraPos();
		//glm::vec3 dir = framework.pCamera->GetCameraCenter();
		pos.x -= 0.1f;
		//dir.x -= 0.1f;
		framework.pCamera->MoveLeft(pos);
		
		//framework.pCamera->SetDirection(dir);
	}
		break;
	case 'X':
	{
		glm::vec3 pos = framework.pCamera->GetCameraPos();
		//glm::vec3 dir = framework.pCamera->GetCameraCenter();
		pos.x += 0.1f;
		framework.pCamera->MoveRight(pos);
		//dir.x += 0.1f;
		
		//framework.pCamera->SetDirection(dir);
	}	
	break;
		
	case 'R':
		framework.pLight->position.z -= 0.3f;
		break;
	case 'r':
		framework.pLight->position.z += 0.3f;
		
		break;
	case 'S':
		framework.snowStop = true;
		break;
	case 's':
		framework.snowStop = false;
		break;
	case 'Y':
	
		framework.RotateCamera(true);
		break;
	case 'y':
		framework.RotateCamera(false);
		break;
	case 'Q':
	case 'q':
		exit(1);
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
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	framework.Draw();
	
	glutSwapBuffers();
}

void ProcessMouseEvent(int button,int state,int x,int y)
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		
	}
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
	
	}



	glutPostRedisplay();
}