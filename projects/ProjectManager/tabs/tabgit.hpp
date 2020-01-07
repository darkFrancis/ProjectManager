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

        private slots:
            void on_pushButton_clicked();

        private:
            Ui::TabGit *ui;
            bool m_git_exists;
    };

#endif // TABGIT_HPP
