//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Timer.h"

//======================================================================================================================================//
// === Static initializations === //
float* Timer::_pDeltaTime = NULL;

//======================================================================================================================================//
// === Timer Methods === //
Timer::Timer(float totalTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_ticking = false;
	_totalTime = totalTime;
	resetTimer();
}

Timer::Timer()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");

	_ticking = false;
	_totalTime = 0.0f;
	resetTimer();
}

Timer::~Timer()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
}

void Timer::decreaseTime()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	if (_ticking)
	{
		_currentTime -= *_pDeltaTime;
		{
			if (_currentTime < 0)
			{
				_zeroed = true;
				_ticking = false;
			}
		}
	}
} // end decreaseTime

bool Timer::isTicking() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _ticking;
} // end isTicking

bool Timer::isZeroed() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _zeroed;
} // end isZeroed

void Timer::resetTimer()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_currentTime = _totalTime;
	_zeroed = false;
} // end resetTimer

void Timer::pause()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_ticking = false;
} // end pause

void Timer::trigger()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_ticking = true;
} // end trigger

void Timer::reset_and_trigger()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	this->resetTimer();
	this->trigger();
} // end reset_and_trigger

void Timer::zeroTimer()
{
	_zeroed = true;
	setCurrentTime(0.0f);
}

void Timer::setTotalTime(float totalTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_totalTime = totalTime;
} // end setTotalTime

float Timer::getTotalTime() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _totalTime;
} // end getTotalTime

void Timer::setCurrentTime(const float currTime)
{
	_currentTime = currTime;
}

float Timer::getCurrentTime() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _currentTime;
} // end getCurrentTime

void Timer::setpDeltaTime(float* pDT)
{
	_pDeltaTime = pDT;
}

float* Timer::getDeltaTime()
{
	return _pDeltaTime;
}
