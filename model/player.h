#ifndef PLAYER_H
#define PLAYER_H
#include "person.h"

class Player : public Person //ANF5 Vererbung
{
public:
    Player();
    void saveHighscore(int highscore);
    int readHighscore();
};

#endif // PLAYER_H
