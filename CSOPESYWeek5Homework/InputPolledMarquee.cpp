#include "InputPolledMarquee.h"

#include <chrono>

#include <Windows.h>
#include <conio.h>

#include "PrintUtil.h"

void InputPolledMarquee::process()
{
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
}

InputPolledMarquee::InputPolledMarquee(std::string msg, int screenWidth, int screenHeight)
	: msg(msg), screenWidth(screenWidth), screenHeight(screenHeight)
{
}

void InputPolledMarquee::run()
{
	HANDLE handle = GetStdHandle(DWORD(-11));

	// loop marquee animation/keyboard polling
	while (this->running) {
		
		system("cls");
		// display marquee header
		WriteConsoleA(handle, this->header.c_str(), this->header.length(), nullptr, nullptr);

		process();

		PrintUtil::printAt(handle, x, 3 + y, msg);

		PrintUtil::printAt(handle, 0, 3 + screenHeight, "Enter a command for MARQUEE_CONSOLE: " + this->cmd + "\n" + this->output);

		// check for i/o
		pollingCounter = (pollingCounter + 1) % pollingRate;

		if (_kbhit() && pollingCounter == 0) {
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
		}

		Sleep(this->refreshDelay);
	}
};