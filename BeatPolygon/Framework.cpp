#include "stdafx.h"
#include "Framework.h"
#include "Cube.h"
#include "Camera.h"

Framework::~Framework()
{
	if (pCube)
	{
		delete pCube;
		pCube = nullptr;
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
	CreateCube();
	CreateCamera(glm::vec3{ 0.0f,0.0f,10.0f }, glm::vec3{ 0.0f,0.0f,-1.0f }, glm::vec3{ 0.0f,1.0f,0.0f });

}

bool Framework::InitShader()
{
	glClearColor(1.f, 1.f, 1.f, 1.f);

	glEnable(GL_DEPTH_TEST);

	glDisable(GL_CULL_FACE);
	glFrontFace(GL_CCW);


	std::string vertexShaderSource{};

	vertexShaderSource = ReadStringFromFile("vertexShader.glvs");


	std::string fragShaderSource = ReadStringFromFile("fragment.glfs");

	GLuint vertShaderObj = CreateShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint fragShaderObj = CreateShader(GL_FRAGMENT_SHADER, fragShaderSource);

	//셰이더 프로그램 오브젝트 생성
	shaderProgram = glCreateProgram();


	//셰이더 프로그램에 ㅂ텍스 및 프래그먼트 셰이더 등록
	glAttachShader(shaderProgram, vertShaderObj);
	glAttachShader(shaderProgram, fragShaderObj);

	glBindAttribLocation(shaderProgram, 0, "vPos");
	glBindAttribLocation(shaderProgram, 1, "vColor");


	//셰이더 프로그램과 셰이더 링킹 그리고 확인
	glLinkProgram(shaderProgram);
	if (!CheckProgram(shaderProgram))
	{
		glDeleteProgram(shaderProgram);
		return false;
	}

	//사용된 셰이더 떼어냄
	glDetachShader(shaderProgram, vertShaderObj);
	glDetachShader(shaderProgram, fragShaderObj);


	glDeleteShader(vertShaderObj);
	glDeleteShader(fragShaderObj);



	return true;
}

void Framework::Draw()
{
	Reshape(fWindowWidth, fWindowHeight);
	
	glUseProgram(shaderProgram);
	
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	if(pCube)
		pCube->Draw(shaderProgram);


	glDisable(GL_BLEND);

	
	glEnable(GL_DEPTH_TEST);
	if (pCamera)
		pCamera->Update(shaderProgram,fWindowWidth,fWindowHeight);


	
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


void Framework::CreateCube()
{

	pCube = new Cube{
		Vertex(glm::vec3(-5.0f, 5.0f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f,0.1f)),		//leftTopFront
		Vertex(glm::vec3(-5.0f, -5.0f, 0.5f), glm::vec4(0.0f, 1.0f, 0.0f,0.1f)),		//leftBottomFront
		Vertex(glm::vec3(5.0f, 5.0f, 0.5f), glm::vec4(0.0f, 1.0f, 0.0f,0.1f)),		//rightTopFront
		Vertex(glm::vec3(5.0f, -5.0f, 0.5f), glm::vec4(0.0f, 1.0f, 0.5f,0.1f)),		//rightBottomFront
		Vertex(glm::vec3(-5.0f, -5.0f, -0.5f), glm::vec4(0.0f, 1.0f, 1.0f,0.1f)),	//leftBottomBack
		Vertex(glm::vec3(-5.0f, 5.0f, -0.5f), glm::vec4(1.0f, 0.0f, 1.0f,0.1f)),		//leftTopBack
		Vertex(glm::vec3(5.0f, 5.0f, -0.5f), glm::vec4(0.0f, 1.0f, 0.0f,0.1f)),		//rightTopBack
		Vertex(glm::vec3(5.0f, -5.0f, -0.5f), glm::vec4(1.0f, 1.0f, 0.1f,0.1f))		//rightBottomBack
	};
	
	glGenBuffers(1, &pCube->vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, pCube->vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, pCube->vCount * sizeof(Vertex), &pCube->v0, GL_STATIC_DRAW);

		


	//front
	pCube->Indices[0] = 0;
	pCube->Indices[1] = 1;
	pCube->Indices[2] = 2;
	
	pCube->Indices[3] = 2;
	pCube->Indices[4] = 1;
	pCube->Indices[5] = 3;
	
	pCube->Indices[6] = 0;
	pCube->Indices[7] = 5;
	pCube->Indices[8] = 4;
	
	pCube->Indices[9] = 0;
	pCube->Indices[10] = 4;
	pCube->Indices[11] = 1;
	
	pCube->Indices[12] = 5;
	pCube->Indices[13] = 6;
	pCube->Indices[14] = 7;
	

	pCube->Indices[15] = 5;
	pCube->Indices[16] = 7;
	pCube->Indices[17] = 4;
	

	pCube->Indices[18] = 2;
	pCube->Indices[19] = 6;
	pCube->Indices[20] = 7;
	
	pCube->Indices[21] = 2;
	pCube->Indices[22] = 7;
	pCube->Indices[23] = 3;
	
	pCube->Indices[24] = 0;
	pCube->Indices[25] = 2;
	pCube->Indices[26] = 5;
	
	pCube->Indices[27] = 2;
	pCube->Indices[28] = 6;
	pCube->Indices[29] = 5;
	
	pCube->Indices[30] = 1;
	pCube->Indices[31] = 4;
	pCube->Indices[32] = 7;
	
	pCube->Indices[33] = 1;
	pCube->Indices[34] = 7;
	pCube->Indices[35] = 3;
	

	glGenBuffers(1, &pCube->elementBufferObject);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pCube->elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * pCube->indexCount, &pCube->Indices[0], GL_STATIC_DRAW);

	
}


GLvoid Framework::Reshape(int w,int h)
{

	glViewport(0, 0, w , h);
	//glOrtho(0.0, (float)w, (float)h, 0.0, -1.0, 1.0);
}
