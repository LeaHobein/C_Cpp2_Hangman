#include "gamecontroller.h"
#include "model/gameround.h"
#include <QDebug>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const int BUFFER_SIZE=20; //maximale Länge für eine Zeile (ein Wort)
const int WORD_COUNT=10; //maximale Anzahl an Wörtern

GameRound gRound;

std::vector<std::string> words(WORD_COUNT); //Vektor von Strings mit Größe WORD_COUNT, beinhaltet alle Ratewörter
std::string outputWord; //string für das Ratewort
int foundLettersCount; //zähle wie viele korrekte Buchstaben insgesamt gefunden wurden

GameController::GameController()
{

}

void GameController::newGame()
{
    readFile();
    selectSecretWord();
    qDebug() << "UNSER GEHEIMWORT: " + gRound.getSecretWord();
    createOutputWord();
    gRound.setPoints(10); //Anzahl Versuche auf 10 setzen
}

//ANF TODO - Datei von Festplatte laden und Daten verwenden.
void GameController::readFile()
{
    qDebug() << "File Read Start";

    std::ifstream file(".\\words.txt"); //Datei öffnen zum Lesen
    if (file.is_open()) { //Wenn Datei geöffnet werden konnte,
        std::string line; //definition eines Strings um temporär Zeile einzulesen
        int counter = 0; //Zähler um Anzahl Zeilen beim Einlesen aus Datei zu zählen
        while (std::getline(file, line)) { //checke ob dateiende erreicht
            line.erase(line.find_last_not_of("\r\n") + 1); //remove line break
            words[counter] = line; //Schreibe aktuelle Zeile in den Vector words an Position counter
            qDebug() << line;
            counter++; //erhöhe counter um 1
        }
        file.close();
    }
    else {
        std::cout << "Fehler: Datei konnte nicht geoeffnet werden" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void GameController::selectSecretWord()
{
    srand(static_cast<unsigned int>(time(nullptr))); // Zufallsgenerator initialisiert - aktuelle Zeit als Input für Zufallsgenerator
    int randomnumber = rand() % WORD_COUNT; // generiere Zufallszahl zwischen 0 und WORD_COUNT (10)
    gRound.setSecretWord(words[randomnumber]);
}

std::string GameController::getSecretWord()
{
    return gRound.getSecretWord();
}

void GameController::createOutputWord()
{
    int secretWordLength = gRound.getSecretWord().length();
    for (int i = 0; i < secretWordLength; ++i) {
        outputWord.append("_");
    }
    qDebug() << "outputWord: " + outputWord;
}

std::string GameController::getOutputWord()
{
    return outputWord;
}

int GameController::getFoundLettersCount()
{
    return foundLettersCount;
}

bool GameController::evaluateLetter(std::string guessedLetter)
{
    std::string secretWord = gRound.getSecretWord();

    bool letterFound = false;
    int count = 0;
    size_t pos = 0;
    while ((pos = secretWord.find(guessedLetter, pos)) != std::string::npos) {
        letterFound = true;
        count++;
        foundLettersCount++;
        outputWord.replace(pos, 1, guessedLetter);

        pos += guessedLetter.size(); // move to the next position
    }
    if (letterFound)
    {
        qDebug() << "found " + std::to_string(count);
    }
    else
    {
        qDebug() << "not found";
        gRound.reducePoints();
    }
    return letterFound;
}

bool GameController::checkWordComplete()
{
    if(foundLettersCount == gRound.getSecretWord().length())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool GameController::checkGameOver()
{
    if(gRound.getPoints() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int GameController::getScore()
{
    return gRound.getPoints();
}

