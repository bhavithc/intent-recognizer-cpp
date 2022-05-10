#include <iostream>
#include "IntentRecognizer.h"

int main(int argc, char** pArgv)
{
    std::string intent;
    IntentRecognizer ir;
    ir.recognizeIntent("What is the weather like today?", intent);
    std::cout << "Intent is : " << intent << "\n";
    return 0;
}
