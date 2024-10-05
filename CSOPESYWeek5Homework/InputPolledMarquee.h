#pragma once

#include <string>

class InputPolledMarquee
{
private:
	std::string msg;
	int screenWidth;
	int screenHeight;

	std::string cmd;
	std::string output;

	// location of message text
	int x = 0;
	int y = 0;

	// Velocity of message text. Positive=right/down, negative=left/up
	int dx = 1;
	int dy = 1;

	bool running = true;

	// refresh delay in milliseconds, polling rate in frames per poll
	int refreshDelay = 0;
	int pollingRate = 1;
	int pollingCounter = 0;

	std::string header =
		"**********************************************\n"
		"* Displaying a Marquee Console! *\n"
		"**********************************************\n"
		;

	void process();

public:
	InputPolledMarquee(std::string msg, int screenWidth, int screenHeight);
	void run();
};