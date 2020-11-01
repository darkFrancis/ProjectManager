#ifndef TABPROJECT_HPP
#define TABPROJECT_HPP

    #include "Tab.hpp"

    namespace Ui {
    class TabProject;
    }

    class TabProject : public Tab
    {
        Q_OBJECT

        public:
            TabProject(QWidget *parent = nullptr);
            ~TabProject();
            void init();
            void clean();
            void save();

        private slots:
            void on_pushButton_add_clicked();
            void on_pushButton_delete_clicked();

        private:
            Ui::TabProject *ui;
    };

#endif // TABPROJECT_HPP
