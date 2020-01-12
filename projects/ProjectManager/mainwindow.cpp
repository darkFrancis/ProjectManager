#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QProcess>

#include "parser.hpp"
#include "context.hpp"
#include "newproject.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Project Manager");
    try
    {
        init();
        status("Initialisation terminée avec succès", STATUS_DEFAULT_TIMEOUT);
    }
    catch(QString msg)
    {
        status(msg);
        QMessageBox::critical(this,
                              QString("Erreur"),
                              msg);
    }
}

MainWindow::~MainWindow()
{
    saveInit();
    delete ui;
}

void MainWindow::init()
{
    QDir::setCurrent(qApp->applicationDirPath());
    if(!QFile::exists(INIT_FILE))
    {
        status("Génaration du fichier d'initialisation", STATUS_DEFAULT_TIMEOUT);
        createInit();
    }
    Parser* parser = Parser::Instance();
    if(parser->load(INIT_FILE))
    {
        // Init Window
        bool ok = true;
        int x = parser->get("x").toInt(&ok);if(!ok) x = INIT_X;
        int y = parser->get("y").toInt(&ok);if(!ok) y = INIT_Y;
        int w = parser->get("width").toInt(&ok);if(!ok) w = INIT_W;
        int h = parser->get("height").toInt(&ok);if(!ok) h = INIT_H;
        this->setGeometry(x, y, w, h);

        // Init Context
        Context* ctx = Context::Instance();
        ctx->setProject(parser->get("project"));
        ctx->setLastSearch(parser->get("last_search"));

        parser->close();
    }
    else
    {
        throw(QString("Erreur, impossible d'ouvrir le fichier d'initialisation"));
    }

    // Init Tab Widget
    m_tabWidget = new QTabWidget(this);
    Tab *tab_project = new TabProject();
    m_tabWidget->addTab(tab_project, "Configuration du projet");
    m_tablist.append(tab_project);
    Tab *tab_doxygen = new TabDoxygen();
    m_tabWidget->addTab(tab_doxygen, "Configuration Doxygen");
    m_tablist.append(tab_doxygen);
    Tab *tab_compiler = new TabCompiler();
    m_tabWidget->addTab(tab_compiler, "Configuration du compilateur");
    m_tablist.append(tab_compiler);
    Tab *tab_git = new TabGit();
    m_tabWidget->addTab(tab_git, "Git");
    m_tablist.append(tab_git);
    ui->centralWidget->layout()->addWidget(m_tabWidget);

    // Last Session
    if(QFile::exists(Context::Instance()->project()))
    {
        try
        {
            Context::Instance()->loadProject();
        }
        catch (QString msg)
        {

        }
    }
    else
    {
        m_tabWidget->setEnabled(true);
    }
}

void MainWindow::clean()
{
    for(int i = 0; i < m_tablist.length(); i++)
    {
        m_tablist[i]->clean();
    }
}

void MainWindow::createInit()
{
    QDir::setCurrent(qApp->applicationDirPath());
    QFile file(INIT_FILE);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        QTextStream stream(&file);
        // Window
        stream << "# Window" << endl;
        stream << "x=" << INIT_X << endl;
        stream << "y=" << INIT_Y << endl;
        stream << "width=" << INIT_W << endl;
        stream << "height=" << INIT_H << endl;
        stream << endl;
        // Project
        stream << "# Project" << endl;
        stream << "project=" << endl;
        stream << endl;
        // Last
        stream << "# Last" << endl;
        stream << "last_search=" << endl;
        file.close();
    }
    else
    {
        throw(QString("Impossible de créer le fichier d'initialisation"));
    }
}

void MainWindow::saveInit()
{
    QDir::setCurrent(qApp->applicationDirPath());
    QFile file(INIT_FILE);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        QTextStream stream(&file);
        // Window
        stream << "# Window" << endl;
        stream << "x=" << this->x() << endl;
        stream << "y=" << this->y() << endl;
        stream << "width=" << this->width() << endl;
        stream << "height=" << this->height() << endl;
        stream << endl;
        // Project
        stream << "# Project" << endl;
        stream << "project=" << Context::Instance()->project() << endl;
        stream << endl;
        // Last
        stream << "# Last" << endl;
        stream << "last_search=" << Context::Instance()->lastSearch() << endl;
        file.close();
    }
    else
    {
        throw(QString("Impossible de sauvegarder le fichier d'initialisation"));
    }
}

void MainWindow::status(QString msg, int timeout)
{
    ui->statusBar->showMessage(msg, timeout * 1000);
}

void MainWindow::on_actionNouveau_triggered()
{
    Context* ctx = Context::Instance();
    if(ctx->isOpen())
    {
        QMessageBox::StandardButton res;
        res = QMessageBox::question(this, "Attention", "Attention ! Si un nouveau fichier est ouvert, tout ce qui n'est pas enregistré sera supprimé.\nVoulez vous continuer ?");
        if(res == QMessageBox::No)
        {
            return;
        }
    }
    NewProject* p = new NewProject(this);
    p->show();
}

void MainWindow::loadProject(QString file_name)
{
    Context::Instance()->setProject(file_name);
    clean();
    Context::Instance()->loadProject();
    for(int i = 0; i < m_tablist.length(); i++)
    {
        m_tablist[i]->init();
    }
}

void MainWindow::on_actionOuvrir_triggered()
{

}

void MainWindow::on_actionEnregistrer_triggered()
{

}

void MainWindow::on_actionQuitter_triggered()
{

}

void MainWindow::on_actionOptions_triggered()
{

}

void MainWindow::on_actionA_propos_triggered()
{

}

void MainWindow::on_actionA_propos_de_Qt_triggered()
{
    QMessageBox::aboutQt(this, "A propos de Qt");
}
