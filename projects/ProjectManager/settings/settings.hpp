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
    #define VERSION "0.1"

    #define SETTINGS_FILE           QString("config/settings.conf")
    #define COLORS_FILE             QString("config/colors.conf")
    #define COMPILER_FILE           QString("config/compiler.conf")

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

    struct Color
    {
        QString name;
        int red;
        int green;
        int blue;
    };
    typedef struct Color Color;

    struct CompilerOption
    {
        QString option;
        QString brief;
        QString tooltip;
    };
    typedef struct CompilerOption CompilerOption;

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
            static Settings* m_instance;
            // View
            QString m_style;
            bool m_keep_size;
            // Doxygen
            QString m_doxygen_template_dir;
            // Compiler
            bool m_clear_screen;
            QString m_color_normal;
            QString m_color_success;
            QString m_color_error;
            QStringList m_sources_extensions;
            QStringList m_headers_extensions;
            // Static config (no set)
            QList<Color> m_colors;
            QList<CompilerOption> m_overall_options;
            QList<CompilerOption> m_language_c_options;
            QList<CompilerOption> m_language_cxx_options;
            QList<CompilerOption> m_diagnostic_options;
            QList<CompilerOption> m_warnings_options;
            QList<CompilerOption> m_debug_options;
            QList<CompilerOption> m_opti_options;
            QList<CompilerOption> m_instru_options;
            QList<CompilerOption> m_preprocessor_options;
            QList<CompilerOption> m_assembler_options;
            QList<CompilerOption> m_linker_options;
            QList<CompilerOption> m_dirs_options;
            QList<CompilerOption> m_code_conv_options;
    };

#endif // SETTINGS_HPP
