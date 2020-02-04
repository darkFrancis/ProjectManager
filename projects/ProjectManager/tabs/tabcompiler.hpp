/**
 * @file tabcompiler.hpp
 * @brief Description de la classe TabCompiler
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef TABCOMPILER_HPP
#define TABCOMPILER_HPP

    #include "tab.hpp"
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
     * @struct Command
     * @brief La structure Command défini une commande à appeler avec un QProcess
     *
     * Cette structure est utilisée pour préparer une file d'attente des commandes à
     * passer dans l'onglet TabCompiler.
     */
    struct Command
    {
        QString programm;/**< Nom du programme à appeler */
        QStringList params;/**< Liste des paramètres à passer au programme */
        QString dir;/**< Répertoire dans lequel exécuter le programme */
    };
    typedef struct Command Command;

    /**
     * @class TabCompiler
     * @brief La classe TabCompiler défini l'onglet de compilation.
     *
     * Elle permet avec de définir :
     * @li les options de compilation
     * @li les dossiers de build et de sortie
     * @li le mode de compilation : release (défini NDEBUG) ou debug (défini _DEBUG)
     *
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
            void updateStandardOutput();
            void updateStandardError();
            void endCmd(int exitCode, QProcess::ExitStatus exitStatus);
            void forceEnd();

        private slots:
            void on_toolButton_buildDir_clicked();
            void on_pushButton_sources_clicked();
            void on_pushButton_param_clicked();
            void on_pushButton_action_clicked();
            void on_pushButton_default_clicked();
            void on_pushButton_apply_clicked();

        private:
            Ui::TabCompiler *ui;/**< UI de la classe TabCompiler */

            // Actions
            QProcess* m_process;/**< Processus en cours */
            /** @addtogroup TABCOMPILER_ACTION
              * @{ */
            void action_build_run();
            void action_build();
            void action_run();
            void action_clean();
            void action_install();
            void action_uninstall();
            /** @} */

            // Commandes
            void send_cmd(QString cmd, QStringList param = QStringList(), QString dir = ".");
            void readProcess();
            void addCommand(QString cmd, QStringList param, QString dir);
            QList<Command> m_commands;/**< Liste des commandes à exécuter */
    };

#endif // TABCOMPILER_HPP
