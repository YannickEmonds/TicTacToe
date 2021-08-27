#include "startwindow.h"
#include <QGridLayout>
#include <QApplication>

StartWindow::StartWindow(QWidget *parent) : QWidget(parent)
{
    startButton = new QPushButton("Start game", this);
    exitButton = new QPushButton("Quit", this);
    boardSizeLineEdit = new QLineEdit("Enter board size", this);

    QGridLayout* layout = new QGridLayout();
    layout->addWidget(boardSizeLineEdit, 0, 0, 1, 2);
    layout->addWidget(startButton, 1, 0);
    layout->addWidget(exitButton, 1,1);
    setLayout(layout);

    connect(boardSizeLineEdit, SIGNAL (returnPressed()), this, SLOT (slotStartButtonClicked()));
    connect(startButton, SIGNAL (clicked()), this, SLOT (slotStartButtonClicked()));
    connect(exitButton, SIGNAL (clicked()), QApplication::instance(), SLOT (quit()));
}

void StartWindow::slotStartButtonClicked()
{
    QString enteredText {boardSizeLineEdit->text()};
    bool ok;
    int width = enteredText.toInt(&ok);
    if (ok)
    {
        emit signalStart(static_cast<std::size_t>(width));
    }
    else
    {
        boardSizeLineEdit->setText("Enter board size again");
    }
}
