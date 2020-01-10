/**
 * @file tab.hpp
 * @brief Description de la classe abstraite Tab
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef TAB_HPP
#define TAB_HPP

    #include <QWidget>

    /**
     * @class Tab tab.hpp tab.hpp
     * @brief La classe Tab est une classe abstraite pour les onglets principaux
     *
     * Cette classe défini des fonctions d'initialisation, de nettoyage et de récupération des informations
     * pour les Widgets des onglets.
     */
    class Tab : public QWidget
    {
        Q_OBJECT
        public:
            Tab(QWidget *parent = nullptr) : QWidget(parent){}
            virtual ~Tab(){clean();}
            virtual void init(){}
            virtual void clean(){}
            virtual QStringList getInfo(){return QStringList();}

        signals:
            void apply(Tab*);
    };

#endif // TAB_HPP
