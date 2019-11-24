#include "stdafx.h"
#include "Framework.h"
#include "Camera.h"

GLvoid DrawScene();
void KeyInput(unsigned char key, int x, int y);
void SpecialKey(int key, int x, int y);
void ProcessMouseEvent(int button, int state, int x, int y);

Framework framework;

int main(int argc,char** argv)
{
	
	framework.Init(argc,argv);

	glutDisplayFunc(DrawScene);
	glutIdleFunc(DrawScene);
	glutKeyboardFunc(KeyInput);	
	glutSpecialFunc(SpecialKey);
	glutMouseFunc(ProcessMouseEvent);
	//glutMotionFunc(DragMouseFunc);

	glutMainLoop();
}

void KeyInput(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'Q':
	case 'q':
		exit(1);
		break;

	}
}
void SpecialKey(int key,int x, int y)
{
	switch(key)
	{

	case GLUT_KEY_UP:
	{
		glm::vec3 pos = framework.pCamera->GetCameraPos();
		pos.y -= 0.1f;
		framework.pCamera->SetPosition(pos);
	}
		break;
	case GLUT_KEY_DOWN:
	{
		glm::vec3 pos = framework.pCamera->GetCameraPos();
		pos.y += 0.1f;
		framework.pCamera->SetPosition(pos);
	}
		break;
	case GLUT_KEY_LEFT:
	{
		glm::vec3 pos = framework.pCamera->GetCameraPos();
		pos.x -= 0.1f;
		framework.pCamera->SetPosition(pos);
	}
		break;
	case GLUT_KEY_RIGHT:
	{
		glm::vec3 pos = framework.pCamera->GetCameraPos();
		pos.x += 0.1f;
		framework.pCamera->SetPosition(pos);
	}
		break;
	}
}


GLvoid DrawScene()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

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