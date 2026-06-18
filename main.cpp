#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "src/lexer.h"

using namespace std;

// Reads entire file into a single string
string readFile(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        cout << "Could not open file: " << path << "\n";
        exit(1);
    }
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

int main(int argc, char* argv[]) {

    // Default to test_cases/sample.cpp if no argument given
    string filepath = "test_cases/sample.cpp";
    if (argc >= 2) {
        filepath = argv[1];
    }

    cout << "\n";
    cout << "=======================================\n";
    cout << "        AlgoDoctor v1.0\n";
    cout << "=======================================\n";
    cout << "File: " << filepath << "\n\n";

    // Step 1: Read the file
    string source = readFile(filepath);
    cout << "File opened successfully!\n\n";

    // Step 2: Tokenize
    Lexer lexer(source);
    vector<Token> tokens = lexer.tokenize();

    // Step 3: Count constructs from tokens (not raw string search!)
    int forCount   = 0;
    int whileCount = 0;
    int ifCount    = 0;
    int elseCount  = 0;
    for (const Token& tok : tokens) {
        if (tok.type == TokenType::FOR)   forCount++;
        if (tok.type == TokenType::WHILE) whileCount++;
        if (tok.type == TokenType::IF)    ifCount++;
        if (tok.type == TokenType::ELSE)  elseCount++;
    }

    // Step 4: Print results
    cout << "---------------------------------------\n";
    cout << "  Constructs Found:\n";
    cout << "---------------------------------------\n";
    cout << "  for   loops  : " << forCount   << "\n";
    cout << "  while loops  : " << whileCount << "\n";
    cout << "  if statements: " << ifCount    << "\n";
    cout << "  else statements: "<< elseCount << "\n";
    cout << "---------------------------------------\n";
    cout << "  Total tokens : " << tokens.size() - 1 << "\n";
    cout << "=======================================\n\n";

    return 0;
}