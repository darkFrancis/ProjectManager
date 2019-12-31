#ifndef TABCOMPILER_HPP
#define TABCOMPILER_HPP

#include <QWidget>

namespace Ui {
    class TabCompiler;
}

class TabCompiler : public QWidget
{
        Q_OBJECT

    public:
        explicit TabCompiler(QWidget *parent = nullptr);
        ~TabCompiler();

    private:
        Ui::TabCompiler *ui;
};

#endif // TABCOMPILER_HPP
