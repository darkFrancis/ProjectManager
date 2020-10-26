#ifndef NEWWINDOW_HPP
#define NEWWINDOW_HPP

#include <QMainWindow>

namespace Ui {
class NewWindow;
}

class NewWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit NewWindow(QWidget *parent = nullptr);
        ~NewWindow();

    private:
        Ui::NewWindow *ui;
};

#endif // NEWWINDOW_HPP
