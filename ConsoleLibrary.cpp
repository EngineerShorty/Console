/*
======================
EXAMPLE: Hi-Lo Guessing Game
======================

This example demonstrates the use of the console library to play the hi-lo guessing game.

*/
#include "Console.h"
#include <string>
#include <random>
#include <ctime>
#include <algorithm>

using namespace Con;
using std::string;

int main() {
    console.titleSet("Guessing Game v1.1");
    //console.debugOn();
    srand(static_cast<unsigned>(time(0)));


    console.println("Welcome to");

    console.txtUnderlineOn();  console.txtBoldOn();  console.txtSetColor(GREEN);
    console.println("The Guessing Game");
    console.txtUnderlineOff();  console.txtBoldOff();  console.txtSetColor(WHITE);
    console.println("v1.1");
    console.println("by Bryan Shortall");
    console.println();
    
    int numberToGuess = rand() % 101;
    console.printerr(std::to_string(numberToGuess));

    console.println("I'm thinking of a number from 0 to 100.");
    console.println("Try to guess what the number is.");

    bool correctGuess = false;
    int tries = 1;
    while (!correctGuess) {
        console.print("What's your guess? ");
        int guess;
        console.txtSetColor(CYAN);
        console.input(guess);
        console.txtSetColor(WHITE);
        if (guess == numberToGuess) {
            correctGuess = true;
        }
        else {
            tries++;
            if (guess > numberToGuess) {
                console.print("Too high!  Guess again.  ");
            }
            if (guess < numberToGuess) {
                console.print("Too low!  Guess again.  ");
            }
        }
    }

    console.txtBlinkingOn();  console.txtSetColor(YELLOW);
    console.println("\nCongratulations!  You guessed it!");
    console.txtBlinkingOff();  console.txtSetColor(WHITE);
    console.print("The number was: "); console.println(numberToGuess);
    console.print("It took you "); console.print(tries); console.println(" tries to guess it.");
    console.print("\nWould you like to play again? ");

    string playAgain;
    console.input(playAgain);    
    std::transform(playAgain.begin(), playAgain.end(), playAgain.begin(), ::toupper);
    if (playAgain == "Y" || playAgain == "YES") {
        console.screenClear();
        console.printerr("You said yes.");
        console.printerr("You asked to play again.");
        main();        
    }
    else {
        console.println("\nThank you for playing!");
        console.println("Press any key to close.");
        console.getNextChar();
        exit(0);
    }
}


