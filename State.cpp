#include "State.h"

State::State(StateData *state_data)
{
	this->stateData = state_data;
	this->window = state_data->window;
	this->supportedKeys = state_data->supportedKeys;
	this->states = state_data->states;
	this->quit = false;
	this->paused = false;
	this->keytime = 0.f;
	this->keytimeMax = 10.f;
	this->gridSize = state_data->gridSize;
}

State::~State()
{
    
}


//Accessors
const bool &State::getQuit() const
{
	return (quit);
}

const bool State::getKeytime()
{
	if (keytime >= keytimeMax)
	{
		keytime = 0.f;
		return (true);
	}
	return (false);
}

void State::endState()
{
	quit = true;
}

void State::pauseState()
{
	paused = true;
}

void State::unPauseState()
{
	paused = false;
}

void State::updateMousePosition(sf::View *view)
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);

	if (view)
		window->setView(*view);
	
	mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	mousePosGrid = sf::Vector2i(
		static_cast<int>(mousePosView.x) / static_cast<int>(gridSize),
		static_cast<int>(mousePosView.y) / static_cast<int>(gridSize)
		);

	window->setView(window->getDefaultView());
}

void State::updateKeytime(const float &dt)
{
	if (keytime < keytimeMax)
		keytime += 100.f * dt;
}
