/**
 * @file settings.hpp
 * @brief Définition de la classe Settings
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef SETTINGS_HPP
#define SETTINGS_HPP

    #include <QString>
    #include <QList>
    #include "build.hpp"

    /** @addtogroup FILE
      * @{ */
    #define SETTINGS_FILE           QString("config/settings.conf")/**< Définition du nom de fichier des options */
    #define COLORS_FILE             QString("config/colors.conf")/**< Définition du nom de fichier des couleurs */
    #define COMPILER_FILE           QString("config/compiler.conf")/**< Définition du nom de fichier d'option de compilateur */
    /** @} */

    /** @addtogroup KW_COMPILE
      * @{ */
    #define COMPILE_OVERALL         QString("overall")/**< Mot clé des options générales */
    #define COMPILE_LANGUAGE_C      QString("c_language")/**< Mot clé des options de langage C */
    #define COMPILE_LANGUAGE_CXX    QString("cxx_language")/**< Mot clé des options langage C++ */
    #define COMPILE_DIAGNOSTIC      QString("diagnostic")/**< Mot clé des options de diagnostique */
    #define COMPILE_WARNINGS        QString("warnings")/**< Mot clé des options de warning */
    #define COMPILE_DEBUG           QString("debug_options")/**< Mot clé des options de debug */
    #define COMPILE_OPTI            QString("optimization")/**< Mot clé des options d'optimisation */
    #define COMPILE_INSTRU          QString("instrumentation")/**< Mot clé des options d'instrumentation */
    #define COMPILE_PREPROCESSOR    QString("preprocessor")/**< Mot clé des options de preprocesseur */
    #define COMPILE_ASSEMBLER       QString("assembler")/**< Mot clé des options de l'assembleur */
    #define COMPILE_LINKER          QString("linker")/**< Mot clé des options du linker */
    #define COMPILE_DIRS            QString("dirs_options")/**< Mot clé des options des dossiers */
    #define COMPILE_CODE_CONV       QString("convention_code")/**< Mot clé des options de convention de code */
    /** @} */

    /** @addtogroup HTML_TAG
      * @{ */
    #define HTML_BEGIN              QString("<html><head><style>i{color:green;}</style></head><body><p>")/**< Balise HTML utilisée avant les tooltips.@n Applique la couleur verte au texte en italique. */
    #define HTML_END                QString("</p></body></html>")/**< Balise HTML utilisée à la fin d'un tooltip */
    /** @} */

    /**
     * @struct Color
     * @brief La structure Color défini une couleur RGB.
     *
     * Le fichier de définition des couleurs contient une couleur par ligne
     * de la forme &lt;nom> &lt;red> &lt;green> &lt;blue>.
     * @n@n Header : settings.hpp
     */
    struct Color
    {
        QString name;/**< Nom de la couleur */
        int red;/**< Composante rouge */
        int green;/**< Composante verte */
        int blue;/**< Composante bleue */
    };
    typedef struct Color Color;/**< Définition du type Color pour la structure de même nom */

    /**
     * @struct CompilerOption
     * @brief La structure CompilerOption défini une option pour l'affichage dans la fenêtre de sélection.
     *
     * Le fichier de définition des options de compilateur contient les options par thême.
     * Les thêmes sont définis comme un mot clé sur une ligne parmi :
     * @li overall
     * @li c_language
     * @li cxx_language
     * @li diagnostic
     * @li warnings
     * @li debug_options
     * @li optimization
     * @li instrumentation
     * @li preprocessor
     * @li assembler
     * @li linker
     * @li dirs_options
     * @li convention_code
     * Les lignes qui suivent un mot clé sont les options de compilateur
     * de la forme &lt;option>;&lt;brief>;&lt;tooltip>.
     * @n@n Header : settings.hpp
     */
    struct CompilerOption
    {
        QString option;/**< Option du compilateur */
        QString brief;/**< Résumé de l'option */
        QString tooltip;/**< Détail de l'option qui apparait en la survolant */
    };
    typedef struct CompilerOption CompilerOption;/**< Définition du type CompilerOption pour la structure de même nom */

    /**
     * @class Settings
     * @brief La classe Settings défini les options.
     *
     * Cette classe est un singleton.
     * Les option sont utilisée par des get/set.
     * @n@n Header : settings.hpp
     */
    class Settings
    {
        public:
            static Settings* Instance();
            void init();
            void save();
            void load();
            // Get
            /** @addtogroup SETTING_GET
             * @{ */
            QString style(){return m_style;}/**< GET : Settings::m_style */
            bool keepSize(){return m_keep_size;}/**< GET : Settings::m_keep_size */
            QString doxygenTemplateDir(){return m_doxygen_template_dir;}/**< GET : Settings::m_doxygen_template_dir */
            bool clearScreen(){return m_clear_screen;}/**< GET : Settings::m_clear_screen */
            QString colorNormal(){return m_color_normal;}/**< GET : Settings::m_color_normal */
            QString colorSuccess(){return m_color_success;}/**< GET : Settings::m_color_success */
            QString colorError(){return m_color_error;}/**< GET : Settings::m_color_error */
            QStringList sourcesExtensions(){return m_sources_extensions;}/**< GET : Settings::m_sources_extensions */
            QStringList headersExtensions(){return m_headers_extensions;}/**< GET : Settings::m_headers_extensions */
            // Get with no set
            QList<Color>* colors(){return &m_colors;}/**< GET : Settings::m_colors */
            QList<CompilerOption>* overallOptions(){return &m_overall_options;}/**< GET : Settings::m_overall_options */
            QList<CompilerOption>* languageCOptions(){return &m_language_c_options;}/**< GET : Settings::m_language_c_options */
            QList<CompilerOption>* languageCxxOptions(){return &m_language_cxx_options;}/**< GET : Settings::m_language_cxx_options */
            QList<CompilerOption>* diagnosticOptions(){return &m_diagnostic_options;}/**< GET : Settings::m_diagnostic_options */
            QList<CompilerOption>* warningsOptions(){return &m_warnings_options;}/**< GET : Settings::m_warnings_options */
            QList<CompilerOption>* debugOptions(){return &m_debug_options;}/**< GET : Settings::m_debug_options */
            QList<CompilerOption>* optimizationOptions(){return &m_opti_options;}/**< GET : Settings::m_opti_options */
            QList<CompilerOption>* instrumentationOptions(){return &m_instru_options;}/**< GET : Settings::m_instru_options */
            QList<CompilerOption>* preprocessorOptions(){return &m_preprocessor_options;}/**< GET : Settings::m_preprocessor_options */
            QList<CompilerOption>* assemblerOptions(){return &m_assembler_options;}/**< GET : Settings::m_assembler_options */
            QList<CompilerOption>* linkerOptions(){return &m_linker_options;}/**< GET : Settings::m_linker_options */
            QList<CompilerOption>* dirsOptions(){return &m_dirs_options;}/**< GET : Settings::m_dirs_options */
            QList<CompilerOption>* codeConvOptions(){return &m_code_conv_options;}/**< GET : Settings::m_code_conv_options */
            /** @} */
            // Set
            /** @addtogroup SETTING_SET
             * @{ */
            void setStyle(QString val){m_style = val;}/**< SET : Settings::m_style */
            void setKeepSize(bool val){m_keep_size = val;}/**< SET : Settings::m_keep_size */
            void setDoxygenTemplateDir(QString val){m_doxygen_template_dir = val;}/**< SET : Settings::m_doxygen_template_dir */
            void setClearScreen(bool val){m_clear_screen = val;}/**< SET : Settings::m_clear_screen */
            void setColorNormal(QString color){m_color_normal = color;}/**< SET : Settings::m_color_normal */
            void setColorSuccess(QString color){m_color_success = color;}/**< SET : Settings::m_color_success */
            void setColorError(QString color){m_color_error = color;}/**< SET : Settings::m_color_error */
            void setSourcesExtensions(QStringList exts){m_sources_extensions = exts;}/**< SET : Settings::m_sources_extensions */
            void setHeadersExtensions(QStringList exts){m_headers_extensions = exts;}/**< SET : Settings::m_headers_extensions */
            /** @} */

        private:
            Settings();
            void create();
            void init_color();
            void init_compiler_options();
            void add_color(QString name, int red, int green, int blue);
            void add_compiler_option(QString key_word, QString option, QString brief, QString tooltip);
            static Settings* m_instance;/**< Pointeur vers l'instance de la classe Settings */
            // View
            QString m_style;/**< Style d'affichage */
            bool m_keep_size;/**< Booléen de conservation de la taille de la fenêtre principale */
            // Doxygen
            QString m_doxygen_template_dir;/**< Chemin vers le dossier de création des templates Doxygen */
            // Compiler
            bool m_clear_screen;/**< Booléen d'effacement d'affichage du compilateur entre chaque action */
            QString m_color_normal;/**< couleur d'affichage de terminal normale */
            QString m_color_success;/**< couleur d'affichage de terminal en cas de succès */
            QString m_color_error;/**< couleur d'affichage de terminal en cas d'erreur */
            QStringList m_sources_extensions;/**< Liste des extensions des fichiers sources */
            QStringList m_headers_extensions;/**< Liste des extensions des fichiers headers */
            // Static config (no set)
            QList<Color> m_colors;/**< Liste des couleurs */
            QList<CompilerOption> m_overall_options;/**< Liste des options de compilateur générales */
            QList<CompilerOption> m_language_c_options;/**< Liste des options de compilateur de langage C */
            QList<CompilerOption> m_language_cxx_options;/**< Liste des options de compilateur de langage C++ */
            QList<CompilerOption> m_diagnostic_options;/**< Liste des options de compilateur de diagnostique */
            QList<CompilerOption> m_warnings_options;/**< Liste des options de compilateur de warnings */
            QList<CompilerOption> m_debug_options;/**< Liste des options de compilateur de debug */
            QList<CompilerOption> m_opti_options;/**< Liste des options de compilateur d'optimisation */
            QList<CompilerOption> m_instru_options;/**< Liste des options de compilateur d'instrumentation */
            QList<CompilerOption> m_preprocessor_options;/**< Liste des options de compilateur du préprocesseur */
            QList<CompilerOption> m_assembler_options;/**< Liste des options de compilateur de l'assembleur */
            QList<CompilerOption> m_linker_options;/**< Liste des options de compilateur du linker */
            QList<CompilerOption> m_dirs_options;/**< Liste des options de compilateur des dossiers */
            QList<CompilerOption> m_code_conv_options;/**< Liste des options de compilateur de convention de code */
    };

#endif // SETTINGS_HPP
