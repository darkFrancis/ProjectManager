/**
 * @file command.hpp
 * @brief Définition de la structure Command
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef COMMAND_HPP
#define COMMAND_HPP

    #include <QString>
    #include <QStringList>

    /**
     * @struct Command
     * @brief La structure Command défini une commande à appeler avec un QProcess
     *
     * Cette structure est utilisée pour préparer une file d'attente des commandes à
     * passer aux classes de gestion de processus.@n
     * Header : command.hpp.
     */
    struct Command
    {
        QString programm;/**< Nom du programme à appeler */
        QStringList params;/**< Liste des paramètres à passer au programme */
        QString dir;/**< Répertoire dans lequel exécuter le programme */
    };
    typedef struct Command Command;

#endif // COMMAND_HPP
