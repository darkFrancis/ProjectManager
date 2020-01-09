#ifndef TABCOMPILER_HPP
#define TABCOMPILER_HPP

    #include "tab.hpp"

    namespace Ui {
        class TabCompiler;
    }

    class TabCompiler : public Tab
    {
        Q_OBJECT

        public:
            TabCompiler(QWidget *parent = nullptr);
            ~TabCompiler();
            void clean();
            QStringList getInfo();

        private:
            Ui::TabCompiler *ui;
    };

#endif // TABCOMPILER_HPP
