#include "Timer.h"
#include <ctime>

Timer::Timer()
	: previous_time_value_(std::time(NULL))
	, frame_count_(0)
	, previous_fps_(0){ }
	
bool Timer::get_fps(unsigned int& fps)
{
	auto retval = false;
	auto tick = std::time(NULL);
	fps = frame_count_;
	if(tick - previous_time_value_ >= 1) //1 second has elapsed
	{
		retval = true;
		previous_fps_ = frame_count_;
		frame_count_ = 0;
		previous_time_value_ = tick;
	}
	frame_count_++;
	return retval;
}

float Timer::get_previous_frame_delta() const
{
	if(previous_fps_ < fps_threshold)
		return 0.0f;
	else
		return 1.0f / static_cast<float>(previous_fps_);
}