/**
 * @file BranchesWindow.hpp
 * @brief Description de la classe BranchesWindow
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef BRANCHESWINDOW_HPP
#define BRANCHESWINDOW_HPP

    #include <QMainWindow>
    #include <QListWidgetItem>

    namespace Ui {
    class BranchesWindow;
    }

    /**
     * @class BranchesWindow
     * @brief La classe BranchesWindow défini la fenêtre de gestion des branches GIT.
     *
     * Ces branches peuvent être ajoutées, supprimées, renommées ou copiées. Toute
     * autre commande devra se faire manuellement depuis l'onglet Git.@n
     * Header : BranchesWindow.hpp
     */
    class BranchesWindow : public QMainWindow
    {
        Q_OBJECT

        public:
            BranchesWindow(QWidget *parent = nullptr);
            ~BranchesWindow();

        public slots:
            void update_branches(QStringList branches);

        signals:
            /**
             * @param args Arguments à utiliser
             *
             * Ce signal est émit pour demander un appel à la commande Git depuis
             * l'onglet Git de la fenêtre principale.
             */
            void action(const QStringList& args);

        private slots:
            void on_listWidget_branch_currentItemChanged(QListWidgetItem *current, QListWidgetItem*);
            void on_pushButton_add_clicked();
            void on_pushButton_rename_clicked();
            void on_pushButton_copy_clicked();
            void on_pushButton_remove_clicked();

        private:
            bool check_branch_name(const QString& name);
            QString get_selected();

        private:
            Ui::BranchesWindow *ui;/**< UI de la classe BranchesWindow */
    };

#endif // BRANCHESWINDOW_HPP
