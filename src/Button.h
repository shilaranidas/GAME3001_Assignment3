#pragma once
#ifndef __BUTTON__
#define __BUTTON__

#include "DisplayObject.h"
#include <SDL.h>
#include "Event.h"
#include <unordered_map>

class Button : public DisplayObject
{
public:
	explicit Button(const std::string& image_path = "../Assets/textures/StartButton.png", 
	                std::string button_name = "startButton", 
	                GameObjectType type = START_BUTTON, 
	                glm::vec2 position = glm::vec2(0.0f, 0.0f), bool is_centered = true);
	
	~Button();

	void draw() override;
	void update() override;
	void clean() override;
	
	// setters
	void setMousePosition(glm::vec2 mouse_position);
	void setMouseButtonClicked(bool clicked);

	void handleMouseEvents(SDL_Event* event);

	typedef void(*EventHandler)(Button*);
	bool addEventListener(Event event, EventHandler handler);

	EventHandler getEventHandler(Event event);

	void setAlpha(Uint8 alpha);
	void setActive(bool value);
	
private:
	Uint8 m_alpha;
	std::string m_name;
	bool m_isCentered;
	bool m_active;

	bool m_mouseOver;
	bool m_mouseOverActive;
	bool m_mouseOutActive;
	glm::vec2 m_mousePosition;

	std::unordered_map<Event, EventHandler> m_events;

	bool m_eventExists(Event id);
	bool m_mouseButtonClicked{};
	
};

#endif /* defined (__BUTTON__) */