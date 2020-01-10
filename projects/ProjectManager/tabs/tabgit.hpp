/**
 * @file tabgit.hpp
 * @brief Description de la classe TabGit
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef TABGIT_HPP
#define TABGIT_HPP

    #include "tab.hpp"

    namespace Ui {
        class TabGit;
    }

    class TabGit : public Tab
    {
        Q_OBJECT

        public:
            TabGit(QWidget *parent = nullptr);
            ~TabGit();

        private slots:
            void on_pushButton_clicked();

        private:
            Ui::TabGit *ui;
            bool m_git_exists;
    };

#endif // TABGIT_HPP
