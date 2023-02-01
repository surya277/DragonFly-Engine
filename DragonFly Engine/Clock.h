#pragma once

#ifndef __CLOCK_H__
#define __CLOCK_H__


namespace df {

	class Clock
	{
	private:
		long int m_previous_time;
		//long int m_current_time;

	public:
		Clock();

		// Return time elapsed since delta was last called. -1 if error
		// Resets previous time to current time
		long int delta();

		// Return time elapsed since delta was called, -1 if error.
		// Does not reset previous time

		long int split() const;

		static long int computeTime();
	};
}

#endif

