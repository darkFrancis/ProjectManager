/**
 * @file MainWindow.hpp
 * @brief Définition de la fenêtre principale
 * @author Dark Francis
 * @date 25/10/2020
 */
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

    #include <QMainWindow>

    namespace Ui {
    class MainWindow;
    }

    /**
     * @header_table MainWindow.hpp @end_table
     * @brief La classe MainWindow défini la fenêtre principale.
     *
     * Cette fenêtre contient des onglets issus de la classe Tab.
     * @sa Ui.
     */
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

        public:
            explicit MainWindow(QWidget *parent = nullptr);
            ~MainWindow();

        private slots:
            void on_actionAbout_triggered();
            void on_actionNouveau_triggered();
            void on_actionOuvrir_triggered();
            void on_actionEnregistrer_triggered();
            void on_actionQuitter_triggered();

        private:
            void enable();

        private:
            Ui::MainWindow *ui;/**< UI de la classe MainWindow */
    };

#endif // MAINWINDOW_HPP
