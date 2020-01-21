#ifndef PARAMSELECTIONWINDOW_HPP
#define PARAMSELECTIONWINDOW_HPP

    #include <QMainWindow>

    namespace Ui {
    class ParamSelectionWindow;
    }

    class ParamSelectionWindow : public QMainWindow
    {
        Q_OBJECT

        public:
            ParamSelectionWindow(QWidget *parent = nullptr, QString param_type = "");
            ~ParamSelectionWindow();

        signals:
            void selected(QString kw, QString option);

        private slots:
            void on_pushButton_close_clicked();
            void on_pushButton_ok_clicked();

        private:
            Ui::ParamSelectionWindow *ui;
            QString m_kw;
    };

#endif // PARAMSELECTIONWINDOW_HPP
