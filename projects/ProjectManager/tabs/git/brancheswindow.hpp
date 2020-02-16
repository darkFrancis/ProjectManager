#ifndef BRANCHESWINDOW_HPP
#define BRANCHESWINDOW_HPP

#include <QMainWindow>

namespace Ui {
class BranchesWindow;
}

class BranchesWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit BranchesWindow(QWidget *parent = nullptr);
        ~BranchesWindow();

    private:
        Ui::BranchesWindow *ui;
};

#endif // BRANCHESWINDOW_HPP
