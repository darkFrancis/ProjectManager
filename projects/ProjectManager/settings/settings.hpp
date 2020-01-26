/**
 * @file settings.hpp
 * @brief Définition des options
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef SETTINGS_HPP
#define SETTINGS_HPP

    #include <QString>
    #include <QList>

    #define BUILD_YEAR_CH0 (__DATE__[ 7])
    #define BUILD_YEAR_CH1 (__DATE__[ 8])
    #define BUILD_YEAR_CH2 (__DATE__[ 9])
    #define BUILD_YEAR_CH3 (__DATE__[10])
    #define BUILD_MONTH_IS_JAN (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
    #define BUILD_MONTH_IS_FEB (__DATE__[0] == 'F')
    #define BUILD_MONTH_IS_MAR (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
    #define BUILD_MONTH_IS_APR (__DATE__[0] == 'A' && __DATE__[1] == 'p')
    #define BUILD_MONTH_IS_MAY (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
    #define BUILD_MONTH_IS_JUN (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
    #define BUILD_MONTH_IS_JUL (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')
    #define BUILD_MONTH_IS_AUG (__DATE__[0] == 'A' && __DATE__[1] == 'u')
    #define BUILD_MONTH_IS_SEP (__DATE__[0] == 'S')
    #define BUILD_MONTH_IS_OCT (__DATE__[0] == 'O')
    #define BUILD_MONTH_IS_NOV (__DATE__[0] == 'N')
    #define BUILD_MONTH_IS_DEC (__DATE__[0] == 'D')
    #define BUILD_MONTH_CH0 \
        ((BUILD_MONTH_IS_OCT || BUILD_MONTH_IS_NOV || BUILD_MONTH_IS_DEC) ? '1' : '0')
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
        )
    #define BUILD_DAY_CH0 ((__DATE__[4] >= '0') ? (__DATE__[4]) : '0')
    #define BUILD_DAY_CH1 (__DATE__[ 5])
    #define BUILD_DATE QString(BUILD_DAY_CH0)+BUILD_DAY_CH1+"/"+BUILD_MONTH_CH0+BUILD_MONTH_CH1+"/"+BUILD_YEAR_CH0+BUILD_YEAR_CH1+BUILD_YEAR_CH2+BUILD_YEAR_CH3
    #define CREATE_DATE QString("21/12/2019")
    #define VERSION "0.2"

    #define SETTINGS_FILE           QString("config/settings.conf")/**< @brief Définition du nom de fichier des options */
    #define COLORS_FILE             QString("config/colors.conf")/**< @brief Définition du nom de fichier des couleurs */
    #define COMPILER_FILE           QString("config/compiler.conf")/**< @brief Définition du nom de fichier d'option de compilateur */

    #define COMPILE_OVERALL         QString("overall")
    #define COMPILE_LANGUAGE_C      QString("c_language")
    #define COMPILE_LANGUAGE_CXX    QString("cxx_language")
    #define COMPILE_DIAGNOSTIC      QString("diagnostic")
    #define COMPILE_WARNINGS        QString("warnings")
    #define COMPILE_DEBUG           QString("debug_options")
    #define COMPILE_OPTI            QString("optimization")
    #define COMPILE_INSTRU          QString("instrumentation")
    #define COMPILE_PREPROCESSOR    QString("preprocessor")
    #define COMPILE_ASSEMBLER       QString("assembler")
    #define COMPILE_LINKER          QString("linker")
    #define COMPILE_DIRS            QString("dirs_options")
    #define COMPILE_CODE_CONV       QString("convention_code")

    #define HTML_BEGIN              QString("<html><head><style>i{color:green;}</style></head><body><p>")
    #define HTML_END                QString("</p></body></html>")

    /**
     * @struct Color
     * @brief La structure Color défini une couleur RGB.
     *
     * Le fichier de définition des couleurs contient une couleur par ligne
     * de la forme <nom> <red> <green> <blue>.
     */
    struct Color
    {
        QString name;/**< Nom de la couleur */
        int red;/**< Composante rouge */
        int green;/**< Composante verte */
        int blue;/**< Composante bleue */
    };
    typedef struct Color Color;

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
     * de la forme <option>;<brief>;<tooltip>.
     */
    struct CompilerOption
    {
        QString option;/**< Option du compilateur */
        QString brief;/**< Résumé de l'option */
        QString tooltip;/**< Détail de l'option qui apparait en la survolant */
    };
    typedef struct CompilerOption CompilerOption;

    /**
     * @class Settings
     * @brief La classe Settings défini les options.
     *
     * Les option sont utilisée par des get/set.
     */
    class Settings
    {
        public:
            static Settings* Instance();
            void init(){}
            void save();
            void load();
            // Get
            QString style(){return m_style;}
            bool keepSize(){return m_keep_size;}
            QString doxygenTemplateDir(){return m_doxygen_template_dir;}
            bool clearScreen(){return m_clear_screen;}
            QString colorNormal(){return m_color_normal;}
            QString colorSuccess(){return m_color_success;}
            QString colorError(){return m_color_error;}
            QStringList sourcesExtensions(){return m_sources_extensions;}
            QStringList headersExtensions(){return m_headers_extensions;}
            // Get with no set
            QList<Color>* colors(){return &m_colors;}
            QList<CompilerOption>* overallOptions(){return &m_overall_options;}
            QList<CompilerOption>* languageCOptions(){return &m_language_c_options;}
            QList<CompilerOption>* languageCxxOptions(){return &m_language_cxx_options;}
            QList<CompilerOption>* diagnosticOptions(){return &m_diagnostic_options;}
            QList<CompilerOption>* warningsOptions(){return &m_warnings_options;}
            QList<CompilerOption>* debugOptions(){return &m_debug_options;}
            QList<CompilerOption>* optimizationOptions(){return &m_opti_options;}
            QList<CompilerOption>* instrumentationOptions(){return &m_instru_options;}
            QList<CompilerOption>* preprocessorOptions(){return &m_preprocessor_options;}
            QList<CompilerOption>* assemblerOptions(){return &m_assembler_options;}
            QList<CompilerOption>* linkerOptions(){return &m_linker_options;}
            QList<CompilerOption>* dirsOptions(){return &m_dirs_options;}
            QList<CompilerOption>* codeConvOptions(){return &m_code_conv_options;}
            // Set
            void setStyle(QString val){m_style = val;}
            void setKeepSize(bool val){m_keep_size = val;}
            void setDoxygenTemplateDir(QString val){m_doxygen_template_dir = val;}
            void setClearScreen(bool val){m_clear_screen = val;}
            void setColorNormal(QString color){m_color_normal = color;}
            void setColorSuccess(QString color){m_color_success = color;}
            void setColorError(QString color){m_color_error = color;}
            void setSourcesExtensions(QStringList exts){m_sources_extensions = exts;}
            void setHeadersExtensions(QStringList exts){m_headers_extensions = exts;}

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
