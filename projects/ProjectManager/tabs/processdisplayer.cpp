#include "processdisplayer.hpp"
#include "logger.hpp"
#include "settings.hpp"
#include <QShortcut>

/**
 * @param parent QWidget parent de ce widget
 *
 * Constructeur de la classe ProcessDisplayer.@n
 * Ce constructeur défini le style de ce widget :
 * @li Fond noir (rgb:0,0,0)
 * @li Texte blanc (rgb:255,255,255)
 * @li Mode lecture seule
 *
 * Il ajoute les raccourcis clavier suivant :
 * @li &lt;Ctrl+X> pour faire appel à la fonction TabCompiler::forceEnd
 * @li &lt;Ctrl+E> pour effacer l'affichage de l'onglet
 */
ProcessDisplayer::ProcessDisplayer(QWidget *parent) :
    QTextEdit(parent)
{
    this->setStyleSheet("background-color: rgb(0, 0, 0);\n"
                        "color: rgb(255, 255, 255);");
    this->setReadOnly(true);
    m_process = nullptr;

    QShortcut* shortcut_terminate = new QShortcut(QKeySequence("Ctrl+X"), this);
    connect(shortcut_terminate, &QShortcut::activated, this, &ProcessDisplayer::forceEnd);
    QShortcut* shortcut_clear = new QShortcut(QKeySequence("Ctrl+E"), this);
    connect(shortcut_clear, &QShortcut::activated, this, &QTextEdit::clear);
}

/**
 * Destructeur de la classe ProcessDisplayer.@n
 * Nettoie la liste ProcessDisplayer::m_commands et détruit le processus
 * ProcessDisplayer::m_process avec le connecteur ProcessDisplayer::forceEnd.
 */
ProcessDisplayer::~ProcessDisplayer()
{
    forceEnd();
    m_commands.clear();
}

/**
 * @param cmd Commande à exécuter
 * @param param Arguments à passer à la commande
 * @param dir Répertoire dans lequel exécuter la commande
 *
 * Si un processus est déjà en cours, ajoute la commande à exécuter dans la
 * file d'attente via la fonction ProcessDisplayer::addCommand. Sinon, prépare le
 * processus et demande son exécution en le connectant comme suit :
 * @li Sortie standard -> TabCompiler::updateStandardOutput
 * @li Erreur standard -> TabCompiler::updateStandardError
 * @li Fin d'exécution -> TabCompiler::endCmd
 *
 * Voir ProcessDisplayer::m_process.
 */
void ProcessDisplayer::send_cmd(QString cmd, QStringList param /*= QStringList()*/, QString dir /*= "."*/)
{
    logger("    cmd: " + cmd + " " + param.join(' '));
    if(m_process == nullptr)
    {
        m_process = new QProcess(this);
        this->append("> " + cmd + " " + param.join(' '));
        m_process->setWorkingDirectory(dir);
        m_process->start(cmd, param);
        connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(updateStandardOutput()));
        connect(m_process, SIGNAL(readyReadStandardError()), this, SLOT(updateStandardError()));
        connect(m_process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(endCmd(int,QProcess::ExitStatus)));
    }
    else
    {
        addCommand(cmd, param, dir);
    }
}

/**
 * Ce connecteur est activé lorsqu'il est possible de lire la sortie standard
 * du processus en cours. La lecture de sortie de processus est cablée sur la
 * sortie standard et la fonction ProcessDisplayer::readProcess est appelée.@n
 * Voir ProcessDisplayer::m_process.
 */
void ProcessDisplayer::updateStandardOutput()
{
    m_process->setReadChannel(QProcess::StandardOutput);
    readProcess();
}

/**
 * Ce connecteur est activé lorsqu'il est possible de lire l'erreur standard
 * du processus en cours. La lecture de sortie de processus est cablée sur
 * l'erreur standard et la fonction ProcessDisplayer::readProcess est appelée.@n
 * Voir ProcessDisplayer::m_process.
 */
void ProcessDisplayer::updateStandardError()
{
    m_process->setReadChannel(QProcess::StandardError);
    readProcess();
}

/**
 * Lecture de la sortie du processus en cours.@n
 * Utilise un format HTML pour afficher la sortie/erreur du processus en cours
 * avec un texte coloré selon le cas (voir Settings::m_color_normal et
 * Settings::m_color_error).@n
 * Voir ProcessDisplayer::m_process.
 */
void ProcessDisplayer::readProcess()
{
    QString to_write = "";
    to_write += "<p style=\"color:";
    to_write += (m_process->readChannel() == QProcess::StandardOutput ? Settings::Instance()->colorNormal() : Settings::Instance()->colorError());
    to_write += "\">";

    QString line = "";
    bool first = true;
    while(m_process->canReadLine())
    {
        if(first)
            first = false;
        else
            to_write += "<br/>";
        line = m_process->readLine();
        // Format
        line = line.left(line.length()-1);
        line = line.replace('<', "&lt;").replace('>', "&gt;").replace(' ', "&nbsp;");
        to_write.append(line);
    }
    to_write += "</p>";
    this->append(to_write);
}

/**
 * @param exitCode Code retour de l'exécution du processus
 * @param exitStatus Status final du processus
 *
 * Ce connecteur est activé lorsque le processus en cours se termine.@n
 * Utilise un format HTML pour afficher le résultat du processus en cours
 * avec un texte coloré selon le cas (voir Settings::m_color_success et
 * Settings::m_color_error). Si il reste des commandes à exécuter dans
 * la fie d'attente, exécute la suivante à l'aide de la fonction
 * ProcessDisplayer::send_cmd. Sinon, émet le signal ProcessDisplayer::end.@n
 * Voir ProcessDisplayer::m_process, Command.
 */
void ProcessDisplayer::endCmd(int exitCode, QProcess::ExitStatus exitStatus)
{
    logger("    end_cmd: " + QString::number(exitCode));
    Settings* setting = Settings::Instance();
    bool ok = exitStatus == QProcess::NormalExit;
    QString result = "<p style=\"color:";
    result += (ok ? setting->colorSuccess() : setting->colorError());
    result += "\">";
    result += (ok ? "OK" : "Crash");
    result += " (exit_code=" + QString::number(exitCode) + ")";
    result += "<br/></p>";
    this->append(result);
    delete m_process;
    m_process = nullptr;

    // Next command
    if(m_commands.length() > 0)
    {
        Command cmd = m_commands.takeFirst();
        send_cmd(cmd.programm, cmd.params, cmd.dir);
    }
    else
    {
        emit end();
    }
}

/**
 * @param cmd Nom de la commande
 * @param param Arguments de la commande
 * @param dir Répertoire dans lequel exécuter la commande
 *
 * Ajoute une commande dans la file d'attente des commandes, ProcessDisplayer::m_commands.@n
 * Un objet Command est créé avec les arguments de cette fonction avant d'être
 * ajouté à cette liste. Cette commande sera exécutée pluus tard par la fonction
 * ProcessDisplayer::send_cmd.@n
 * Voir ProcessDisplayer::endCmd.
 */
void ProcessDisplayer::addCommand(QString cmd, QStringList param, QString dir)
{
    Command command;
    command.programm = cmd;
    command.params = param;
    command.dir = dir;
    m_commands.append(command);
}

/**
 * Tue le processus en cours.@n
 * Ceci entraine un crash du processus si celui-ci n'était pas terminé.
 * Le connecteur ProcessDisplayer::endCmd est donc appelé.@n
 * Voir ProcessDisplayer::m_process.
 */
void ProcessDisplayer::forceEnd()
{
    logger(__PRETTY_FUNCTION__);
    m_commands.clear();
    if(m_process) m_process->kill();
}
