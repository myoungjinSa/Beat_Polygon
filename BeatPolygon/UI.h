#pragma once


constexpr int uiCount = 1;
class UI;
class UIManager
{
public:
	explicit UIManager();
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
	UI()=delete;
	explicit UI(unsigned char font,const std::string& s,const float& px,const float& py);
	~UI();

	UI(const UI& ref) = delete;
	UI& operator=(const UI& ref) = delete;

	UI(UI&& rval) = default;
	UI& operator=(UI&& rval) = default;

	void Create(void* fontStyle, const std::string& text,const float& x,const float& y);
	void Modify(const std::string& newText);
	void Draw() const;

private:
	
	unsigned char fontStyle;
	std::string text;
	float xPos;
	float yPos;

};
