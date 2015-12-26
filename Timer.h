#ifndef TIMER_H
#define TIMER_H

/* class representing a timer */
class Timer
{
	public:
		/* make a timer */
		Timer();
		
		/* gets the fps if available. only call this 
		   function ONCE each frame! */
		bool get_fps(unsigned int& fps);
		
		/* gets the time between frames last second */
		float get_previous_frame_delta() const;

	private:
		/* seconds since epoch last time get_previous_frame_delta
		   was called */
		unsigned int previous_time_value_;
		
		/* frame count */
		unsigned int frame_count_;
		
		/* frames in the previous second */
		unsigned int previous_fps_;
		
		/* threshold fps for us to report a dt > 0
		   in get_previous_frame_delta */
		static constexpr auto fps_threshold = 24;
};

#endif