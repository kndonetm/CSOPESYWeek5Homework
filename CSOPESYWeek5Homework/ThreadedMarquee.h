#pragma once

#include <string>
#include <thread>
#include <semaphore>

#include <Windows.h>

class ThreadedMarquee
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

	// refresh rate in fps, polling rate in frames per poll
	int refreshDelay = 17;
	int pollingRate = 1;
	int pollingCounter = 0;

	// Marquee worker thread
	std::thread marqueeThread;

	// prevent both threads from outputting to console at once
	std::binary_semaphore ioLock{ 1 };

	std::string header =
		"**********************************************\n"
		"* Displaying a Marquee Console! *\n"
		"**********************************************\n"
		;

	void drawMarquee(HANDLE handle);

public:
	ThreadedMarquee(std::string msg, int screenWidth, int screenHeight);
	void run();
};