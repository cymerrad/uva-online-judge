#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

const char *ROUND_N = "Round %d\n";
const char *WIN = "You win.\n";
const char *LOSE = "You lose.\n";
const char *CHICKEN = "You chickened out.\n";
const int FAIL_COUNT = 7;

enum class LetterState : char
{
    YetToBeFound,
    Tried,
};

const char *analyzeGame(const string word, const string guesses)
{
    int fails = 0;
    int distinctLetters = 0;
    int found = 0;
    map<char, LetterState> guessesStates;
    for (char c : word)
    {
        auto effect = guessesStates.emplace(c, LetterState::YetToBeFound);
        if (effect.second)
        {
            distinctLetters++;
        }
    }

    for (char c : guesses)
    {
        if (fails == FAIL_COUNT)
            return LOSE;

        if (found == distinctLetters)
            return WIN;

        auto effect = guessesStates.emplace(c, LetterState::Tried);
        if (effect.second)
        {
            // emplaced => didn't exist in map => bad guess
            fails++;
            continue;
        }
        else
        {
            if (effect.first->second == LetterState::Tried)
            {
                // tried something again => doesn't matter => ignore
                continue;
            }
            else
            {
                // had to be the other option => correct guess
                found++;
                effect.first->second = LetterState::Tried;
                continue;
            }
        }
    }

    if (fails == FAIL_COUNT)
        return LOSE;

    if (found == distinctLetters)
        return WIN;

    return CHICKEN;
}

int main(int argc, char const *argv[])
{
    // #include "../vsdebug.cpp"
    int round;
    string word;
    string guesses;
    while (cin >> round, round > 0)
    {
        cin >> word;
        cin >> guesses;

        printf(ROUND_N, round);
        printf(analyzeGame(word, guesses));
    }

    return 0;
}
