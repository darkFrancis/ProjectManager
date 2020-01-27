/**
 * @file newproject.hpp
 * @brief Description de la classe NewProject
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef NEWPROJECT_HPP
#define NEWPROJECT_HPP

    #include <QMainWindow>

    #define FILE_EXTENSION QString(".pjm")/**< Extension des fichiers projets */

    namespace Ui {
        class NewProject;
    }

    /**
     * @class NewProject
     * @brief La classe NewProject définie la fenêtre de création d'un nouveau projet.
     *
     * Cette fenêtre s'ouvre depuis la fenêtre principale MainWindow.
     * On peut y définir un nouveau projet en sélectionnant un dossier Git et en
     * spécifiant ou enregistrer le fichier Doxygen.
     */
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
            Ui::NewProject *ui;/**< UI de la classe NewProject */
    };

#endif // NEWPROJECT_HPP
