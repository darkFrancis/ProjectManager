/**
 * @file MainWindow.hpp
 * @brief Definition de la fenêtre principale
 * @author Dark Francis
 * @date 25/10/2020
 */
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

    #include <QMainWindow>

    namespace Ui {
    class MainWindow;
    }

    class MainWindow : public QMainWindow
    {
            Q_OBJECT

        public:
            explicit MainWindow(QWidget *parent = nullptr);
            ~MainWindow();

        private:
            Ui::MainWindow *ui;
    };

#endif // MAINWINDOW_HPP
