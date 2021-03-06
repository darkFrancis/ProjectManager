/**
 * @file ErrorViewer.hpp
 * @brief Définition de la fenêtre de visualisation d'erreur Git
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef ERRORVIEWER_HPP
#define ERRORVIEWER_HPP

    #include <QMainWindow>

    namespace Ui {
    class ErrorViewer;
    }

    /**
     * @header_table ErrorViewer.hpp @end_table
     * @brief La classe ErrorViewer permet l'affichage d'une erreur.
     *
     * Cette fenêtre popup permet d'afficher un texte d'erreur suivit d'un détail
     * de cette erreur. Ce détail peut être affiché/masqué à l'aide d'un bouton
     * détail.
     */
    class ErrorViewer : public QMainWindow
    {
        Q_OBJECT

        public:
            ErrorViewer(QWidget *parent = nullptr, const QString& error = "Unknow Error", const QString& details = "");
            ~ErrorViewer();

        private slots:
            void on_pushButton_details_clicked();

        private:
            Ui::ErrorViewer *ui;/**< UI de la classe ErrorViewer */
    };

#endif // ERRORVIEWER_HPP
