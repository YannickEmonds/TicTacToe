#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <cstddef>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

class StartWindow : public QWidget
{
    Q_OBJECT
public:
    explicit StartWindow(QWidget *parent = nullptr);

signals:
    void signalStart(const std::size_t width);
    void signalQuit();
private slots:
    void slotStartButtonClicked();
private:
    QPushButton* startButton;
    QPushButton* exitButton;
    QLineEdit* boardSizeLineEdit;
};

#endif // STARTWINDOW_H
