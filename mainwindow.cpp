#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "gamecontroller.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLineItem>

GameController gc;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->BtnInfo, &QPushButton::clicked, this, &MainWindow::hideInfo);
    connect(ui->BtnGuess, &QPushButton::clicked, this, &MainWindow::rateBtnClicked);
    connect(ui->textGuessLetter, &QLineEdit::textChanged, this, &MainWindow::onTextChanged);

    gc.newGame(); //TODO datei laden, wort aussuchen, string mit unterstrichen füllen (outputWord)
    ui->labelOutputWord->setText(QString::fromStdString(gc.getOutputWord())); // Update Output Word in der GUI
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTextChanged(const QString &text) { //eingegebene Buchstaben großschreiben
    QString capitalizedText = text.toUpper();
    ui->textGuessLetter->setText(capitalizedText);
}

void MainWindow::hideInfo()
{
    ui->TxtInfo->hide();
    ui->BtnInfo->hide();
}

void MainWindow::rateBtnClicked()
{
    std::string guessedLetter = ui->textGuessLetter->text().toStdString();
    qDebug() << "Letter: " + guessedLetter;
    bool foundLetter = gc.evaluateLetter(guessedLetter);
    if (foundLetter)
    {
        ui->labelOutputWord->setText(QString::fromStdString(gc.getOutputWord())); // Update Output Word in der GUI
        ui->labelRvF->setText("Richtig! " + QString::fromStdString(guessedLetter) + " ist im Wort enthalten!");
    }
    else
    {
        ui->labelRvF->setText("Falsch! " + QString::fromStdString(guessedLetter) + " ist im Wort nicht enthalten!");
        drawHangman();
    }

    ui->labelTries->setText("Übrige Versuche: " + QString::number(gc.getScore()));

    if(gc.checkWordComplete())
    {
        qDebug() << "Fertig ";
        ui->labelRvF->setText("Du hast gewonnen!");
    }
    if(gc.checkGameOver())
    {
        ui->labelRvF->setText("Du hast verloren. :( Das Wort war: " + QString::fromStdString(gc.getSecretWord()));
    }
}

void MainWindow::drawHangman()
{
    QGraphicsView* view = ui->graphicsView;
    QGraphicsScene* scene = view->scene();
    if (!scene) {
        // Create a new scene if one doesn't exist
        scene = new QGraphicsScene();
        view->setScene(scene);
    }
    switch (gc.getScore()) {
    case 9:
        scene->addLine(80.0, 260.0, 310.0, 260.0);
        break;
    case 8:
        scene->addLine(150.0, 40.0, 150.0, 260.0);
        break;
    case 7:
        scene->addLine(150.0, 40.0, 230.0, 40.0);
        break;
    case 6:
        scene->addLine(190.0, 40.0, 150.0, 70.0);
        break;
    case 5:
        scene->addLine(230.0, 40.0, 230.0, 70.0);
        break;
    case 4:
        scene->addEllipse(210.0, 70.0, 40.0, 40.0);
        break;
    case 3:
        scene->addLine(230.0, 110.0, 230.0, 170.0);
        break;
    case 2:
        scene->addLine(200.0, 140.0, 260.0, 140.0);
        break;
    case 1:
        scene->addLine(230.0, 170.0, 200.0, 200.0);
        break;
    case 0:
        scene->addLine(230.0, 170.0, 260.0, 200.0);
        break;
    default:
        qDebug() << "Invalid";
        break;


}
}
