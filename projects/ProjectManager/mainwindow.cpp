#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "parser.hpp"

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

        // Init Tab Widget
        m_tabWidget = new QTabWidget(this);
        ui->centralWidget->layout()->addWidget(m_tabWidget);
    }
    else
    {
        throw(QString("Erreur, impossible d'ouvrir le fichier d'initialisation"));
    }
}

void MainWindow::createInit()
{
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
        file.close();
    }
    else
    {
        throw(QString("Impossible de créer le fichier d'initialisation"));
    }
}

void MainWindow::saveInit()
{
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

void MainWindow::openFileClicked()
{
    status("OK");
}
