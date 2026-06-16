#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
   ifstream file("test_cases/sample.cpp");

    if (!file.is_open()) {
        cout << "Could not open sample.cpp" << endl;
        return 1;
    }

    cout << "File opened successfully!\n\n";

    string line;
    int forcount=0;
    int whilecount=0;
    int ifcount=0;
    while (getline(file, line)) {
        if (line.find("for") != string::npos) {
            forcount++;
        }
        if (line.find("while") != string::npos) {
            whilecount++;
        }
        if (line.find("if") != string::npos) {
            ifcount++;
        }
    }

    cout << "Number of 'for' loops found: " << forcount << endl;
    cout << "Number of 'while' loops found: " << whilecount << endl;
    cout << "Number of 'if' statements found: " << ifcount << endl;

    file.close();
    return 0;
}
