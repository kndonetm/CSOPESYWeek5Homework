#include "ThreadedMarquee.h"

#include <iostream>
#include <conio.h>

#include "PrintUtil.h"

// fix name conflict
#undef max

void ThreadedMarquee::drawMarquee(HANDLE handle) {
	std::string clear = std::string(this->msg.length(), ' ');

	while (running) {
		// clear the old marquee
		PrintUtil::printAt(handle, x, 3 + y, clear);

		// update x, y according to their velocity
		x += dx;
		y += dy;

		// check if they hit the wall
		if (x == screenWidth - msg.length()) {
			// reverse velocity
			dx = -1;
		}
		else if (x == 0) {
			dx = 1;
		}

		if (y == screenHeight - 1) {
			dy = -1;
		}
		else if (y == 0) {
			dy = 1;
		}

		// draw the updated marquee
		ioLock.acquire();
		PrintUtil::printAt(handle, x, 3 + y, msg);
		ioLock.release();

		// sleep
		Sleep(refreshDelay);
	}
}

ThreadedMarquee::ThreadedMarquee(std::string msg, int screenWidth, int screenHeight)
	: msg(msg), screenWidth(screenWidth), screenHeight(screenHeight)
{

}

void ThreadedMarquee::run()
{
	HANDLE handle = GetStdHandle((DWORD) -11);
	
	system("cls");
	WriteConsoleA(handle, this->header.c_str(), (DWORD) this->header.length(), nullptr, nullptr);

	PrintUtil::printAt(handle, 0, 3 + screenHeight, "Enter a command for MARQUEE_CONSOLE: " + this->cmd + "\n" + this->output);

	marqueeThread = std::thread(&ThreadedMarquee::drawMarquee, this, handle);
	marqueeThread.detach();

	while (running) {

		pollingCounter = (pollingCounter + 1) % pollingRate;

		if (_kbhit() && pollingCounter == 0) {
			ioLock.acquire();
			
			char c = _getch();

			if (c == '\r') {
				if (this->cmd == "exit") {
					this->running = false;
				}
				else {
					this->output.append("Command processed in MARQUEE_CONSOLE: " + this->cmd + "\n");
					this->cmd = "";
				}
			}
			else if (c == 8) {
				// if user pressed backspace
				this->cmd = this->cmd.substr(0, this->cmd.length() - 1);
			}
			else {
				this->cmd.append(std::string(1, c));
			}

			system("cls");
			SetConsoleCursorPosition(handle, { 0, 0 });
			WriteConsoleA(handle, this->header.c_str(), (DWORD) this->header.length(), nullptr, nullptr);
			PrintUtil::printAt(handle, 0, 3 + screenHeight, "Enter a command for MARQUEE_CONSOLE: " + this->cmd + "\n" + this->output);

			ioLock.release();
		}
	}
}
