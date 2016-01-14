#include "Timer.h"

Timer::Timer()
	: previous_time_value_(std::chrono::high_resolution_clock::now())
	, frame_count_(0)
	, previous_fps_(0){ }
	
bool Timer::get_fps(unsigned int& fps)
{
	auto retval = false;
	auto tick = std::chrono::high_resolution_clock::now();
	auto duration = tick - previous_time_value_;
	fps = frame_count_;
	if(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() >= 1000)
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
