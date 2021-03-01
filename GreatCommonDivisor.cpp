#include <iostream>

using namespace std;

// https://math.stackexchange.com/questions/3379695/why-does-the-euclidean-algorithm-for-finding-gcd-work

class FindGreatCommonDivisor {
public:
    int Find(int a, int b) {
        // The logic here is if b < a then b % a == b, which equals to Find(b, a).
        return a == 0 ? b : Find(b % a, a);
    }
};

int main () {
    FindGreatCommonDivisor findGreatCommonDivisor;

    // Test 1:
    cout << findGreatCommonDivisor.Find(7, 2) << endl;

    // Test 2:
    cout << findGreatCommonDivisor.Find(2, 7) << endl;

    // Test 3:
    cout << findGreatCommonDivisor.Find(25, 10) << endl;

    // Test 4:
    cout << findGreatCommonDivisor.Find(10, 25) << endl;
}