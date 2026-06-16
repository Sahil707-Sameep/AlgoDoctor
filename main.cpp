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
    while (getline(file, line)) {
        cout << line << "\n";
    }

    file.close();
    return 0;
}