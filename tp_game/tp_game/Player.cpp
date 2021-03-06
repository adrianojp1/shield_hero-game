//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Player.h"

//======================================================================================================================================//
// === Player methods === //

Player::Player(const sf::Vector2f initPosition) :
	Character(initPosition)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_jumpHeight = 140.0f;
	_speed = 200.f;
	_points = 0;

	_maxHp = 10;
	resetHp();

	_curr_spawnPoint = {initPosition};

	_defCounterUp = false;

	initialize_animator();
	initialize_AllColliders();

	_defCounterTimer.setTotalTime(0.3f);
	_invulnerability.setTotalTime(0.5f);

} // end constr (parameters)

Player::Player() : 
	Character()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1| ");

	_facingRight = true;
	_defCounterUp = false;
	_canJump = true;
	_speed = 0.0f;
	_jumpHeight = 0.0f;
	_points = 0;
	_position = {0.0f, 0.0f};

	_defCounterTimer.setTotalTime(0.3f); //Counter defense time

} // end constr (no parameters)

Player::~Player()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	//Destroy animators
	if (_animator != NULL)
		delete _animator;
} // end destr

void Player::initialize_animator()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_animator = new Animator(static_cast<Entity*>(this));

	*_animator << new Animation(gMng::player_idle_texture, 1, 0.0f, 2);
	*_animator << new Animation(gMng::player_walk_texture, 4, 0.250f, 2);
	*_animator << new Animation(gMng::player_die_texture, 3, 0.500f, 2);
	*_animator << new Animation(gMng::player_def1_texture, 1, 0.0f, 2);
	*_animator << new Animation(gMng::player_def2_texture, 1, 0.0f, 2);
} // end initializeAnimators

void Player::updateAction(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	if (defendKeyPressed())
	{
		_state = COMBAT;
		manageDefenseCounter();
	}
	// Player is not defending
	else
	{
		_state = IDLE;
		_defCounterTimer.resetTimer();

		if (leftIsKeyPressed() || rightIsKeyPressed())
		{
			_state = WALK;
			//Move the player
			if (leftIsKeyPressed()) //Left
				moveToLeft();

			if (rightIsKeyPressed()) //Right
				moveToRight();
		}

		if (jumpKeyPressed() && _canJump) //Jump
		{
			_canJump = false;
			jump();
		}
	}
} // end updateAction

void Player::switchTo_combat()
{
	_current_collider = _combat_collider;
	if (_defCounterUp)
		//Counter defense animation
		_animator->setCurrentAnime(COMBAT + 1); //Def2
	else
		//Normal defense animation
		_animator->setCurrentAnime(COMBAT); //Def1
}

void Player::resetHp()
{
	_hp = 10;
}

void Player::decreaseTimers()
{
	_defCounterTimer.decreaseTime();
	_invulnerability.decreaseTime();
}

void Player::manageDefenseCounter()
{
	if (_defCounterTimer.isTicking())
		_defCounterUp = true;
	else if (_defCounterTimer.isZeroed())
		_defCounterUp = false;
	else
		_defCounterTimer.trigger();
}

void Player::ressurect()
{
	if (_state == DEATH)
	{
		_state = IDLE;
		resetHp();
		_velocity = { 0.0f, 0.0f };
		_facingRight = true;
	}
	
	this->setPosition(_curr_spawnPoint);
}

void Player::doAfterDeath()
{
	ressurect();
}

bool Player::leftIsKeyPressed() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return (sf::Keyboard::isKeyPressed(_leftKey));
} // end leftIsKeyPressed

bool Player::rightIsKeyPressed() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return (sf::Keyboard::isKeyPressed(_rightKey));
} // end rightIsKeyPressed

bool Player::jumpKeyPressed() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return (sf::Keyboard::isKeyPressed(_jumpKey));
} // end jumpKeyPressed

bool Player::anyMoveKeyPressed() const
{
	return (leftIsKeyPressed() || rightIsKeyPressed() || jumpKeyPressed());
}

bool Player::defendKeyPressed() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return (sf::Keyboard::isKeyPressed(_defenseKey));
} // end defendKeyPressed

bool Player::isDefendingInFront(const sf::Vector2f coll_direction) const
{
	if (this->isDefending())
	{
		if (coll_direction.x > 0.0f && _facingRight)
		{
			return true;
		}
		else if (coll_direction.x < 0.0f && !_facingRight)
		{
			return true;
		}
	}
	return false;
}

void Player::setPoints(const int pts)
{
	_points = pts;
}

int Player::getPoints() const
{
	return _points;
}

void Player::add_points(const int pts)
{
	_points += pts;
}

void Player::setJumpKey(const sf::Keyboard::Key jumpkey)
{
	_jumpKey = jumpkey;
}

sf::Keyboard::Key Player::getJumpKey() const
{
	return _jumpKey;
}

void Player::setRightKey(const sf::Keyboard::Key rightKey)
{
	_rightKey = rightKey;
}

sf::Keyboard::Key Player::getRightKey() const
{
	return _rightKey;
}

void Player::setLeftKey(const sf::Keyboard::Key leftKey)
{
	_leftKey = leftKey;
}

sf::Keyboard::Key Player::getLeftKey() const
{
	return _leftKey;
}

void Player::setDefenseKey(const sf::Keyboard::Key defenseKey)
{
	_defenseKey = defenseKey;
}

sf::Keyboard::Key Player::getDefenseKey() const
{
	return _defenseKey;
}

void Player::setCurrSpawnPoint(const sf::Vector2f spawnPoint)
{
	_curr_spawnPoint = spawnPoint;
}

const sf::Vector2f Player::getCurrSpawnPoint() const
{
	return _curr_spawnPoint;
}

void Player::setPlayer1_configs()
{
	this->setDefenseKey(sf::Keyboard::S);
	this->setJumpKey(sf::Keyboard::W);
	this->setLeftKey(sf::Keyboard::A);
	this->setRightKey(sf::Keyboard::D);
}

void Player::setPlayer2_configs()
{
	this->setDefenseKey(sf::Keyboard::K);
	this->setJumpKey(sf::Keyboard::I);
	this->setLeftKey(sf::Keyboard::J);
	this->setRightKey(sf::Keyboard::L);
}

void Player::reset()
{
	resetHp();
	_velocity = { 0.0f, 0.0f };
	_facingRight = true;
	_points = 0;
	this->setPosition(_curr_spawnPoint);
}

bool Player::isDefending() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	if(_state == COMBAT)
		return true;
	return false;
}

bool Player::isCounterUp() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _defCounterUp;
}

bool Player::isDefending_with_Counter() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	if (this->isDefending() && this->isCounterUp())
		return true;

	return false;
}