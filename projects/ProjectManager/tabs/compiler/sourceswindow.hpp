#ifndef SOURCESWINDOW_HPP
#define SOURCESWINDOW_HPP

#include <QMainWindow>

namespace Ui {
class SourcesWindow;
}

class SourcesWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit SourcesWindow(QWidget *parent = nullptr);
        ~SourcesWindow();

    private:
        Ui::SourcesWindow *ui;
};

#endif // SOURCESWINDOW_HPP
