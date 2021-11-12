/**
 * @file DoxygenFilesHelper.hpp
 * @brief Définition de la fenêtre de gestion des fichiers Doxygen
 * @author Dark Francis
 * @date 27/02/2021
 */
#ifndef DOXYGENFILESHELPERESHELPER_HPP
#define DOXYGENFILESHELPERESHELPER_HPP

    #include <QMainWindow>
    #include <QLineEdit>
    #include <QLabel>

    namespace Ui {
    class DoxygenFilesHelper;
    }

    class DoxygenFilesHelper : public QMainWindow
    {
        Q_OBJECT

        public:
            DoxygenFilesHelper(const QString& docDir, QWidget *parent = nullptr);
            ~DoxygenFilesHelper();

        private slots:
            void on_pushButton_generateTemplates_clicked();
            void on_pushButton_openDir_clicked();
            void on_pushButton_generateIndex_clicked();
            void on_pushButton_openIndex_clicked();

        private:
            void command(const QString& cmd, const QString& workingDir = ".");

        private:
            Ui::DoxygenFilesHelper *ui;
            QString m_docDir; /**< Dossier principal de documentation */
            QList<QLabel*> m_labels; /**< Liste des noms de projets affichés */
            QList<QLineEdit*> m_lines; /**< Liste des lignes de descriptions de projets */
    };

#endif // DOXYGENFILESHELPERESHELPER_HPP
