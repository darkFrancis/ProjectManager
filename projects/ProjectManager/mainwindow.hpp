/**
 * @file mainwindow.hpp
 * @brief Description de la classe MainWindow
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

    #include <QMainWindow>
    #include <QList>
    #include "tabcompiler.hpp"
    #include "tabdoxygen.hpp"
    #include "tabgit.hpp"
    #include "tabproject.hpp"

    #define STATUS_DEFAULT_TIMEOUT 5/**< Timeout par défaut pour l'affichage du status */

    // Init
    /** @addtogroup FILE
      * @{ */
    #define INIT_FILE   QString("config/projectmanager.ini")/**< Fichier d'initialisation du programme */
    /** @}*/
    #define INIT_X      200/**< Position X par défaut d'affichage de la fenêtre principale */
    #define INIT_Y      200/**< Position Y par défaut d'affichage de la fenêtre principale */
    #define INIT_W      400/**< Largeur par défaut d'affichage de la fenêtre principale */
    #define INIT_H      300/**< Hauteur X par défaut d'affichage de la fenêtre principale */

    namespace Ui {
        class MainWindow;
    }

    /**
     * @class MainWindow
     * @brief La classe MainWindow défini la fenêtre principale de ProjectManager.
     *
     * Cette fenêtre comporte différent onglets pour la gestion :
     * @li du projet
     * @li de la documentation avec Doxygen
     * @li de la compilation avec GNU/GCC
     * @li du suivi avec Git
     *
     * Header : mainwindow.hpp
     */
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

        public:
            MainWindow(QWidget *parent = nullptr);
            ~MainWindow();
            void initApp();
            void clean();
            void init();

        public slots:
            void loadProject();
            void save();
            void status(QString msg, int timeout = 0);

        private slots:
            /** @addtogroup MENU_FUNC
             * @{ */
            void on_actionNouveau_triggered();
            void on_actionOuvrir_triggered();
            void on_actionEnregistrer_triggered();
            void on_actionFermer_triggered();
            void on_actionQuitter_triggered();
            void on_actionOptions_triggered();
            void on_actionA_propos_triggered();
            void on_actionA_propos_de_Qt_triggered();
            /** @} */

        private:
            // UI
            Ui::MainWindow *ui;/**< UI de la classe MainWindow */
            QTabWidget* m_tabWidget;/**< Widget principal de gestion des onglets */
            void createInit();
            void saveInit();
            // Tabs
            QList<Tab*> m_tablist;/**< Liste de chaque Widget principal d'onglet */
    };

#endif // MAINWINDOW_HPP
