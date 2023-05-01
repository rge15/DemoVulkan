#pragma once
#include "chronoTypeAlias.hpp"
#include <utilities/typeAliases.hpp>

struct Timer
{
	public:
		timePoint _initTime = demoClock::now();

		double _refreshTime { 1.f / 60 };

		double _lastTime { 0.f };

	private:
		/**	@brief Constructor for class Timer */
		explicit
		Timer( int p_frameRate = 60 ) noexcept;

		/**	@brief Default destructor for class Timer	*/
		~Timer() = default;


	public:
		static
		Timer& getInstance()
		{
			static Timer timer;
			return timer;
		}


		/**
		 * 	@brief Gives the total ellapsed time in nanoseconds
		 * 
		 * 	@return Nanoseconds ellapsed from the init/reset of the timer
		*/
		double
		ellapsedTime() const noexcept;

		/**
		 * 	@brief Gives the total ellapsed time in seconds
		 * 
		 * 	@return Seconds ellapsed from the init/reset of the timer
		*/
		double
		ellapsedSeconds() const noexcept;

		/**
		 * 	@brief Gives the ellapsed time in seconds from the last rendered frame
		 * 
		 * 	@return Delta time since the last rendered frame
		*/
		double
		deltaTime() const noexcept;
	
		/**
		 * 	@brief Check if it has to render a frame
		 * 
		 * 	@return True if it passed the _refreshTime
		*/
		bool
		update() noexcept;

		/**
		 * 	@brief Resets the timer ans sets a new framerate if wanted
		 * 
		 * 	@param p_framerate New framerate if wanted to be set. If 0 doesn't update.
		*/
		void
		reset( int p_frameRate = 0 ) noexcept;

		/**
		 * @brief Sets the refresh rate manually 
		 * 
		 * @param p_refreshRate New refresh rate to set
		 */
		void
		setManualRefreshRate( double p_refreshRate) noexcept { _refreshTime = p_refreshRate; };
};