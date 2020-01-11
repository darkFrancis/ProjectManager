/**
 * @headerfile tabcompiler.hpp "tabcompiler.hpp"
 * @brief Description de la classe TabCompiler
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef TABCOMPILER_HPP
#define TABCOMPILER_HPP

    #include "tab.hpp"

    #define TEXT_BUILDRUN    QString("build&run")
    #define TEXT_BUILD       QString("build")
    #define TEXT_RUN         QString("run")
    #define TEXT_MAKEFILE    QString("makefile")
    #define TEXT_CLEAN       QString("clean")
    #define TEXT_INSTALL     QString("install")
    #define TEXT_UNINSTALL   QString("uninstall")

    namespace Ui {
        class TabCompiler;
    }

    /**
     * @class TabCompiler tabcompiler.hpp "tabcompiler.hpp"
     * @brief La classe TabCompiler défini l'onglet de compilation
     *
     * Elle permet avec de définir :
     * @li les options de compilation
     * @li des defines à appliquer à la compilation
     * @li les librairie à importer
     * @li le mode de compilation : release (défini NDEBUG) ou debug (défini _DEBUG)
     *
     * @todo finir la classe TabCompiler
     */
    class TabCompiler : public Tab
    {
        Q_OBJECT

        public:
            TabCompiler(QWidget *parent = nullptr);
            ~TabCompiler();
            /*void clean();
            QStringList getInfo();*/

        private slots:
            void on_toolButton_buildDir_clicked();
            void on_toolButton_gestion_clicked();
            void on_pushButton_action_clicked();

        private:
            Ui::TabCompiler *ui;

            // Actions
            void action_build();
            void action_run();
            void action_clean();
            void action_makefile();
            void action_install();
            void action_uninstall();
    };

#endif // TABCOMPILER_HPP
