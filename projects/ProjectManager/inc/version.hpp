/**
 * @file version.hpp
 * @brief Définition des variables de versionning
 * @author Dark Francis
 * @date 25/10/2020
 */
#ifndef VERSION_HPP
#define VERSION_HPP

    #include <QString>

    const QString _APPLICATION_NAME_    = D_APP_NAME; /*< Nom de l'application */
    const QString _VERSION_             = D_APP_VERSION; /*< Version de l'application */

    /* ======================================================================================================== */

    /**
     * @mainpage Documentation de ProjectManager
     * @author Dark Francis
     * @date 26/01/2020
     *
     * ProjectManager est un outil de gestion de projet.@n
     * Cet outil se base sur les outils suivant :
     * @li Doxygen : permet de générer une documentation de code au format
     * HTML, LaTeX ou autre et des graphique avec Dot.
     * @li Git : permet la gestion des sources et du versionning.
     */

    /**
     * Version 1.1 - 27/02/2021
     *  - Gestion des chemin relatifs
     *  - Ajout système de génération d'index de documentation
     *  - Corrections mineures
     */

    /**
     * Version 1.0 - 04/11/2020
     *  - Réorganisation complète de l'IHM
     *  - 3 onglets : projetS, doxygen, git
     *  - Simplification de l'IHM
     *  - Ajout gestion versionning ProjectManager
     *  - Ajout de documentation
     */

    /**
     * Version 0.4 - 22/03/2020
     *  - Ajout système de build pour onglet compilateur
     *  - Ajout de documentation
     */

    /**
     * Version 0.3 - 01/03/2020
     *  - Réorganisation projet
     *  - Ajout fonctions avancées git : gestion branches, gestion conflit (exp)
     *  - Ajout de documentation
     */

    /**
     * Version 0.2 - 06/02/2020
     *  - Stabilisation des parser
     *  - Ajout de documentation
     */

    /**
     * Version 0.1 - 26/01/2020
     *  - Première version stable
     *  - 4 onglets : projet, git, doxygen et compilateur
     */


    /* ======================================================================================================== */

    // TIMESTAMP COMPILE
    #define ____BUILD_YEAR_CH0 (__DATE__[ 7]) /**< 1er caractère de l'année de compilation */
    #define ____BUILD_YEAR_CH1 (__DATE__[ 8]) /**< 2e caractère de l'année de compilation */
    #define ____BUILD_YEAR_CH2 (__DATE__[ 9]) /**< 3e caractère de l'année de compilation */
    #define ____BUILD_YEAR_CH3 (__DATE__[10]) /**< 4e caractère de l'année de compilation */
    #define ____BUILD_MONTH_IS_JAN (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n') /**< Booléen : mois de compilation = Janvier */
    #define ____BUILD_MONTH_IS_FEB (__DATE__[0] == 'F') /**< Booléen : mois de compilation = Février */
    #define ____BUILD_MONTH_IS_MAR (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r') /**< Booléen : mois de compilation = Mars */
    #define ____BUILD_MONTH_IS_APR (__DATE__[0] == 'A' && __DATE__[1] == 'p') /**< Booléen : mois de compilation = Avril */
    #define ____BUILD_MONTH_IS_MAY (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y') /**< Booléen : mois de compilation = Mai */
    #define ____BUILD_MONTH_IS_JUN (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n') /**< Booléen : mois de compilation = Juin */
    #define ____BUILD_MONTH_IS_JUL (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l') /**< Booléen : mois de compilation = Juillet */
    #define ____BUILD_MONTH_IS_AUG (__DATE__[0] == 'A' && __DATE__[1] == 'u') /**< Booléen : mois de compilation = Août */
    #define ____BUILD_MONTH_IS_SEP (__DATE__[0] == 'S') /**< Booléen : mois de compilation = Septembre */
    #define ____BUILD_MONTH_IS_OCT (__DATE__[0] == 'O') /**< Booléen : mois de compilation = Octobre */
    #define ____BUILD_MONTH_IS_NOV (__DATE__[0] == 'N') /**< Booléen : mois de compilation = Novembre */
    #define ____BUILD_MONTH_IS_DEC (__DATE__[0] == 'D') /**< Booléen : mois de compilation = Décembre */
    #define ____BUILD_MONTH_CH0 \
        ((____BUILD_MONTH_IS_OCT || ____BUILD_MONTH_IS_NOV || ____BUILD_MONTH_IS_DEC) ? '1' : '0') /**< 1er caractère du mois de compilation */
    #define ____BUILD_MONTH_CH1 \
        ( \
            (____BUILD_MONTH_IS_JAN) ? '1' : \
            (____BUILD_MONTH_IS_FEB) ? '2' : \
            (____BUILD_MONTH_IS_MAR) ? '3' : \
            (____BUILD_MONTH_IS_APR) ? '4' : \
            (____BUILD_MONTH_IS_MAY) ? '5' : \
            (____BUILD_MONTH_IS_JUN) ? '6' : \
            (____BUILD_MONTH_IS_JUL) ? '7' : \
            (____BUILD_MONTH_IS_AUG) ? '8' : \
            (____BUILD_MONTH_IS_SEP) ? '9' : \
            (____BUILD_MONTH_IS_OCT) ? '0' : \
            (____BUILD_MONTH_IS_NOV) ? '1' : \
            (____BUILD_MONTH_IS_DEC) ? '2' : \
            /* error default */        '?' \
        ) /**< 2e caractère du mois de compilation */
    #define D_BUILD_DAY     ((__DATE__[4] >= '0') ? (__DATE__[4]) : '0') + __DATE__[ 5] /**< Jour de compilation */
    #define D_BUILD_MONTH   ____BUILD_MONTH_CH0 + ____BUILD_MONTH_CH1 /**< Mois de compilation */
    #define D_BUILD_YEAR    __DATE__[7] + __DATE__[8] + __DATE__[9] + __DATE__[10] /**< Année de compilation */
    #define D_BUILD_DATE    D_BUILD_YEAR + D_BUILD_MONTH + D_BUILD_DAY /**< Date de compilation */
    #define D_BUILD_TIME    __TIME__[0] + __TIME__[1] + __TIME__[3] + __TIME__[4] + __TIME__[6] + __TIME__[7] /**< Horaire de compilation */

    /* ======================================================================================================== */

    /**
     * @namespace Ui
     * @brief Namespece QT
     *
     * Le namespace Ui permet de définir les objets graphiques construit à
     * partir du designer de QtCreator.
     */

    /**
     * @class QMainWindow
     * @brief Classe QT
     *
     * La classe QMainWindow définie la base des fenêtres principales fournie
     * par l'API QT.
     * @sa Ui.
     */

    /**
     * @class QWidget
     * @brief Classe QT
     *
     * La classe QWidget définie la base des widgets fournis par l'API QT.
     * @sa Ui.
     */

#endif // VERSION_HPP
