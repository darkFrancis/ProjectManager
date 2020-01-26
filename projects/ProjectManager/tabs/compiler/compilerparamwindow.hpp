/**
 * @file compilerparamwindow.hpp
 * @brief Description de la classe CompilerParamWindow
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef COMPILERPARAMWINDOW_HPP
#define COMPILERPARAMWINDOW_HPP

    #include <QMainWindow>
    #include <QLineEdit>

    namespace Ui {
    class CompilerParamWindow;
    }

    /**
     * @class CompilerParamWindow
     * @brief La classe CompilerParamWindow défini la fenêtre de configuration de paramètres de compilation.
     */
    class CompilerParamWindow : public QMainWindow
    {
        Q_OBJECT

        public:
            explicit CompilerParamWindow(QWidget *parent = nullptr);
            ~CompilerParamWindow();

        private slots:
            void on_toolButton_overall_clicked();
            void on_toolButton_languageC_clicked();
            void on_toolButton_languageCxx_clicked();
            void on_toolButton_diagnostic_clicked();
            void on_toolButton_warnings_clicked();
            void on_toolButton_debug_clicked();
            void on_toolButton_optimization_clicked();
            void on_toolButton_instrumentation_clicked();
            void on_toolButton_preprocessor_clicked();
            void on_toolButton_assembler_clicked();
            void on_toolButton_linker_clicked();
            void on_toolButton_dirs_clicked();
            void on_toolButton_codeConvention_clicked();
            void on_pushButton_ok_clicked();
            void on_pushButton_apply_clicked();
            void on_pushButton_close_clicked();
            void selected(QString kw, QString option);

        private:
            Ui::CompilerParamWindow *ui;/**< UI de la classe CompilerParamWindow */
            void add_option(QLineEdit* line_edit, QString option);
            void open_param(QString kw);
            void init();
            void apply();
    };

#endif // COMPILERPARAMWINDOW_HPP
