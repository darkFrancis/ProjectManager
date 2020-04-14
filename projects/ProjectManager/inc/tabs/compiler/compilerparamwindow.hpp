/**
 * @file compilerparamwindow.hpp
 * @brief Description de la classe CompilerParamWindow
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef COMPILERPARAMWINDOW_HPP
#define COMPILERPARAMWINDOW_HPP

    #include <QMainWindow>
    #include <QListWidget>

    #define IDX_TAB_EXTRA_PRE   0
    #define IDX_TAB_EXTRA_POST  1
    #define IDX_TAB_EXTRA_CLEAN 2

    namespace Ui {
    class CompilerParamWindow;
    }

    /**
     * @class CompilerParamWindow
     * @brief La classe CompilerParamWindow défini la fenêtre de configuration de paramètres de compilation.
     *
     * Les paramètres sont classés par catégories (Voir @ref KW_COMPILE).@n
     * Chaque champs permet de sélectionner les paramètres qui seront utilisés lors
     * de la compilation par la classe TabCompiler. Un champs est présent pour l'ajout
     * d'options supplémentaires. Les options prédéfinies sont celles de GCC 7.4.0.
     *
     * @n Header : compilerparamwindow.hpp.
     */
    class CompilerParamWindow : public QMainWindow
    {
        Q_OBJECT

        public:
            CompilerParamWindow(QWidget *parent = nullptr);
            ~CompilerParamWindow();

        private slots:
            void on_pushButton_ok_clicked();
            void on_pushButton_apply_clicked();
            void on_pushButton_close_clicked();
            void selected(QString kw, QString option);
            void on_pushButton_addDefine_clicked();
            void on_pushButton_removeDefine_clicked();
            void on_toolButton_includePath_clicked();
            void on_pushButton_addIncludePath_clicked();
            void on_pushButton_removeIncludePath_clicked();
            void on_toolButton_links_clicked();
            void on_pushButton_addLinks_clicked();
            void on_pushButton_removeLinks_clicked();
            void on_toolButton_compilerOption_clicked();
            void on_toolButton_addExtraCmd_clicked();
            void on_pushButton_removeExtraCmd_clicked();

        private:
            Ui::CompilerParamWindow *ui;/**< UI de la classe CompilerParamWindow */
            void open_param(QString kw);
            void init();
            void apply();
            QStringList itemsFromList(QListWidget* widget);
    };

#endif // COMPILERPARAMWINDOW_HPP
