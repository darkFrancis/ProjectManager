/**
 * @file processdisplayer.hpp
 * @brief Définition de la classe ProcessDisplayer
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef PROCESSDISPLAYER_HPP
#define PROCESSDISPLAYER_HPP

    #include <QTextEdit>
    #include <QProcess>

    #include "command.hpp"

    /**
     * @class ProcessDisplayer
     * @brief La classe ProcessDisplayer permet d'exécuter des commande et afficher leur sortie
     * en temps réel
     *
     * La classe ProcessDisplayer hérite de la classe Qt QTextEdit.@n
     * Ce widget permet d'exécuter des commandes et affiche la sortie standard et
     * l'erreur standard. Les couleurs d'affichage peuvent être configurées dans
     * les options.@n
     * Voir Settings, SettingsWindow, Command.@n
     * Header : processdisplayer.hpp.
     */
    class ProcessDisplayer : public QTextEdit
    {
        Q_OBJECT

        public:
            ProcessDisplayer(QWidget *parent = nullptr);
            ~ProcessDisplayer();
            void send_cmd(QString cmd, QStringList param = QStringList(), QString dir = ".");

        public slots:
            void updateStandardOutput();
            void updateStandardError();
            void endCmd(int exitCode, QProcess::ExitStatus exitStatus);
            void forceEnd();

        signals:
            void end();/**< Ce signal est émit lorsque toutes les commandes de la liste ProcessDisplayer ont été exécutées */

        private:
            QProcess* m_process;/**< Unique processus en cours dont la sortie est affichée */
            QList<Command> m_commands;/**< Liste des commandes à exécuter */
            void readProcess();
            void addCommand(QString cmd, QStringList param, QString dir);
    };

#endif // PROCESSDISPLAYER_HPP
