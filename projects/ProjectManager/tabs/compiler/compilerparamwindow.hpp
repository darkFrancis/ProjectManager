#ifndef COMPILERPARAMWINDOW_HPP
#define COMPILERPARAMWINDOW_HPP

    #include <QMainWindow>
    #include <QLineEdit>

    namespace Ui {
    class CompilerParamWindow;
    }

    class CompilerParamWindow : public QMainWindow
    {
        Q_OBJECT

        public:
            explicit CompilerParamWindow(QWidget *parent = nullptr);
            ~CompilerParamWindow();

        private slots:
            void on_toolButton_overallOptions_clicked();
            void on_toolButton_languageCOptions_clicked();
            void on_toolButton_languageCxxOptions_clicked();
            void selected(QString kw, QString option);

        private:
            Ui::CompilerParamWindow *ui;
            void add_option(QLineEdit* line_edit, QString option);
            void open_param(QString kw);
    };

#endif // COMPILERPARAMWINDOW_HPP
