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
            void overall_selected(QString option);
            void on_toolButton_languageCOptions_clicked();
            void language_c_selected(QString option);
            void on_toolButton_languageCxxOptions_clicked();
            void language_cxx_selected(QString option);

        private:
            Ui::CompilerParamWindow *ui;
            void add_option(QLineEdit* line_edit, QString option);
    };

#endif // COMPILERPARAMWINDOW_HPP
