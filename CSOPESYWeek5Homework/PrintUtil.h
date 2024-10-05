#pragma once

#include <string>

#include <Windows.h>

class PrintUtil
{
public:
    static void printAt(
        HANDLE handle,
        SHORT line,
        SHORT column,
        std::string text
    );
};

