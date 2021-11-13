/**
 * @file DoxygenFilesHelper.cpp
 * @brief Sources de la fenêtre de gestion des fichiers Doxygen
 * @author Dark Francis
 * @date 27/02/2021
 */
#include "gui/tabs/doxygen/DoxygenFilesHelper.hpp"
#include "ui_DoxygenFilesHelper.h"

#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QProcess>
#include <QTextStream>

#include "tools/Context.hpp"
#include "Logger/Logger.hpp"

#define INDEX_FILE_NAME "index.html"
#define DEFAULT_DOC_DIR "doc"

/**
 * @param docDir Dossier principal de documentation
 * @param parent QWidget parent
 *
 * Constructeur de la classe DoxygenFilesHelper.
 */
DoxygenFilesHelper::DoxygenFilesHelper(const QString& docDir, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DoxygenFilesHelper),
    m_docDir(QDir(qCtx->projectDir()).absoluteFilePath(docDir))
{
    ui->setupUi(this);

    for(const QString& projectFile : qCtx->subProjects())
    {
        QFileInfo info(projectFile);
        QLabel* label = new QLabel(info.baseName());
        QLineEdit* line = new QLineEdit;
        line->setText(qCtx->projectDescription(projectFile));
        ui->formLayout_descriptions->addRow(label, line);
        m_labels << label;
        m_lines << line;
    }
}

/**
 * Destructeur de la classe DoxygenFilesHelper.
 */
DoxygenFilesHelper::~DoxygenFilesHelper()
{
    delete ui;
}

/**
 * Ce connecteur est activé lors d'un clic souris par l'utilisateur sur le
 * bouton "Générer" des templates.@n
 * Exécute les commandes de génération des templates Doxygen dans le dossier
 * spécifié dans l'instance Settings à partir du dossier de configuration
 * de Doxygen.
 * @sa Context::doxygenTemplateDir().
 */
void DoxygenFilesHelper::on_pushButton_generateTemplates_clicked()
{
    QFileInfo infos(qCtx->doxyfile());
    QString dir = infos.absoluteDir().absolutePath();
    if(!dir.endsWith('/')) dir.append('/');

    try
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        // Create Dir
        dir += qCtx->doxygenTemplateDir();
        if(!dir.endsWith('/')) dir.append('/');
        command("mkdir " + dir, ".");
        command("mkdir rtf", dir);
        command("mkdir html", dir);
        command("mkdir latex", dir);
        command("doxygen -l layout.xml", dir);
        command("doxygen -w rtf styleSheetFile", dir + "rtf");
        command("doxygen -e rtf extensionsFile", dir + "rtf");
        command("doxygen -w html header.html footer.html stylesheet.css", dir + "html");
        command("doxygen -w latex header.html footer.html stylesheet.css", dir + "latex");
        QApplication::restoreOverrideCursor();
        QMessageBox::information(this,
                                 "Création des templates",
                                 "Les templates ont été créés dans le dossier\n" + dir);
    }
    catch(QString msg)
    {
        QMessageBox::critical(this, "Erreur", msg);
    }
}

/**
 * Ce connecteur est activé lors d'un clic souris par l'utilisateur sur le
 * bouton "Ouvrir dossier" des templates.@n
 * Ouvre le dossier des templates.
 */
void DoxygenFilesHelper::on_pushButton_openDir_clicked()
{
    try
    {
#ifdef Q_OS_WIN32
        command("explorer .", QDir(qCtx->projectDir()).absoluteFilePath(qCtx->projectHiddenDirName()));
#elif defined(Q_OS_LINUX)
        command("browse .", QDir(qCtx->projectDir()).absoluteFilePath(qCtx->projectHiddenDirName()));
#endif
    }
    catch(QString msg)
    {
        QMessageBox::critical(this, "Erreur", msg);
    }
}

/**
 * Ce connecteur est activé lors d'un clic souris par l'utilisateur sur le
 * bouton "Ouvrir dossier" des templates.@n
 * Ouvre le dossier des templates.
 */
void DoxygenFilesHelper::on_pushButton_generateIndex_clicked()
{
    // Enregistrement dans le context
    for(int i = 0; i < m_lines.length(); i++)
    {
        QString subProject = m_labels.at(i)->text();
        QString description = m_lines.at(i)->text();
        for(const QString& projectFile : qCtx->subProjects())
        {
            if(QFileInfo(projectFile).baseName() == subProject)
            {
                qCtx->setProjectDescription(projectFile, description);
                break;
            }
        }
    }
    qCtx->saveSubProjects();

    // Ecriture de l'index
    QFile file(QDir(m_docDir).absoluteFilePath(INDEX_FILE_NAME));
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream.setCodec("UTF-8");

        // Entête
        QString projectName = QDir(qCtx->projectDir()).dirName();
        QString text =
        "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">"
        "\n<html xmlns=\"http://www.w3.org/1999/xhtml\">"
        "\n<head>"
        "\n  <meta http-equiv=\"Content-Type\" content=\"text/xhtml;charset=UTF-8\"/>"
        "\n  <title>" + projectName + " : Documentation</title>"
        "\n  <link href=\"../.projectmanager/html/stylesheet.css\" rel=\"stylesheet\" type=\"text/css\" />"
        "\n</head>"
        "\n<body>"
        "\n  <div>"
        "\n    <div id=\"titlearea\">"
        "\n      <table cellspacing=\"0\" cellpadding=\"0\">"
        "\n        <tbody>"
        "\n          <tr style=\"height: 56px;\">"
        "\n            <td id=\"projectalign\" style=\"padding-left: 0.5em;\">"
        "\n              <div id=\"projectname\">" + projectName + "</div>"
        "\n            </td>"
        "\n          </tr>"
        "\n        </tbody>"
        "\n      </table>"
        "\n    </div>"
        "\n  </div>"
        "\n  <div class=\"header\">"
        "\n    <div class=\"headertitle\">"
        "\n      <div class=\"title\">Index de " + projectName + "</div>"
        "\n    </div>"
        "\n  </div>"
        "\n  <div class=\"contents\">"
        "\n    <div class=\"textblock\">"
        "\n      <p>Liste des sous-projets :"
        "\n        <ul>";

        for(int i = 0; i < m_lines.length(); i++)
        {
            QString subProject = m_labels.at(i)->text();
            QString description = m_lines.at(i)->text();
            text += "\n          <li><a href=\"" + subProject + "/index.html\">"
                    + subProject + "</a> : " + description + "</li>";
        }

        // Fin
        text +=
        "\n        </ul>"
        "\n      </p>"
        "\n    </div>"
        "\n  </div>"
        "\n  <hr/>"
        "\n</body>"
        "\n</html>";

        stream << text;
        file.close();
    }
    else
    {
        QMessageBox::critical(this,
                              "Erreur",
                              "Impossible d'ouvrir le fichier " + QFileInfo(file).absoluteFilePath() + " !");
    }
}

/**
 * Ce connecteur est activé lors d'un clic souris par l'utilisateur sur le
 * bouton "Ouvrir" de l'index.@n
 * Ouvre la documentation d'index.
 */
void DoxygenFilesHelper::on_pushButton_openIndex_clicked()
{
    try
    {
#ifdef Q_OS_WIN32
        command("start " + QString(INDEX_FILE_NAME), m_docDir);
#elif defined(Q_OS_LINUX)
        command("browse " + QString(INDEX_FILE_NAME), m_docDir);
#endif
    }
    catch(QString msg)
    {
        QMessageBox::critical(this, "Erreur", msg);
    }
}

/**
 * @param cmd Commande à exécuter
 * @param workingDir Dossier de travail
 *
 * Cette fonction exécute la commande @c cmd dans le dossier @c workingDir
 * à l'aide d'un objet QProcess.
 */
void DoxygenFilesHelper::command(const QString& cmd, const QString& workingDir)
{
    qLog->debug("Doxygen - Commande (" + workingDir + ") : " + cmd);
    QProcess process;
    process.setWorkingDirectory(workingDir);
    process.start(cmd);
    if(!process.waitForFinished())
    {
        throw QString("Erreur pour la commande : " + cmd + " [" + workingDir + "]");
    }
}
