#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include "scanner/scanner.h"

using namespace std;

void run(string fileContent) {
    // std::cout << fileContent;
    Scanner scanner(fileContent);
    vector<Token> tokens = scanner.scanTokens();

    for (Token token : tokens) {
        cout << token.toString() << endl;
    }
}

void runFile(string filename) {
    ifstream inputFile(filename);

    if (!inputFile) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        exit(1); // Exit if the file cannot be opened
    }

    std::stringstream buffer;
    buffer << inputFile.rdbuf(); // Read the entire file into the buffer

    // Get the content of the buffer as a string
    std::string fileContent = buffer.str();
    // std::cout << fileContent << std::endl; // Output the entire file content

    run(fileContent);

    inputFile.close();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        // run an interactrive propmt
        cout << "Interactive prompt mode not supported yet." << endl;
    }
}
