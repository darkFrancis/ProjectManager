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
            void clean();

        private slots:
            void on_pushButton_default_clicked();
            void on_pushButton_apply_clicked();

        private:
            Ui::TabProject *ui;
    };

#endif // TABPROJECT_HPP
