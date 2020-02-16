#ifndef BRANCHESWINDOW_HPP
#define BRANCHESWINDOW_HPP

    #include <QMainWindow>
    #include <QListWidgetItem>

    namespace Ui {
    class BranchesWindow;
    }

    class BranchesWindow : public QMainWindow
    {
        Q_OBJECT

        public:
            BranchesWindow(QWidget *parent = nullptr);
            ~BranchesWindow();

        public slots:
            void update_branches(QStringList branches);

        signals:
            void action(QStringList args);

        private slots:
            void on_listWidget_branch_currentItemChanged(QListWidgetItem *current, QListWidgetItem*);
            void on_pushButton_add_clicked();
            void on_pushButton_rename_clicked();
            void on_pushButton_copy_clicked();
            void on_pushButton_remove_clicked();

        private:
            Ui::BranchesWindow *ui;
    };

#endif // BRANCHESWINDOW_HPP
