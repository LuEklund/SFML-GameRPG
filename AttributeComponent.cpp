#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(unsigned level)
{
	this->level = level;
	exp = 0;
	expNext = 0;
	attributePoints = 3;

	vitality = 1;
	strength = 1;
	dexterity = 1;
	agility = 1;
	intelligence = 1;

	updateStats();
}

AttributeComponent::~AttributeComponent()
{
}

// functions
void AttributeComponent::calculateExpNext()
{
}

void AttributeComponent::updateStats()
{
}

void AttributeComponent::levelUp()
{
}

void AttributeComponent::update()
{
}
