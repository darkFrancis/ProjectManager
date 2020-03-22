/**
 * @file extern_doc.hpp
 * @brief Documentation des membres externes au programme.
 * @author Dark Francis
 * @date 21/12/2019
 *
 * Voir @ref EXTERN_DOC.
 * @todo Ajouter les autres membre Qt à la doc.
 */
#ifndef EXTERN_DOC_HPP
#define EXTERN_DOC_HPP

    /** @addtogroup EXTERN_DOC
     * @{ */

    /**
     * @namespace Ui
     * @brief Namespace de définition des interfaces utilisateur.
     *
     * Utilisé par Qt pour construire des fichiers intermédiaires moc
     * à partir des fichiers de structure ui.@n@n
     * Voir https://doc.qt.io/qt-5/designer-ui-file-format.html.
     */
    namespace Ui {}

    /**
     * @class QMainWindow
     * @brief Classe Qt
     *
     * Cette classe permet de décrire des fenêtres.@n@n
     * Voir : https://doc.qt.io/qt-5/qmainwindow.html.
     */
    class QMainWindow{};

    /**
     * @class QWidget
     * @brief Classe Qt
     *
     * Cette classe permet de décrire des widgets.@n@n
     * Voir : https://doc.qt.io/qt-5/qwidget.html.
     */
    class QWidget{};

    /**
     * @class QTextEdit
     * @brief Classe Qt
     *
     * Cette classe permet de décrire des zone de texte éditable.@n@n
     * Voir : https://doc.qt.io/qt-5/qtextedit.html.
     */
    class QTextEdit{};

    /**
     * @class QString
     * @brief Classe Qt
     *
     * Cette classe permet de décrire des chaînes de caractères.@n@n
     * Voir : https://doc.qt.io/qt-5/qstring.html.
     */
    class QString{};

    /**
     * @class QStringList
     * @brief Classe Qt
     *
     * Cette classe permet de décrire des listes de chaînes de caractères.@n@n
     * Voir : https://doc.qt.io/qt-5/qstringlist.html.
     */
    class QStringList{};

    /**
     * @class QList
     * @brief Classe Qt
     *
     * Cette classe permet de décrire des listes d'objets.@n@n
     * Voir : https://doc.qt.io/qt-5/qlist.html.
     */
    class QList{};

    /** @} */

#endif // EXTERN_DOC_HPP
