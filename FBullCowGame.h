#pragma once
#include <string>

using FString = std::string;
using int32 = int;

//all values initialized to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Lenght,
	Not_Word,
	Not_Lowercase
};

class FBullCowGame{
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetMyCurrentTry() const;
	int32 GetHiddenWordLenght() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; 

	void Reset(); // TODO make a more rich return value;
	FBullCowCount SubmitValidGuess(FString);
	//Ignore below!
private:
	//see constructor for initialisation
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	bool bGameIsWon;
};