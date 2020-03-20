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

        private:
            Ui::CompilerParamWindow *ui;/**< UI de la classe CompilerParamWindow */
            void open_param(QString kw);
            void init();
            void apply();
    };

#endif // COMPILERPARAMWINDOW_HPP
