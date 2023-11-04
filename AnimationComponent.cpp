
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite &sprite, sf::Texture &textureSheet)
	:	spriteCom(sprite), textureSheetCom(textureSheet), lastAnimation(NULL), priorityAnimation(NULL)
{
}

AnimationComponent::~AnimationComponent()
{
	for (auto &i : animations)
	{
		delete i.second;
	}
}

const bool &AnimationComponent::isDone(const std::string key) 
{
	return (animations[key]->isDone());
}

void AnimationComponent::addAniamtion(const std::string key,
	float animationTimer,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
{

	animations[key] = new Animation(spriteCom, textureSheetCom,
						animationTimer,
						start_frame_x, start_frame_y, frames_x, frames_y, width, height);

}



const bool& AnimationComponent::play(const std::string key, const float & dt, const bool priority)
{
	if (priorityAnimation) //If there is a priority animation
	{
		if (priorityAnimation == animations[key])
		{
			if (lastAnimation != animations[key])
			{
				if (lastAnimation == NULL)
					lastAnimation = animations[key];
				else
				{
					lastAnimation->reset();
					lastAnimation = animations[key];
				}
			}

			//If the priority animation is done, remove it
			if (animations[key]->play(dt))
			{
				priorityAnimation = NULL;
			}
		}
	}
	else //Play animation of no other priority animation is set
	{
		//If this is a priority animation, set it.
		if (priority)
		{
			priorityAnimation = animations[key];
		}

		if (lastAnimation != animations[key])
		{
			if (lastAnimation == NULL)
				lastAnimation = animations[key];
			else
			{
				lastAnimation->reset();
				lastAnimation = animations[key];
			}
		}

		animations[key]->play(dt);
	}

	return animations[key]->isDone();
}

const bool& AnimationComponent::play(const std::string key, const float & dt, const float& modifier, const float& modifier_max, const bool priority)
{
	if (priorityAnimation) //If there is a priority animation
	{
		if (priorityAnimation == animations[key])
		{
			if (lastAnimation != animations[key])
			{
				if (lastAnimation == NULL)
					lastAnimation = animations[key];
				else
				{
					lastAnimation->reset();
					lastAnimation = animations[key];
				}
			}

			//If the priority animation is done, remove it
			if (animations[key]->play(dt, abs(modifier / modifier_max)))
			{
				priorityAnimation = NULL;
			}
		}
	}
	else //Play animation of no other priority animation is set
	{
		//If this is a priority animation, set it.
		if (priority)
		{
			priorityAnimation = animations[key];
		}

		if (lastAnimation != animations[key])
		{
			if (lastAnimation == NULL)
				lastAnimation = animations[key];
			else
			{
				lastAnimation->reset();
				lastAnimation = animations[key];
			}
		}

		animations[key]->play(dt, abs(modifier / modifier_max));
	}

	return animations[key]->isDone();
}