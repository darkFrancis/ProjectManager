/**
 * @file build.hpp
 * @brief Définition des variables de build
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef BUILD_HPP
#define BUILD_HPP

    #define BUILD_YEAR_CH0 (__DATE__[ 7])/**< 1er chiffre de l'année */
    #define BUILD_YEAR_CH1 (__DATE__[ 8])/**< 2e chiffre de l'année */
    #define BUILD_YEAR_CH2 (__DATE__[ 9])/**< 3e chiffre de l'année */
    #define BUILD_YEAR_CH3 (__DATE__[10])/**< 4e chiffre de l'année */
    #define BUILD_MONTH_IS_JAN (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')/**< Booléen mois de Janvier */
    #define BUILD_MONTH_IS_FEB (__DATE__[0] == 'F')/**< Booléen mois de Fevrier */
    #define BUILD_MONTH_IS_MAR (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')/**< Booléen mois de Mars */
    #define BUILD_MONTH_IS_APR (__DATE__[0] == 'A' && __DATE__[1] == 'p')/**< Booléen mois de Avril */
    #define BUILD_MONTH_IS_MAY (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')/**< Booléen mois de Mai */
    #define BUILD_MONTH_IS_JUN (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')/**< Booléen mois de Juin */
    #define BUILD_MONTH_IS_JUL (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')/**< Booléen mois de Juillet */
    #define BUILD_MONTH_IS_AUG (__DATE__[0] == 'A' && __DATE__[1] == 'u')/**< Booléen mois de Août */
    #define BUILD_MONTH_IS_SEP (__DATE__[0] == 'S')/**< Booléen mois de Septembre */
    #define BUILD_MONTH_IS_OCT (__DATE__[0] == 'O')/**< Booléen mois de Octobre */
    #define BUILD_MONTH_IS_NOV (__DATE__[0] == 'N')/**< Booléen mois de Novembre */
    #define BUILD_MONTH_IS_DEC (__DATE__[0] == 'D')/**< Booléen mois de Décembre */
    #define BUILD_MONTH_CH0 \
        ((BUILD_MONTH_IS_OCT || BUILD_MONTH_IS_NOV || BUILD_MONTH_IS_DEC) ? '1' : '0')/**< 1er chiffre du mois */
    #define BUILD_MONTH_CH1 \
        ( \
            (BUILD_MONTH_IS_JAN) ? '1' : \
            (BUILD_MONTH_IS_FEB) ? '2' : \
            (BUILD_MONTH_IS_MAR) ? '3' : \
            (BUILD_MONTH_IS_APR) ? '4' : \
            (BUILD_MONTH_IS_MAY) ? '5' : \
            (BUILD_MONTH_IS_JUN) ? '6' : \
            (BUILD_MONTH_IS_JUL) ? '7' : \
            (BUILD_MONTH_IS_AUG) ? '8' : \
            (BUILD_MONTH_IS_SEP) ? '9' : \
            (BUILD_MONTH_IS_OCT) ? '0' : \
            (BUILD_MONTH_IS_NOV) ? '1' : \
            (BUILD_MONTH_IS_DEC) ? '2' : \
            /* error default */    '?' \
        )/**< 2e chiffre du mois */
    #define BUILD_DAY_CH0 ((__DATE__[4] >= '0') ? (__DATE__[4]) : '0')/**< 1er chiffre du jour */
    #define BUILD_DAY_CH1 (__DATE__[ 5])/**< 2e chiffre du jour */
    #define BUILD_DATE QString(BUILD_DAY_CH0)+BUILD_DAY_CH1+"/"+BUILD_MONTH_CH0+BUILD_MONTH_CH1+"/"+BUILD_YEAR_CH0+BUILD_YEAR_CH1+BUILD_YEAR_CH2+BUILD_YEAR_CH3/**< Date au format DD/MM/YYYY */
    #define CREATE_DATE QString("21/12/2019")/**< Date de création du projet */
    #define VERSION "0.3"/**< Version du projet */

#endif // BUILD_HPP
