/**
 * @file TabProject.cpp
 * @brief Définition de l'onglet de projet
 * @author Dark Francis
 * @date 26/10/2020
 */
#ifndef TABPROJECT_HPP
#define TABPROJECT_HPP

    #include "Tab.hpp"

    namespace Ui {
    class TabProject;
    }

    /**
     * @header_table TabProject.hpp @end_table
     * @brief La classe TabProject définie l'onglet de projet.
     *
     * Cet onglet contient la liste des sous-projets qui doivent être utilisés
     * par les autres onglets.
     */
    class TabProject : public Tab
    {
        Q_OBJECT

        public:
            TabProject(QWidget *parent = nullptr);
            ~TabProject();
            void init();
            void clean();
            void save();

        signals:
            void projectListChange();

        private slots:
            void on_pushButton_add_clicked();
            void on_pushButton_delete_clicked();

        private:
            Ui::TabProject *ui;/**< UI de la classe TabProject */
    };

#endif // TABPROJECT_HPP
