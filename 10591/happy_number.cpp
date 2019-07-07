#include <iostream>
#include <fstream>
#include <map>

using namespace std;

const char *ACCEPTED = "Case #%d: %d is a Happy number.\n";
const char *REJECTED = "Case #%d: %d is an Unhappy number.\n";

map<int, bool> happyCache;

void init()
{
    happyCache.emplace(0, false);
    happyCache.emplace(1, true);
}

int sumSquaredDigits(int N)
{
    int sum = 0;
    int digit;
    while (10 <= N)
    {
        digit = N % 10;
        sum += digit * digit;
        N -= digit;
        N /= 10;
    }
    return sum + N * N;
}

bool checkHappinessRecursiveCached(const int N)
{
    auto entry = happyCache.emplace(N, false); // false will break the recursive loop
    if (entry.second == false)
    {
        // not added anything new
        return entry.first->second;
    }

    int reduced = sumSquaredDigits(N);
    bool isHappy = checkHappinessRecursiveCached(reduced);
    entry.first->second = isHappy;

    return isHappy;
}

const char *checkHappiness(const int N)
{
    if (checkHappinessRecursiveCached(N))
    {
        return ACCEPTED;
    }
    return REJECTED;
}

int main(int argc, char const *argv[])
{
    init();

    int cases;
    int N;
    cin >> cases;
    // #include "../vsdebug.cpp"
    for (int i = 1; i <= cases; i++)
    {
        cin >> N;
        printf(checkHappiness(N), i, N);
    }

    return 0;
}