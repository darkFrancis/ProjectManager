#ifndef TABGIT_HPP
#define TABGIT_HPP

#include <QWidget>

namespace Ui {
    class TabGit;
}

class TabGit : public QWidget
{
        Q_OBJECT

    public:
        explicit TabGit(QWidget *parent = nullptr);
        ~TabGit();

    private:
        Ui::TabGit *ui;
};

#endif // TABGIT_HPP
