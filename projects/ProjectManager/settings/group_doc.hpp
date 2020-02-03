/**
 * @file group_doc.hpp
 * @brief Documentation des groupes/modules du programme et de la page principale
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef GROUP_DOC_HPP
#define GROUP_DOC_HPP

    /**
      * @mainpage Documentation de ProjectManager
      * @author Dark Francis
      * @date 21/12/2019
      *
      * ProjectManager est un logiciel de gestion de projet.
      */

    /**
      * @defgroup FILE Fichiers
      * @brief Ensemble des fichiers utilisés
      *
      * Tous ces fichiers sont utilisés pour charger des informations par
      * défaut ou conserver des paramètres entre deux utilisations.
      */

    /**
      * @defgroup HTML_TAG Balises HTML
      * @brief Les balises HTML particulières
      *
      * Ces balises forment une base pour simplifier le code lors de la
      * création de texte au format HTML.
      */

    /**
      * @defgroup COMPILE_ACTION Actions du compilateur
      * @brief Les actions possibles du compilateur
      *
      * Ces différentes actions sont sélectionnables par un menu déroulant sur
      * l'onglet TabCompiler. Les fonctions leur correspondant sont activée par
      * le connecteur TabCompiler::on_pushButton_action_clicked.@n
      * Voir @ref TABCOMPILER_ACTION.
      */

    /**
      * @defgroup TABCOMPILER_ACTION Fonctions du compilateur
      * @brief Les fonctions d'actions du compilateur
      *
      * Ces différentes fonctions sont sélectionnables par un menu déroulant sur
      * l'onglet TabCompiler à travers des mots clés d'action. Elle sont activée
      * par le connecteur TabCompiler::on_pushButton_action_clicked.@n
      * Voir @ref COMPILE_ACTION.
      */

    /**
      * @defgroup PROJECT_TYPE Types de projet
      * @brief Les différents types de projets possibles et leurs labels
      *
      * Ces types de projets sont utilisés lors de la compilation pour choisir
      * des options supplémentaires à appliquer par défaut. Les labels sont
      * utiliser pour remplir les listes déroulantes pour la sélection du type
      * de projet.
      */

    /**
      * @defgroup PROJECT_FLAGS Flags du fichier projet
      * @brief Les différents flags utilisable dans un fichier projet
      *
      * Ces différents flags permettent de spécifier des informations utilisable
      * par ProjectManager pour:
      * @li Générer une documentation à l'aide de Doxygen
      * @li Gérer les versions à l'aide de GIT
      * @li Compiler à l'aide de GNU/GCC
      */

    /**
      * @defgroup KW_COMPILE Mots clés compilateur
      * @brief Les mots clés des options de compilation
      *
      * Ces mots clés sont utilisés :
      * @li lors de la lecture du fichier #COMPILER_FILE
      * @li lors de l'initialisation des fenêtres de gestions des paramètres
      * de compilation
      */

    /**
      * @defgroup CONTEXT_GET Context::get
      * @brief Ce groupe contient les méthodes GET de l'instance Context.
      *
      * Toutes ces méthodes sont publiques et permettent l'accès aux attributs
      * de l'instance Context.
      */

    /**
      * @defgroup CONTEXT_SET Context::set
      * @brief Ce groupe contient les méthodes SET de l'instance Context.
      *
      * Toutes ces méthodes sont publiques et permettent la modification des
      * attributs de l'instance Context.
      */

    /**
      * @defgroup SETTING_GET Settings::get
      * @brief Ce groupe contient les méthodes GET de l'instance Settings.
      *
      * Toutes ces méthodes sont publiques et permettent l'accès aux attributs
      * de l'instance Settings.
      */

    /**
      * @defgroup SETTING_SET Settings::set
      * @brief Ce groupe contient les méthodes SET de l'instance Settings.
      *
      * Toutes ces méthodes sont publiques et permettent la modification des
      * attributs de l'instance Settings.
      */

    /**
      * @defgroup INIT_DOXYTAB Initialisation Doxygen
      * @brief Fonctions d'initialisation de l'onglet Doxygen
      *
      * Ces méthodes servent chacune à initialiser une portion de l'onglet
      * de configuration de Doxygen.
      */

    /**
      * @defgroup SAVE_DOXYTAB Enregistrement Doxygen
      * @brief Fonctions d'enregistrement de l'onglet Doxygen
      *
      * Ces méthodes servent chacune à enregistrer une portion de l'onglet
      * de configuration de Doxygen.
      */

    /**
      * @defgroup SUB_INIT_DOXYTAB Sous-initialisation Doxygen
      * @brief Sous-fonctions d'initialisation de l'onglet Doxygen
      *
      * Ces méthodes servent chacune à initialiser les objets de l'interface
      * de façon spécifique.
      */

    /**
      * @defgroup SUB_SAVE_DOXYTAB Sous-enregistrement Doxygen
      * @brief Sous-fonctions d'enregistrement de l'onglet Doxygen
      *
      * Ces méthodes servent chacune à enregistrer les données de l'interface
      * de façon spécifique.
      */

    /**
      * @defgroup EXTERN_DOC Documentation externe
      * @brief Les membres externes à ProjectManager
      */

#endif // GROUP_DOC_HPP
