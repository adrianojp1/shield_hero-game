#pragma once

//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === Classes Headers === //
#include "Animator.h"

//======================================================================================================================================//
// === Player Class === //
class Player
{
private:
	// ========= Visual Members ========= //
	//Player animators
	Animator* _idle_anmt;
	Animator* _walk_anmt;
	
	sf::Sprite _sprite; //Sprite for textures setting
	bool _facingRight; //Bool for the side direction
	
	// ========= Motion Members ========= //
	float _speed; //Horizontal speed
	float _jumpHeight;

public:
	//Constr
	Player(sf::Vector2f initPosition, float speed, float jumpHeight);
	Player();
	//Destr
	~Player();

	void initializeAnimators();

	void execute(float deltaTime);
	void draw(sf::RenderWindow& window);

private:
	// ========== Control keys methods ========== //
	bool leftIsKeyPressed();
	bool rightIsKeyPressed();
	bool jumpKeyPressed();
	bool defendKeyPressed();

	// ========== Movement methods ========== //
	void moveToLeft(float* HorizontalMovement, float offset);
	void moveToRight(float* HorizontalMovement, float offset);
	bool isIdle(float HorizontalMovement);
};

