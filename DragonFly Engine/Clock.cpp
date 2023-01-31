#include "Clock.h"

#include <Windows.h>


SYSTEMTIME before_st, after_st;

df::Clock::Clock() {
	GetSystemTime(&before_st);
}

long int df::Clock::delta() {
	GetSystemTime(&before_st);
	computeTime();
	long int elapsed_time = m_current_time - m_previous_time;

	m_previous_time = m_current_time;
	return elapsed_time;
}

void df::Clock::computeTime() {
	m_previous_time = (before_st.wDay * 24 * 60 * 60 * 1000000) + (before_st.wHour * 60 * 60 * 1000000) + (before_st.wMinute * 60 * 1000000) + (before_st.wSecond * 1000000) + (before_st.wMilliseconds * 1000);
	
	m_current_time = (after_st.wDay * 24 * 60 * 60 * 1000000) + (after_st.wHour * 60 * 60 * 1000000) + (after_st.wMinute * 60 * 1000000) + (after_st.wSecond * 1000000) + (after_st.wMilliseconds * 1000);
}