#ifndef SETTINGSWINDOW_HPP
#define SETTINGSWINDOW_HPP

    #include <QMainWindow>
    #include "settings.hpp"

    namespace Ui {
    class SettingsWindow;
    }

    class SettingsWindow : public QMainWindow
    {
            Q_OBJECT

        public:
            explicit SettingsWindow(QWidget *parent = nullptr);
            ~SettingsWindow();

        private slots:
            void on_pushButton_ok_clicked();
            void on_pushButton_apply_clicked();
            void on_pushButton_cancel_clicked();

        private:
            Ui::SettingsWindow *ui;
            void save();
    };

#endif // SETTINGSWINDOW_HPP
