#pragma once


constexpr int uiCount = 1;
class UI;
class UIManager
{
public:
	UIManager();
	~UIManager();


	void AddUI(void* font,const std::string& text,const float& x,const float& y);
	void Modify(const std::string& s,const std::string& newText);
	void Draw();
private:
	std::map<const std::string,UI> uiArray;

};

class UI
{
public:
	UI();
	UI(unsigned char font,const std::string& s,const float& px,const float& py);
	virtual ~UI();

	void Create(void* fontStyle, const std::string& text,const float& x,const float& y);
	void Modify(const std::string& newText);
	void Draw() const;

private:
	std::string text;
	unsigned char fontStyle;
	float xPos{0.0f};
	float yPos{0.0f};



};
