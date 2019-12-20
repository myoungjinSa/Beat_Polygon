#include "stdafx.h"
#include "UI.h"


UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

void UIManager::AddUI(void* font,const std::string& text,const float& x,const float& y)
{

	uiArray.emplace(text,UI{(unsigned char) font,text,x,y });

}
void UIManager::Modify(const std::string& s,const std::string& newText)
{
	auto iter = uiArray.find(s);
 
	if(iter != uiArray.end())
	{
		iter->second.Modify(newText);
	}
}
void UIManager::Draw()
{
	for(const auto& d:uiArray)
	{
		d.second.Draw();
	}
}

UI::UI(unsigned char font,const std::string& s,const float& px,const float& py)
	:fontStyle{font},text{s},xPos{px},yPos{py}
{
	std::cout << "UI 생성자 호출" << std::endl;
}


UI::~UI()
{


}

void UI::Modify(const std::string& newText) 
{
	this->text = newText;
	
}

void UI::Draw() const 
{
	glRasterPos2f(xPos, yPos);
	 int len = text.length();
   for (int i = 0; i < len; i++)
      glutBitmapCharacter((void*)fontStyle, text[i]);
}
void UI::Create(void* fontStyle,const std::string& text,const float& x,const float& y)
{
	this->fontStyle = (unsigned char)fontStyle;
	this->text = text;

	xPos = x;
	yPos = y;
}