#include <QDebug>
#include <iostream>
#include <fstream>
#include "player.h"

Player::Player() {}

//ANF8 - Datei auf Festplatte speichern.
void Player::saveHighscore(int highscore)
{
    qDebug() << "Highscore File save Start";
    std::fstream file(".\\highscore.txt", std::ios::in | std::ios::out);
    file.seekp(0); // Move to the beginning of the file
    file << std::to_string(highscore) << std::endl;
    file.flush(); // Make sure the changes are written to disk
    file.close();
}

//ANF8 - Datei von Festplatte laden und Daten verwenden.
int Player::readHighscore()
{
    qDebug() << "Highscore File Read Start";

    std::string filename = ".\\highscore.txt";
    std::string line;

    //ANF10 Try Catch
    try {
        std::ifstream file(filename); //Datei öffnen zum Lesen
        if (!file) {
            throw std::runtime_error("Failed to open file");
        }

        std::getline(file, line);
        line.erase(line.find_last_not_of("\r\n") + 1); //remove line break
        if (!file) {
            throw std::runtime_error("Failed to read line");
        }

        qDebug() << "highscore: " + line;
        file.close();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 0;
    }

    return std::stoi(line);
}
