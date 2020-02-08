/**
 * @file tabgit.hpp
 * @brief Description de la classe TabGit
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef TABGIT_HPP
#define TABGIT_HPP

    #include "tab.hpp"

    #define GIT_COMMIT_DEFAULT_MSG QString("Commit without message")/**< Message par défaut pour un commit si aucun message n'est renseigné */
    #define GIT_COMMIT_PLACEHOLDER QString("Ajoutez un message au commit")/**< Affichage dans la ligne d'édition du commit si aucun message renseigné */

    namespace Ui {
        class TabGit;
    }

    /**
     * @class TabGit
     * @brief La classe TabGit défini l'onglet de gestion de Git.
     *
     * Cette fenêtre lance le programme GitKraken pour la gestion de Git. --> Plus maintenant
     * @n Header : tabgit.hpp
     *
     * @todo Remplacement de l'utilisation de GitKraken par des commandes internes
     */
    class TabGit : public Tab
    {
        Q_OBJECT

        public:
            TabGit(QWidget *parent = nullptr);
            ~TabGit();
            void init();
            void clear();

        private slots:
            // Commit
            void on_pushButton_commit_clicked();
            void on_checkBox_amend_stateChanged(int arg1);
            // Branches
            void on_comboBox_branch_currentTextChanged(const QString &arg1);
            void on_toolButton_branch_clicked();
            // Actions
            void on_pushButton_add_clicked();
            void on_pushButton_reset_clicked();
            void on_pushButton_checkout_clicked();
            void on_pushButton_gitk_clicked();
            void on_pushButton_tags_clicked();
            void on_pushButton_push_clicked();
            void on_pushButton_fetch_clicked();
            void on_pushButton_rebase_clicked();

        private:
            Ui::TabGit *ui;/**< UI de la classe TabGit */
    };

#endif // TABGIT_HPP
