#ifndef ANIMATIONCOMPONENT_H
# define ANIMATIONCOMPONENT_H

# include <iostream>
# include <map>

# include "SFML/Graphics.hpp"

class AnimationComponent
{
private:
	class Animation
	{
		public:
		//variables
		sf::Sprite	&sprite;
		sf::Texture &textureSheet;
		float		animationTimer;
		float		timer;
		bool		done;
		int			width;
		int			height;
		sf::IntRect	startRect;
		sf::IntRect	currRect;
		sf::IntRect	endRect;

		Animation(sf::Sprite &sprite, sf::Texture &textureSheet,
			float animationTimer,
			int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
			:	sprite(sprite), textureSheet(textureSheet),
				animationTimer(animationTimer), timer(0.f), done(false),
				width(width), height(height)
		{
			timer = 0.f;
			startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
			currRect = startRect;
			endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

			sprite.setTexture(textureSheet, true);
			sprite.setTextureRect(startRect);
		};
		~Animation(){};

		//Accessor
		const bool &isDone() const
		{
			return (done);
		}

		//functions
		const bool	&play(const float &dt)
		{
			done = false;
			timer += 100.f * dt;
			if (timer >= animationTimer)
			{
				//reset timer
				timer = 0.f;

				//animate
				if (currRect != endRect)
				{
					currRect.left += width;
				}
				else //Reset
				{
					currRect.left = startRect.left;
					done = true;
				}
				sprite.setTextureRect(currRect);
			}	
			return (done);
		};
		const bool	&play(const float &dt, float mod_percent)
		{
			done = false;

			if (mod_percent < 0.5f)
					mod_percent = 0.5f;

			timer += mod_percent * 100.f * dt;
			if (timer >= animationTimer)
			{
				//reset timer
				timer = 0.f;

				//animate
				if (currRect != endRect)
				{
					currRect.left += width;
				}
				else //Reset
				{
					currRect.left = startRect.left;
					done = true;
				}
				sprite.setTextureRect(currRect);
			}	
			return (done);
		};
		void	reset()
		{
			timer = animationTimer;
			currRect = startRect;
		};
	};

	sf::Sprite 							&spriteCom;
	sf::Texture 						&textureSheetCom;
	std::map<std::string, Animation*>	animations;
	Animation 							*lastAnimation;
	Animation 							*priorityAnimation;
	
public:
	AnimationComponent(sf::Sprite &sprite, sf::Texture &textureSheet);
	~AnimationComponent();

	//Accessor
	const bool &isDone(const std::string key) ;

	//Functions
	void	addAniamtion(const std::string key,
				float animationTimer,
				int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

	const bool	&play(const std::string key, const float &dt, const bool priority = false);
	const bool	&play(const std::string key, const float &dt, const float &modifier, const float &modifier_max, const bool priority = false);
};

#endif
