#include "gameround.h"

GameRound::GameRound() {}

int points;
std::string secretWord;

int GameRound::getPoints()
{
    return points;
}
void GameRound::setPoints(int newPoints)
{
    points = newPoints;
}

std::string GameRound::getSecretWord()
{
    return secretWord;
}
void GameRound::setSecretWord(std::string newSecretWord)
{
    secretWord = newSecretWord;
}

void GameRound::reducePoints()
{
    points--;
}
