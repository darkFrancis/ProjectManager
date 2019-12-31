#ifndef TABDOXYGEN_HPP
#define TABDOXYGEN_HPP

    #include <QWidget>
    #include <QCheckBox>
    #include <QComboBox>
    #include <QLineEdit>
    #include <QSpinBox>
    #include <QFontComboBox>
    #include <QGroupBox>

    #define DOC_YES QString("YES")
    #define DOC_NO  QString("NO")

    namespace Ui {
        class TabDoxygen;
    }

    class TabDoxygen : public QWidget
    {
        Q_OBJECT

        public:
            explicit TabDoxygen(QWidget *parent = nullptr);
            ~TabDoxygen();
            void init();
            void save();
            void createDoxyfile();

        signals:
            void foundPath(QString path, QLineEdit* lineedit);

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
            void writePath(QString path, QLineEdit* lineedit);
            // Click PushButtons
            void on_pushButton_apply_clicked();
            void on_pushButton_default_clicked();
            void on_pushButton_generateFiles_clicked();

        private:
            Ui::TabDoxygen *ui;
            QString m_doxyfile;
            QTextStream* m_stream;

            // Init tabs
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

            // Save tabs
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

            // Init Widgets
            void initCheckbox(QString key, QCheckBox* checkbox, bool default_value, bool default_cond = false);
            void initGroupbox(QString key, QGroupBox* groupbox, bool default_value, bool default_cond = false);
            void initCombobox(QString key, QComboBox* combobox, QString default_value = "", bool default_cond = false);
            void initFontCbox(QString key, QFontComboBox* fontcombobox, QString default_value = "", bool default_cond = false);
            void initLineedit(QString key, QLineEdit* lineedit, QString default_value = "", bool default_cond = false);
            void initSpinbox_(QString key, QSpinBox* spinbox, int default_value = 0, bool default_cond = false);

            // Save Widgets
            void saveCheckbox(QString key, QCheckBox* checkbox, bool default_value);
            void saveGroupbox(QString key, QGroupBox* groupbox, bool default_value);
            void saveCombobox(QString key, QComboBox* combobox, QString default_value = "");
            void saveFontCbox(QString key, QFontComboBox* fontcombobox, QString default_value = "");
            void saveLineedit(QString key, QLineEdit* lineedit, QString default_value = "");
            void saveSpinbox_(QString key, QSpinBox* spinbox, int default_value = 0);

            // Templates
            void command(QString cmd);
            void move(QString path);
    };

#endif // TABDOXYGEN_HPP
