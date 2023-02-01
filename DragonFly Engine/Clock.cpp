#include "Clock.h"

#include <Windows.h>


namespace df {


	Clock::Clock() {
		m_previous_time = computeTime();
	}
	

	// Return time elapsed since delta was last called. -1 if error
	// Resets previous time to current time
	//
	long int Clock::delta() {

		long int current_time = computeTime();
		long int elapsed_time = current_time - m_previous_time;

		m_previous_time = current_time;
		
		if (elapsed_time >= 0)
			return elapsed_time;

		return -1;
	}

	// Return time elapsed since delta was called, -1 if error.
	// Does not reset previous time
	//
	long int Clock::split() const {
		long int elapsed_time = computeTime() - m_previous_time;
		
		if (elapsed_time >= 0)
			return elapsed_time;

		return -1;
	}


	// Get System Time and Compute time
	// 
	long int Clock::computeTime() {
		//Initialize and get time from system
		SYSTEMTIME current_st;
		GetSystemTime(&current_st);

		//Compute Current time in Microseconds
		long int current_time = (current_st.wDay * 24 * 60 * 60 * 1000000) + (current_st.wHour * 60 * 60 * 1000000) + (current_st.wMinute * 60 * 1000000) + (current_st.wSecond * 1000000) + (current_st.wMilliseconds * 1000);

		return current_time;
	}
}
