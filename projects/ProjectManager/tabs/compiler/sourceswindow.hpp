/**
 * @file sourceswindow.hpp
 * @brief Description de la classe SourcesWindow
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef SOURCESWINDOW_HPP
#define SOURCESWINDOW_HPP

    #include <QMainWindow>
    #include <QListWidget>

    namespace Ui {
    class SourcesWindow;
    }
    /**
     * @class SourcesWindow
     * @brief La classe SourcesWindow permet la gestion des sources pour la compilation.
     * @li Avec le bouton ajout, une fenêtre de dialog s'ouvre pour ajouter des fichiers
     * @li Il est possible de cocher les fichier pour les supprimer avec le boutons Supprimer
     *
     * @todo Les extensions de fichier pour être considérées comme sources, header ou ressource
     * peuvent être configurées dans les options.
     */
    class SourcesWindow : public QMainWindow
    {
        Q_OBJECT

        public:
            SourcesWindow(QWidget *parent = nullptr);
            ~SourcesWindow();
            QStringList getSources();
            QStringList getHeaders();
            QStringList getRessources();

        public slots:
            void setChecked(QListWidgetItem* item);

        signals:
            /**
             * @brief Le signal changed permet d'avertir de changements
             * @param window définie cette fenêtre pour le changement
             *
             * Si un ajout/retrait de sources est effectué, ce signal est émit.@n
             * Les listes peuvent être récupérées via les fonctions get de la classe SourcesWindow.
             */
            void changed(SourcesWindow* window);

        private slots:
            void on_pushButton_add_clicked();
            void on_pushButton_remove_clicked();

        private:
            Ui::SourcesWindow *ui;
            void addItem(QString text, QListWidget* widget);
            bool isSource(QString extension);
            bool isHeader(QString extension);
    };

#endif // SOURCESWINDOW_HPP
