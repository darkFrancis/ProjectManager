/**
 * @file tabcompiler.hpp
 * @brief Description de la classe TabCompiler
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef TABCOMPILER_HPP
#define TABCOMPILER_HPP

    #include "tab.hpp"
    #include "processdisplayer.hpp"
    #include <QProcess>

    /** @addtogroup COMPILE_ACTION
      * @{ */
    #define TEXT_BUILDRUN   QString("build&run")/**< Texte pour l'action de compilation puis d'exécution */
    #define TEXT_BUILD      QString("build")/**< Texte pour l'action de compilation seule */
    #define TEXT_RUN        QString("run")/**< Texte pour l'action d'exécution seule */
    #define TEXT_CLEAN      QString("clean")/**< Texte pour l'action de nettoyage */
    #define TEXT_INSTALL    QString("install")/**< Texte pour l'action d'installation */
    #define TEXT_UNINSTALL  QString("uninstall")/**< Texte pour l'action de désinstallation */
    /** @} */

    namespace Ui {
        class TabCompiler;
    }

    /**
     * @class TabCompiler
     * @brief La classe TabCompiler défini l'onglet de compilation.
     *
     * Elle permet avec de définir :
     * @li les options de compilation
     * @li les dossiers de build et de sortie
     * @li le mode de compilation : release (défini NDEBUG) ou debug (défini _DEBUG)
     *
     * Cet onglet utilise le widget ProcessDisplayer pour afficher les commandes en
     * cours.@n
     * Header : tabcompiler.hpp
     *
     * @todo finir la classe TabCompiler
     */
    class TabCompiler : public Tab
    {
        Q_OBJECT

        public:
            TabCompiler(QWidget *parent = nullptr);
            ~TabCompiler();
            void save();
            void init();

        public slots:
            void activate_action();

        private slots:
            void on_toolButton_buildDir_clicked();
            void on_pushButton_sources_clicked();
            void on_pushButton_param_clicked();
            void on_pushButton_action_clicked();
            void on_pushButton_default_clicked();
            void on_pushButton_apply_clicked();

        private:
            Ui::TabCompiler *ui;/**< UI de la classe TabCompiler */
            ProcessDisplayer* m_displayer;/**< Widget d'affichage et de gestion des commandes */

            // Actions
            /** @addtogroup TABCOMPILER_ACTION
              * @{ */
            void action_build_run();
            void action_build();
            void action_run();
            void action_clean();
            void action_install();
            void action_uninstall();
            /** @} */
    };

#endif // TABCOMPILER_HPP
