#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <string>

class GameController
{
public:
    GameController();
    void newGame();
    std::string getOutputWord();
    bool evaluateLetter(std::string guessedLetter);
    int getFoundLettersCount();
    bool checkWordComplete();
    int getScore();
    bool checkGameOver();
    std::string getSecretWord();

private:
    void readFile();
    void selectSecretWord();
    void createOutputWord();
};

#endif // GAMECONTROLLER_H
