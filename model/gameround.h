#ifndef GAMEROUND_H
#define GAMEROUND_H
#include <string>

class GameRound
{
public:
    GameRound();

    int getPoints();
    void setPoints(int newPoints);

    std::string getSecretWord();
    void setSecretWord(std::string newSecretWord);

    void reducePoints();
};

#endif // GAMEROUND_H
