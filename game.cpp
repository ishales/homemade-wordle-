//
//  main.cpp
//  project 5
//
//  Created by Isabelle Hales on 11/4/22.
//  Copyright © 2022 CS31. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <cstring>
#include <cctype>
#include "utilities.h"
using namespace std;

const char WORDFILENAME[] = "/Users/isabellehales/Desktop/words.txt";

//check valid word
bool checkValidWord (char guess[], const char words[][7]){
    for (int a = 0; a < 9999; a++){
        if(strcmp(guess, words[a]) == 0){
            return 1;
        }
    }
    return 0;
}


//get user prompt
int getPromptWord (char guess[], int &tries, const char words[][7]) {
    cout << "Probe word: ";
    cin >> guess;
    
    if(strlen(guess) > 7){
        cout << "Your probe word must be a word of 4 to 6 lowercase letters." << endl;
        return -1;
    } else if (checkValidWord(guess, words) == 0) {
        cout << "I don't know that word." << endl;
        return -1;
    } else {
        tries++;
        return 1;
    }
}

//calculate # of golds
void calcGoldsandSilvers(char hiddenword[], char guess[]) {
    int golds = 0;
    int silvers = 0;
    
    for (int i = 0; i < strlen(hiddenword); i++){
        for(int j = 0; j < strlen(guess); j++){
            if(guess[j] == hiddenword[i] && i == j){
                golds++;
            } else if (guess[j] == hiddenword[i] && i != j){
                silvers++;
            }
        }
    }
    
    cout << "Golds: " << golds << ", ";
    cout << "Silvers: " << silvers << endl;
}


//play one round
int playOneRound (const char words[][7], int nWords, int wordnum) {
    int tries = 0;
    char hiddenword[7] = "";
    strcpy(hiddenword, words[wordnum]);
    char guess[100] = "";
    //int totalTries = 0;
    if(nWords < 0){
        return -1;
    }
    
    if(wordnum < 0 || wordnum >= nWords){
        return -1;
    }
    //cout the length of the hidden word
    cout << "The hidden word is " << strlen(words[wordnum]) << " letters long." << endl;
    //cerr << "[debug] hiddenword in playOneRound: " << hiddenword << endl;
    
    //checks if player is correct until they are
    while(strcmp(guess, hiddenword) != 0) {
        strcpy(guess, "");
        if(getPromptWord(guess, tries, words) == 1 && strcmp(guess, hiddenword) != 0){
            calcGoldsandSilvers(hiddenword, guess);
        }
    }
    
    //if(strcmp(guess, hiddenword) == 0){
    //    totalTries += tries;
    //}
    
    return tries;
}

int main() {
    int rounds = 0;
    char wordList[10000][7];
    int nWords = getWords(wordList, 10000, WORDFILENAME);
    double average = 0;
    cout.setf(ios::fixed);
    cout.precision(2);
    int roundScore = 0;
    double totalTries = 0;
    int minTries = 0;
    int maxTries = 0;
    
    //get # of rounds
    cout << "How many rounds would you like to play: ";
    cin >> rounds;
    cout << endl;
    
    //rounds must be positive
    if(rounds < 0){
        cout << "The number of rounds must be positive.";
        return 0;
    }
    
     //play each round
    for(int i = 1; i <= rounds; i++){
        cout << "Round " << i << endl;
        
        roundScore = playOneRound(wordList, nWords, randInt(0,7264));
        cout << "You got it in ";
        cout << roundScore;
        if(roundScore == 1) {
            cout << " try." << endl;
        } else {
            cout << " tries." << endl;
        }
        
        //calc average
        totalTries = totalTries + roundScore;
        average = totalTries / i;
        
        if(i == 1){
            minTries = roundScore;
            maxTries = roundScore;
        }
        //calc min
        if(roundScore < minTries){
            minTries = roundScore;
        }
        
        //calc max
        if(roundScore > maxTries){
            maxTries = roundScore;
        }
        
        
        cout << "Average: " << average << ", minimum: " << minTries << ", maximum: " << maxTries;
        cout << endl << endl;
        
   }
    
    return 0;
}

