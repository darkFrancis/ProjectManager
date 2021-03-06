/**
 * @file TagsWindow.hpp
 * @brief Définition de la fenêtre de gestion des tags
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef TAGSWINDOW_HPP
#define TAGSWINDOW_HPP

    #include <QMainWindow>

    namespace Ui {
    class TagsWindow;
    }

    /**
     * @header_table TagsWindow.hpp @end_table
     * @brief La classe TagsWindow défini la fenêtre de gestion des tags GIT.
     *
     * Ces tags peuvent être ajoutés, supprimés ou poussés. Toute autre commande
     * devra se faire manuellement depuis l'onglet Git.
     */
    class TagsWindow : public QMainWindow
    {
        Q_OBJECT

        public:
            TagsWindow(QWidget *parent = nullptr, const QStringList& tags = QStringList());
            ~TagsWindow();

        public slots:
            void clean_tag_name();
            void update_tags(QStringList tags);

        signals:
            /**
             * @param args Arguments à utiliser
             *
             * Ce signal est émit pour demander un appel à la commande Git depuis
             * l'onglet Git de la fenêtre principale.
             */
            void action(const QStringList& args);

        private slots:
            void on_pushButton_add_clicked();
            void on_pushButton_push_clicked();
            void on_pushButton_remove_clicked();

        private:
            Ui::TagsWindow *ui;/**< UI de la classe TagsWindow */
    };

#endif // TAGSWINDOW_HPP
