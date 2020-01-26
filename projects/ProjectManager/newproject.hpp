/**
 * @file newproject.hpp
 * @brief Description de la classe NewProject
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef NEWPROJECT_HPP
#define NEWPROJECT_HPP

    #include <QMainWindow>

    #define FILE_EXTENSION QString(".pm")

    namespace Ui {
        class NewProject;
    }

    class NewProject : public QMainWindow
    {
            Q_OBJECT

        public:
            explicit NewProject(QWidget *parent);
            ~NewProject();

        signals:
            void created();

        private slots:
            void on_toolButton_projectDir_clicked();
            void on_toolButton_mainGitDir_clicked();
            void on_toolButton_doxyfile_clicked();
            void on_pushButton_cancel_clicked();
            void on_pushButton_create_clicked();

        private:
            Ui::NewProject *ui;
    };

#endif // NEWPROJECT_HPP
