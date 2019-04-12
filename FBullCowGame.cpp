#include "FBullCowGame.h"
#include <Map>
#define TMap std::map

using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame() // a constructor for reseting the game
{
	Reset();
}
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries;}
int32 FBullCowGame::GetMyCurrentTry() const { return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLenght() const {return MyHiddenWord.length();}

bool FBullCowGame::IsGameWon() const { return bGameIsWon;}


void FBullCowGame::Reset() //Resets the game altogether
{  
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "entari";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}
// receives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++; 
	FBullCowCount BullCowCount;
	int32 WordLenght = MyHiddenWord.length(); //assuming same length as guess
	//loop through all the letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLenght; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLenght; GChar++) {
			//if they match them
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				//  if they're in the same place
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++;
				}
				// incriment bulls
				  // else
				else
				{
					BullCowCount.Cows++; 
				}
				// incriment cows 
			}
		}
	} 	
	if (BullCowCount.Bulls == WordLenght)
	{
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (! IsIsogram(Guess)) //if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram; //TODO write function
	}
	else if (! IsLowercase(Guess)) //if the guess isn't all lowercase 
	{
		return EGuessStatus::Not_Lowercase; //TODO write function
	}
	else if (Guess.length() != GetHiddenWordLenght())//if the guess length is wrong 
	{
		
		return EGuessStatus::Wrong_Lenght;
	}
	else 	// otherwise
	{
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::IsIsogram(FString Word) const {
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true;	}
	TMap <char, bool> LetterSeen; //setup our map
	for (auto Letter : Word)  // loop through all the letters of the word 
	{
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter]) { // if the letters is in the map
				return false;
			}    // we do NOT have an isogram
			else {  // otherwise
				LetterSeen[Letter] = true;// add the letter to the map as seen 
			}
		}
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (Letter == tolower(Letter)) // if all the letters in the map is lowercase
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}
