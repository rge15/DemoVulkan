#include "Timer.hpp"


Timer::Timer( int p_frameRate ) noexcept
: _refreshTime { 1.f / p_frameRate }
{}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

double
Timer::ellapsedTime() const noexcept
{
	return ( demoClock::now() - _initTime ).count();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void
Timer::reset( int p_frameRate ) noexcept
{
	if( p_frameRate > 0 )
	{
		_refreshTime = 1.f/p_frameRate;
	}
	_initTime = demoClock::now();

	_lastTime = 0.f ;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

double
Timer::ellapsedSeconds() const noexcept
{
	return ( ellapsedTime() / 1000000000.0f );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

double
Timer::deltaTime() const noexcept
{
	return ellapsedSeconds() - _lastTime;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

bool
Timer::update() noexcept
{
	if( deltaTime() >= _refreshTime )
	{
		_lastTime = ellapsedSeconds();
		return true;
	}
	return false;
}
