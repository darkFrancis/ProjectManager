/**
 * @file TabGit.hpp
 * @brief Définition de l'onglet Git
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef TABGIT_HPP
#define TABGIT_HPP

    #include "Tab.hpp"
    #include <QProcess>
    #include <QListWidget>
    #include <QTimer>

    #define GIT_COMMIT_DEFAULT_MSG QString("Commit without message")/**< Message par défaut pour un commit si aucun message n'est renseigné */
    #define GIT_COMMIT_PLACEHOLDER QString("Ajoutez un message au commit")/**< Affichage dans la ligne d'édition du commit si aucun message renseigné */

    #define GIT_STATUS_LABEL_0 QString("Non modifié")
    #define GIT_STATUS_LABEL_1 QString("Non suivi")
    #define GIT_STATUS_LABEL_2 QString("Ignoré")
    #define GIT_STATUS_LABEL_M QString("Modifié")
    #define GIT_STATUS_LABEL_A QString("Ajouté")
    #define GIT_STATUS_LABEL_D QString("Supprimé")
    #define GIT_STATUS_LABEL_R QString("Renommé")
    #define GIT_STATUS_LABEL_C QString("Copié")
    #define GIT_STATUS_LABEL_U QString("A jour non fusionné")

    namespace Ui {
        class TabGit;
    }

    /**
     * @header_table TabGit.hpp @end_table
     * @brief La classe TabGit défini l'onglet de gestion de Git.
     *
     * Cet onglet affiche en permanence l'état actuel du dépôt local Git.
     * Il permet d'effectuer des commit de façon simplifié et d'acceder aux
     * différentes fenêtre de gestion Git.
     * @sa BranchesWindow, ErrorViewer, TagsWindow.
     */
    class TabGit : public Tab
    {
        Q_OBJECT

        public:
            TabGit(QWidget *parent = nullptr);
            ~TabGit();
            void init();
            void clean();

        public slots:
            void updateProjectNames();

        signals:
            /**
             * Ce signal est émit en cas de création d'un nouveau tag.
             */
            void tag_created();
            /**
             * @param tags Liste des tags
             *
             * Ce signal est émit pour mettre à jour la liste des tag dans la fenêtre
             * de gestion des tags.
             */
            void tag_update(const QStringList& tags);
            /**
             * @param branches Liste des tags
             *
             * Ce signal est émit pour mettre à jour la liste des branches dans la fenêtre
             * de gestion des branches.
             */
            void branch_update(const QStringList& branches);

        private slots:
            void update_all();
            // Commit
            void on_pushButton_commit_clicked();
            void on_checkBox_amend_stateChanged(int arg1);
            void on_lineEdit_commit_returnPressed();
            void on_lineEdit_issue_textChanged(const QString &arg1);
            // Branches
            void on_toolButton_branch_clicked();
            void on_pushButton_branchMerge_clicked();
            void on_pushButton_branchSwitch_clicked();
            void on_comboBox_branch_currentIndexChanged(const QString &arg1);
            // Actions
            void on_pushButton_add_clicked();
            void on_pushButton_reset_clicked();
            void on_pushButton_checkout_clicked();
            void on_pushButton_gitk_clicked();
            void on_pushButton_tags_clicked();
            void on_pushButton_conflicts_clicked();
            void on_pushButton_push_clicked();
            void on_pushButton_fetch_clicked();
            void on_pushButton_rebase_clicked();
            void on_pushButton_extra_clicked();
            void on_lineEdit_extra_returnPressed();
            void action_tags(QStringList args);
            void action_branch(const QStringList& args);
            void closeMergeTool();
            void on_pushButton_stash_clicked();
            void on_pushButton_pop_clicked();
            void on_pushButton_pull_clicked();

        private:
            bool action(const QStringList& args, bool status = true);
            QStringList getSelected(QListWidget* list_view, bool only_files = true);
            QStringList getAllItems(QListWidget* list_view, bool only_files = true);
            QString stateChar2Label(const QChar& c, bool staged = false);
            // Update
            void update_status();
            void update_branches();
            void update_remote();
            void update_stash();

        private:
            Ui::TabGit *ui;/**< UI de la classe TabGit */
            QProcess* m_process;/**< Processus pour exécution des commandes Git */
            int m_last_exit_code;/**< Dernier code retour du processus */
            QString m_output;/**< Sortie standard du dernier processus */
            QString m_error;/**< Erreur standard du dernier processus */
            QStringList m_unmerged;/**< Liste des fichiers en conflit */
            QTimer m_timer;/**< Timer pour la mise à jour du status */
    };

#endif // TABGIT_HPP
