/*This is the console executabe, that makes use of BullCow Class.
This acts as the view in a MVC pattern, and is responsible for all user interaction. For game logic see the FBullCowGame class.

*/


#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;
using FText = std::string;
void PrintIntro();
void PlayGame();
void PrintGameSummary();
bool AskToPlayAgain();
FText GetValidGuess();
//FText PrintGuess();
FBullCowGame BCGame;

//the entry point for our game
int32 main()
{
	//std::cout << BCGame.GetMyCurrentTry();
	bool bPlayAgain = false;
	do{
		std::cout << std::endl;
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	return 0; //exits the game
}

void PlayGame()
{
//instantiate a new game
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << "Max Tries " << MaxTries << std::endl;


	//loop asking for guesses while the game
	// is NOT an there are still tries remeaning
	while (!BCGame.IsGameWon() && BCGame.GetMyCurrentTry() <= MaxTries)			//TODO change from FOR to WHILE loop once we are validating tries
	{
		FText Guess = GetValidGuess(); 

		
		//submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
	
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}
	//TODO Summurise game here
	PrintGameSummary();
	return;
}

bool AskToPlayAgain() // asks player to input an answer
{
	std::cout << "Do you want to play again with the same hidden word? y/n ";
	FText Response = "";
	std::getline(std::cin, Response);
	return(Response[0] == 'y') || (Response[0] == 'Y');
}


// introduce the game
void PrintIntro() {
	//FBullCowCount GetHiddenWordLenght();
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLenght() << " letter isogram I'am thinking of?\n";
	std::cout << std::endl;
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() 
{ 	
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player 
		int32 GetCurrentTry = BCGame.GetMyCurrentTry();
		std::cout << "Try " << GetCurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Lenght:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all letters lowercase.\n\n";
			break;
		default:
			//assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); //keep looping until we get no errors
	return Guess;
}

void PrintGameSummary() {


	if (BCGame.IsGameWon() == true)
	{
		std::cout << " YOU WIN! \n\n";
	}
	else if(BCGame.IsGameWon() == false)
	{
		std::cout << "YOU LOSE! \n\n";
	}
	return;
}
//print the guess back
//FText PrintGuess() {
//	std::cout << "Your guess was: " << Guess << std::endl;
//	std::cout << std::endl;
//}