#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <cstddef>
#include <vector>
#include <memory>

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(const std::size_t width, QWidget *parent = nullptr);
signals:
    void counterReached();
private slots:
    void slotButtonClicked();
private:
    const std::size_t boardWidth;
    // TODO: clean up raw pointers
    std::vector<QPushButton*> buttons;
//    QPushButton *m_button;
};

#endif // WINDOW_H
