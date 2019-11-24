#include "stdafx.h"
#include "Framework.h"

Framework::~Framework()
{
	
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
	


	glUseProgram(shaderProgram);

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

GLvoid Framework::Reshape(int w,int h)
{

	glViewport(0, 0, w , h);
	//glOrtho(0.0, (float)w, (float)h, 0.0, -1.0, 1.0);
}
