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
            void init();
            void save();
            QStringList getSources();
            QStringList getHeaders();
            QStringList getRessources();

        private slots:
            void on_pushButton_add_clicked();
            void on_pushButton_remove_clicked();
            void on_listWidget_sources_itemDoubleClicked(QListWidgetItem *item);
            void on_listWidget_headers_itemDoubleClicked(QListWidgetItem *item);
            void on_listWidget_ressources_itemDoubleClicked(QListWidgetItem *item);

        private:
            Ui::SourcesWindow *ui;/**< UI de la classe SourcesWindow */
            void addItem(QString text, QListWidget* widget);
            bool isSource(QString extension);
            bool isHeader(QString extension);
            void itemDoubleClicked(QListWidgetItem *item);
    };

#endif // SOURCESWINDOW_HPP
