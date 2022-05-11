#include <iostream>
#include <sstream>
#include "IntentRecognizer.h"

#define MAX_WORDS_SUPPORTED 10

void printHelp()
{
    std::stringstream ss;
    ss << "Usage:\n";
    ss << "\tIntentRecognizer <your message here>\n";
    ss << "\t@remark: message should not exceed " << MAX_WORDS_SUPPORTED << " word(s)";
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
