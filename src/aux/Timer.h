/*
 * Timer.h
 *
 *  Created on: 14.01.2013
 *      Author: Christian Staudt (christian.staudt@kit.edu)
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <chrono>
#include <sstream>

namespace Aux {



class Timer {

protected:

	bool running;			//!< true if timer has been started and not stopped after that
	std::chrono::steady_clock::time_point started;	//!< time at which timer has been started
	std::chrono::steady_clock::time_point stopped;		//!< time at which timer has been stopped

public:

	Timer();

	virtual ~Timer();

	/**
	 * Start the clock.
        Returns the time at which the instance was started.
	 */
	virtual std::chrono::steady_clock::time_point start();

	/**
	 * Stops the clock permanently for the instance of the Timer.
        Returns the time at which the instance was stopped.
	 */
	virtual std::chrono::steady_clock::time_point stop();

	/**
	 * The number of seconds since the current time that the Timer
        object was created.  If stop() was called, it is the number
        of seconds from the instance creation until stop() was called.
	 */
	virtual std::chrono::duration<int64_t, std::milli> elapsed();

	/**
	 * Returns the time at which the instance was started.
	 */
	virtual std::chrono::steady_clock::time_point startTime();

	/**
	 * Returns the time at which the instance was stopped.
	 *
	 */
	virtual std::chrono::steady_clock::time_point stopTime();


	/**
	 *
	 */
	virtual std::string elapsedTag();
};

} /* namespace Aux */
#endif /* TIMER_H_ */
