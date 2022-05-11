#include <iostream>
#include <sstream>
#include <string.h>

#include "IntentRecognizer.h"

#define MAX_WORDS_SUPPORTED 10

void printHelp()
{
    std::stringstream ss;
    ss << "Usage: IntentRecognizer [--help | -h] <your message here>\n";
    ss << "       @remark: message should not exceed " 
        << MAX_WORDS_SUPPORTED << " word(s)";
    std::cout << ss.str() << "\n";
}

int main(int argc, char** pArgv)
{
    std::string sentence;
    std::string intent;

    if (argc == 1) {
        std::cerr << "No message provided ! \n";
        printHelp();
        return -1;
    }

    if (argc > MAX_WORDS_SUPPORTED) {
        std::cerr << "Message has more than " << MAX_WORDS_SUPPORTED << " words \n";
        printHelp();
        return -1;
    }

    if ((strncasecmp(pArgv[1], "--help", sizeof("--help")) == 0) || 
        (strncasecmp(pArgv[1], "-h", sizeof("-h")) == 0)) {
        printHelp();
        return 0;
    }

    for (auto i = 1; i < argc; i++) {
        sentence += pArgv[i];
        if (i != argc - 1) {
            sentence += " ";
        }
    }

    IntentRecognizer ir;
    ir.recognizeIntent(sentence, intent);
    std::cout << sentence << " => (Intent: " << intent << ")\n";
    return 0;
}
