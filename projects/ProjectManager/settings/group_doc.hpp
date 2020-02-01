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
      * Ces différentes actions sont sélectionnable par un menu déroulant sur
      * l'onglet TabCompiler. Elle sont activée par le connecteur
      * TabCompiler::on_pushButton_action_clicked.
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

#endif // GROUP_DOC_HPP
