/**
 * @file main.cpp
 * @brief Fonction principale main
 * @author Dark Francis
 * @date 21/12/2019
 */
#include "mainwindow.hpp"
#include "settings/logger.hpp"
#include <QApplication>

/**
 * @param argc Le nombre d'argument passés au programme
 * @param argv Les arguments passés au programme (l'argument 0 est le nom du programme)
 * @return Code retour de l'exécution du programme
 *
 * Ceci est la fonction principale du programme ProjectManager.@n
 * Elle initialise tout d'abord les fichiers de log.@n
 * Elle créé un objet QApplication en lui passant ses paramètres @c argc et @c argv.@n
 * Elle instancie une fenêtre de la classe MainWindow.@n
 * Enfin elle retourne le résultat de la fonction exec() de l'objet QApplication créé.
 */
int main(int argc, char *argv[])
{
    create_logger();
    logger("--- MAIN BEGINNING ---");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
