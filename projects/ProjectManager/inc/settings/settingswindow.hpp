/**
 * @file settingswindow.hpp
 * @brief Description de la classe SettingsWindow
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef SETTINGSWINDOW_HPP
#define SETTINGSWINDOW_HPP

    #include <QMainWindow>
    #include "settings.hpp"

    #define STYLE_LIST  QStringList() << "default" << "darkstyle" /**< Liste des style de l'application */

    namespace Ui {
    class SettingsWindow;
    }

    /**
     * @class SettingsWindow
     * @brief La classe SettingsWindow défini la fenêtre de gestion des options.
     *
     * Les options sont répartie en trois partie :
     * @li Affichage pour le style d'affichage
     * @li Doxygen pour la configuration des templates
     * @li Compilateur pour le format de sortie
     *
     * Header : settingswindow.hpp
     */
    class SettingsWindow : public QMainWindow
    {
        Q_OBJECT

        public:
            SettingsWindow(QWidget *parent = nullptr);
            ~SettingsWindow();

        private slots:
            void on_pushButton_ok_clicked();
            void on_pushButton_apply_clicked();
            void on_pushButton_cancel_clicked();

        private:
            Ui::SettingsWindow *ui;/**< UI de la classe SettingsWindow */
            void save();
    };

#endif // SETTINGSWINDOW_HPP
