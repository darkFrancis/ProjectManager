#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

    #include <QMainWindow>
    #include "tabs/tabdoxygen.hpp"

    #define STATUS_DEFAULT_TIMEOUT 5

    // Init
    #define INIT_FILE   "projectmanager.ini"
    #define INIT_X      200
    #define INIT_Y      200
    #define INIT_W      400
    #define INIT_H      300

    namespace Ui {
        class MainWindow;
    }

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

        public:
            explicit MainWindow(QWidget *parent = nullptr);
            ~MainWindow();
            void init();

        private slots:
            void on_actionNouveau_triggered();

        private:
            // UI
            Ui::MainWindow *ui;
            QTabWidget* m_tabWidget;
            void status(QString msg, int timeout = 0);
            void createInit();
            void saveInit();
            // Tabs
            TabDoxygen* m_tab_doxygen;
    };

#endif // MAINWINDOW_HPP
