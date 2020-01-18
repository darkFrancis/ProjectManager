#ifndef COMPILERPARAMWINDOW_HPP
#define COMPILERPARAMWINDOW_HPP

#include <QMainWindow>

namespace Ui {
class CompilerParamWindow;
}

class CompilerParamWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit CompilerParamWindow(QWidget *parent = nullptr);
        ~CompilerParamWindow();

    private:
        Ui::CompilerParamWindow *ui;
};

#endif // COMPILERPARAMWINDOW_HPP
