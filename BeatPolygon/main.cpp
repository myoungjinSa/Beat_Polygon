#include "stdafx.h"
#include "Framework.h"
#include "Camera.h"
#include "Cube.h"
#include "Light.h"

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
	case'd':
	case 'D':
		framework.pLight->dir = Light::DIRECTION::STOP;

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
void SpecialKey(int key,int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_LEFT:
	{
		framework.pLight->position.x -= 0.3f;
		std::cout << framework.pLight->position.x << "," << framework.pLight->position.y << "," << framework.pLight->position.z<<std::endl;
	}
		break;

	case GLUT_KEY_RIGHT:
	{
		framework.pLight->position.x += 0.3f;
		std::cout << framework.pLight->position.x << "," << framework.pLight->position.y << "," << framework.pLight->position.z<<std::endl;
	}
		break;
	case GLUT_KEY_UP:
	{
		//glm::vec3 pos = framework.pCamera->GetCameraPos();
		//pos.y -= 0.1f;
		//framework.pCamera->SetPosition(pos);
		framework.pLight->position.y += 0.3f;
		std::cout << framework.pLight->position.x << "," << framework.pLight->position.x << "," << framework.pLight->position.z<<std::endl;
	}
		break;
	case GLUT_KEY_DOWN:
	{

		framework.pLight->position.y -= 0.3f;
	//	std::cout << framework.pCube->lightPos.x << "," << framework.pCube->lightPos.y << "," << framework.pCube->lightPos.z<<std::endl;
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