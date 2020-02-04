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

    /**
     * @class TabGit
     * @brief La classe TabGit défini l'onglet de gestion de Git.
     *
     * Cette fenêtre lance le programme GitKraken pour la gestion de Git.
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

        private slots:
            void on_pushButton_clicked();

        private:
            Ui::TabGit *ui;/**< UI de la classe TabGit */
            bool m_git_exists;/**< Booléen de l'existance du dossier .git */
    };

#endif // TABGIT_HPP
