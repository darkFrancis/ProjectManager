/**
 * @file Tab.hpp
 * @brief Définition de la classe abstraite des onglets
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef TAB_HPP
#define TAB_HPP

    #include <QWidget>

    /**
     * @header_table Tab.hpp @end_table
     * @brief La classe Tab est une classe abstraite pour les onglets principaux
     *
     * Cette classe défini des fonctions d'initialisation, de nettoyage et d'enregistrement
     * pour les onglets.
     */
    class Tab : public QWidget
    {
        Q_OBJECT
        public:
            Tab(QWidget *parent = nullptr) : QWidget(parent){}
            virtual ~Tab(){}
            virtual void init(){}
            virtual void clean(){}
            virtual void save(){}

        signals:
            /**
             * @param msg Message à afficher
             * @param timeout Temps d'affichage en secondes
             *
             * Ce signal est émit pour effectuer un affichage de status dans la
             * fenêtre principale.
             */
            void status(const QString& msg, int timeout);
    };

#endif // TAB_HPP
