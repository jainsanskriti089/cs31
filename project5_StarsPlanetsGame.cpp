#pragma warning(disable : 6262)
#define _CRT_SECURE_NO_WARNINGS
#include "utilities.h"
#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;

const int MAXGUESSLEN = 100;
const int MAXWORDS = 8000;
const char WORDFILENAME[] = "smallwords.txt";
// Windows users:  Use / instead of \ for pathname separators.

int runOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum);
bool countStarsPlanets(const char word[], const char guess[], int& stars, int& planets);
bool isInArray(const char words[][MAXWORDLEN + 1], int nWords, char guess[]);
bool validTrialWord(char guess[]);

/*void testRound(const char words[][MAXWORDLEN + 1]) {
    assert(runOneRound(words, 0, 0) == -1);  //zero words in word list and word position is same as number of words
    assert(runOneRound(words, 5, 6) == -1);  //word position is larger than number of words
    assert(runOneRound(words, -1, 0) == -1); //negative words in word list
    assert(runOneRound(words, 7, 7) == -1);  //>0 words in word list and word position is same as number of words
    
    cerr << "tested runOneRound successfully" << endl;
}*/

int main()
{
    char wordList[MAXWORDS][MAXWORDLEN + 1];
    int numWords = getWords(wordList, MAXWORDS, WORDFILENAME);
    //testRound(wordList);

    /* check on getWords implementation
    if (numWords == 2)
    {
        cerr << "getWords successfully found the file and read its two words." << endl;
        cerr << "You're ready to start working on Project 5." << endl;
    }
    else if (numWords == -1)
        cerr << "The path to your file of words is probably incorrect" << endl;
    else {
        cerr << "getWords found the file, but loaded " << numWords << " words instead of 2" << endl;
        return 0;
    }*/

    //checks whether words were loaded in + terminates programs otherwise
    if (numWords < 1) {
        cout << "No words were loaded, so I can't play the game." << endl;
        return 0;
    }

    //start the game
    int numRounds;
    cout << "How many rounds do you want to play? ";
    cin >> numRounds;
    cin.ignore(10000, '\n');

    if (numRounds < 1) {
        cout << "The number of rounds must be positive." << endl;
        return 0;
    }

    int sumGuesses = 0;
    int min = 0;
    int max = 0;

    for (int i = 1; i <= numRounds; i++) {
        cout << "\nRound " << i << endl;

        //choose a random word
        int randWordPos = randInt(0, numWords - 1);
        cout << "The secret word is " << strlen(wordList[randWordPos]) << " letters long." << endl;
        cerr << "secret word: " << wordList[randWordPos] << endl;

        //play round
        int roundStatus = runOneRound(wordList, numWords, randWordPos);

        if (roundStatus == -1) {
            cout << "This round has invalid conditions." << endl;
            return 0;
        }

        //update/print success message + statistics
        if (i == 1 || roundStatus < min) min = roundStatus; //updates the minimum number of guesses (sets it to the number of guesses in the first round)
        if (i == 1 || roundStatus > max) max = roundStatus; //updates the maximum number of guesses (sets it to the number of guesses in the first round)
        sumGuesses += roundStatus; //tallies the total number of guesses (used to find the average)
        
        cout << "You got it in " << roundStatus;
        if (roundStatus == 1) cout << " try." << endl;
        else cout << " tries." << endl;
        
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << "Average: " << static_cast<double>(sumGuesses) / i << ", minimum: " << min << ", maximum: " << max << endl;
    }

}

int runOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum) {
    if (nWords <= 0 || wordnum < 0 || wordnum >= nWords) return -1;
    
    char guess[MAXGUESSLEN];
    int guesses = 0;
    bool correct = false;

    //loop until the user guesses the secret word
    for (;!correct;) {
        cout << "Trial word: ";
        //store the user's guess
        cin.getline(guess, MAXGUESSLEN);
        //for debugging: cerr << guess << endl;

        //checks if the guess satisfies all conditions
        if (!validTrialWord(guess)) {
            cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
        }
        else if (!isInArray(words, nWords, guess)) {
            cout << "I don't know that word." << endl;
        }
        //compares the guess to the secret word and informs the user of any stars and planets
        else {
            //set stars/planets to 0 for the new guess
            int stars = 0;
            int planets = 0;
            correct = countStarsPlanets(words[wordnum], guess, stars, planets);
            if (!correct) cout << "Stars: " << stars << ", Planets: " << planets << endl;
            guesses++;
        }
    }
    return guesses;
}

bool countStarsPlanets(const char word[], const char guess[], int& stars, int& planets) {
    char secretUsed[MAXWORDLEN + 1]; //keeps track of stars (1) and planet (2) pairings
    char guessUsed[MAXGUESSLEN + 1]; 
    strcpy(secretUsed, word);
    strcpy(guessUsed, guess);

    //find the shorter word length
    int min = strlen(word);
    if (min > strlen(guess)) {
        min = strlen(guess);
    }

    //count stars (only goes up to the end of the shorter word to avoid going out of bounds
    for (int i = 0; i < min; i++) {
        //checks whether the letters of the secret word and guess match at the same index
        if (word[i] == guess[i]) {
            secretUsed[i] = '1';
            guessUsed[i] = '1';
            stars++;
        }
    }
    
    //count planets
    for (int k = 0; k < strlen(guess); k++) {
        if (guessUsed[k] == '1') continue;
        bool planetFound = false;
        //compare the current letter of the guess to each letter in the secret word
        for (int j = 0; j < strlen(word) && !planetFound; j++) {
            //checks whether the letter of the secret word is already involved in another pairing and if the letters match
            if (isalpha(secretUsed[j]) && guessUsed[k] == secretUsed[j]) {
                secretUsed[j] = '2';
                guessUsed[k] = '2';
                planets++;
                //a match (planet pairing) was found
                planetFound = true;
            }
        }
    }
    return stars == strlen(word);
}

bool isInArray(const char words[][MAXWORDLEN + 1], int nWords, char guess[]) {
    //checks whether the guess is a word found in the array of cstrings (words)
    for (int i = 0; i < nWords; i++) {
        if (strcmp(words[i], guess) == 0) return true;
    }
    return false;
}

bool validTrialWord(char guess[]) {
    int length = strlen(guess);
    //checks if the length of the guess is between 4 to 6 letters (inclusive)
    if (length < MINWORDLEN || length > MAXWORDLEN) {
        return false;
    }
    //checks if all letters in guess are lowercase letters
    for (int i = 0; i < length; i++) {
        if (isupper(guess[i]) || !isalpha(guess[i])) {
            return false;
        }
    }
    return true;
}