#pragma once

#ifndef __CLOCK_H__
#define __CLOCK_H__


namespace df {

	class Clock
	{
	private:
		long int m_previous_time;
		long int m_current_time;

	public:
		Clock();

		long int delta();

		long int split() const;

		void computeTime();
	};
}

#endif

