#include "../stdafx.h"
#include "gun.h"

void gun::initBullet()
{
	isMove = true;
	crabOpen = 0;

	this->clock2_bullet.restart();
	this->bulletCurrentFrame = sf::IntRect(0, 0, 30, 30);

}

void gun::initGunShape()
{
	this->clock1_gun.restart();
	this->gunCurrentFrame = sf::IntRect(0, 0, 30, 30);
	this->gunbackground.setSize(sf::Vector2f(BASE_SIZE, BASE_SIZE));
	this->gunbackground.setFillColor(sf::Color(0, 0, 0, 180));
	this->gunbackground.setPosition(GunPosition);
}

void gun::initSprite()
{
	this->bulletShape.setPosition(GunPosition);
	this->bulletShape.setTexture(m_assets.get_texture(asset_holder::group_member_name::GANESH, asset_holder::ganesh_textures::BULLET));
	this->bulletShape.setTextureRect(bulletCurrentFrame);
	this->bulletShape.setScale(BASE_SIZE/30.f,BASE_SIZE/30.f);
	//this->bulletShape.setOrigin(bulletShape.getGlobalBounds().width/ 2.f, bulletShape.getGlobalBounds().height/2.f);

	
	this->gunShape.setTexture(m_assets.get_texture(asset_holder::group_member_name::GANESH, asset_holder::ganesh_textures::GUN_CRAB));
	this->gunShape.setTextureRect(gunCurrentFrame);
	//this->gunShape.setOrigin(BASE_SIZE / 2.f, BASE_SIZE / 2.f);
	this->gunShape.setScale(BASE_SIZE / 30.f, BASE_SIZE / 30.f);

	switch (dir)
	{
	case gun::direction::Left:
		this->gunShape.setRotation(270.f);
		this->gunShape.setPosition(GunPosition+sf::Vector2f(0.f,BASE_SIZE));
		this->bulletShape.setRotation(90.f);
		this->bulletShape.setPosition(GunPosition+sf::Vector2f(BASE_SIZE,0.f));
		break;
	case gun::direction::Down:
		this->gunShape.setRotation(180.f);
		this->gunShape.setPosition(GunPosition + sf::Vector2f(BASE_SIZE, BASE_SIZE));
		this->bulletShape.setPosition(GunPosition);
		break;
	case gun::direction::Up:
		this->gunShape.setPosition(GunPosition);
		this->bulletShape.setRotation(180.f);
		this->bulletShape.setPosition(GunPosition + sf::Vector2f(BASE_SIZE, BASE_SIZE));
		break;
	case gun::direction::Right:
		this->gunShape.setRotation(90.f);
		this->gunShape.setPosition(GunPosition + sf::Vector2f(BASE_SIZE, 0.f) );
		this->bulletShape.setRotation(270.f);
		this->bulletShape.setPosition(GunPosition + sf::Vector2f(0.f, BASE_SIZE));
		break;
	default:
		break;
	}
}

void gun::initDirection()
{
	if (TargetPosition.x > GunPosition.x)
		dir = direction::Right;
	else if (TargetPosition.x < GunPosition.x)
		dir = direction::Left;

	if (TargetPosition.y > GunPosition.y)
		dir = direction::Down;
	else if (TargetPosition.y < GunPosition.y)
		dir = direction::Up;
}

void gun::Animation(float dt)
{
	if (this->clock1_gun.getElapsedTime().asSeconds() >= 0.2f)
	{

		switch (crabOpen)
		{
		case 0:
			this->gunCurrentFrame.left = 0;
			break;
		case 1:
			this->gunCurrentFrame.left += 30;
			if (this->gunCurrentFrame.left >= 60)
				crabOpen = -1;
			break;
		case -1:
			this->gunCurrentFrame.left -= 30;
			if (this->gunCurrentFrame.left <= 0)
				crabOpen = 0;
			break;
		default:
			break;
		}

		this->clock1_gun.restart();
		this->gunShape.setTextureRect(this->gunCurrentFrame);
	}

	if (this->clock2_bullet.getElapsedTime().asSeconds() >= 0.2f)
	{
		if (this->bulletCurrentFrame.left == 0 && this->bulletCurrentFrame.top == 0)
			this->bulletCurrentFrame.left += 30;
		else if (this->bulletCurrentFrame.left == 30 && this->bulletCurrentFrame.top == 0)
			this->bulletCurrentFrame.top += 30;
		else if (this->bulletCurrentFrame.left == 30 && this->bulletCurrentFrame.top == 30)
			this->bulletCurrentFrame.left -= 30;
		else if (this->bulletCurrentFrame.left == 0 && this->bulletCurrentFrame.top == 30)
			this->bulletCurrentFrame.top -= 30;

		this->clock2_bullet.restart();
		this->bulletShape.setTextureRect(this->bulletCurrentFrame);
	}

}

gun::gun(sf::Vector2u GunPosition, sf::Vector2u TargetPosition,asset_holder* assets):m_assets(*assets)
{
	this->Type = Obstacle::obstacle_type::Gun;
	this->GunPosition.x = BASE_SIZE * GunPosition.x;
	this->GunPosition.y = BASE_SIZE * GunPosition.y;
	this->TargetPosition.x = BASE_SIZE * TargetPosition.x;
	this->TargetPosition.y = BASE_SIZE * TargetPosition.y;
	this->counter = 0;

	initGunShape();
	initDirection();
	initBullet();
	initSprite();

}

gun::~gun()
{

}

void gun::setGunPosition(sf::Vector2f GunPosition)
{
	this->GunPosition.x = BASE_SIZE * GunPosition.x;
	this->GunPosition.y = BASE_SIZE * GunPosition.y;
	gunShape.setPosition(GunPosition);
}

void gun::setTargetPosition(sf::Vector2f TargetPosition)
{
	this->TargetPosition.x = BASE_SIZE * TargetPosition.x;
	this->TargetPosition.y = BASE_SIZE * TargetPosition.y;
	initBullet();
}

void gun::update(const float dt)
{
	this->Animation(dt);
	//check erase

	switch (dir)
	{
	case direction::Right:
		if (bulletShape.getGlobalBounds().left+bulletShape.getGlobalBounds().width >= TargetPosition.x+(BASE_SIZE/4.f))
		{
			this->bulletShape.setPosition(GunPosition + sf::Vector2f(0.f, BASE_SIZE ));
			m_assets.play_sound(asset_holder::group_member_name::GANESH, asset_holder::ganesh_sounds::FIRE_END, 10.f);
			isMove = false;
		}
		break;
	case direction::Left:
		if (bulletShape.getGlobalBounds().left <= TargetPosition.x-(BASE_SIZE/4.f))
		{
			this->bulletShape.setPosition(GunPosition + sf::Vector2f(BASE_SIZE, 0.f));
			m_assets.play_sound(asset_holder::group_member_name::GANESH, asset_holder::ganesh_sounds::FIRE_END, 10.f);
			isMove = false;
		}
		break;
	case direction::Down:
		if (bulletShape.getGlobalBounds().top+bulletShape.getGlobalBounds().height >= TargetPosition.y+(BASE_SIZE/4.f))
		{
			this->bulletShape.setPosition(GunPosition);
			m_assets.play_sound(asset_holder::group_member_name::GANESH, asset_holder::ganesh_sounds::FIRE_END, 10.f);
			isMove = false;
		}
		break;
	case direction::Up:
		if (bulletShape.getGlobalBounds().top <= TargetPosition.y-(BASE_SIZE/4.f))
		{
			this->bulletShape.setPosition(GunPosition + sf::Vector2f(BASE_SIZE, BASE_SIZE));
			m_assets.play_sound(asset_holder::group_member_name::GANESH, asset_holder::ganesh_sounds::FIRE_END, 10.f);
			isMove = false;
		}
		break;

	}

	//update new bullets

	float dist = fabs((TargetPosition.x - GunPosition.x + TargetPosition.y - GunPosition.y + 300.f)/300.f);
	
	
	if (counter < 2*dist )
		counter+=dt;
	if (counter >= 2*dist )
	{
		m_assets.play_sound(asset_holder::group_member_name::GANESH, asset_holder::ganesh_sounds::FIRE_START, 10.f);
		counter = 0;
		isMove = true;
		crabOpen = 1;
	}
	

	// move

	
	float speed = 200.f; // 5.f at frame rate 60
	if (isMove)
	{
		switch (dir)
		{
		case direction::Right:
			bulletShape.move(dt * speed, 0.f);
			break;
		case direction::Left:
			bulletShape.move(-speed * dt, 0.f);
			break;
		case direction::Down:
			bulletShape.move(0.f, dt * speed);
			break;
		case direction::Up:
			bulletShape.move(0.f, -dt * speed);
			break;
		}
	}

}

void gun::render(sf::RenderTarget* window)
{
	window->draw(gunbackground);
	window->draw(bulletShape);
	window->draw(gunShape);

}

const sf::Vector2f gun::getGunPosition()
{
	return sf::Vector2f(gunShape.getPosition());
}

const sf::Vector2f gun::getTargetPosition()
{
	return sf::Vector2f(TargetPosition);
}

const bool gun::isCollide(const sf::FloatRect &shape)
{
	if (bulletShape.getGlobalBounds().intersects(shape))
		return true;
	
	return false;
}

void gun::read(std::ifstream & fin, Data &data, size_t & size)
{
	unsigned temp_var1, temp_var2, temp_var3, temp_var4;

	for (size_t i = 0; i < size; i++)
	{
		fin >> temp_var1 >> temp_var2;
		fin >> temp_var3 >> temp_var4;

		data.gun_arg.push_back(std::pair< sf::Vector2u, sf::Vector2u >(sf::Vector2u(temp_var1, temp_var2), sf::Vector2u(temp_var3, temp_var4)));
	}


}
