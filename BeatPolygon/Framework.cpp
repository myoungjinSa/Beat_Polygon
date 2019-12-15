
#include "stdafx.h"
#include "Framework.h"
#include "stb_image.h"

#include "WallManager.h"
#include "Cube.h"
#include "Camera.h"
#include "Light.h"

#include "Pyramid.h"
#include "Snow.h"
#include "AlphaBlock.h"
#include "UI.h"
#include "Sound.h"
#include "ScreenEffect.h"

unsigned short Framework::hitCount{ 0 };
unsigned short Framework::combo{ 0 };

Framework::Framework()
{


	uiManager = std::make_unique<UIManager>();

	

}
Framework::~Framework()
{
	if (pCube)
	{
		delete pCube;
		pCube = nullptr;
	}


	if(pLight)
	{
		delete pLight;
		pLight = nullptr;
	}

	for (int i = 0; i < snowCount; ++i)
	{
		if (pSnow[i])
		{
			delete pSnow[i];
			pSnow[i] = nullptr;
		}
		delete[] pSnow;
		pSnow = nullptr;
	}

	for (int i = 0; i < blockCount; ++i)
	{
		if (pBlocks[i])
		{
			delete pBlocks[i];
			pBlocks[i] = nullptr;
		}
		delete[] pBlocks;
		pBlocks = nullptr;
	}

	if(pWallManager)
	{
#ifdef WRITE_MUSIC
		pWallManager->CloseMusicFile();
#endif
		delete pWallManager;
		pWallManager = nullptr;
	}


}

void Framework::CreateCamera(glm::vec3 pos,glm::vec3 dir,glm::vec3 up)
{
	pCamera = new Camera{ pos,dir,up };

	if(pCamera == nullptr)
	{
		std::cout << "카메라 생성 실패" << std::endl;
	}


}
void Framework::CreateBlocks()
{
	std::uniform_real_distribution<double>uxd(3.0f, 12.0f);
	std::uniform_real_distribution<double>uxd2(-12.0f, -3.0f);

	std::uniform_real_distribution<double>uzd(-12.0f, 12.0f);
	

	std::default_random_engine dre((unsigned int)time(0));
	pBlocks = new AlphaBlock*[blockCount];

	if (pBlocks)
	{
		for (int i = 0; i < blockCount; ++i)
		{
			pBlocks[i] = new AlphaBlock{};
			if (pBlocks[i])
			{
				pBlocks[i]->Create(shaderProgram[2]);
				if(i %2 == 0)
					pBlocks[i]->SetPosition(glm::vec3(uxd(dre), 0.0f, uzd(dre)));
				else
					pBlocks[i]->SetPosition(glm::vec3(uxd2(dre), 0.0f, uzd(dre)));

			}
		}
	}
}
void Framework::Init(int argc,char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(fWindowWidth, fWindowHeight);
	glutCreateWindow("도형 자르기");
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialze GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "GLEW Initiallize\n";
	}
	InitShader();
	CreateTexture();
	CreateCube();
	//CreateCeiling();
	mapInfo.upPos = 10.0f;
	CreateRightCube();
	CreateLeftCube();
	CreateLight();
	CreateSnow();
	CreateSound();
	CreateScreenEffect();
	CreateWallManager();
	AddFont();

	gameState = GAME_STATE::INTRO;

	//CreateObjModel();
	CreateCamera(glm::vec3{ pLight->GetPosition() + glm::vec3(0.0f,10.0f,35.0f)}, glm::vec3{ 0.0f,10.0f,-1.0f}, glm::vec3{ 0.0f,1.0f,0.0f });
	timer.Start();

	
	
}
void Framework::CreateScreenEffect()
{
	screenEffect = std::make_unique<ScreenEffect>();

	if(screenEffect)
	{
		
		screenEffect->Create(shaderProgram[3],"christmas.png","Intro.png");

	}

}
void Framework::CreateSound()
{
	gameSound = std::make_unique<GAMESOUND>();
	
	if (gameSound)
	{
		gameSound->Create("../BeatPolygon/sound/piano3.mp3");
		
	}

}
void Framework::CreateWallManager()
{
	pWallManager = new WallManager{};


	if(pWallManager)
	{
		
#ifdef WRITE_MUSIC
		pWallManager->OpenMusicFile();
#else
		pWallManager->ReadMusicFile();
#endif

		pWallManager->Create(shaderProgram[2],shaderProgram[1]);
	}
}

void Framework::CreatePyramid()
{
	pPyramid = new Pyramid{};

	if (pPyramid)
		pPyramid->Create(shaderProgram[2]);


}
void Framework::AddFont()
{
	if (uiManager) 
	{
		uiManager->AddUI(GLUT_BITMAP_TIMES_ROMAN_24,"HIT : ",-0.05f,0.2f);
		uiManager->AddUI(GLUT_BITMAP_TIMES_ROMAN_24, "COMBO : ", -0.05F, 0.1f);

	}
}

void Framework::DrawFont()
{
	if (uiManager)
		uiManager->Draw();
}

void Framework::CreateLight()
{
	pLight = new Light{
		Diffuse_Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f,1.0f)),		//leftTopFront
		Diffuse_Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f,1.0f)),		//leftBottomFront
		Diffuse_Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f,1.0f)),		//rightTopFront
		Diffuse_Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f,1.0f)),		//rightBottomFront
		Diffuse_Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 0.0f, 0.0f,1.0f)),	//leftBottomBack
		Diffuse_Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec4(1.0f, 0.0f, 0.0f,1.0f)),		//leftTopBack
		Diffuse_Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec4(1.0f, 0.0f, 0.0f,1.0f)),		//rightTopBack
		Diffuse_Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 0.0f,0.0f,1.0f))		//rightBottomBack};
	};
	glGenBuffers(1, &pLight->vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, pLight->vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, pLight->vCount * sizeof(Diffuse_Vertex), &pLight->v0, GL_STATIC_DRAW);

		
	//front
	pLight->Indices[0] = 0;
	pLight->Indices[1] = 1;
	pLight->Indices[2] = 2;
	
	pLight->Indices[3] = 2;
	pLight->Indices[4] = 1;
	pLight->Indices[5] = 3;
	
	pLight->Indices[6] = 0;
	pLight->Indices[7] = 5;
	pLight->Indices[8] = 4;
	
	pLight->Indices[9] = 0;
	pLight->Indices[10] = 4;
	pLight->Indices[11] = 1;
	
	pLight->Indices[12] = 5;
	pLight->Indices[13] = 6;
	pLight->Indices[14] = 7;
	

	pLight->Indices[15] = 5;
	pLight->Indices[16] = 7;
	pLight->Indices[17] = 4;
	

	pLight->Indices[18] = 6;
	pLight->Indices[19] = 2;
	pLight->Indices[20] = 7;
	
	pLight->Indices[21] = 3;
	pLight->Indices[22] = 7;
	pLight->Indices[23] = 2;
	
	pLight->Indices[24] = 0;
	pLight->Indices[25] = 2;
	pLight->Indices[26] = 5;
	
	pLight->Indices[27] = 2;
	pLight->Indices[28] = 6;
	pLight->Indices[29] = 5;
	
	pLight->Indices[30] = 1;
	pLight->Indices[31] = 4;
	pLight->Indices[32] = 7;
	
	pLight->Indices[33] = 1;
	pLight->Indices[34] = 7;
	pLight->Indices[35] = 3;
	

	glGenBuffers(1, &pLight->elementBufferObject);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pLight->elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * pLight->indexCount, &pLight->Indices[0], GL_STATIC_DRAW);

	pLight->InitShader(shaderProgram[1]);
	pLight->SetPosition(glm::vec3(0.0f, 3.5f, -5.0f));
	pLight->SetRange(10.0f);
	pLight->SetSpeed(20.0f);
	pLight->SetWidth(1.0f);
	pLight->SetDepth(1.0f);
	pLight->SetHeight(1.0f);

}



bool Framework::InitShader()
{
	glClearColor(1.f, 1.f, 1.f, 1.f);

	glEnable(GL_DEPTH_TEST);
	
	glFrontFace(GL_CCW);
	

	for (int i = 0; i < shaderCount; ++i)
	{
		std::string vertexShaderSource{};
		std::string fragShaderSource{};
		
		//셰이더 프로그램 오브젝트 생성
		shaderProgram[i] = glCreateProgram();
		if (i == 0)
		{
			vertexShaderSource = ReadStringFromFile("vertexShader.glvs");
			fragShaderSource = ReadStringFromFile("fragment.glfs");
			glBindAttribLocation(shaderProgram[i], 0, "vPos");
			glBindAttribLocation(shaderProgram[i], 1, "vNormal");
			glBindAttribLocation(shaderProgram[i], 2, "vUV");
		}
		else if(i == 1)
		{
			vertexShaderSource = ReadStringFromFile("lightVs.glvs");
			fragShaderSource = ReadStringFromFile("lightFs.glfs");
			glBindAttribLocation(shaderProgram[i], 0, "vPos");
			glBindAttribLocation(shaderProgram[i], 1, "vColor");
		}
		else if(i == 2)
		{
			vertexShaderSource = ReadStringFromFile("alphaVertexShader.glvs");
			fragShaderSource = ReadStringFromFile("alphaFragmentShader.glfs");
			glBindAttribLocation(shaderProgram[i], 0, "vPos");
			glBindAttribLocation(shaderProgram[i], 1, "vColor");
			glBindAttribLocation(shaderProgram[i], 2, "vNormal");
			glBindAttribLocation(shaderProgram[i], 3, "vUV");
		}
		else if(i == 3)
		{
			vertexShaderSource = ReadStringFromFile("screenVertexShader.glvs");
			fragShaderSource = ReadStringFromFile("screenFragmentShader.glfs");
			
		}
		GLuint vertShaderObj = CreateShader(GL_VERTEX_SHADER, vertexShaderSource);
		GLuint fragShaderObj = CreateShader(GL_FRAGMENT_SHADER, fragShaderSource);



		//셰이더 프로그램에 ㅂ텍스 및 프래그먼트 셰이더 등록
		glAttachShader(shaderProgram[i], vertShaderObj);
		glAttachShader(shaderProgram[i], fragShaderObj);

	



		//셰이더 프로그램과 셰이더 링킹 그리고 확인
		glLinkProgram(shaderProgram[i]);
		if (!CheckProgram(shaderProgram[i]))
		{
			glDeleteProgram(shaderProgram[i]);
			return false;
		}

		//사용된 셰이더 떼어냄
		glDetachShader(shaderProgram[i], vertShaderObj);
		glDetachShader(shaderProgram[i], fragShaderObj);


		glDeleteShader(vertShaderObj);
		glDeleteShader(fragShaderObj);

	}


	return true;
}

void Framework::DrawRightWall()
{
	glFrontFace(GL_CW);
	if(pRightCube)
	{
		for(int i =0;i<cubeCount;++i)
		{
			pRightCube[i]->Draw(shaderProgram[0]);
			
		}
	}
}

void Framework::DrawLeftWall()
{
	glFrontFace(GL_CW);
	if(pLeftCube)
	{
		for(int i =0;i<cubeCount;++i)
		{
			pLeftCube[i]->Draw(shaderProgram[0]);
			
		}
	}
}
void Framework::DrawCeiling()
{
	glFrontFace(GL_CCW);
	if (pCeiling)
	{
		for (int i = 0; i < cubeCount; ++i)
		{
			
			pCeiling[i]->Draw(shaderProgram[0]);
		
		}
	}

}
void Framework::DrawFloor()
{
	glFrontFace(GL_CCW);
	if (pCube)
	{
		for (int i = 0; i < cubeCount; ++i)
		{
			
			pCube[i]->Draw(shaderProgram[0]);
		
		}
	}

}
void Framework::StartDash()
{
	pLight->bDash = true;
}
void Framework::EndDash()
{
	pLight->bDash = false;
}
void Framework::Update()
{
	
	if (gameState == GAME_STATE::INGAME)
	{
		if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
		{
			if (pLight->bDash == false)
				StartDash();
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			float moveSpeed = pLight->GetSpeed() * timer.GetTimeElapsed();
			float dashPower = 1.0f;
			(pLight->bDash) ? dashPower = 8.0f : dashPower = 1.0f;
			pLight->position.x += moveSpeed * dashPower;

		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			float moveSpeed = pLight->GetSpeed() * timer.GetTimeElapsed();
			float dashPower = 1.0f;
			(pLight->bDash) ? dashPower = 8.0f : dashPower = 1.0f;
			pLight->position.x -= moveSpeed * dashPower;

		}


		if (gameSound->musicStart == false && gameSound)
		{
			gameSound->PlaySOUND(0);
			Timer::musicStartTime = std::chrono::steady_clock::now();
			gameSound->musicStart = true;

		}


		CheckCollision();
	}
}

void Framework::CheckCollision()
{
	
	if(pLight->position.x - pLight->GetWidth() <= mapInfo.leftPos  )
	{
		pLight->position.x = mapInfo.leftPos + pLight->GetWidth();
	}
	if(pLight->position.x + pLight->GetWidth() >= mapInfo.rightPos)
	{
		pLight->position.x = mapInfo.rightPos - pLight->GetWidth();
		
	}
	if(pLight->position.y - pLight->GetHeight()<= mapInfo.downPos)
	{
		pLight->position.y = mapInfo.downPos + pLight->GetHeight();
		
	}
	if(pLight->position.y + pLight->GetHeight()>= mapInfo.upPos)
	{
		pLight->position.y = mapInfo.upPos - pLight->GetHeight();
		
	}


}
void Framework::Draw()
{
	timer.Tick(0.0f);

	

	Reshape(fWindowWidth, fWindowHeight);

	Update();

	switch (gameState)
	{
	case GAME_STATE::INGAME:
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST);

		glUseProgram(shaderProgram[0]);
		DrawLeftWall();
		DrawRightWall();
		DrawFloor();
		//DrawCeiling();

		if (pCamera) {

			if (pLight)
			{
				pCamera->Update(shaderProgram[0], fWindowWidth, fWindowHeight);

				SetTexture();
				if (pSnow)
				{
					for (int i = 0; i < snowCount; ++i)
					{
						if (snowStop == false)
							pSnow[i]->MoveDown(timer.GetTimeElapsed());
						pSnow[i]->Draw(shaderProgram[0]);
					}
				}
				glBindTexture(GL_TEXTURE_2D, 0);

				pLight->Draw(shaderProgram[0]);


				pCamera->Update(shaderProgram[1], fWindowWidth, fWindowHeight);


			}

		}


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		glUseProgram(shaderProgram[2]);



		if (pWallManager)
		{
			if (pLight)
			{
				if (gameSound->musicStart)
				{
					pWallManager->Update(timer.GetTimeElapsed(), pLight, gameSound);
					pWallManager->Draw(timer.GetTimeElapsed(), shaderProgram[2]);
				}
			}
		}

		if (pCamera)
		{
			pCamera->Update(shaderProgram[2], fWindowWidth, fWindowHeight);
			if (pLight)
				pLight->Draw(shaderProgram[2]);
		}
		//셰이더 프로그램 사용 중지
		glUseProgram(0);
		if (uiManager)
		{
			uiManager->Modify("HIT : ", std::string("HIT : ") + std::to_string(hitCount));
			uiManager->Modify("COMBO : ", std::string("COMBO : ") + std::to_string(combo));
			uiManager->Draw();
		}

		glUseProgram(shaderProgram[3]);
		if (screenEffect)
		{
			screenEffect->Draw(shaderProgram[3]);
		}
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		break;
	}
	case GAME_STATE::INTRO:
	{
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glUseProgram(shaderProgram[3]);
		if (screenEffect)
		{
			screenEffect->Draw(shaderProgram[3]);
		}

		break;
	}
	default:
		std::cout << "정의되지 않은 GameState입니다" << std::endl;
		break;
	}

	//셰이더 프로그램 사용 중지
	glUseProgram(0);
	


	


}

bool Framework::CheckProgram(GLuint program)
{
	GLint state;
	glGetProgramiv(program, GL_LINK_STATUS, &state);
	if (GL_FALSE == state) {
		int infologLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infologLength);
		if (infologLength > 1){
			int charsWritten = 0;
			char *infoLog = new char[infologLength];
			glGetProgramInfoLog(program, infologLength, &charsWritten, infoLog);
			std::cout << infoLog << std::endl;
			delete[] infoLog;
		}
		return false;
	}
	return true;
}

GLuint Framework::CreateShader(GLenum shaderType, const std::string& source)
{
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0)
		return 0;

	// set shader source
	const char* raw_str = source.c_str();
	glShaderSource(shader, 1, &raw_str, NULL);

	// compile shader object
	glCompileShader(shader);

	// check compilation error
	if (!CheckProgram(shader)){
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

const std::string Framework::ReadStringFromFile(const std::string& filename) {
	std::ifstream f(filename);

	if (!f.is_open())
		return "";

	return std::string(std::istreambuf_iterator<char>(f),
		std::istreambuf_iterator<char>());
}

void Framework::CreateSnow()
{
	std::uniform_real_distribution<double>uxd(-15.0f, 15.0f);
	std::uniform_real_distribution<double>uzd(-15.0f, 15.0f);
	std::uniform_real_distribution<double> uyd(5.0f, 10.0f);
	std::default_random_engine dre((unsigned int)time(0));

	pSnow = new Snow*[100];

	for (int i = 0; i < snowCount; ++i)
	{
		pSnow[i] = new Snow{};


		pSnow[i]->Create();
		
		pSnow[i]->SetPosition(glm::vec3(uxd(dre), uyd(dre), uzd(dre)));
		pSnow[i]->SetSpeed(uyd(dre));
	}

	
}



void Framework::RotateCamera(bool bRot)
{
	if(pCamera)
	{
		pCamera->bRotation = bRot;
	}
}
void Framework::CreateTexture()
{
	glGenSamplers(1, &sampler);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT,16.0f);

	
	stbi_set_flip_vertically_on_load(true); 
	int widthImage, heightImage, numberOfChannel;

	

	//텍스쳐 이름 생성
	glGenTextures(1, &texture1);
	
	//이제 GL_TEXTURE_2D 바인딩 포인트를 사용하여 콘텍스트에 바인딩 한다.
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data = stbi_load("ice4.png", &widthImage, &heightImage, &numberOfChannel,0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	int tLocation_1 = glGetUniformLocation(shaderProgram[0], "texture1"); 
	glUniform1i (tLocation_1, 0); 
}
void Framework::ChangeGameState(bool isStart)
{
	if(isStart)
	{
		gameState = GAME_STATE::INGAME;
		screenEffect->IsGameStart(true);
	}
	else
	{
		gameState = GAME_STATE::INTRO;
		screenEffect->IsGameStart(false);
	}
}
void Framework::SetTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
}
void Framework::CreateCube()
{

	pCube = new Cube*[cubeCount];
	

	if (pCube) 
	{
		for (int i = 0; i < cubeCount; ++i)
		{
			pCube[i] = new Cube{};
			pCube[i]->vCube[0] = UVVertex(glm::vec3(-15.0f, 0.1f, -30.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
			pCube[i]->vCube[1] = UVVertex(glm::vec3(-15.0f, -0.1f, -30.0f), glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
			pCube[i]->vCube[2] = UVVertex(glm::vec3(15.0f, 0.1f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));


			pCube[i]->vCube[3] = UVVertex(glm::vec3(15.0f, 0.1f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));
			pCube[i]->vCube[4] = UVVertex(glm::vec3(-15.0f, -0.1f, -30.0f), glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
			pCube[i]->vCube[5] = UVVertex(glm::vec3(15.0f, -0.1f, -30.0f), glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f));

			//left
			pCube[i]->vCube[6] = UVVertex(glm::vec3(-15.0f, 0.1f, -30.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));
			pCube[i]->vCube[7] = UVVertex(glm::vec3(-15.0f, 0.1f, 0.0f), glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pCube[i]->vCube[8] = UVVertex(glm::vec3(-15.0f, -0.1f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f));


			pCube[i]->vCube[9] = UVVertex(glm::vec3(-15.0f, 0.1f, -30.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));
			pCube[i]->vCube[10] = UVVertex(glm::vec3(-15.0f, -0.1f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f));
			pCube[i]->vCube[11] = UVVertex(glm::vec3(-15.0f, -0.1f, -30.0f), glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f));

			//back
			pCube[i]->vCube[12] = UVVertex(glm::vec3(-15.0f, 0.1f, 0.0f), glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f));
			pCube[i]->vCube[13] = UVVertex(glm::vec3(15.0f, 0.1f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pCube[i]->vCube[14] = UVVertex(glm::vec3(-15.0f, -0.1f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f));


			pCube[i]->vCube[15] = UVVertex(glm::vec3(15.0f, 0.1f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pCube[i]->vCube[16] = UVVertex(glm::vec3(15.0f, -0.1f, 0.0f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f));
			pCube[i]->vCube[17] = UVVertex(glm::vec3(-15.0f, -0.1f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f));

			//right
			pCube[i]->vCube[18] = UVVertex(glm::vec3(15.0f, 0.1f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f));
			pCube[i]->vCube[19] = UVVertex(glm::vec3(15.0f, 0.1f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
			pCube[i]->vCube[20] = UVVertex(glm::vec3(15.0f, -0.1f, 0.0f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f));


			pCube[i]->vCube[21] = UVVertex(glm::vec3(15.0f, 0.1f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
			pCube[i]->vCube[22] = UVVertex(glm::vec3(15.0f, -0.1f, -30.0f), glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
			pCube[i]->vCube[23] = UVVertex(glm::vec3(15.0f, -0.1f, 0.0f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f));

			//top
			pCube[i]->vCube[24] = UVVertex(glm::vec3(15.0f, 0.1f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f));
			pCube[i]->vCube[25] = UVVertex(glm::vec3(-15.0f, 0.1f, 0.0f), glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pCube[i]->vCube[26] = UVVertex(glm::vec3(-15.0f, 0.1f, -30.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));


			pCube[i]->vCube[27] = UVVertex(glm::vec3(15.0f, 0.1f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f));
			pCube[i]->vCube[28] = UVVertex(glm::vec3(-15.0f, 0.1f, -30.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
			pCube[i]->vCube[29] = UVVertex(glm::vec3(15.0f, 0.1f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f));

			//bottom
			pCube[i]->vCube[30] = UVVertex(glm::vec3(-15.0f, -0.1f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 1.0f));
			pCube[i]->vCube[31] = UVVertex(glm::vec3(15.0f, -0.1f, 0.0f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pCube[i]->vCube[32] = UVVertex(glm::vec3(15.0f, -0.1f, -30.0f), glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f));


			pCube[i]->vCube[33] = UVVertex(glm::vec3(-15.0f, -0.1f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pCube[i]->vCube[34] = UVVertex(glm::vec3(15.0f, -0.1f, -30.0f), glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
			pCube[i]->vCube[35] = UVVertex(glm::vec3(-15.0f, -0.1f, -30.0f), glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f));


			glGenBuffers(1, &pCube[i]->vertexBufferObject);

			glBindBuffer(GL_ARRAY_BUFFER, pCube[i]->vertexBufferObject);
			glBufferData(GL_ARRAY_BUFFER, pCube[i]->vCube.size() * sizeof(UVVertex), &pCube[i]->vCube, GL_STATIC_DRAW);

			pCube[i]->CreateTexture(shaderProgram[0],"ice4.png");
			//pCube[i]->Create(shaderProgram[0]);
			pCube[i]->SetPosition(glm::vec3(0.0f, 0.0f, (-30.0f*i)));
			mapInfo.downPos = 0.2f;
		}


	}


}
void Framework::CreateCeiling()
{

	pCeiling = new Cube*[cubeCount];
	

	if (pCeiling) 
	{
		for (int i = 0; i < cubeCount; ++i)
		{
			pCeiling[i] = new Cube{};
			pCeiling[i]->vCube[0] = UVVertex(glm::vec3(-15.0f, 10.2f, -30.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
			pCeiling[i]->vCube[1] = UVVertex(glm::vec3(-15.0f, 10.0f, -30.0f), glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
			pCeiling[i]->vCube[2] = UVVertex(glm::vec3(15.0f, 10.2f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));


			pCeiling[i]->vCube[3] = UVVertex(glm::vec3(15.0f, 10.2f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));
			pCeiling[i]->vCube[4] = UVVertex(glm::vec3(-15.0f,10.0f, -30.0f), glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
			pCeiling[i]->vCube[5] = UVVertex(glm::vec3(15.0f, 10.0f, -30.0f), glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f));

			//left
			pCeiling[i]->vCube[6] = UVVertex(glm::vec3(-15.0f, 10.2f, -30.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));
			pCeiling[i]->vCube[7] = UVVertex(glm::vec3(-15.0f, 10.2f, 0.0f), glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pCeiling[i]->vCube[8] = UVVertex(glm::vec3(-15.0f, 10.0f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f));


			pCeiling[i]->vCube[9] = UVVertex(glm::vec3(-15.0f, 10.2f, -30.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));
			pCeiling[i]->vCube[10] = UVVertex(glm::vec3(-15.0f,10.0f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f));
			pCeiling[i]->vCube[11] = UVVertex(glm::vec3(-15.0f,10.0f, -30.0f), glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f));

			//back
			pCeiling[i]->vCube[12] = UVVertex(glm::vec3(-15.0f,10.2f, 0.0f), glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f));
			pCeiling[i]->vCube[13] = UVVertex(glm::vec3(15.0f, 10.2f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pCeiling[i]->vCube[14] = UVVertex(glm::vec3(-15.0f,10.0f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f));


			pCeiling[i]->vCube[15] = UVVertex(glm::vec3(15.0f,10.2f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pCeiling[i]->vCube[16] = UVVertex(glm::vec3(15.0f,10.0f, 0.0f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f));
			pCeiling[i]->vCube[17] = UVVertex(glm::vec3(-15.0f,10.2f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f));

			//right
			pCeiling[i]->vCube[18] = UVVertex(glm::vec3(15.0f, 10.2f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f));
			pCeiling[i]->vCube[19] = UVVertex(glm::vec3(15.0f, 10.2f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
			pCeiling[i]->vCube[20] = UVVertex(glm::vec3(15.0f, 10.0f, 0.0f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f));


			pCeiling[i]->vCube[21] = UVVertex(glm::vec3(15.0f, 10.2f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
			pCeiling[i]->vCube[22] = UVVertex(glm::vec3(15.0f, 10.0f, -30.0f), glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
			pCeiling[i]->vCube[23] = UVVertex(glm::vec3(15.0f, 10.0f, 0.0f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f));

			//top
			pCeiling[i]->vCube[24] = UVVertex(glm::vec3(15.0f, 10.2f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f));
			pCeiling[i]->vCube[25] = UVVertex(glm::vec3(-15.0f,10.2f, 0.0f), glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pCeiling[i]->vCube[26] = UVVertex(glm::vec3(-15.0f,10.2f, -30.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));


			pCeiling[i]->vCube[27] = UVVertex(glm::vec3(15.0f, 10.2f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f));
			pCeiling[i]->vCube[28] = UVVertex(glm::vec3(-15.0f,10.2f, -30.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
			pCeiling[i]->vCube[29] = UVVertex(glm::vec3(15.0f, 10.2f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f));

			//bottom
			pCeiling[i]->vCube[30] = UVVertex(glm::vec3(-15.0f,10.0f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 1.0f));
			pCeiling[i]->vCube[31] = UVVertex(glm::vec3(15.0f, 10.0f, 0.0f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pCeiling[i]->vCube[32] = UVVertex(glm::vec3(15.0f, 10.0f, -30.0f), glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f));


			pCeiling[i]->vCube[33] = UVVertex(glm::vec3(-15.0f,10.0f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pCeiling[i]->vCube[34] = UVVertex(glm::vec3(15.0f, 10.0f, -30.0f), glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
			pCeiling[i]->vCube[35] = UVVertex(glm::vec3(-15.0f,10.0f, -30.0f), glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f));


			glGenBuffers(1, &pCeiling[i]->vertexBufferObject);

			glBindBuffer(GL_ARRAY_BUFFER, pCeiling[i]->vertexBufferObject);
			glBufferData(GL_ARRAY_BUFFER, pCeiling[i]->vCube.size() * sizeof(UVVertex), &pCeiling[i]->vCube, GL_STATIC_DRAW);

			pCeiling[i]->CreateTexture(shaderProgram[0],"ice4.png");
			//pCube[i]->Create(shaderProgram[0]);
			pCeiling[i]->SetPosition(glm::vec3(0.0f, 0.0f, (-30.0f*i)));
			
		}


	}


}

void Framework::CreateRightCube()
{
	pRightCube = new Cube*[cubeCount];
	

	if (pRightCube) 
	{
		for (int i = 0; i < cubeCount; ++i)
		{
			pRightCube[i] = new Cube{};
			pRightCube[i]->vCube[0] = UVVertex(glm::vec3(-1.0f, 10.0f, -30.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
			pRightCube[i]->vCube[1] = UVVertex(glm::vec3(-1.0f, -0.1f, -30.0f), glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
			pRightCube[i]->vCube[2] = UVVertex(glm::vec3(1.0f, 10.0f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));


			pRightCube[i]->vCube[3] = UVVertex(glm::vec3(1.0f, 10.0f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));
			pRightCube[i]->vCube[4] = UVVertex(glm::vec3(-1.0f, -0.1f, -30.0f), glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
			pRightCube[i]->vCube[5] = UVVertex(glm::vec3(1.0f, -0.1f, -30.0f), glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f));

			//left
			pRightCube[i]->vCube[6] = UVVertex(glm::vec3(-1.0f, 10.0f, -30.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));
			pRightCube[i]->vCube[7] = UVVertex(glm::vec3(-1.0f, 10.0f, 0.0f), glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pRightCube[i]->vCube[8] = UVVertex(glm::vec3(-1.0f, -0.1f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f));


			pRightCube[i]->vCube[9] = UVVertex(glm::vec3(-1.0f, 10.0f, -30.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));
			pRightCube[i]->vCube[10] = UVVertex(glm::vec3(-1.0f, -0.1f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f));
			pRightCube[i]->vCube[11] = UVVertex(glm::vec3(-1.0f, -0.1f, -30.0f), glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f));

			//back
			pRightCube[i]->vCube[12] = UVVertex(glm::vec3(-1.0f, 10.0f, 0.0f), glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f));
			pRightCube[i]->vCube[13] = UVVertex(glm::vec3(1.0f, 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pRightCube[i]->vCube[14] = UVVertex(glm::vec3(-1.0f, -0.1f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f));


			pRightCube[i]->vCube[15] = UVVertex(glm::vec3(1.0f, 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pRightCube[i]->vCube[16] = UVVertex(glm::vec3(1.0f, -0.1f, 0.0f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f));
			pRightCube[i]->vCube[17] = UVVertex(glm::vec3(-1.0f, -0.1f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f));

			//right
			pRightCube[i]->vCube[18] = UVVertex(glm::vec3(1.0f, 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f));
			pRightCube[i]->vCube[19] = UVVertex(glm::vec3(1.0f, 10.0f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
			pRightCube[i]->vCube[20] = UVVertex(glm::vec3(1.0f, -0.1f, 0.0f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f));


			pRightCube[i]->vCube[21] = UVVertex(glm::vec3(1.0f, 10.0f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
			pRightCube[i]->vCube[22] = UVVertex(glm::vec3(1.0f, -0.1f, -30.0f), glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
			pRightCube[i]->vCube[23] = UVVertex(glm::vec3(1.0f, -0.1f, 0.0f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f));

			//top
			pRightCube[i]->vCube[24] = UVVertex(glm::vec3(1.0f, 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f));
			pRightCube[i]->vCube[25] = UVVertex(glm::vec3(-1.0f, 10.0f, 0.0f), glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pRightCube[i]->vCube[26] = UVVertex(glm::vec3(-1.0f, 10.0f, -30.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));


			pRightCube[i]->vCube[27] = UVVertex(glm::vec3(1.0f, 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f));
			pRightCube[i]->vCube[28] = UVVertex(glm::vec3(-1.0f, 10.0f, -30.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
			pRightCube[i]->vCube[29] = UVVertex(glm::vec3(1.0f, 10.0f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f));

			//bottom
			pRightCube[i]->vCube[30] = UVVertex(glm::vec3(-1.0f, -0.1f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 1.0f));
			pRightCube[i]->vCube[31] = UVVertex(glm::vec3(1.0f, -0.1f, 0.0f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pRightCube[i]->vCube[32] = UVVertex(glm::vec3(1.0f, -0.1f, -30.0f), glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f));


			pRightCube[i]->vCube[33] = UVVertex(glm::vec3(-1.0f, -0.1f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pRightCube[i]->vCube[34] = UVVertex(glm::vec3(1.0f, -0.1f, -30.0f), glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
			pRightCube[i]->vCube[35] = UVVertex(glm::vec3(-1.0f, -0.1f, -30.0f), glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f));


			glGenBuffers(1, &pRightCube[i]->vertexBufferObject);

			glBindBuffer(GL_ARRAY_BUFFER, pRightCube[i]->vertexBufferObject);
			glBufferData(GL_ARRAY_BUFFER, pRightCube[i]->vCube.size() * sizeof(UVVertex), &pRightCube[i]->vCube, GL_STATIC_DRAW);

			pRightCube[i]->CreateTexture(shaderProgram[0],"ice4.png");
			//pCube[i]->Create(shaderProgram[0]);
			pRightCube[i]->SetPosition(glm::vec3(15.0f, 0.0f, (-30.0f * i)));
			mapInfo.rightPos = 14.0f;
		}


	}
}


void Framework::CreateLeftCube()
{
	pLeftCube = new Cube*[cubeCount];
	

	if (pLeftCube) 
	{
		for (int i = 0; i < cubeCount; ++i)
		{
			pLeftCube[i] = new Cube{};
			pLeftCube[i]->vCube[0] = UVVertex(glm::vec3(-1.0f, 10.0f, -30.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
			pLeftCube[i]->vCube[1] = UVVertex(glm::vec3(-1.0f, -0.1f, -30.0f), glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
			pLeftCube[i]->vCube[2] = UVVertex(glm::vec3(1.0f, 10.0f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));


			pLeftCube[i]->vCube[3] = UVVertex(glm::vec3(1.0f, 10.0f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));
			pLeftCube[i]->vCube[4] = UVVertex(glm::vec3(-1.0f, -0.1f, -30.0f), glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
			pLeftCube[i]->vCube[5] = UVVertex(glm::vec3(1.0f, -0.1f, -30.0f), glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f));

			//left
			pLeftCube[i]->vCube[6] = UVVertex(glm::vec3(-1.0f, 10.0f, -30.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));
			pLeftCube[i]->vCube[7] = UVVertex(glm::vec3(-1.0f, 10.0f, 0.0f), glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pLeftCube[i]->vCube[8] = UVVertex(glm::vec3(-1.0f, -0.1f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f));


			pLeftCube[i]->vCube[9] = UVVertex(glm::vec3(-1.0f, 10.0f, -30.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));
			pLeftCube[i]->vCube[10] = UVVertex(glm::vec3(-1.0f, -0.1f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f));
			pLeftCube[i]->vCube[11] = UVVertex(glm::vec3(-1.0f, -0.1f, -30.0f), glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f));

			//back
			pLeftCube[i]->vCube[12] = UVVertex(glm::vec3(-1.0f, 10.0f, 0.0f), glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f));
			pLeftCube[i]->vCube[13] = UVVertex(glm::vec3(1.0f, 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pLeftCube[i]->vCube[14] = UVVertex(glm::vec3(-1.0f, -0.1f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f));


			pLeftCube[i]->vCube[15] = UVVertex(glm::vec3(1.0f, 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pLeftCube[i]->vCube[16] = UVVertex(glm::vec3(1.0f, -0.1f, 0.0f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f));
			pLeftCube[i]->vCube[17] = UVVertex(glm::vec3(-1.0f, -0.1f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f));

			//right
			pLeftCube[i]->vCube[18] = UVVertex(glm::vec3(1.0f, 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f));
			pLeftCube[i]->vCube[19] = UVVertex(glm::vec3(1.0f, 10.0f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
			pLeftCube[i]->vCube[20] = UVVertex(glm::vec3(1.0f, -0.1f, 0.0f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f));


			pLeftCube[i]->vCube[21] = UVVertex(glm::vec3(1.0f, 10.0f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
			pLeftCube[i]->vCube[22] = UVVertex(glm::vec3(1.0f, -0.1f, -30.0f), glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
			pLeftCube[i]->vCube[23] = UVVertex(glm::vec3(1.0f, -0.1f, 0.0f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f));

			//top
			pLeftCube[i]->vCube[24] = UVVertex(glm::vec3(1.0f, 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f));
			pLeftCube[i]->vCube[25] = UVVertex(glm::vec3(-1.0f, 10.0f, 0.0f), glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pLeftCube[i]->vCube[26] = UVVertex(glm::vec3(-1.0f, 10.0f, -30.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));


			pLeftCube[i]->vCube[27] = UVVertex(glm::vec3(1.0f, 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f));
			pLeftCube[i]->vCube[28] = UVVertex(glm::vec3(-1.0f,10.0f, -30.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
			pLeftCube[i]->vCube[29] = UVVertex(glm::vec3(1.0f, 10.0f, -30.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f));

			//bottom
			pLeftCube[i]->vCube[30] = UVVertex(glm::vec3(-1.0f, -0.1f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 1.0f));
			pLeftCube[i]->vCube[31] = UVVertex(glm::vec3(1.0f, -0.1f, 0.0f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pLeftCube[i]->vCube[32] = UVVertex(glm::vec3(1.0f, -0.1f, -30.0f), glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f));


			pLeftCube[i]->vCube[33] = UVVertex(glm::vec3(-1.0f, -0.1f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 1.0f));
			pLeftCube[i]->vCube[34] = UVVertex(glm::vec3(1.0f, -0.1f, -30.0f), glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
			pLeftCube[i]->vCube[35] = UVVertex(glm::vec3(-1.0f, -0.1f, -30.0f), glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f));


			glGenBuffers(1, &pLeftCube[i]->vertexBufferObject);

			glBindBuffer(GL_ARRAY_BUFFER, pLeftCube[i]->vertexBufferObject);
			glBufferData(GL_ARRAY_BUFFER, pLeftCube[i]->vCube.size() * sizeof(UVVertex), &pLeftCube[i]->vCube, GL_STATIC_DRAW);

			pLeftCube[i]->CreateTexture(shaderProgram[0],"ice4.png");
			//pCube[i]->Create(shaderProgram[0]);
			
			pLeftCube[i]->SetPosition(glm::vec3(-15.0f, 0.0f, (-30.0f * i)));
			mapInfo.leftPos = -14.0f;
		}


	}
}


GLvoid Framework::Reshape(int w,int h)
{

	glViewport(0, 0, w , h);
	//glOrtho(0.0, (float)w, (float)h, 0.0, -1.0, 1.0);
}
