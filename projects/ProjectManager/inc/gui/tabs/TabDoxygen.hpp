/**
 * @file TabDoxygen.hpp
 * @brief Description de la classe TabDoxygen
 * @author Dark Francis
 * @date 21/12/2019
 */
#ifndef TABDOXYGEN_HPP
#define TABDOXYGEN_HPP

    #include "Tab.hpp"
    #include <QCheckBox>
    #include <QComboBox>
    #include <QLineEdit>
    #include <QSpinBox>
    #include <QFontComboBox>
    #include <QGroupBox>
    #include <QDir>
    #include "InitParser.hpp"

    #define DOC_YES QString("YES")/**< Valeur @c true pour la configuration Doxygen */
    #define DOC_NO  QString("NO")/**< Valeur @c false pour la configuration Doxygen */

    namespace Ui {
        class TabDoxygen;
    }

    /**
     * @class TabDoxygen
     * @brief La classe TabDoxygen défini l'onglet de configuration de Doxygen.
     *
     * Cette fenêtre est séparée en différentes sections pour la configuration :
     * @li Projet
     * @li Build
     * @li Message
     * @li Fichiers d'entrée
     * @li Recherche des sources
     * @li HTML
     * @li Autres sortie
     * @li Préprocesseur
     * @li Références externes
     * @li Graphiques
     *
     * Les boutons en bas de la fenêtre permettent :
     * @li de générer les templates
     * @li de remettre les paramètres par défaut
     * @li d'appliquer les changements
     *
     * Header : TabDoxygen.hpp
     */
    class TabDoxygen : public Tab
    {
        Q_OBJECT

        public:
            TabDoxygen(QWidget *parent = nullptr);
            ~TabDoxygen();
            void init();
            void save();
            void createDoxyfile();

        private slots:
            // Click ToolButtons
            void on_toolButton_projectLogo_clicked();
            void on_toolButton_outputDir_clicked();
            void on_toolButton_fileVersionFilter_clicked();
            void on_toolButton_layoutFile_clicked();
            void on_toolButton_citeBibFiles_clicked();
            void on_toolButton_warnLogfile_clicked();
            void on_toolButton_examplePath_clicked();
            void on_toolButton_imagePath_clicked();
            void on_toolButton_inputFilter_clicked();
            void on_toolButton_useMdfileAsMainpage_clicked();
            void on_toolButton_htmlHeader_clicked();
            void on_toolButton_htmlFooter_clicked();
            void on_toolButton_htmlStylesheet_clicked();
            void on_toolButton_htmlExtraStylesheet_clicked();
            void on_toolButton_hhcLocation_clicked();
            void on_toolButton_qhgLocation_clicked();
            void on_toolButton_mathjaxCodefile_clicked();
            void on_toolButton_latexHeader_clicked();
            void on_toolButton_latexFooter_clicked();
            void on_toolButton_latexExtraStylesheet_clicked();
            void on_toolButton_latexExtraFiles_clicked();
            void on_toolButton_rtfStylesheetFile_clicked();
            void on_toolButton_rtfExtensionsFile_clicked();
            void on_toolButton_perlPath_clicked();
            void on_toolButton_mscgenPath_clicked();
            void on_toolButton_diaPath_clicked();
            void on_toolButton_dotFontpath_clicked();
            void on_toolButton_dotPath_clicked();
            void on_toolButton_plantumlJarPath_clicked();
            void on_toolButton_plantumlCfgFile_clicked();
            // Path Finder
            void getSaveFile(QLineEdit* lineedit);
            void getOpenFile(QLineEdit* lineedit);
            void getOpenFiles(QLineEdit* lineedit);
            void getDir(QLineEdit* lineedit);
            void writePath(const QString& path, QLineEdit* lineedit);
            // Click PushButtons
            void on_pushButton_apply_clicked();
            void on_pushButton_default_clicked();
            void on_pushButton_generateFiles_clicked();
            void on_pushButton_generateDoc_clicked();

        private:
            // Init tabs
            /** @addtogroup INIT_DOXYTAB
              * @{ */
            void init_tabProject();
            void init_tabBuild();
            void init_tabMsg();
            void init_tabInput();
            void init_tabSource();
            void init_tabHtml();
            void init_tabOutput();
            void init_tabProcessor();
            void init_tabExternRef();
            void init_tabGraph();
            /** @} */

            // Save tabs
            /** @addtogroup SAVE_DOXYTAB
              * @{ */
            void save_tabProject();
            void save_tabBuild();
            void save_tabMsg();
            void save_tabInput();
            void save_tabSource();
            void save_tabHtml();
            void save_tabOutput();
            void save_tabProcessor();
            void save_tabExternRef();
            void save_tabGraph();
            /** @} */

            // Init Widgets
            /** @addtogroup SUB_INIT_DOXYTAB
              * @{ */
            void initCheckbox(const QString& key, QCheckBox* checkbox, bool default_value, bool default_cond = false);
            void initGroupbox(const QString& key, QGroupBox* groupbox, bool default_value, bool default_cond = false);
            void initCombobox(const QString& key, QComboBox* combobox, const QString& default_value = "", bool default_cond = false);
            void initFontCbox(const QString& key, QFontComboBox* fontcombobox, const QString& default_value = "", bool default_cond = false);
            void initLineedit(const QString& key, QLineEdit* lineedit, const QString& default_value = "", bool default_cond = false);
            void initSpinbox_(const QString& key, QSpinBox* spinbox, int default_value = 0, bool default_cond = false);
            /** @} */

            // Save Widgets
            /** @addtogroup SUB_SAVE_DOXYTAB
              * @{ */
            void saveCheckbox(const QString& key, QCheckBox* checkbox, bool default_value);
            void saveGroupbox(const QString& key, QGroupBox* groupbox, bool default_value);
            void saveCombobox(const QString& key, QComboBox* combobox, const QString& default_value = "");
            void saveFontCbox(const QString& key, QFontComboBox* fontcombobox, const QString& default_value = "");
            void saveLineedit(const QString& key, QLineEdit* lineedit, const QString& default_value = "");
            void saveSpinbox_(const QString& key, QSpinBox* spinbox, int default_value = 0);
            /** @} */

            // Templates
            void command(const QString& cmd, const QString& workingDir = ".");

            // Doc
            QString generateDocFromDir(const QDir& dir, const QString& projectName);

        private:
            Ui::TabDoxygen *ui;/**< UI de la classe TabDoxygen */
            QString m_doxyfile;/**< Fichier Doxyfile à utiliser */
            QTextStream* m_stream;/**< Flux vers le fichier Doxyfile */
            InitParser m_parser; /**< Parser de fichier INI */
    };

#endif // TABDOXYGEN_HPP
