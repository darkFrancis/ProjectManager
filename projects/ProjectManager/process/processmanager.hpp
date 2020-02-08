/**
 * @file processmanager.hpp
 * @brief Définition de la classe ProcessManager
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef PROCESSMANAGER_HPP
#define PROCESSMANAGER_HPP

    #include <QObject>
    #include <QProcess>

    #include "command.hpp"

    /**
     * La classe ProcessManager hérite de la classe Qt QObject.@n
     * Ce widget permet d'exécuter des commandes et de récupérer leur sortie standard
     * et erreur standard sous forme de chaines de caractères.@n
     * Voir Command.@n
     * Header : processmanager.hpp.
     */
    class ProcessManager : public QObject
    {
        Q_OBJECT

        public:
            ProcessManager(QObject *parent = nullptr);
            ~ProcessManager();
            bool send_cmd(QString cmd, QStringList param = QStringList(), QString dir = ".");
            QString getStandardOutput(){return m_output;}/**< GET : ProcessManager::m_output */
            QString getStandardError(){return m_error;}/**< GET : ProcessManager::m_error */

        signals:
            void end(bool success);

        public slots:
            void updateStandardOutput();
            void updateStandardError();
            void endCmd(int exitCode, QProcess::ExitStatus exitStatus);
            void forceEnd();

        private:
            QProcess* m_process;/**< Unique processus en cours dont la sortie est affichée */
            Command m_command;/**< Commande à exécuter */
            QString m_output;/**< Résultat de la sortie standard */
            QString m_error;/**< Résultat de l'erreur standard */
            void readProcess();
    };

#endif // PROCESSMANAGER_HPP
