/**
 * @file main.cpp
 * @brief Definition de la fonction principale
 * @author Dark Francis
 * @date 25/10/2020
 */
#include "MainWindow.hpp"

#include <QApplication>
#include <QFile>

#include "Logger.hpp"
#include "version.hpp"

void setStyle();

/**
 * @param argc Nombre d'arugments passés au programme
 * @param argv Arguments passés au programme
 * @return Code retour d'exécution.
 *
 * Fonction principale de l'application.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Log
    Logger logger;
    qLog->createLog("data/log/" + _APPLICATION_NAME_ + ".log", 10);
    qLog->info("Démarrage de l'application : " + _APPLICATION_NAME_);
    qLog->info("Version : " + _VERSION_);
#ifdef _DEBUG
    qLog->setLogLevel(Debug);
#else
    qLog->setLogLevel(Debug);
#endif

    // Style
    setStyle();

    // Exécution
    MainWindow w;
    w.show();
    int returnCode = a.exec(); // Bloquant

    // Fin d'exécution
    qLog->info("Fin de l'exécution");
    qLog->info("Code retour : " + QString::number(returnCode));
    return returnCode;
}

/**
 * Fonction de mise en place du style de l'application.
 */
void setStyle()
{
    // Set palette
    QPalette palette = qApp->palette();
    palette.setColor(QPalette::Window, QColor(53, 53, 53));
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Disabled, QPalette::WindowText, QColor(127, 127, 127));
    palette.setColor(QPalette::Base, QColor(42, 42, 42));
    palette.setColor(QPalette::AlternateBase, QColor(66, 66, 66));
    palette.setColor(QPalette::ToolTipBase, Qt::white);
    palette.setColor(QPalette::ToolTipText, QColor(53, 53, 53));
    palette.setColor(QPalette::Text, Qt::white);
    palette.setColor(QPalette::Disabled, QPalette::Text, QColor(127, 127, 127));
    palette.setColor(QPalette::Dark, QColor(35, 35, 35));
    palette.setColor(QPalette::Shadow, QColor(20, 20, 20));
    palette.setColor(QPalette::Button, QColor(53, 53, 53));
    palette.setColor(QPalette::ButtonText, Qt::white);
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(127, 127, 127));
    palette.setColor(QPalette::BrightText, Qt::red);
    palette.setColor(QPalette::Link, QColor(42, 130, 218));
    palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    palette.setColor(QPalette::Disabled, QPalette::Highlight, QColor(80, 80, 80));
    palette.setColor(QPalette::HighlightedText, Qt::white);
    palette.setColor(QPalette::Disabled, QPalette::HighlightedText, QColor(127, 127, 127));

    // Set style
    QFile styleFile(":/darkstyle/darkstyle.qss");
    if(styleFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qApp->setPalette(palette);
        qApp->setStyleSheet(QString::fromLatin1(styleFile.readAll()));
        styleFile.close();
    }
}
