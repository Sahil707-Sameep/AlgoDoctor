#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) 
        {
            cout << i << " is even\n";
        } 
        else 
        {
            cout << i << " is odd\n";
        }
    }
    while(n > 0) 
    {
        n--;
    }
    return 0;
}
