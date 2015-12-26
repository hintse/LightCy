#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>

/* class representing messages to be shown on the screen */
class Message {
	public:
		/* render the message on the screen */
		void show(float width, float height) const;
		
		/* set the current message and the timeout value */
		void write(std::string message, float timeout);
		
		/* clears the current message and timeout */
		void clear();
		
		/* update the current message timeout and clear if
		   message has timed out */
		void update(float dt);

	private:
		/* the message to be shown */
		std::string message_;
		
		/* timeout in seconds for the message */
		float timeout_;
};

#endif
