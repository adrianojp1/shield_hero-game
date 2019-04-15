#pragma once

//======================================================================================================================================//
// === Timer Class === //
class Timer
{
	bool _ticking; // = not paused
	bool _zeroed;  // true when the time ends

	// ========= Time control ========= //
	float _totalTime; //Time for which it will be reseted
	float _currentTime;

public:
	//================================================================//
	// ========== Constructors ========== //
	Timer(float totalTime);
	Timer();
	// ========== Destructors ========== //
	~Timer();

	//================================================================//
	// ========== Loop methods ========== //
	void decreaseTime(float deltaTime);

	//================================================================//
	// ========== Time control methods ========== //
	bool isTicking() const;
	bool isZeroed() const;
	void resetTimer();
	void pause();
	void trigger();
	void reset_and_trigger();

	//================================================================//
	// ========== Sets & Gets ========== //
	//_totalTime
	void setTotalTime(float totalTime);
	float getTotalTime() const;
	//_currentTime
	float getCurrentTime() const;
};