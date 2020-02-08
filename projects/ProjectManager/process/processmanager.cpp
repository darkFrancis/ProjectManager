#include "processmanager.hpp"
#include "logger.hpp"

/**
 * @param parent QObject parent de cete classe
 *
 * Constructeur de la classe ProcessManager.@n
 *
 */
ProcessManager::ProcessManager(QObject *parent) : QObject(parent)
{
    logger(__PRETTY_FUNCTION__);
}

/**
 * Destructeur de la classe ProcessManager.@n
 * Détruit le processus ProcessManager::m_process avec le connecteur ProcessManager::forceEnd.
 */
ProcessManager::~ProcessManager()
{
    forceEnd();
}

/**
 * @param cmd Commande à exécuter
 * @param param Arguments à passer à la commande
 * @param dir Répertoire dans lequel exécuter la commande
 *
 * Si un processus est déjà en cours, renvoie @c false. Sinon, prépare le
 * processus et demande son exécution en le connectant comme suit avant de
 * renvoyer @c true :
 * @li Sortie standard -> ProcessManager::updateStandardOutput
 * @li Erreur standard -> ProcessManager::updateStandardError
 * @li Fin d'exécution -> ProcessManager::endCmd
 *
 * Voir ProcessManager::m_process.
 */
bool ProcessManager::send_cmd(QString cmd, QStringList param /*= QStringList()*/, QString dir /*= "."*/)
{
    logger("    cmd: " + cmd + " " + param.join(' '));
    if(m_process == nullptr)
    {
        m_process = new QProcess(this);
        m_process->setWorkingDirectory(dir);
        m_process->start(cmd, param);
        connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(updateStandardOutput()));
        connect(m_process, SIGNAL(readyReadStandardError()), this, SLOT(updateStandardError()));
        connect(m_process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(endCmd(int,QProcess::ExitStatus)));
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Ce connecteur est activé lorsqu'il est possible de lire la sortie standard
 * du processus en cours. La lecture de sortie de processus est cablée sur la
 * sortie standard et la fonction ProcessManager::readProcess est appelée.@n
 * Voir ProcessManager::m_process.
 */
void ProcessManager::updateStandardOutput()
{
    m_process->setReadChannel(QProcess::StandardOutput);
    readProcess();
}

/**
 * Ce connecteur est activé lorsqu'il est possible de lire l'erreur standard
 * du processus en cours. La lecture de sortie de processus est cablée sur
 * l'erreur standard et la fonction ProcessManager::readProcess est appelée.@n
 * Voir ProcessManager::m_process.
 */
void ProcessManager::updateStandardError()
{
    m_process->setReadChannel(QProcess::StandardError);
    readProcess();
}

/**
 * Lecture de la sortie du processus en cours.@n
 * La sortie standard est enregistrée dans l'attribut ProcessManager::m_output
 * et l'erreur standard est enregistrée dans l'attribut ProcessManager::m_error.
 * Ces attributs sont accessible avec les méthodes GET de cette classe.@n
 * Voir ProcessManager::m_process, ProcessManager::getStandardOutput,
 * ProcessManager::getStandardError.
 */
void ProcessManager::readProcess()
{
    QString line = "";
    while(m_process->canReadLine())
    {
        line = m_process->readLine();
        // Format
        line = line.left(line.length()-1);
        if(m_process->readChannel() == QProcess::StandardOutput)
        {
            m_output.append(line);
        }
        else
        {
            m_error.append(line);
        }
    }
}

/**
 * @param exitCode Code retour de l'exécution du processus
 * @param exitStatus Status final du processus
 *
 * Ce connecteur est activé lorsque le processus en cours se termine.@n
 * Si il reste des commandes à exécuter dans
 * la fie d'attente, exécute la suivante à l'aide de la fonction
 * ProcessManager::send_cmd. Sinon, émet le signal ProcessManager::end.@n
 * Voir ProcessManager::m_process, Command.
 */
void ProcessManager::endCmd(int exitCode, QProcess::ExitStatus exitStatus)
{
    logger("    end_cmd: " + QString::number(exitCode));
    delete m_process;
    m_process = nullptr;

    emit end(exitStatus == QProcess::NormalExit && exitCode == 0);
}

/**
 * Tue le processus en cours.@n
 * Ceci entraine un crash du processus si celui-ci n'était pas terminé.
 * Le connecteur ProcessManager::endCmd est donc appelé.@n
 * Voir ProcessManager::m_process.
 */
void ProcessManager::forceEnd()
{
    logger(__PRETTY_FUNCTION__);
    if(m_process) m_process->kill();
}
