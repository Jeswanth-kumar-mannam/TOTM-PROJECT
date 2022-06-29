#ifndef DRAGON_H
#define DRAGON_H

#include "../define.h"
#include "Obstacle.h"
#include "../asset_holder.h"

class Dragon : public Obstacle
{
private:

	float BASE_SIZE = PLAYER_BASE_SIZE;

	asset_holder& m_assets;

	enum direction { Left = -2, Down = -1, Up = 1, Right = 2 }moving_dir;

	float isStuck;
	float counter_sound;

	sf::Clock clock;

	sf::Sprite dragonShape;
	sf::IntRect CurrentFrame;

	sf::Vector2f InitialPosition;
	sf::Vector2f FinalPosition;

	std::pair<direction, sf::Vector2f> dir;

	void initDirection();
	void initVariable();
	void initSprite();

	void update_movement(float mpving_speed, float dt);
	void fly();

public:

	///////////////////////////////////////////////////
	///	
	///	\brief Constructor for constructing objects 
	///	
	///	\param InitialPosition sf::Vector2u initial position of bat
	///	
	///	\param FinalPosition sf::Vector2u final position of bat 
	///	
	///////////////////////////////////////////////////
	Dragon(sf::Vector2u InitialPosition, sf::Vector2u FinalPosition, asset_holder* assets);

	///////////////////////////////////////////////////
	///	
	///	\brief 
	///	
	///	
	///	
	///
	///	
	///////////////////////////////////////////////////
	virtual ~Dragon();

	///////////////////////////////////////////////////
	///	
	///	\brief 
	///	
	///	\param dt float time between frame changing for making frame rate independent
	///	
	/// \note this function will update all the player position automatically including movement and animination
	///	
	///////////////////////////////////////////////////
	void update(float dt);


	///////////////////////////////////////////////////
	///	
	///	\brief draw the dragonShape 
	///	
	///	\param *target Sf::RenderTarget target on which shape has to be drawn
	///	
	///	
	///	
	///////////////////////////////////////////////////
	void render(sf::RenderTarget *target);


	///////////////////////////////////////////////////
	///	
	///	\brief check the collision between dragonShape and paramater
	///	
	///	\param rect sf::FloatRect object with which collision has to be check
	///		
	///	\return true if collide
	/// \return false if not collide
	///		
	///////////////////////////////////////////////////
	const bool isCollide(const sf::FloatRect &rect);

	///////////////////////////////////////////////////
	///	
	///	\brief read the details of dragon from the file
	///	
	///	\param fin std::ifstream& file stream
	///	\param data Data& file stream \file Data.h
	///	\param size size_t& file no of inputs to be taken
	///	
	///	
	///////////////////////////////////////////////////
	static void read(std::ifstream &fin, Data &data, size_t &size);
};


////////////////////////////////////////////////////////////
/// 
/// \class Dragon
///
/// \brief bat/dragon a obstacle flies regularly between two blocks ( initialposition and finalposition )
///
/// 
///
/// Usage Example:
///
/// \code
///
/// Dragon dragon(sf::Vector2f(10U,10U),sf::Vector2f(15U,10U));
///	dragon.update(0.016f); //inside game.update()
///	dragon.render(this->window); //inside game.render()
/// if(dragon.isCollide(player.shape.getglobalound()))
///		//end game
///
/// \endcode
////////////////////////////////////////////////////////////

#endif