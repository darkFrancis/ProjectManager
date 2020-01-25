/**
 * @file tabproject.hpp
 * @brief Description de la classe TabProject
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef TABPROJECT_HPP
#define TABPROJECT_HPP

    #include "tab.hpp"

    namespace Ui {
    class TabProject;
    }

    class TabProject : public Tab
    {
        Q_OBJECT

        public:
            explicit TabProject(QWidget *parent = nullptr);
            ~TabProject();
            void init();
            void clean();
            void save();

        private slots:
            void on_pushButton_default_clicked();
            void on_pushButton_apply_clicked();
            void on_toolButton_doxyfile_clicked();
            void on_toolButton_git_clicked();

        private:
            Ui::TabProject *ui;
    };

#endif // TABPROJECT_HPP
