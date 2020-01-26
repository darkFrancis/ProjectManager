/**
 * @file tab.hpp
 * @brief Description de la classe abstraite Tab
 * @author Dark Francis
 * @date 21/12/2019
 */
/**
 * @file tab.hpp
 * @brief Description de la classe abstraite Tab
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef TAB_HPP
#define TAB_HPP

    #include <QWidget>

    #define MOUSE_WAIT QApplication::setOverrideCursor (Qt :: WaitCursor);
    #define MOUSE_RESTORE QApplication::restoreOverrideCursor ();

    /**
     * @class Tab
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
            virtual void save(){}
    };

#endif // TAB_HPP
