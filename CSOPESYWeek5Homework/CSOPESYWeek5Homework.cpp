#include <iostream>
#include <Windows.h>

#include "InputPolledMarquee.h"
#include "ThreadedMarquee.h"

int main()
{
    std::string marqueeType;
    
    std::cout << "Please select a type of marquee console to display:\n";
    std::cout << "[1] Input Polled\n";
    std::cout << "[2] Threaded\n";

    // get standard output screen width for marquee animation
    CONSOLE_SCREEN_BUFFER_INFO screenInfo;
    GetConsoleScreenBufferInfo(GetStdHandle((DWORD)-11), &screenInfo);

    do {
        std::cin >> marqueeType;
        if (marqueeType == "1") {  
            InputPolledMarquee marquee = InputPolledMarquee("Hello world in marquee!", screenInfo.dwSize.X, 18);
            marquee.run();
        }
        else if (marqueeType == "2") {
            ThreadedMarquee marquee = ThreadedMarquee("Hello world in marquee!", screenInfo.dwSize.X, 18);
            marquee.run();
        } 
    } while (marqueeType != "1" && marqueeType != "2");
}
