#include "PrintUtil.h"

void PrintUtil::printAt(HANDLE handle, SHORT x, SHORT y, std::string text)
{
    // get current cursor location
    CONSOLE_SCREEN_BUFFER_INFO screenInfo;
    GetConsoleScreenBufferInfo(handle, &screenInfo);
    COORD currentConsolePosition = screenInfo.dwCursorPosition;

    // SetConsoleCursorPosition expects x, y coords to be in a COORD struct
    // Line/column numbers are 1-indexed, so convert
    COORD newConsolePosition = COORD();
    newConsolePosition.X = x;
    newConsolePosition.Y = y;

    SetConsoleCursorPosition(handle, newConsolePosition);
    WriteConsoleA(handle, text.c_str(), text.length(), nullptr, nullptr);

    // Return to original console position
    SetConsoleCursorPosition(handle, currentConsolePosition);
}
