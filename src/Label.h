#pragma once
#ifndef __LABEL__
#define __LABEL__

#include <string>

#include "DisplayObject.h"
#include "FontManager.h"

class Label final : public DisplayObject
{
public:
	explicit Label(const std::string& text = "Default Label Text", const std::string& font_name = "lazy", int size = 20, SDL_Color colour = {0, 0, 0, 255}, glm::vec2 position = glm::vec2(), int font_style = TTF_STYLE_NORMAL, bool is_centered = true);
	~Label();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void setText(const std::string& new_text);
	void setColour(SDL_Color new_colour) const;
	void setSize(int new_size);
	void setBorder(bool b);
	void setBorderColor(SDL_Color c);
	void setFillColor(SDL_Color c);
	int value;
private:
	std::string m_fontPath;
	std::string m_fontID;
	SDL_Color m_fontColour;
	SDL_Color m_borderColour;
	SDL_Color m_fillColour;
	std::string m_fontName;
	std::string m_text;
	bool m_isCentered = true;
	bool m_isBordered = false;
	bool m_isFilled = false;
	int m_fontSize;
	int m_fontStyle;

	void m_buildFontID();
};

#endif /* defined (__LABEL__) */