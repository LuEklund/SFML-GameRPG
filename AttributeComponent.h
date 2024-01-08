#ifndef ATTRIBUTECOMPONENT_H
# define ATTRIBUTECOMPONENT_H
class AttributeComponent
{
private:
	
public:
	//Leveling
	unsigned level;
	unsigned exp;
	unsigned expNext;
	unsigned attributePoints;

	//Attributes
	unsigned vitality;
	unsigned strength;
	unsigned dexterity;
	unsigned agility;
	unsigned intelligence;

	//Stats
	int 	hp;
	int 	hpMax;
	int 	damageMin;
	int 	damageMax;
	int 	accuracy;
	int 	defence;
	int 	luck;

	//Constructor / Destructor
	AttributeComponent(unsigned level);
	~AttributeComponent();

	//functions
	void	calculateExpNext();
	void	updateStats();
	void	levelUp();
	void	update();
};

#endif

