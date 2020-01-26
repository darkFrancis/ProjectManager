/**
 * @file paramselectionwindow.hpp
 * @brief Description de la classe ParamSelectionWindow
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef PARAMSELECTIONWINDOW_HPP
#define PARAMSELECTIONWINDOW_HPP

    #include <QMainWindow>

    namespace Ui {
    class ParamSelectionWindow;
    }

    /**
     * @class ParamSelectionWindow
     * @brief La classe ParamSelectionWindow défini la fenêtre de sélection de paramètre de compilation.
     *
     * L'affichage est défini par la strcture CompilerOption.
     */
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
            Ui::ParamSelectionWindow *ui;/**< UI de la classe ParamSelectionWindow */
            QString m_kw;/**< Mot clé pour l'affichage des paramètres */
    };

#endif // PARAMSELECTIONWINDOW_HPP
