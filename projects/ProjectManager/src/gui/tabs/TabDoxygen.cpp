/**
 * @file TabDoxygen.cpp
 * @brief Source de l'onglet Doxygen
 * @author Dark Francis
 * @date 21/12/2019
 */
#include "TabDoxygen.hpp"
#include "ui_TabDoxygen.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include "Logger.hpp"
#include "Context.hpp"

/**
 * @param parent Le QWidget parent de cet onglet
 *
 * Contructeur de la classe TabDoxygen.
 */
TabDoxygen::TabDoxygen(QWidget *parent) :
    Tab(parent),
    ui(new Ui::TabDoxygen)
{
    ui->setupUi(this);
    qLog->debug("TabDoxygen generated");

    // Ajout police d'écriture par défaut de Dot si non présente
    if(ui->fontComboBox_dotFontName->findText("Helvetica") == -1)
    {
        ui->fontComboBox_dotFontName->addItem("Helvetica");
    }
}

/**
 * Destructeur de la classe TabDoxygen.
 */
TabDoxygen::~TabDoxygen()
{
    delete ui;
    qLog->debug("TabDoxygen destroyed");
}

/**
 * Fonction d'initialisation de la classe TabDoxygen.@n
 * Si le fichier Doxygen n'éxiste pas, le créé avec les valeurs par défaut
 * pour chaque option. Ensuite, les différentes fonctions d'initialisation
 * de cet onglet sont appelées.@n
 * Voir Context::m_doxyfile, @ref INIT_DOXYTAB.
 */
void TabDoxygen::init()
{
    qLog->debug("TabDoxygen - initialisation...");
    m_doxyfile = qCtx->doxyfile();
    if(!QFile::exists(m_doxyfile))
    {
        createDoxyfile();
    }

    if(m_parser.loadIni(m_doxyfile))
    {
        init_tabProject();
        init_tabBuild();
        init_tabMsg();
        init_tabInput();
        init_tabSource();
        init_tabHtml();
        init_tabOutput();
        init_tabProcessor();
        init_tabExternRef();
        init_tabGraph();
        ui->toolBox->setCurrentIndex(0);
    }
    else
    {
        throw(QString("Impossible d'ouvrir le fichier Doxyfile pour lecture"));
    }
}

/**
 * Fonction d'enregistrement de la classe TabDoxygen.@n
 * Appelle les différentes fonctions d'enregistrement pour mettre à jour
 * le fichier de configuration de Doxygen.@n
 * Voir @ref SAVE_DOXYTAB.
 */
void TabDoxygen::save()
{
    QFile file(m_doxyfile);
    if(file.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate))
    {
        m_stream = new QTextStream(&file);
        m_stream->setCodec("UTF-8");
        save_tabProject();
        save_tabBuild();
        save_tabMsg();
        save_tabInput();
        save_tabSource();
        save_tabHtml();
        save_tabOutput();
        save_tabProcessor();
        save_tabExternRef();
        save_tabGraph();
        file.close();
    }
    else
    {
        throw(QString("Impossible d'ouvrir le fichier Doxyfile pour écriture"));
    }
}

/**
 * Fonction de création du fichier de configuration de Doxygen.@n
 * Chaque option de configuration de Doxygen est écrite avec sa valeur par défaut
 * dans le fichier Doxyfile choisi par l'utilisateur
 * @warning Si un fichier Doxyfile existe déjà, le supprime.
 * @sa http://www.doxygen.nl/manual/index.html.
 */
void TabDoxygen::createDoxyfile()
{
    QFile doxyfile(m_doxyfile);
    if(doxyfile.open(QIODevice::Text | QIODevice::Truncate | QIODevice::WriteOnly))
    {
        m_stream = new QTextStream(&doxyfile);
        *m_stream << "# Configuration du projet" << endl;
        *m_stream << "DOXYFILE_ENCODING=UTF-8" << endl;
        *m_stream << "PROJECT_NAME=\"My Project\"" << endl;
        *m_stream << "PROJECT_NUMBER=" << endl;
        *m_stream << "PROJECT_BRIEF=" << endl;
        *m_stream << "PROJECT_LOGO=" << endl;
        *m_stream << "OUTPUT_DIRECTORY=" << endl;
        *m_stream << "CREATE_SUBDIRS=NO" << endl;
        *m_stream << "ALLOW_UNICODE_NAMES=NO" << endl;
        *m_stream << "OUTPUT_LANGUAGE=English" << endl;
        *m_stream << "BRIEF_MEMBER_DESC=YES" << endl;
        *m_stream << "REPEAT_BRIEF=YES" << endl;
        *m_stream << "ABBREVIATE_BRIEF=\"The $name class\" \"The $name widget\" \"The $name file\" is provides specifies contains represents a an the" << endl;
        *m_stream << "ALWAYS_DETAILED_SEC=NO" << endl;
        *m_stream << "INLINE_INHERITED_MEMB=NO" << endl;
        *m_stream << "FULL_PATH_NAMES=YES" << endl;
        *m_stream << "STRIP_FROM_PATH=" << endl;
        *m_stream << "STRIP_FROM_INC_PATH=" << endl;
        *m_stream << "SHORT_NAMES=NO" << endl;
        *m_stream << "JAVADOC_AUTOBRIEF=NO" << endl;
        *m_stream << "QT_AUTOBRIEF=NO" << endl;
        *m_stream << "MULTILINE_CPP_IS_BRIEF=NO" << endl;
        *m_stream << "INHERIT_DOCS=YES" << endl;
        *m_stream << "SEPARATE_MEMBER_PAGES=NO" << endl;
        *m_stream << "TAB_SIZE=4" << endl;
        *m_stream << "ALIASES=" << endl;
        *m_stream << "TCL_SUBST=" << endl;
        *m_stream << "OPTIMIZE_OUTPUT_FOR_C=NO" << endl;
        *m_stream << "OPTIMIZE_OUTPUT_JAVA=NO" << endl;
        *m_stream << "OPTIMIZE_FOR_FORTRAN=NO" << endl;
        *m_stream << "OPTIMIZE_OUTPUT_VHDL=NO" << endl;
        *m_stream << "EXTENSION_MAPPING=" << endl;
        *m_stream << "MARKDOWN_SUPPORT=YES" << endl;
        *m_stream << "TOC_INCLUDE_HEADINGS=0" << endl;
        *m_stream << "AUTOLINK_SUPPORT=YES" << endl;
        *m_stream << "BUILTIN_STL_SUPPORT=NO" << endl;
        *m_stream << "CPP_CLI_SUPPORT=NO" << endl;
        *m_stream << "SIP_SUPPORT=NO" << endl;
        *m_stream << "IDL_PROPERTY_SUPPORT=YES" << endl;
        *m_stream << "DISTRIBUTE_GROUP_DOC=NO" << endl;
        *m_stream << "GROUP_NESTED_COMPOUNDS=NO" << endl;
        *m_stream << "SUBGROUPING=YES" << endl;
        *m_stream << "INLINE_GROUPED_CLASSES=NO" << endl;
        *m_stream << "INLINE_SIMPLE_STRUCTS=NO" << endl;
        *m_stream << "TYPEDEF_HIDES_STRUCT=NO" << endl;
        *m_stream << "LOOKUP_CACHE_SIZE=0" << endl;
        *m_stream << endl;
        *m_stream << "# Configuration de build" << endl;
        *m_stream << "EXTRACT_ALL=NO" << endl;
        *m_stream << "EXTRACT_PRIVATE=NO" << endl;
        *m_stream << "EXTRACT_PACKAGE=NO" << endl;
        *m_stream << "EXTRACT_STATIC=NO" << endl;
        *m_stream << "EXTRACT_LOCAL_CLASSES=YES" << endl;
        *m_stream << "EXTRACT_LOCAL_METHODS=NO" << endl;
        *m_stream << "EXTRACT_ANON_NSPACES=NO" << endl;
        *m_stream << "HIDE_UNDOC_MEMBERS=NO" << endl;
        *m_stream << "HIDE_UNDOC_CLASSES=NO" << endl;
        *m_stream << "HIDE_FRIEND_COMPOUNDS=NO" << endl;
        *m_stream << "HIDE_IN_BODY_DOCS=NO" << endl;
        *m_stream << "INTERNAL_DOCS=NO" << endl;
        *m_stream << "CASE_SENSE_NAMES=YES" << endl;
        *m_stream << "HIDE_SCOPE_NAMES=NO" << endl;
        *m_stream << "HIDE_COMPOUND_REFERENCE=NO" << endl;
        *m_stream << "SHOW_INCLUDE_FILES=YES" << endl;
        *m_stream << "SHOW_GROUPED_MEMB_INC=NO" << endl;
        *m_stream << "FORCE_LOCAL_INCLUDES=NO" << endl;
        *m_stream << "INLINE_INFO=YES" << endl;
        *m_stream << "SORT_MEMBER_DOCS=YES" << endl;
        *m_stream << "SORT_BRIEF_DOCS=NO" << endl;
        *m_stream << "SORT_MEMBERS_CTORS_1ST=NO" << endl;
        *m_stream << "SORT_GROUP_NAMES=NO" << endl;
        *m_stream << "SORT_BY_SCOPE_NAME=NO" << endl;
        *m_stream << "STRICT_PROTO_MATCHING=NO" << endl;
        *m_stream << "GENERATE_TODOLIST=YES" << endl;
        *m_stream << "GENERATE_TESTLIST=YES" << endl;
        *m_stream << "GENERATE_BUGLIST=YES" << endl;
        *m_stream << "GENERATE_DEPRECATEDLIST=YES" << endl;
        *m_stream << "ENABLED_SECTIONS=" << endl;
        *m_stream << "MAX_INITIALIZER_LINES=30" << endl;
        *m_stream << "SHOW_USED_FILES=YES" << endl;
        *m_stream << "SHOW_FILES=YES" << endl;
        *m_stream << "SHOW_NAMESPACES=YES" << endl;
        *m_stream << "FILE_VERSION_FILTER=" << endl;
        *m_stream << "LAYOUT_FILE=" << endl;
        *m_stream << "CITE_BIB_FILES=" << endl;
        *m_stream << endl;
        *m_stream << "# Configuration des messages" << endl;
        *m_stream << "QUIET=NO" << endl;
        *m_stream << "WARNINGS=YES" << endl;
        *m_stream << "WARN_IF_UNDOCUMENTED=YES" << endl;
        *m_stream << "WARN_IF_DOC_ERROR=YES" << endl;
        *m_stream << "WARN_NO_PARAMDOC=NO" << endl;
        *m_stream << "WARN_AS_ERROR=NO" << endl;
        *m_stream << "WARN_FORMAT=\"$file:$line:$text\"" << endl;
        *m_stream << "WARN_LOGFILE=" << endl;
        *m_stream << endl;
        *m_stream << "# Configuration des entrées" << endl;
        *m_stream << "INPUT=" << endl;
        *m_stream << "INPUT_ENCODING=UTF-8" << endl;
        *m_stream << "FILE_PATTERNS=*.c *.cc *.cxx *.cpp *.c++ *.java *.ii *.ixx *.ipp *.i++ *.inl *.idl *.ddl *.odl *.h *.hh *.hxx *.hpp *.h++ *.cs *.d *.php *.php4 *.php5 *.phtml *.inc *.m *.markdown *.md *.mm *.dox *.py *.pyw *.f90 *.f95 *.f03 *.f08 *.f *.for *.tcl *.vhd *.vhdl *.ucf *.qsf" << endl;
        *m_stream << "RECURSIVE=NO" << endl;
        *m_stream << "EXCLUDE=" << endl;
        *m_stream << "EXCLUDE_SYMLINKS=NO" << endl;
        *m_stream << "EXCLUDE_PATTERNS=" << endl;
        *m_stream << "EXCLUDE_SYMBOLS=" << endl;
        *m_stream << "EXAMPLE_PATH=" << endl;
        *m_stream << "EXAMPLE_PATTERNS=*" << endl;
        *m_stream << "EXAMPLE_RECURSIVE=NO" << endl;
        *m_stream << "IMAGE_PATH=" << endl;
        *m_stream << "INPUT_FILTER=" << endl;
        *m_stream << "FILTER_PATTERNS=" << endl;
        *m_stream << "FILTER_SOURCE_FILES=NO" << endl;
        *m_stream << "FILTER_SOURCE_PATTERNS=" << endl;
        *m_stream << "USE_MDFILE_AS_MAINPAGE=" << endl;
        *m_stream << endl;
        *m_stream << "# Configurartion de la recherche de sources" << endl;
        *m_stream << "SOURCE_BROWSER=NO" << endl;
        *m_stream << "INLINE_SOURCES=NO" << endl;
        *m_stream << "STRIP_CODE_COMMENTS=YES" << endl;
        *m_stream << "REFERENCED_BY_RELATION=NO" << endl;
        *m_stream << "REFERENCES_RELATION=NO" << endl;
        *m_stream << "REFERENCES_LINK_SOURCE=YES" << endl;
        *m_stream << "SOURCE_TOOLTIPS=YES" << endl;
        *m_stream << "USE_HTAGS=NO" << endl;
        *m_stream << "VERBATIM_HEADERS=YES" << endl;
        *m_stream << "CLANG_ASSISTED_PARSING=NO" << endl;
        *m_stream << "CLANG_OPTIONS=" << endl;
        *m_stream << endl;
        *m_stream << "# Configuration de l'index alphabétique" << endl;
        *m_stream << "ALPHABETICAL_INDEX=YES" << endl;
        *m_stream << "COLS_IN_ALPHA_INDEX=5" << endl;
        *m_stream << "IGNORE_PREFIX=" << endl;
        *m_stream << endl;
        *m_stream << "# Configuration de sortie HTML" << endl;
        *m_stream << "GENERATE_HTML=YES" << endl;
        *m_stream << "HTML_OUTPUT=html" << endl;
        *m_stream << "HTML_FILE_EXTENSION=.html" << endl;
        *m_stream << "HTML_HEADER=" << endl;
        *m_stream << "HTML_FOOTER=" << endl;
        *m_stream << "HTML_STYLESHEET=" << endl;
        *m_stream << "HTML_EXTRA_STYLESHEET=" << endl;
        *m_stream << "HTML_EXTRA_FILES=" << endl;
        *m_stream << "HTML_COLORSTYLE_HUE=220" << endl;
        *m_stream << "HTML_COLORSTYLE_SAT=100" << endl;
        *m_stream << "HTML_COLORSTYLE_GAMMA=80" << endl;
        *m_stream << "HTML_TIMESTAMP=NO" << endl;
        *m_stream << "HTML_DYNAMIC_SECTIONS=NO" << endl;
        *m_stream << "HTML_INDEX_NUM_ENTRIES=100" << endl;
        *m_stream << "GENERATE_DOCSET=NO" << endl;
        *m_stream << "DOCSET_FEEDNAME=\"Doxygengenerateddocs\"" << endl;
        *m_stream << "DOCSET_BUNDLE_ID=org.doxygen.Project" << endl;
        *m_stream << "DOCSET_PUBLISHER_ID=org.doxygen.Publisher" << endl;
        *m_stream << "DOCSET_PUBLISHER_NAME=Publisher" << endl;
        *m_stream << "GENERATE_HTMLHELP=NO" << endl;
        *m_stream << "CHM_FILE=" << endl;
        *m_stream << "HHC_LOCATION=" << endl;
        *m_stream << "GENERATE_CHI=NO" << endl;
        *m_stream << "CHM_INDEX_ENCODING=" << endl;
        *m_stream << "BINARY_TOC=NO" << endl;
        *m_stream << "TOC_EXPAND=NO" << endl;
        *m_stream << "GENERATE_QHP=NO" << endl;
        *m_stream << "QCH_FILE=" << endl;
        *m_stream << "QHP_NAMESPACE=org.doxygen.Project" << endl;
        *m_stream << "QHP_VIRTUAL_FOLDER=doc" << endl;
        *m_stream << "QHP_CUST_FILTER_NAME=" << endl;
        *m_stream << "QHP_CUST_FILTER_ATTRS=" << endl;
        *m_stream << "QHP_SECT_FILTER_ATTRS=" << endl;
        *m_stream << "QHG_LOCATION=" << endl;
        *m_stream << "GENERATE_ECLIPSEHELP=NO" << endl;
        *m_stream << "ECLIPSE_DOC_ID=org.doxygen.Project" << endl;
        *m_stream << "DISABLE_INDEX=NO" << endl;
        *m_stream << "GENERATE_TREEVIEW=NO" << endl;
        *m_stream << "ENUM_VALUES_PER_LINE=4" << endl;
        *m_stream << "TREEVIEW_WIDTH=250" << endl;
        *m_stream << "EXT_LINKS_IN_WINDOW=NO" << endl;
        *m_stream << "FORMULA_FONTSIZE=10" << endl;
        *m_stream << "FORMULA_TRANSPARENT=YES" << endl;
        *m_stream << "USE_MATHJAX=NO" << endl;
        *m_stream << "MATHJAX_FORMAT=HTML-CSS" << endl;
        *m_stream << "MATHJAX_RELPATH=http://cdn.mathjax.org/mathjax/latest" << endl;
        *m_stream << "MATHJAX_EXTENSIONS=" << endl;
        *m_stream << "MATHJAX_CODEFILE=" << endl;
        *m_stream << "SEARCHENGINE=YES" << endl;
        *m_stream << "SERVER_BASED_SEARCH=NO" << endl;
        *m_stream << "EXTERNAL_SEARCH=NO" << endl;
        *m_stream << "SEARCHENGINE_URL=" << endl;
        *m_stream << "SEARCHDATA_FILE=searchdata.xml" << endl;
        *m_stream << "EXTERNAL_SEARCH_ID=" << endl;
        *m_stream << "EXTRA_SEARCH_MAPPINGS=" << endl;
        *m_stream << endl;
        *m_stream << "# Configuration de sortie LaTeX" << endl;
        *m_stream << "GENERATE_LATEX=YES" << endl;
        *m_stream << "LATEX_OUTPUT=latex" << endl;
        *m_stream << "LATEX_CMD_NAME=latex" << endl;
        *m_stream << "MAKEINDEX_CMD_NAME=makeindex" << endl;
        *m_stream << "COMPACT_LATEX=NO" << endl;
        *m_stream << "PAPER_TYPE=a4" << endl;
        *m_stream << "EXTRA_PACKAGES=" << endl;
        *m_stream << "LATEX_HEADER=" << endl;
        *m_stream << "LATEX_FOOTER=" << endl;
        *m_stream << "LATEX_EXTRA_STYLESHEET=" << endl;
        *m_stream << "LATEX_EXTRA_FILES=" << endl;
        *m_stream << "PDF_HYPERLINKS=YES" << endl;
        *m_stream << "USE_PDFLATEX=YES" << endl;
        *m_stream << "LATEX_BATCHMODE=NO" << endl;
        *m_stream << "LATEX_HIDE_INDICES=NO" << endl;
        *m_stream << "LATEX_SOURCE_CODE=NO" << endl;
        *m_stream << "LATEX_BIB_STYLE=plain" << endl;
        *m_stream << "LATEX_TIMESTAMP=NO" << endl;
        *m_stream << endl;
        *m_stream << "# Configuration de sortie RTF" << endl;
        *m_stream << "GENERATE_RTF=NO" << endl;
        *m_stream << "RTF_OUTPUT=rtf" << endl;
        *m_stream << "COMPACT_RTF=NO" << endl;
        *m_stream << "RTF_HYPERLINKS=NO" << endl;
        *m_stream << "RTF_STYLESHEET_FILE=" << endl;
        *m_stream << "RTF_EXTENSIONS_FILE=" << endl;
        *m_stream << "RTF_SOURCE_CODE=NO" << endl;
        *m_stream << endl;
        *m_stream << "# Configuration de sortie MAN" << endl;
        *m_stream << "GENERATE_MAN=NO" << endl;
        *m_stream << "MAN_OUTPUT=man" << endl;
        *m_stream << "MAN_EXTENSION=.3" << endl;
        *m_stream << "MAN_SUBDIR=" << endl;
        *m_stream << "MAN_LINKS=NO" << endl;
        *m_stream << endl;
        *m_stream << "# Configuration de sortie XML" << endl;
        *m_stream << "GENERATE_XML=NO" << endl;
        *m_stream << "XML_OUTPUT=xml" << endl;
        *m_stream << "XML_PROGRAMLISTING=YES" << endl;
        *m_stream << endl;
        *m_stream << "# Configuration de sortie DocBook" << endl;
        *m_stream << "GENERATE_DOCBOOK=NO" << endl;
        *m_stream << "DOCBOOK_OUTPUT=docbook" << endl;
        *m_stream << "DOCBOOK_PROGRAMLISTING=NO" << endl;
        *m_stream << endl;
        *m_stream << "# Configuration des définitions AutoGen" << endl;
        *m_stream << "GENERATE_AUTOGEN_DEF=NO" << endl;
        *m_stream << endl;
        *m_stream << "# Configuration du module Perl" << endl;
        *m_stream << "GENERATE_PERLMOD=NO" << endl;
        *m_stream << "PERLMOD_LATEX=NO" << endl;
        *m_stream << "PERLMOD_PRETTY=YES" << endl;
        *m_stream << "PERLMOD_MAKEVAR_PREFIX=" << endl;
        *m_stream << endl;
        *m_stream << "# Configuration du processeur" << endl;
        *m_stream << "ENABLE_PREPROCESSING=YES" << endl;
        *m_stream << "MACRO_EXPANSION=NO" << endl;
        *m_stream << "EXPAND_ONLY_PREDEF=NO" << endl;
        *m_stream << "SEARCH_INCLUDES=YES" << endl;
        *m_stream << "INCLUDE_PATH=" << endl;
        *m_stream << "INCLUDE_FILE_PATTERNS=" << endl;
        *m_stream << "PREDEFINED=" << endl;
        *m_stream << "EXPAND_AS_DEFINED=" << endl;
        *m_stream << "SKIP_FUNCTION_MACROS=YES" << endl;
        *m_stream << endl;
        *m_stream << "# Configuration des références externes" << endl;
        *m_stream << "TAGFILES=" << endl;
        *m_stream << "GENERATE_TAGFILE=" << endl;
        *m_stream << "ALLEXTERNALS=NO" << endl;
        *m_stream << "EXTERNAL_GROUPS=YES" << endl;
        *m_stream << "EXTERNAL_PAGES=YES" << endl;
        *m_stream << "PERL_PATH=/usr/bin/perl" << endl;
        *m_stream << endl;
        *m_stream << "# Configuration de l'outil DOT" << endl;
        *m_stream << "CLASS_DIAGRAMS=YES" << endl;
        *m_stream << "MSCGEN_PATH=" << endl;
        *m_stream << "DIA_PATH=" << endl;
        *m_stream << "HIDE_UNDOC_RELATIONS=YES" << endl;
        *m_stream << "HAVE_DOT=YES" << endl;
        *m_stream << "DOT_NUM_THREADS=0" << endl;
        *m_stream << "DOT_FONTNAME=Helvetica" << endl;
        *m_stream << "DOT_FONTSIZE=10" << endl;
        *m_stream << "DOT_FONTPATH=" << endl;
        *m_stream << "CLASS_GRAPH=YES" << endl;
        *m_stream << "COLLABORATION_GRAPH=YES" << endl;
        *m_stream << "GROUP_GRAPHS=YES" << endl;
        *m_stream << "UML_LOOK=NO" << endl;
        *m_stream << "UML_LIMIT_NUM_FIELDS=10" << endl;
        *m_stream << "TEMPLATE_RELATIONS=NO" << endl;
        *m_stream << "INCLUDE_GRAPH=YES" << endl;
        *m_stream << "INCLUDED_BY_GRAPH=YES" << endl;
        *m_stream << "CALL_GRAPH=NO" << endl;
        *m_stream << "CALLER_GRAPH=NO" << endl;
        *m_stream << "GRAPHICAL_HIERARCHY=YES" << endl;
        *m_stream << "DIRECTORY_GRAPH=YES" << endl;
        *m_stream << "DOT_IMAGE_FORMAT=png" << endl;
        *m_stream << "INTERACTIVE_SVG=NO" << endl;
        *m_stream << "DOT_PATH=" << endl;
        *m_stream << "DOTFILE_DIRS=" << endl;
        *m_stream << "MSCFILE_DIRS=" << endl;
        *m_stream << "DIAFILE_DIRS=" << endl;
        *m_stream << "PLANTUML_JAR_PATH=" << endl;
        *m_stream << "PLANTUML_CFG_FILE=" << endl;
        *m_stream << "PLANTUML_INCLUDE_PATH=" << endl;
        *m_stream << "DOT_GRAPH_MAX_NODES=50" << endl;
        *m_stream << "MAX_DOT_GRAPH_DEPTH=0" << endl;
        *m_stream << "DOT_TRANSPARENT=NO" << endl;
        *m_stream << "DOT_MULTI_TARGETS=NO" << endl;
        *m_stream << "GENERATE_LEGEND=YES" << endl;
        *m_stream << "DOT_CLEANUP=YES" << endl;
        doxyfile.close();
    }
    else
    {
        throw(QString("Impossible de créer le fichier Doxyfile"));
    }
}

/**
 * Fonction d'initialisation de la section "Projet" de l'onglet Doxygen.@n
 * Utilise les fonctions @ref SUB_INIT_DOXYTAB.
 */
void TabDoxygen::init_tabProject()
{
    initCombobox("DOXYFILE_ENCODING", ui->comboBox_encoding, "UTF-8");
    initLineedit("PROJECT_NAME", ui->lineEdit_projectName);
    initLineedit("PROJECT_NUMBER", ui->lineEdit_projectNumber);
    initLineedit("PROJECT_BRIEF", ui->lineEdit_projectBrief);
    initLineedit("PROJECT_LOGO", ui->lineEdit_projectLogo);
    initLineedit("OUTPUT_DIRECTORY", ui->lineEdit_outputDir);
    initCheckbox("CREATE_SUBDIRS", ui->checkBox_subDir, false);
    initCheckbox("ALLOW_UNICODE_NAMES", ui->checkBox_unicodeNames, false);
    initCombobox("OUTPUT_LANGUAGE", ui->comboBox_outputLanguage, "English");
    initCheckbox("BRIEF_MEMBER_DESC", ui->checkBox_briefMemberDesc, true);
    initCheckbox("REPEAT_BRIEF", ui->checkBox_briefRepeat, true);
    initLineedit("ABBREVIATE_BRIEF", ui->lineEdit_abbreviateBrief, "\"The $name class\" \"The $name widget\" \"The $name file\" is provides specifies contains represents a an the");
    initCheckbox("ALWAYS_DETAILED_SEC", ui->checkBox_alwaysDetailSec, false);
    initCheckbox("INLINE_INHERITED_MEMB", ui->checkBox_inlineInheritedMemb, false);
    initCheckbox("FULL_PATH_NAMES", ui->checkBox_fullPathNames, true);
    initLineedit("STRIP_FROM_PATH", ui->lineEdit_stripFromPath, "", !ui->checkBox_fullPathNames->isChecked());
    initLineedit("STRIP_FROM_INC_PATH", ui->lineEdit_stripFromIncPath);
    initCheckbox("SHORT_NAMES", ui->checkBox_shortNames, false);
    initCheckbox("JAVADOC_AUTOBRIEF", ui->checkBox_javadocAutobrief, false);
    initCheckbox("QT_AUTOBRIEF", ui->checkBox_qtAutobrief, false);
    initCheckbox("MULTILINE_CPP_IS_BRIEF", ui->checkBox_multilineCppIsBrief, false);
    initCheckbox("INHERIT_DOCS", ui->checkBox_inheriteDocs, true);
    initCheckbox("SEPARATE_MEMBER_PAGES", ui->checkBox_separateMemberPages, false);
    initSpinbox_("TAB_SIZE", ui->spinBox_tabSize, 4);
    initLineedit("ALIASES", ui->lineEdit_aliases);
    initLineedit("TCL_SUBST", ui->lineEdit_tclSubst);
    initCheckbox("OPTIMIZE_OUTPUT_FOR_C", ui->checkBox_optimizeOutputForC, false);
    initCheckbox("OPTIMIZE_OUTPUT_JAVA", ui->checkBox_optimizeOutputJava, false);
    initCheckbox("OPTIMIZE_FOR_FORTRAN", ui->checkBox_optimizeOutputFortran, false);
    initCheckbox("OPTIMIZE_OUTPUT_VHDL", ui->checkBox_optimizeOutputVhdl, false);
    initLineedit("EXTENSION_MAPPING", ui->lineEdit_extensionMapping);
    initCheckbox("MARKDOWN_SUPPORT", ui->checkBox_markdownSupport, true);
    initSpinbox_("TOC_INCLUDE_HEADINGS", ui->spinBox_tocIncludeHeading, 0, !ui->checkBox_markdownSupport->isChecked());
    initCheckbox("AUTOLINK_SUPPORT", ui->checkBox_autolinkSupport, true);
    initCheckbox("BUILTIN_STL_SUPPORT", ui->checkBox_builtinStlSupport, false);
    initCheckbox("CPP_CLI_SUPPORT", ui->checkBox_cppCliSupport, false);
    initCheckbox("SIP_SUPPORT", ui->checkBox_sipSupport, false);
    initCheckbox("IDL_PROPERTY_SUPPORT", ui->checkBox_idlPropertySupport, true);
    initCheckbox("DISTRIBUTE_GROUP_DOC", ui->checkBox_distributeGroupDoc, false);
    initCheckbox("GROUP_NESTED_COMPOUNDS", ui->checkBox_groupNestedCompounds, false);
    initCheckbox("SUBGROUPING", ui->checkBox_subgrouping, true);
    initCheckbox("INLINE_GROUPED_CLASSES", ui->checkBox_inlineGroupedClasses, false);
    initCheckbox("INLINE_SIMPLE_STRUCTS", ui->checkBox_inlineSimpleStructs, false);
    initCheckbox("TYPEDEF_HIDES_STRUCT", ui->checkBox_typedefHidesStruct, false);
    initSpinbox_("LOOKUP_CACHE_SIZE", ui->spinBox_lookupCacheSize);
}

/**
 * Fonction d'initialisation de la section "Build" de l'onglet Doxygen.@n
 * Utilise les fonctions @ref SUB_INIT_DOXYTAB.
 */
void TabDoxygen::init_tabBuild()
{
    initCheckbox("EXTRACT_ALL", ui->checkBox_extractAll, false);
    initCheckbox("EXTRACT_PRIVATE", ui->checkBox_extractPrivate, false);
    initCheckbox("EXTRACT_PACKAGE", ui->checkBox_extractPackage, false);
    initCheckbox("EXTRACT_STATIC", ui->checkBox_extractStatic, false);
    initCheckbox("EXTRACT_LOCAL_CLASSES", ui->checkBox_extractLocalClasses, true);
    initCheckbox("EXTRACT_LOCAL_METHODS", ui->checkBox_extractLocalMethods, false);
    initCheckbox("EXTRACT_ANON_NSPACES", ui->checkBox_extractAnonNspaces, false);
    initCheckbox("HIDE_UNDOC_MEMBERS", ui->checkBox_hideUndocMembers, false, ui->checkBox_extractAll->isChecked());
    initCheckbox("HIDE_UNDOC_CLASSES", ui->checkBox_hideUndocClasses, false, ui->checkBox_extractAll->isChecked());
    initCheckbox("HIDE_FRIEND_COMPOUNDS", ui->checkBox_hideFriendCompounds, false);
    initCheckbox("HIDE_IN_BODY_DOCS", ui->checkBox_hideFriendCompounds, false);
    initCheckbox("INTERNAL_DOCS", ui->checkBox_internalDocs, false);
    initCheckbox("CASE_SENSE_NAMES", ui->checkBox_caseSenseNames, true);
    initCheckbox("HIDE_SCOPE_NAMES", ui->checkBox_hideScopeNames, false);
    initCheckbox("HIDE_COMPOUND_REFERENCE", ui->checkBox_hideCompoundReference, false);
    initCheckbox("INLINE_INFO", ui->checkBox_inlineInfo, true);
    initCheckbox("SORT_MEMBER_DOCS", ui->checkBox_sortMemberDocs, true);
    initCheckbox("SORT_BRIEF_DOCS", ui->checkBox_sortBriefDocs, false);
    initCheckbox("SORT_MEMBERS_CTORS_1ST", ui->checkBox_sortMembersCtors1st, false, !ui->checkBox_sortMemberDocs->isChecked() || !ui->checkBox_sortBriefDocs->isChecked());
    initCheckbox("SORT_GROUP_NAMES", ui->checkBox_sortGroupNames, false);
    initCheckbox("SORT_BY_SCOPE_NAME", ui->checkBox_sortByScopeName, false);
    initCheckbox("STRICT_PROTO_MATCHING", ui->checkBox_strictProtoMatching, false);
    initCheckbox("GENERATE_TODOLIST", ui->checkBox_generateTodolist, true);
    initCheckbox("GENERATE_TESTLIST", ui->checkBox_generateTestlist, true);
    initCheckbox("GENERATE_BUGLIST", ui->checkBox_generateBuglist, true);
    initCheckbox("GENERATE_DEPRECATEDLIST", ui->checkBox_generateDeprecatedlist, true);
    initLineedit("ENABLED_SECTIONS", ui->lineEdit_enabledSetions);
    initSpinbox_("MAX_INITIALIZER_LINES", ui->spinBox_maxInitializerLines, 30);
    initCheckbox("SHOW_USED_FILES", ui->checkBox_showUsedFiles, true);
    initCheckbox("SHOW_FILES", ui->checkBox_showFiles, true);
    initCheckbox("SHOW_NAMESPACES", ui->checkBox_showNamespaces, true);
    initLineedit("FILE_VERSION_FILTER", ui->lineEdit_fileVersionFilter);
    initLineedit("LAYOUT_FILE", ui->lineEdit_layoutFile);
    initLineedit("CITE_BIB_FILES", ui->lineEdit_citeBibFiles);
}

/**
 * Fonction d'initialisation de la section "Message" de l'onglet Doxygen.@n
 * Utilise les fonctions @ref SUB_INIT_DOXYTAB.
 */
void TabDoxygen::init_tabMsg()
{
    initCheckbox("QUIET", ui->checkBox_quiet, false);
    initCheckbox("WARNINGS", ui->checkBox_warnings, true);
    initCheckbox("WARN_IF_UNDOCUMENTED", ui->checkBox_warnIfUndocumented, true);
    initCheckbox("WARN_IF_DOC_ERROR", ui->checkBox_warnIfDocError, true);
    initCheckbox("WARN_NO_PARAMDOC", ui->checkBox_warnNoParamdoc, false);
    initCheckbox("WARN_AS_ERROR", ui->checkBox_warnAsError, false);
    initLineedit("WARN_FORMAT", ui->lineEdit_warnFormat, "\"$file:$line: $text\"");
    initLineedit("WARN_LOGFILE", ui->lineEdit_warnLogfile);
}

/**
 * Fonction d'initialisation de la section "Entrée" de l'onglet Doxygen.@n
 * Utilise les fonctions @ref SUB_INIT_DOXYTAB.
 */
void TabDoxygen::init_tabInput()
{
    initLineedit("INPUT", ui->lineEdit_input);
    initCombobox("INPUT_ENCODING", ui->comboBox_inputEncoding, "UTF-8");
    initLineedit("FILE_PATTERNS", ui->lineEdit_filePatterns, "*.c *.cc *.cxx *.cpp *.c++ *.java *.ii *.ixx *.ipp *.i++ *.inl *.idl *.ddl *.odl *.h *.hh *.hxx *.hpp *.h++ *.cs *.d *.php *.php4 *.php5 *.phtml *.inc *.m *.markdown *.md *.mm *.dox *.py *.pyw *.f90 *.f95 *.f03 *.f08 *.f *.for *.tcl *.vhd *.vhdl *.ucf *.qsf");
    initCheckbox("RECURSIVE", ui->checkBox_recursive, false);
    initLineedit("EXCLUDE", ui->lineEdit_exclude);
    initCheckbox("EXCLUDE_SYMLINKS", ui->checkBox_excludeSymlinks, false);
    initLineedit("EXCLUDE_PATTERNS", ui->lineEdit_excludePatterns);
    initLineedit("EXCLUDE_SYMBOLS", ui->lineEdit_excludeSymbols);
    initLineedit("EXAMPLE_PATH", ui->lineEdit_examplePath);
    initLineedit("EXAMPLE_PATTERNS", ui->lineEdit_examplePatterns, "*");
    initCheckbox("EXAMPLE_RECURSIVE", ui->checkBox_exampleRecursive, false);
    initLineedit("IMAGE_PATH", ui->lineEdit_imagePath);
    initLineedit("INPUT_FILTER", ui->lineEdit_inputFilter);
    initLineedit("FILTER_PATTERNS", ui->lineEdit_filterPatterns);
    initCheckbox("FILTER_SOURCE_FILES", ui->checkBox_filterSourceFiles, false);
    initLineedit("FILTER_SOURCE_PATTERNS", ui->lineEdit_filterSourcePatterns, "", !ui->checkBox_filterSourceFiles->isChecked());
    initLineedit("USE_MDFILE_AS_MAINPAGE", ui->lineEdit_useMdfileAsMainpage);
}

/**
 * Fonction d'initialisation de la section "Recherche des sources" de l'onglet Doxygen.@n
 * Utilise les fonctions @ref SUB_INIT_DOXYTAB.
 */
void TabDoxygen::init_tabSource()
{
    initCheckbox("SOURCE_BROWSER", ui->checkBox_sourceBrowser, false);
    initCheckbox("INLINE_SOURCES", ui->checkBox_inlineSources, false);
    initCheckbox("STRIP_CODE_COMMENTS", ui->checkBox_stripCodeComments, true);
    initCheckbox("REFERENCED_BY_RELATION", ui->checkBox_referencedByRelation, false);
    initCheckbox("REFERENCES_RELATION", ui->checkBox_referencesRelation, false);
    initCheckbox("REFERENCES_LINK_SOURCE", ui->checkBox_referencesLinkSource, true);
    initCheckbox("SOURCE_TOOLTIPS", ui->checkBox_sourceTooltips, true, !ui->checkBox_sourceBrowser->isChecked());
    initCheckbox("USE_HTAGS", ui->checkBox_useHtags, false, !ui->checkBox_sourceBrowser->isChecked());
    initCheckbox("VERBATIM_HEADERS", ui->checkBox_verbatimHeaders, true);
    initCheckbox("CLANG_ASSISTED_PARSING", ui->checkBox_clangAssistedParsing, false);
    initLineedit("CLANG_OPTIONS", ui->lineEdit_clangOptions, "", !ui->checkBox_clangAssistedParsing->isChecked());
    initGroupbox("ALPHABETICAL_INDEX", ui->groupBox_alphabeticalIndex, true);
    initSpinbox_("COLS_IN_ALPHA_INDEX", ui->spinBox_colsInAlphaIndex, 5, !ui->groupBox_alphabeticalIndex->isChecked());
    initLineedit("IGNORE_PREFIX", ui->lineEdit_ignorePrefix, "", !ui->groupBox_alphabeticalIndex->isChecked());
}

/**
 * Fonction d'initialisation de la section "HTML" de l'onglet Doxygen.@n
 * Utilise les fonctions @ref SUB_INIT_DOXYTAB.
 */
void TabDoxygen::init_tabHtml()
{
    initGroupbox("GENERATE_HTML", ui->groupBox_generateHtml, true);
    bool html = ui->groupBox_generateHtml->isChecked();
    initLineedit("HTML_OUTPUT", ui->lineEdit_htmlOutput, "html", !html);
    initLineedit("HTML_FILE_EXTENSION", ui->lineEdit_htmlFileExtension, ".html", !html);
    initLineedit("HTML_HEADER", ui->lineEdit_htmlHeader, "", !html);
    initLineedit("HTML_FOOTER", ui->lineEdit_htmlFooter, "", !html);
    initLineedit("HTML_STYLESHEET", ui->lineEdit_htmlStylesheet, "", !html);
    initLineedit("HTML_EXTRA_STYLESHEET", ui->lineEdit_htmlExtraStylesheet, "", !html);
    initLineedit("HTML_EXTRA_FILES", ui->lineEdit_htmlExtraFiles, "", !html);
    initSpinbox_("HTML_COLORSTYLE_HUE", ui->spinBox_htmlColorstyleHue, 220, !html);
    initSpinbox_("HTML_COLORSTYLE_SAT", ui->spinBox_htmlColorstyleSat, 100, !html);
    initSpinbox_("HTML_COLORSTYLE_GAMMA", ui->spinBox_htmlColorstyleGamma, 80, !html);
    initCheckbox("HTML_TIMESTAMP", ui->checkBox_htmlTimestamp, false, !html);
    initCheckbox("HTML_DYNAMIC_SECTIONS", ui->checkBox_htmlDynamicSections, false, !html);
    initSpinbox_("HTML_INDEX_NUM_ENTRIES", ui->spinBox_htmlIndexNumEntries, 100, !html);
    initGroupbox("GENERATE_DOCSET", ui->groupBox_generateDocset, false, !html);
    bool docset = ui->groupBox_generateDocset->isChecked();
    initLineedit("DOCSET_FEEDNAME", ui->lineEdit_docsetFeedname, "\"Doxygen generated docs\"", !docset);
    initLineedit("DOCSET_BUNDLE_ID", ui->lineEdit_docsetBundleId, "org.doxygen.Project", !docset);
    initLineedit("DOCSET_PUBLISHER_ID", ui->lineEdit_docsetPublisherId, "org.doxygen.Publisher", !docset);
    initLineedit("DOCSET_PUBLISHER_NAME", ui->lineEdit_docsetPublisherName, "Publisher", !docset);
    initGroupbox("GENERATE_HTMLHELP", ui->groupBox_generateHtmlhelp, false, !html);
    bool htmlhelp = ui->groupBox_generateHtmlhelp->isChecked();
    initLineedit("CHM_FILE", ui->lineEdit_chmFile, "", !htmlhelp);
    initLineedit("HHC_LOCATION", ui->lineEdit_hhcLocation, "", !htmlhelp);
    initCheckbox("GENERATE_CHI", ui->checkBox_generateChi, false, !htmlhelp);
    initCombobox("CHM_INDEX_ENCODING", ui->comboBox_chmIndexEncoding, "UTF-8", !htmlhelp);
    initCheckbox("BINARY_TOC", ui->checkBox_binaryToc, false, !htmlhelp);
    initCheckbox("TOC_EXPAND", ui->checkBox_tocExpand, false, !htmlhelp);
    initGroupbox("GENERATE_QHP", ui->groupBox_generateQhp, false, !html);
    bool qhp = ui->groupBox_generateQhp->isChecked();
    initLineedit("QCH_FILE", ui->lineEdit_qchFile, "", !qhp);
    initLineedit("QHP_NAMESPACE", ui->lineEdit_qhpNamespace, "org.doxygen.Project", !qhp);
    initLineedit("QHP_VIRTUAL_FOLDER", ui->lineEdit_qhpVirtualFolder, "doc", !qhp);
    initLineedit("QHP_CUST_FILTER_NAME", ui->lineEdit_qhpCustFilterName, "", !qhp);
    initLineedit("QHP_CUST_FILTER_ATTRS", ui->lineEdit_qhpCustFilterAttrs, "", !qhp);
    initLineedit("QHP_SECT_FILTER_ATTRS", ui->lineEdit_qhpSectFilterAttrs, "", !qhp);
    initLineedit("QHG_LOCATION", ui->lineEdit_qhgLocation, "", !qhp);
    initGroupbox("GENERATE_ECLIPSEHELP", ui->groupBox_generateEclipsehelp, false, !html);
    bool eclipse = ui->groupBox_generateEclipsehelp->isChecked();
    initLineedit("ECLIPSE_DOC_ID", ui->lineEdit_eclipseDocId, "org.doxygen.Project", !eclipse);
    initCheckbox("DISABLE_INDEX", ui->checkBox_disableIndex, false, !html);
    initCheckbox("GENERATE_TREEVIEW", ui->checkBox_generateTreeview, false, !html);
    initSpinbox_("ENUM_VALUES_PER_LINE", ui->spinBox_enumValuesPerLine, 4, !html);
    initSpinbox_("TREEVIEW_WIDTH", ui->spinBox_treeviewWidth, 250, !html);
    initCheckbox("EXT_LINKS_IN_WINDOW", ui->checkBox_extLinksInWindow, false, !html);
    initSpinbox_("FORMULA_FONTSIZE", ui->spinBox_formulaFontsize, 10, !html);
    initCheckbox("FORMULA_TRANSPARENT", ui->checkBox_formulaTransparent, true, !html);
    initGroupbox("USE_MATHJAX", ui->groupBox_useMathjax, false, !html);
    bool mathjax = ui->groupBox_useMathjax->isChecked();
    initCombobox("MATHJAX_FORMAT", ui->comboBox_mathjaxFormat, "HTML-CSS", !mathjax);
    initLineedit("MATHJAX_RELPATH", ui->lineEdit_mathjaxRelpath, "http://cdn.mathjax.org/mathjax/latest", !mathjax);
    initLineedit("MATHJAX_EXTENSIONS", ui->lineEdit_mathjaxExtensions, "", !mathjax);
    initLineedit("MATHJAX_CODEFILE", ui->lineEdit_mathjaxCodefile, "", !mathjax);
    initGroupbox("SEARCHENGINE", ui->groupBox_searchengine, true, !html);
    bool search = ui->groupBox_searchengine->isChecked();
    initCheckbox("SERVER_BASED_SEARCH", ui->checkBox_serverBasedSearch, false, !search);
    initCheckbox("EXTERNAL_SEARCH", ui->checkBox_externalSearch, false, !search);
    initLineedit("SEARCHENGINE_URL", ui->lineEdit_searchengineUrl, "", !search);
    initLineedit("SEARCHDATA_FILE", ui->lineEdit_searchdataFile, "searchdata.xml", !search);
    initLineedit("EXTERNAL_SEARCH_ID", ui->lineEdit_externalSearchId, "", !search);
    initLineedit("EXTRA_SEARCH_MAPPINGS", ui->lineEdit_extraSearchMapping, "", !search);
}

/**
 * Fonction d'initialisation de la section "Autres sorties" de l'onglet Doxygen.@n
 * Utilise les fonctions @ref SUB_INIT_DOXYTAB.
 */
void TabDoxygen::init_tabOutput()
{
    initGroupbox("GENERATE_LATEX", ui->groupBox_generateLatex, true);
    bool latex = ui->groupBox_generateLatex->isChecked();
    initLineedit("LATEX_OUTPUT", ui->lineEdit_latexOutput, "latex", !latex);
    initLineedit("LATEX_CMD_NAME", ui->lineEdit_latexCmdName, "latex", !latex);
    initLineedit("MAKEINDEX_CMD_NAME", ui->lineEdit_makeindexCmdName, "makeindex", !latex);
    initCheckbox("COMPACT_LATEX", ui->checkBox_compatLatex, false, !latex);
    initCombobox("PAPER_TYPE", ui->comboBox_paperType, "a4", !latex);
    initLineedit("EXTRA_PACKAGES", ui->lineEdit_extraPackages, "", !latex);
    initLineedit("LATEX_HEADER", ui->lineEdit_latexHeader, "", !latex);
    initLineedit("LATEX_FOOTER", ui->lineEdit_latexFooter, "", !latex);
    initLineedit("LATEX_EXTRA_STYLESHEET", ui->lineEdit_latexExtraStylesheet, "", !latex);
    initLineedit("LATEX_EXTRA_FILES", ui->lineEdit_latexExtraFiles, "", !latex);
    initCheckbox("PDF_HYPERLINKS", ui->checkBox_pdfHyperlinks, true, !latex);
    initCheckbox("USE_PDFLATEX", ui->checkBox_usePdflatex, true, !latex);
    initCheckbox("LATEX_BATCHMODE", ui->checkBox_latexBatchmode, false, !latex);
    initCheckbox("LATEX_HIDE_INDICES", ui->checkBox_latexHideIndices, false, !latex);
    initCheckbox("LATEX_SOURCE_CODE", ui->checkBox_latexSourceCode, false, !latex);
    initLineedit("LATEX_BIB_STYLE", ui->lineEdit_latexBibStyle, "plain", !latex);
    initCheckbox("LATEX_TIMESTAMP", ui->checkBox_latexTimestamp, false, !latex);
    initGroupbox("GENERATE_RTF", ui->groupBox_generateRtf, false);
    bool rtf = ui->groupBox_generateRtf->isChecked();
    initLineedit("RTF_OUTPUT", ui->lineEdit_rtfOutput, "rtf", !rtf);
    initCheckbox("COMPACT_RTF", ui->checkBox_compactRtf, false, !rtf);
    initCheckbox("RTF_HYPERLINKS", ui->checkBox_rtfHyperlinks, false, !rtf);
    initLineedit("RTF_STYLESHEET_FILE", ui->lineEdit_rtfStylesheetFile, "", !rtf);
    initLineedit("RTF_EXTENSIONS_FILE", ui->lineEdit_rtfExtensionsFile, "", !rtf);
    initCheckbox("RTF_SOURCE_CODE", ui->checkBox_rtfSourceCode, false, !rtf);
    initGroupbox("GENERATE_MAN", ui->groupBox_generateMan, false);
    bool man = ui->groupBox_generateMan->isChecked();
    initLineedit("MAN_OUTPUT", ui->lineEdit_manOutput, "man", !man);
    initLineedit("MAN_EXTENSION", ui->lineEdit_manExtension, ".3", !man);
    initLineedit("MAN_SUBDIR", ui->lineEdit_manSubdir, "", !man);
    initCheckbox("MAN_LINKS", ui->checkBox_manLinks, false, !man);
    initGroupbox("GENERATE_XML", ui->groupBox_generateXml, false);
    bool xml = ui->groupBox_generateXml->isChecked();
    initLineedit("XML_OUTPUT", ui->lineEdit_xmlOutput, "xml", !xml);
    initCheckbox("XML_PROGRAMLISTING", ui->checkBox_xmlProgramlisting, true, !xml);
    initGroupbox("GENERATE_DOCBOOK", ui->groupBox_generateDocbook, false);
    bool docbook = ui->groupBox_generateDocbook->isChecked();
    initLineedit("DOCBOOK_OUTPUT", ui->lineEdit_docbookOutput, "docbook", !docbook);
    initCheckbox("DOCBOOK_PROGRAMLISTING", ui->checkBox_docbookProgramlisting, false, !docbook);
    initCheckbox("GENERATE_AUTOGEN_DEF", ui->checkBox_generateAutogenDef, false);
    initGroupbox("GENERATE_PERLMOD", ui->groupBox_generatePerlmod, false);
    bool perl = ui->groupBox_generatePerlmod->isChecked();
    initCheckbox("PERLMOD_LATEX", ui->checkBox_perlmodLatex, false, !perl);
    initCheckbox("PERLMOD_PRETTY", ui->checkBox_perlmodPretty, true, !perl);
    initLineedit("PERLMOD_MAKEVAR_PREFIX", ui->lineEdit_perlmodMakevarPrefix, "", !perl);
}

/**
 * Fonction d'initialisation de la section "Préprocesseur" de l'onglet Doxygen.@n
 * Utilise les fonctions @ref SUB_INIT_DOXYTAB.
 */
void TabDoxygen::init_tabProcessor()
{
    initGroupbox("ENABLE_PREPROCESSING", ui->groupBox_enablePreprocessing, true);
    bool preprocess = ui->groupBox_enablePreprocessing->isChecked();
    initCheckbox("MACRO_EXPANSION", ui->checkBox_macroExpansion, false, !preprocess);
    initCheckbox("EXPAND_ONLY_PREDEF", ui->checkBox_expandOnlyPredef, false, !preprocess);
    initCheckbox("SEARCH_INCLUDES", ui->checkBox_searchIncludes, true, !preprocess);
    initLineedit("INCLUDE_PATH", ui->lineEdit_includePath, "", !preprocess);
    initLineedit("INCLUDE_FILE_PATTERNS", ui->lineEdit_includeFilePatterns, "", !preprocess);
    initLineedit("PREDEFINED", ui->lineEdit_predefined, "", !preprocess);
    initLineedit("EXPAND_AS_DEFINED", ui->lineEdit_expandAsDefined, "", !preprocess);
    initCheckbox("SKIP_FUNCTION_MACROS", ui->checkBox_skipFunctionMacros, true, !preprocess);
}

/**
 * Fonction d'initialisation de la section "Références externes" de l'onglet Doxygen.@n
 * Utilise les fonctions @ref SUB_INIT_DOXYTAB.
 */
void TabDoxygen::init_tabExternRef()
{
    initLineedit("TAGFILES", ui->lineEdit_tagfiles);
    initLineedit("GENERATE_TAGFILE", ui->lineEdit_generateTagfile);
    initCheckbox("ALLEXTERNALS", ui->checkBox_allexternals, false);
    initCheckbox("EXTERNAL_GROUPS", ui->checkBox_externalGroups, true);
    initCheckbox("EXTERNAL_PAGES", ui->checkBox_externalPages, true);
    initLineedit("PERL_PATH", ui->lineEdit_perlPath, "/usr/bin/perl");
}

/**
 * Fonction d'initialisation de la section "Graphiques" de l'onglet Doxygen.@n
 * Utilise les fonctions @ref SUB_INIT_DOXYTAB.
 */
void TabDoxygen::init_tabGraph()
{
    initCheckbox("CLASS_DIAGRAMS", ui->checkBox_classDiagrams, true);
    initLineedit("MSCGEN_PATH", ui->lineEdit_mscgenPath);
    initLineedit("DIA_PATH", ui->lineEdit_diaPath);
    initCheckbox("HIDE_UNDOC_RELATIONS", ui->checkBox_hideUndocRelations, true);
    initGroupbox("HAVE_DOT", ui->groupBox_haveDot, true);
    bool dot = ui->groupBox_haveDot->isChecked();
    initSpinbox_("DOT_NUM_THREADS", ui->spinBox_dotNumThreads, 0, !dot);
    initFontCbox("DOT_FONTNAME", ui->fontComboBox_dotFontName, "Helvetica", !dot);
    initSpinbox_("DOT_FONTSIZE", ui->spinBox_dotFontsize, 10, !dot);
    initLineedit("DOT_FONTPATH", ui->lineEdit_dotFontpath, "", !dot);
    initCheckbox("CLASS_GRAPH", ui->checkBox_classGraph, true, !dot);
    initCheckbox("COLLABORATION_GRAPH", ui->checkBox_collaborationGraph, true, !dot);
    initCheckbox("GROUP_GRAPHS", ui->checkBox_groupGraphs, true, !dot);
    initCheckbox("UML_LOOK", ui->checkBox_umlLook, false, !dot);
    initSpinbox_("UML_LIMIT_NUM_FIELDS", ui->spinBox_umlLimitNumFields, 10, !dot);
    initCheckbox("TEMPLATE_RELATIONS", ui->checkBox_templateRelations, false, !dot);
    initCheckbox("INCLUDE_GRAPH", ui->checkBox_includeGraph, true, !dot);
    initCheckbox("INCLUDED_BY_GRAPH", ui->checkBox_includedByGraph, true, !dot);
    initCheckbox("CALL_GRAPH", ui->checkBox_callGraph, false, !dot);
    initCheckbox("CALLER_GRAPH", ui->checkBox_callerGraph, false, !dot);
    initCheckbox("GRAPHICAL_HIERARCHY", ui->checkBox_graphicalHierarchy, true, !dot);
    initCheckbox("DIRECTORY_GRAPH", ui->checkBox_directoryGraph, true, !dot);
    initCombobox("DOT_IMAGE_FORMAT", ui->comboBox_dotImageFormat, "png", !dot);
    initCheckbox("INTERACTIVE_SVG", ui->checkBox_interactiveSvg, false, !dot);
    initLineedit("DOT_PATH", ui->lineEdit_dotPath, "", !dot);
    initLineedit("DOTFILE_DIRS", ui->lineEdit_dotfileDirs, "", !dot);
    initSpinbox_("DOT_GRAPH_MAX_NODES", ui->spinBox_dotGraphMaxNodes, 50, !dot);
    initSpinbox_("MAX_DOT_GRAPH_DEPTH", ui->spinBox_maxDotGraphDepth, 0, !dot);
    initCheckbox("DOT_TRANSPARENT", ui->checkBox_dotTransparent, false, !dot);
    initCheckbox("DOT_MULTI_TARGETS", ui->checkBox_dotMultiTargets, false, !dot);
    initCheckbox("GENERATE_LEGEND", ui->checkBox_generateLegend, true, !dot);
    initCheckbox("DOT_CLEANUP", ui->checkBox_dotCleanup, true, !dot);
    initLineedit("MSCFILE_DIRS", ui->lineEdit_mscfileDirs);
    initLineedit("DIAFILE_DIRS", ui->lineEdit_diafileDirs);
    initLineedit("PLANTUML_JAR_PATH", ui->lineEdit_plantumlJarPath);
    initLineedit("PLANTUML_CFG_FILE", ui->lineEdit_plantumlCfgFile);
    initLineedit("PLANTUML_INCLUDE_PATH", ui->lineEdit_plantumlIncludePath);
}

/**
 * @param key Le mot clé de l'option de configuration de Doxygen
 * @param checkbox L'objet QCheckBox associé à l'option
 * @param default_value La valeur par défaut de l'option
 * @param default_cond Si @c true, force la valeur par défaut
 *
 * Fonction d'initialisation spécifique aux widgets QCheckBox.@n
 * Cette fonction coche la case @c checkbox correspondant au mot clé @c key
 * en fonction de la valeur retournée par la fonction InitParser::get pour @c key.
 * Si aucune valeur n'est retournée par cette fonction ou si @c default_cond
 * vaut @c true, la valeur par défaut @c default_value est utilisée.
 */
void TabDoxygen::initCheckbox(const QString& key, QCheckBox* checkbox, bool default_value, bool default_cond /*= false*/)
{
    if(default_cond)
    {
        checkbox->setChecked(default_value);
    }
    else
    {
        QString value = m_parser.emptyGroup().get(key);
        QString default_word;
        if(default_value == true)
        {
            default_word = DOC_NO;
        }
        else
        {
            default_word = DOC_YES;
        }
        if(value == default_word)
        {
            checkbox->setChecked(!default_value);
        }
        else
        {
            checkbox->setChecked(default_value);
        }
    }
}

/**
 * @param key Le mot clé de l'option de configuration de Doxygen
 * @param groupbox L'objet QGroupBox associé à l'option
 * @param default_value La valeur par défaut de l'option
 * @param default_cond Si @c true, force la valeur par défaut
 *
 * Fonction d'initialisation spécifique aux widgets QGroupBox.@n
 * Cette fonction coche la section @c groupbox correspondant au mot clé @c key
 * en fonction de la valeur retournée par la fonction InitParser::get pour @c key.
 * Si aucune valeur n'est retournée par cette fonction ou si @c default_cond
 * vaut @c true, la valeur par défaut @c default_value est utilisée.
 */
void TabDoxygen::initGroupbox(const QString& key, QGroupBox* groupbox, bool default_value, bool default_cond /*= false*/)
{
    if(default_cond)
    {
        groupbox->setChecked(default_value);
    }
    else
    {
        QString value = m_parser.emptyGroup().get(key);
        QString default_word;
        if(default_value == true)
        {
            default_word = DOC_NO;
        }
        else
        {
            default_word = DOC_YES;
        }
        if(value == default_word)
        {
            groupbox->setChecked(!default_value);
        }
        else
        {
            groupbox->setChecked(default_value);
        }
    }
}

/**
 * @param key Le mot clé de l'option de configuration de Doxygen
 * @param combobox L'objet QComboBox associé à l'option
 * @param default_value La valeur par défaut de l'option
 * @param default_cond Si @c true, force la valeur par défaut
 *
 * Fonction d'initialisation spécifique aux widgets QComboBox.@n
 * Cette fonction initialise la liste déroulante @c combobox correspondant au
 * mot clé @c key en fonction de la valeur retournée par la fonction InitParser::get
 * pour @c key. Si aucune valeur n'est retournée par cette fonction ou si @c
 * default_cond vaut @c true, la valeur par défaut @c default_value est utilisée.
 */
void TabDoxygen::initCombobox(const QString& key, QComboBox* combobox, const QString& default_value /*= ""*/, bool default_cond /*= false*/)
{
    int index;
    if(default_cond)
    {
        index = combobox->findText(default_value);
        if(index == -1)
        {
            index = 0;
        }
    }
    else
    {
        QString value = m_parser.emptyGroup().get(key);
        index = combobox->findText(value);
        if(index == -1)
        {
            index = combobox->findText(default_value);
            if(index == -1)
            {
                index = 0;
            }
        }
    }
    combobox->setCurrentIndex(index);
}

/**
 * @param key Le mot clé de l'option de configuration de Doxygen
 * @param fontcombobox L'objet QFontComboBox associé à l'option
 * @param default_value La valeur par défaut de l'option
 * @param default_cond Si @c true, force la valeur par défaut
 *
 * Fonction d'initialisation spécifique aux widgets QFontComboBox.@n
 * Cette fonction initialise la liste de polices @c fontcombobox correspondant au
 * mot clé @c key en fonction de la valeur retournée par la fonction InitParser::get
 * pour @c key. Si aucune valeur n'est retournée par cette fonction ou si @c
 * default_cond vaut @c true, la valeur par défaut @c default_value est utilisée.
 */
void TabDoxygen::initFontCbox(const QString& key, QFontComboBox* fontcombobox, const QString& default_value /*= ""*/, bool default_cond /*= false*/)
{
    int index;
    if(default_cond)
    {
        index = fontcombobox->findText(default_value);
        if(index == -1)
        {
            index = 0;
        }
    }
    else
    {
        QString value = m_parser.emptyGroup().get(key);
        index = fontcombobox->findText(value);
        if(index == -1)
        {
            index = fontcombobox->findText(default_value);
            if(index == -1)
            {
                index = 0;
            }
        }
    }
    fontcombobox->setCurrentIndex(index);
}

/**
 * @param key Le mot clé de l'option de configuration de Doxygen
 * @param lineedit L'objet QLineEdit associé à l'option
 * @param default_value La valeur par défaut de l'option
 * @param default_cond Si @c true, force la valeur par défaut
 *
 * Fonction d'initialisation spécifique aux widgets QLineEdit.@n
 * Cette fonction initialise la ligne d'édition @c lineedit correspondant au
 * mot clé @c key en fonction de la valeur retournée par la fonction InitParser::get
 * pour @c key. Si aucune valeur n'est retournée par cette fonction ou si @c
 * default_cond vaut @c true, la valeur par défaut @c default_value est utilisée.
 */
void TabDoxygen::initLineedit(const QString& key, QLineEdit *lineedit, const QString& default_value /*= ""*/, bool default_cond /*= false*/)
{
    if(default_cond)
    {
        lineedit->setText(default_value);
    }
    else
    {
        QString value = m_parser.emptyGroup().get(key);
        if(value.simplified() == QString(""))
        {
            lineedit->setText(default_value);
        }
        else
        {
            lineedit->setText(value);
        }
    }
}

/**
 * @param key Le mot clé de l'option de configuration de Doxygen
 * @param spinbox L'objet QSpinBox associé à l'option
 * @param default_value La valeur par défaut de l'option
 * @param default_cond Si @c true, force la valeur par défaut
 *
 * Fonction d'initialisation spécifique aux widgets QSpinBox.@n
 * Cette fonction initialise le sélecteur d'entier @c spinbox correspondant au
 * mot clé @c key en fonction de la valeur retournée par la fonction InitParser::get
 * pour @c key. Si aucune valeur n'est retournée par cette fonction ou si @c
 * default_cond vaut @c true, la valeur par défaut @c default_value est utilisée.
 */
void TabDoxygen::initSpinbox_(const QString& key, QSpinBox* spinbox, int default_value /*= 0*/, bool default_cond /*= false*/)
{
    int value_int;
    if(default_cond)
    {
        value_int = default_value;
    }
    else
    {
        bool ok;
        QString value = m_parser.emptyGroup().get(key);
        value_int = value.toInt(&ok);
        if(ok)
        {
            if(value_int > spinbox->maximum())
            {
                value_int = spinbox->maximum();
            }
            else if(value_int < spinbox->minimum())
            {
                value_int = spinbox->minimum();
            }
        }
        else
        {
            value_int = default_value;
        }
    }
    spinbox->setValue(value_int);
}

/**
 * Fonction d'enregistrement de la section "Projet" de l'onglet Doxygen.@n
 * Utilise les fonctions @ref SUB_SAVE_DOXYTAB.
 */
void TabDoxygen::save_tabProject()
{
    *m_stream << "# Configuration du projet" << endl;
    saveCombobox("DOXYFILE_ENCODING", ui->comboBox_encoding, "UTF-8");
    saveLineedit("PROJECT_NAME", ui->lineEdit_projectName, "\"My Project\"");
    saveLineedit("PROJECT_NUMBER", ui->lineEdit_projectNumber);
    saveLineedit("PROJECT_BRIEF", ui->lineEdit_projectBrief);
    saveLineedit("PROJECT_LOGO", ui->lineEdit_projectLogo);
    saveLineedit("OUTPUT_DIRECTORY", ui->lineEdit_outputDir);
    saveCheckbox("CREATE_SUBDIRS", ui->checkBox_subDir, false);
    saveCheckbox("ALLOW_UNICODE_NAMES", ui->checkBox_unicodeNames, false);
    saveCombobox("OUTPUT_LANGUAGE", ui->comboBox_outputLanguage, "English");
    saveCheckbox("BRIEF_MEMBER_DESC", ui->checkBox_briefMemberDesc, true);
    saveCheckbox("REPEAT_BRIEF", ui->checkBox_briefRepeat, true);
    saveLineedit("ABBREVIATE_BRIEF", ui->lineEdit_abbreviateBrief, "\"The $name class\" \"The $name widget\" \"The $name file\" is provides specifies contains represents a an the");
    saveCheckbox("ALWAYS_DETAILED_SEC", ui->checkBox_alwaysDetailSec, false);
    saveCheckbox("INLINE_INHERITED_MEMB", ui->checkBox_inlineInheritedMemb, false);
    saveCheckbox("FULL_PATH_NAMES", ui->checkBox_fullPathNames, true);
    if(ui->checkBox_fullPathNames->isChecked())
    {
        saveLineedit("STRIP_FROM_PATH", ui->lineEdit_stripFromPath);
    }
    saveLineedit("STRIP_FROM_INC_PATH", ui->lineEdit_stripFromIncPath);
    saveCheckbox("SHORT_NAMES", ui->checkBox_shortNames, false);
    saveCheckbox("JAVADOC_AUTOBRIEF", ui->checkBox_javadocAutobrief, false);
    saveCheckbox("QT_AUTOBRIEF", ui->checkBox_qtAutobrief, false);
    saveCheckbox("MULTILINE_CPP_IS_BRIEF", ui->checkBox_multilineCppIsBrief, false);
    saveCheckbox("INHERIT_DOCS", ui->checkBox_inheriteDocs, true);
    saveCheckbox("SEPARATE_MEMBER_PAGES", ui->checkBox_separateMemberPages, false);
    saveSpinbox_("TAB_SIZE", ui->spinBox_tabSize, 4);
    saveLineedit("ALIASES", ui->lineEdit_aliases);
    saveLineedit("TCL_SUBST", ui->lineEdit_tclSubst);
    saveCheckbox("OPTIMIZE_OUTPUT_FOR_C", ui->checkBox_optimizeOutputForC, false);
    saveCheckbox("OPTIMIZE_OUTPUT_JAVA", ui->checkBox_optimizeOutputJava, false);
    saveCheckbox("OPTIMIZE_FOR_FORTRAN", ui->checkBox_optimizeOutputFortran, false);
    saveCheckbox("OPTIMIZE_OUTPUT_VHDL", ui->checkBox_optimizeOutputVhdl, false);
    saveLineedit("EXTENSION_MAPPING", ui->lineEdit_extensionMapping);
    saveCheckbox("MARKDOWN_SUPPORT", ui->checkBox_markdownSupport, true);
    saveSpinbox_("TOC_INCLUDE_HEADINGS", ui->spinBox_tocIncludeHeading);
    saveCheckbox("AUTOLINK_SUPPORT", ui->checkBox_autolinkSupport, true);
    saveCheckbox("BUILTIN_STL_SUPPORT", ui->checkBox_builtinStlSupport, false);
    saveCheckbox("CPP_CLI_SUPPORT", ui->checkBox_cppCliSupport, false);
    saveCheckbox("SIP_SUPPORT", ui->checkBox_sipSupport, false);
    saveCheckbox("IDL_PROPERTY_SUPPORT", ui->checkBox_idlPropertySupport, true);
    saveCheckbox("DISTRIBUTE_GROUP_DOC", ui->checkBox_distributeGroupDoc, false);
    saveCheckbox("GROUP_NESTED_COMPOUNDS", ui->checkBox_groupNestedCompounds, false);
    saveCheckbox("SUBGROUPING", ui->checkBox_subgrouping, true);
    saveCheckbox("INLINE_GROUPED_CLASSES", ui->checkBox_inlineGroupedClasses, false);
    saveCheckbox("INLINE_SIMPLE_STRUCTS", ui->checkBox_inlineSimpleStructs, false);
    saveCheckbox("TYPEDEF_HIDES_STRUCT", ui->checkBox_typedefHidesStruct, false);
    saveSpinbox_("LOOKUP_CACHE_SIZE", ui->spinBox_lookupCacheSize);
    *m_stream << endl;
}

/**
 * Fonction d'enregistrement de la section "Build" de l'onglet Doxygen.@n
 * Utilise les fonctions @ref SUB_SAVE_DOXYTAB.
 */
void TabDoxygen::save_tabBuild()
{
    *m_stream << "# Configuration de build" << endl;
    saveCheckbox("EXTRACT_ALL", ui->checkBox_extractAll, false);
    saveCheckbox("EXTRACT_PRIVATE", ui->checkBox_extractPrivate, false);
    saveCheckbox("EXTRACT_PACKAGE", ui->checkBox_extractPackage, false);
    saveCheckbox("EXTRACT_STATIC", ui->checkBox_extractStatic, false);
    saveCheckbox("EXTRACT_LOCAL_CLASSES", ui->checkBox_extractLocalClasses, true);
    saveCheckbox("EXTRACT_LOCAL_METHODS", ui->checkBox_extractLocalClasses, false);
    saveCheckbox("EXTRACT_ANON_NSPACES", ui->checkBox_extractAnonNspaces, false);
    saveCheckbox("HIDE_UNDOC_MEMBERS", ui->checkBox_hideUndocMembers, false);
    saveCheckbox("HIDE_UNDOC_CLASSES", ui->checkBox_hideUndocClasses, false);
    saveCheckbox("HIDE_FRIEND_COMPOUNDS", ui->checkBox_hideFriendCompounds, false);
    saveCheckbox("HIDE_IN_BODY_DOCS", ui->checkBox_hideInBodyDocs, false);
    saveCheckbox("INTERNAL_DOCS", ui->checkBox_internalDocs, false);
    saveCheckbox("CASE_SENSE_NAMES", ui->checkBox_caseSenseNames, true);
    saveCheckbox("HIDE_SCOPE_NAMES", ui->checkBox_hideScopeNames, false);
    saveCheckbox("HIDE_COMPOUND_REFERENCE", ui->checkBox_hideCompoundReference, false);
    saveCheckbox("SHOW_INCLUDE_FILES", ui->checkBox_showIncludeFiles, true);
    saveCheckbox("SHOW_GROUPED_MEMB_INC", ui->checkBox_showGroupedMembInc, false);
    saveCheckbox("FORCE_LOCAL_INCLUDES", ui->checkBox_forceLocalIncludes, false);
    saveCheckbox("INLINE_INFO", ui->checkBox_inlineInfo, true);
    saveCheckbox("SORT_MEMBER_DOCS", ui->checkBox_sortMemberDocs, true);
    saveCheckbox("SORT_BRIEF_DOCS", ui->checkBox_sortBriefDocs, false);
    saveCheckbox("SORT_MEMBERS_CTORS_1ST", ui->checkBox_sortMemberDocs, false);
    saveCheckbox("SORT_GROUP_NAMES", ui->checkBox_sortGroupNames, false);
    saveCheckbox("SORT_BY_SCOPE_NAME", ui->checkBox_sortByScopeName, false);
    saveCheckbox("STRICT_PROTO_MATCHING", ui->checkBox_strictProtoMatching, false);
    saveCheckbox("GENERATE_TODOLIST", ui->checkBox_generateTodolist, true);
    saveCheckbox("GENERATE_TESTLIST", ui->checkBox_generateTestlist, true);
    saveCheckbox("GENERATE_BUGLIST", ui->checkBox_generateBuglist, true);
    saveCheckbox("GENERATE_DEPRECATEDLIST", ui->checkBox_generateDeprecatedlist, true);
    saveLineedit("ENABLED_SECTIONS", ui->lineEdit_enabledSetions);
    saveSpinbox_("MAX_INITIALIZER_LINES", ui->spinBox_maxInitializerLines, 30);
    saveCheckbox("SHOW_USED_FILES", ui->checkBox_showUsedFiles, true);
    saveCheckbox("SHOW_FILES", ui->checkBox_showFiles, true);
    saveCheckbox("SHOW_NAMESPACES", ui->checkBox_showNamespaces, true);
    saveLineedit("FILE_VERSION_FILTER", ui->lineEdit_fileVersionFilter);
    saveLineedit("LAYOUT_FILE", ui->lineEdit_layoutFile);
    saveLineedit("CITE_BIB_FILES", ui->lineEdit_citeBibFiles);
    *m_stream << endl;
}

/**
 * Fonction d'enregistrement de la section "Messages" de l'onglet Doxygen.@n
 * Utilise les fonctions @ref SUB_SAVE_DOXYTAB.
 */
void TabDoxygen::save_tabMsg()
{
    *m_stream << "# Configuration des messages" << endl;
    saveCheckbox("QUIET", ui->checkBox_quiet, false);
    saveCheckbox("WARNINGS", ui->checkBox_warnings, true);
    saveCheckbox("WARN_IF_UNDOCUMENTED", ui->checkBox_warnIfUndocumented, true);
    saveCheckbox("WARN_IF_DOC_ERROR", ui->checkBox_warnIfDocError, true);
    saveCheckbox("WARN_NO_PARAMDOC", ui->checkBox_warnNoParamdoc, false);
    saveCheckbox("WARN_AS_ERROR", ui->checkBox_warnAsError, false);
    saveLineedit("WARN_FORMAT", ui->lineEdit_warnFormat, "\"$file:$line:$text\"");
    saveLineedit("WARN_LOGFILE", ui->lineEdit_warnLogfile);
    *m_stream << endl;
}

/**
 * Fonction d'enregistrement de la section "Fichiers d'entrée" de l'onglet Doxygen.@n
 * Utilise les fonctions @ref SUB_SAVE_DOXYTAB.
 */
void TabDoxygen::save_tabInput()
{
    *m_stream << "# Configuration des entrées" << endl;
    saveLineedit("INPUT", ui->lineEdit_input);
    saveCombobox("INPUT_ENCODING", ui->comboBox_inputEncoding, "UTF-8");
    saveLineedit("FILE_PATTERNS", ui->lineEdit_filePatterns, "*.c *.cc *.cxx *.cpp *.c++ *.java *.ii *.ixx *.ipp *.i++ *.inl *.idl *.ddl *.odl *.h *.hh *.hxx *.hpp *.h++ *.cs *.d *.php *.php4 *.php5 *.phtml *.inc *.m *.markdown *.md *.mm *.dox *.py *.pyw *.f90 *.f95 *.f03 *.f08 *.f *.for *.tcl *.vhd *.vhdl *.ucf *.qsf");
    saveCheckbox("RECURSIVE", ui->checkBox_recursive, false);
    saveLineedit("EXCLUDE", ui->lineEdit_exclude);
    saveCheckbox("EXCLUDE_SYMLINKS", ui->checkBox_excludeSymlinks, false);
    saveLineedit("EXCLUDE_PATTERNS", ui->lineEdit_excludePatterns);
    saveLineedit("EXCLUDE_SYMBOLS", ui->lineEdit_excludeSymbols);
    saveLineedit("EXAMPLE_PATH", ui->lineEdit_examplePath);
    saveLineedit("EXAMPLE_PATTERNS", ui->lineEdit_examplePatterns, "*");
    saveCheckbox("EXAMPLE_RECURSIVE", ui->checkBox_exampleRecursive, false);
    saveLineedit("IMAGE_PATH", ui->lineEdit_imagePath);
    saveLineedit("INPUT_FILTER", ui->lineEdit_inputFilter);
    saveLineedit("FILTER_PATTERNS", ui->lineEdit_filterPatterns);
    saveCheckbox("FILTER_SOURCE_FILES", ui->checkBox_filterSourceFiles, false);
    saveLineedit("FILTER_SOURCE_PATTERNS", ui->lineEdit_filterSourcePatterns);
    saveLineedit("USE_MDFILE_AS_MAINPAGE", ui->lineEdit_useMdfileAsMainpage);
    *m_stream << endl;
}

/**
 * Fonction d'enregistrement de la section "Recherche des sources" de l'onglet Doxygen.@n
 * Utilise les fonctions @ref SUB_SAVE_DOXYTAB.
 */
void TabDoxygen::save_tabSource()
{
    *m_stream << "# Configurartion de la recherche de sources" << endl;
    saveCheckbox("SOURCE_BROWSER", ui->checkBox_sourceBrowser, false);
    saveCheckbox("INLINE_SOURCES", ui->checkBox_inlineSources, false);
    saveCheckbox("STRIP_CODE_COMMENTS", ui->checkBox_stripCodeComments, true);
    saveCheckbox("REFERENCED_BY_RELATION", ui->checkBox_referencedByRelation, false);
    saveCheckbox("REFERENCES_RELATION", ui->checkBox_referencesRelation, false);
    saveCheckbox("REFERENCES_LINK_SOURCE", ui->checkBox_referencesLinkSource, true);
    if(ui->checkBox_sourceBrowser->isChecked())
    {
        saveCheckbox("SOURCE_TOOLTIPS", ui->checkBox_sourceTooltips, true);
        saveCheckbox("USE_HTAGS", ui->checkBox_useHtags, false);
    }
    saveCheckbox("VERBATIM_HEADERS", ui->checkBox_verbatimHeaders, true);
    saveCheckbox("CLANG_ASSISTED_PARSING", ui->checkBox_clangAssistedParsing, false);
    saveLineedit("CLANG_OPTIONS", ui->lineEdit_clangOptions);
    *m_stream << endl;
    *m_stream << "# Configuration de l'index alphabétique" << endl;
    saveGroupbox("ALPHABETICAL_INDEX", ui->groupBox_alphabeticalIndex, true);
    saveSpinbox_("COLS_IN_ALPHA_INDEX", ui->spinBox_colsInAlphaIndex, 5);
    saveLineedit("IGNORE_PREFIX", ui->lineEdit_ignorePrefix);
    *m_stream << endl;
}

/**
 * Fonction d'enregistrement de la section "HTML" de l'onglet Doxygen.@n
 * Utilise les fonctions @ref SUB_SAVE_DOXYTAB.
 */
void TabDoxygen::save_tabHtml()
{
    *m_stream << "# Configuration de sortie HTML" << endl;
    saveGroupbox("GENERATE_HTML", ui->groupBox_generateHtml, true);
    if(ui->groupBox_generateHtml->isChecked())
    {
        saveLineedit("HTML_OUTPUT", ui->lineEdit_htmlOutput, "html");
        saveLineedit("HTML_FILE_EXTENSION", ui->lineEdit_htmlFileExtension, ".html");
        saveLineedit("HTML_HEADER", ui->lineEdit_htmlHeader);
        saveLineedit("HTML_FOOTER", ui->lineEdit_htmlFooter);
        saveLineedit("HTML_STYLESHEET", ui->lineEdit_htmlStylesheet);
        saveLineedit("HTML_EXTRA_STYLESHEET", ui->lineEdit_htmlExtraStylesheet);
        saveLineedit("HTML_EXTRA_FILES", ui->lineEdit_htmlExtraFiles);
        saveSpinbox_("HTML_COLORSTYLE_HUE", ui->spinBox_htmlColorstyleHue, 220);
        saveSpinbox_("HTML_COLORSTYLE_SAT", ui->spinBox_htmlColorstyleSat, 100);
        saveSpinbox_("HTML_COLORSTYLE_GAMMA", ui->spinBox_htmlColorstyleGamma, 80);
        saveCheckbox("HTML_TIMESTAMP", ui->checkBox_htmlTimestamp, false);
        saveCheckbox("HTML_DYNAMIC_SECTIONS", ui->checkBox_htmlDynamicSections, false);
        saveSpinbox_("HTML_INDEX_NUM_ENTRIES", ui->spinBox_htmlIndexNumEntries, 100);
        saveGroupbox("GENERATE_DOCSET", ui->groupBox_generateDocset, false);
        if(ui->groupBox_generateDocset->isChecked())
        {
            saveLineedit("DOCSET_FEEDNAME", ui->lineEdit_docsetFeedname, "\"Doxygengenerateddocs\"");
            saveLineedit("DOCSET_BUNDLE_ID", ui->lineEdit_docsetBundleId, "org.doxygen.Project");
            saveLineedit("DOCSET_PUBLISHER_ID", ui->lineEdit_docsetPublisherId, "org.doxygen.Publisher");
            saveLineedit("DOCSET_PUBLISHER_NAME", ui->lineEdit_docsetPublisherName, "Publisher");
        }
        saveGroupbox("GENERATE_HTMLHELP", ui->groupBox_generateHtmlhelp, false);
        if(ui->groupBox_generateHtmlhelp->isChecked())
        {
            saveLineedit("CHM_FILE", ui->lineEdit_chmFile);
            saveLineedit("HHC_LOCATION", ui->lineEdit_hhcLocation);
            saveCheckbox("GENERATE_CHI", ui->checkBox_generateChi, false);
            saveLineedit("CHM_INDEX_ENCODING", ui->lineEdit_hhcLocation);
            saveCheckbox("BINARY_TOC", ui->checkBox_binaryToc, false);
            saveCheckbox("TOC_EXPAND", ui->checkBox_tocExpand, false);
        }
        saveGroupbox("GENERATE_QHP", ui->groupBox_generateQhp, false);
        if(ui->groupBox_generateQhp->isChecked())
        {
            saveLineedit("QCH_FILE", ui->lineEdit_qchFile);
            saveLineedit("QHP_NAMESPACE", ui->lineEdit_qhpNamespace, "org.doxygen.Project");
            saveLineedit("QHP_VIRTUAL_FOLDER", ui->lineEdit_qhpVirtualFolder, "doc");
            saveLineedit("QHP_CUST_FILTER_NAME", ui->lineEdit_qhpCustFilterName);
            saveLineedit("QHP_CUST_FILTER_ATTRS", ui->lineEdit_qhpCustFilterAttrs);
            saveLineedit("QHP_SECT_FILTER_ATTRS", ui->lineEdit_qhpSectFilterAttrs);
            saveLineedit("QHG_LOCATION", ui->lineEdit_qhgLocation);
        }
        saveGroupbox("GENERATE_ECLIPSEHELP", ui->groupBox_generateEclipsehelp, false);
        if(ui->groupBox_generateEclipsehelp->isChecked())
        {
            saveLineedit("ECLIPSE_DOC_ID", ui->lineEdit_eclipseDocId, "org.doxygen.Project");
        }
        saveCheckbox("DISABLE_INDEX", ui->checkBox_disableIndex, false);
        saveCheckbox("GENERATE_TREEVIEW", ui->checkBox_generateTreeview, false);
        saveSpinbox_("ENUM_VALUES_PER_LINE", ui->spinBox_enumValuesPerLine, 4);
        saveSpinbox_("TREEVIEW_WIDTH", ui->spinBox_treeviewWidth, 250);
        saveCheckbox("EXT_LINKS_IN_WINDOW", ui->checkBox_extLinksInWindow, false);
        saveSpinbox_("FORMULA_FONTSIZE", ui->spinBox_formulaFontsize, 10);
        saveCheckbox("FORMULA_TRANSPARENT", ui->checkBox_formulaTransparent, true);
        saveGroupbox("USE_MATHJAX", ui->groupBox_useMathjax, false);
        if(ui->groupBox_useMathjax->isChecked())
        {
            saveCombobox("MATHJAX_FORMAT", ui->comboBox_mathjaxFormat, "HTML-CSS");
            saveLineedit("MATHJAX_RELPATH", ui->lineEdit_mathjaxRelpath, "http://cdn.mathjax.org/mathjax/latest");
            saveLineedit("MATHJAX_EXTENSIONS", ui->lineEdit_mathjaxExtensions);
            saveLineedit("MATHJAX_CODEFILE", ui->lineEdit_mathjaxCodefile);
        }
        saveGroupbox("SEARCHENGINE", ui->groupBox_searchengine, true);
        if(ui->groupBox_searchengine->isChecked())
        {
            saveCheckbox("SERVER_BASED_SEARCH", ui->checkBox_serverBasedSearch, false);
            saveCheckbox("EXTERNAL_SEARCH", ui->checkBox_externalSearch, false);
            saveLineedit("SEARCHENGINE_URL", ui->lineEdit_searchengineUrl);
            saveLineedit("SEARCHDATA_FILE", ui->lineEdit_searchdataFile, "searchdata.xml");
            saveLineedit("EXTERNAL_SEARCH_ID", ui->lineEdit_externalSearchId);
            saveLineedit("EXTRA_SEARCH_MAPPINGS", ui->lineEdit_extraSearchMapping);
        }
    }
    *m_stream << endl;
}

/**
 * Fonction d'enregistrement de la section "Autres sorties" de l'onglet Doxygen.@n
 * Utilise les fonctions @ref SUB_SAVE_DOXYTAB.
 */
void TabDoxygen::save_tabOutput()
{
    *m_stream << "# Configuration de sortie LaTeX" << endl;
    saveGroupbox("GENERATE_LATEX", ui->groupBox_generateLatex, true);
    if(ui->groupBox_generateLatex->isChecked())
    {
        saveLineedit("LATEX_OUTPUT", ui->lineEdit_latexOutput, "latex");
        saveLineedit("LATEX_CMD_NAME", ui->lineEdit_latexCmdName, "latex");
        saveLineedit("MAKEINDEX_CMD_NAME", ui->lineEdit_makeindexCmdName, "makeindex");
        saveCheckbox("COMPACT_LATEX", ui->checkBox_compatLatex, false);
        saveCombobox("PAPER_TYPE", ui->comboBox_paperType, "a4");
        saveLineedit("EXTRA_PACKAGES", ui->lineEdit_extraPackages);
        saveLineedit("LATEX_HEADER", ui->lineEdit_latexHeader);
        saveLineedit("LATEX_FOOTER", ui->lineEdit_latexFooter);
        saveLineedit("LATEX_EXTRA_STYLESHEET", ui->lineEdit_latexExtraStylesheet);
        saveLineedit("LATEX_EXTRA_FILES", ui->lineEdit_latexExtraFiles);
        saveCheckbox("PDF_HYPERLINKS", ui->checkBox_pdfHyperlinks, true);
        saveCheckbox("USE_PDFLATEX", ui->checkBox_usePdflatex, true);
        saveCheckbox("LATEX_BATCHMODE", ui->checkBox_latexBatchmode, false);
        saveCheckbox("LATEX_HIDE_INDICES", ui->checkBox_latexHideIndices, false);
        saveCheckbox("LATEX_SOURCE_CODE", ui->checkBox_latexSourceCode, false);
        saveLineedit("LATEX_BIB_STYLE", ui->lineEdit_latexBibStyle, "plain");
        saveCheckbox("LATEX_TIMESTAMP", ui->checkBox_latexTimestamp, false);
    }
    *m_stream << endl;
    *m_stream << "# Configuration de sortie RTF" << endl;
    saveGroupbox("GENERATE_RTF", ui->groupBox_generateRtf, false);
    if(ui->groupBox_generateRtf->isChecked())
    {
        saveLineedit("RTF_OUTPUT", ui->lineEdit_rtfOutput, "rtf");
        saveCheckbox("COMPACT_RTF", ui->checkBox_compactRtf, false);
        saveCheckbox("RTF_HYPERLINKS", ui->checkBox_rtfHyperlinks, false);
        saveLineedit("RTF_STYLESHEET_FILE", ui->lineEdit_rtfStylesheetFile);
        saveLineedit("RTF_EXTENSIONS_FILE", ui->lineEdit_rtfExtensionsFile);
        saveCheckbox("RTF_SOURCE_CODE", ui->checkBox_rtfSourceCode, false);
    }
    *m_stream << endl;
    *m_stream << "# Configuration de sortie MAN" << endl;
    saveGroupbox("GENERATE_MAN", ui->groupBox_generateMan, false);
    if(ui->groupBox_generateMan->isChecked())
    {
        saveLineedit("MAN_OUTPUT", ui->lineEdit_manOutput, "man");
        saveLineedit("MAN_EXTENSION", ui->lineEdit_manExtension, ".3");
        saveLineedit("MAN_SUBDIR", ui->lineEdit_manSubdir);
        saveCheckbox("MAN_LINKS", ui->checkBox_manLinks, false);
    }
    *m_stream << endl;
    *m_stream << "# Configuration de sortie XML" << endl;
    saveGroupbox("GENERATE_XML", ui->groupBox_generateXml, false);
    if(ui->groupBox_generateXml->isChecked())
    {
        saveLineedit("XML_OUTPUT", ui->lineEdit_xmlOutput, "xml");
        saveCheckbox("XML_PROGRAMLISTING", ui->checkBox_xmlProgramlisting, true);
    }
    *m_stream << endl;
    *m_stream << "# Configuration de sortie DocBook" << endl;
    saveGroupbox("GENERATE_DOCBOOK", ui->groupBox_generateDocbook, false);
    if(ui->groupBox_generateDocbook->isChecked())
    {
        saveLineedit("DOCBOOK_OUTPUT", ui->lineEdit_docbookOutput, "docbook");
        saveCheckbox("DOCBOOK_PROGRAMLISTING", ui->checkBox_docbookProgramlisting, false);
    }
    *m_stream << endl;
    *m_stream << "# Configuration des définitions AutoGen" << endl;
    saveCheckbox("GENERATE_AUTOGEN_DEF", ui->checkBox_generateAutogenDef, false);
    *m_stream << endl;
    *m_stream << "# Configuration du module Perl" << endl;
    saveGroupbox("GENERATE_PERLMOD", ui->groupBox_generatePerlmod, false);
    if(ui->groupBox_generateXml->isChecked())
    {
        saveCheckbox("PERLMOD_LATEX", ui->checkBox_perlmodLatex, false);
        saveCheckbox("PERLMOD_PRETTY", ui->checkBox_perlmodPretty, true);
        saveLineedit("PERLMOD_MAKEVAR_PREFIX", ui->lineEdit_perlmodMakevarPrefix);
    }
    *m_stream << endl;
}

/**
 * Fonction d'enregistrement de la section "Préprocesseur" de l'onglet Doxygen.@n
 * Utilise les fonctions @ref SUB_SAVE_DOXYTAB.
 */
void TabDoxygen::save_tabProcessor()
{
    *m_stream << "# Configuration du processeur" << endl;
    saveGroupbox("ENABLE_PREPROCESSING", ui->groupBox_enablePreprocessing, true);
    if(ui->groupBox_enablePreprocessing->isChecked())
    {
        saveCheckbox("MACRO_EXPANSION", ui->checkBox_macroExpansion, false);
        saveCheckbox("EXPAND_ONLY_PREDEF", ui->checkBox_expandOnlyPredef, false);
        saveCheckbox("SEARCH_INCLUDES", ui->checkBox_searchIncludes, true);
        if(ui->checkBox_searchIncludes->isChecked())
        {
            saveLineedit("INCLUDE_PATH", ui->lineEdit_includePath);
        }
        saveLineedit("INCLUDE_FILE_PATTERNS", ui->lineEdit_includeFilePatterns);
        saveLineedit("PREDEFINED", ui->lineEdit_predefined);
        saveLineedit("EXPAND_AS_DEFINED", ui->lineEdit_expandAsDefined);
        saveCheckbox("SKIP_FUNCTION_MACROS", ui->checkBox_skipFunctionMacros, true);
    }
    *m_stream << endl;
}

/**
 * Fonction d'enregistrement de la section "Références externes" de l'onglet Doxygen.@n
 * Utilise les fonctions @ref SUB_SAVE_DOXYTAB.
 */
void TabDoxygen::save_tabExternRef()
{
    *m_stream << "# Configuration des références externes" << endl;
    saveLineedit("TAGFILES", ui->lineEdit_tagfiles);
    saveLineedit("GENERATE_TAGFILE", ui->lineEdit_generateTagfile);
    saveCheckbox("ALLEXTERNALS", ui->checkBox_allexternals, false);
    saveCheckbox("EXTERNAL_GROUPS", ui->checkBox_externalGroups, true);
    saveCheckbox("EXTERNAL_PAGES", ui->checkBox_externalPages, true);
    saveLineedit("PERL_PATH", ui->lineEdit_perlPath, "/usr/bin/perl");
    *m_stream << endl;
}

/**
 * Fonction d'enregistrement de la section "Graphiques" de l'onglet Doxygen.@n
 * Utilise les fonctions @ref SUB_SAVE_DOXYTAB.
 */
void TabDoxygen::save_tabGraph()
{
    *m_stream << "# Configuration de l'outil DOT" << endl;
    saveCheckbox("CLASS_DIAGRAMS", ui->checkBox_classDiagrams, true);
    saveLineedit("MSCGEN_PATH", ui->lineEdit_mscgenPath);
    saveLineedit("DIA_PATH", ui->lineEdit_diaPath);
    saveCheckbox("HIDE_UNDOC_RELATIONS", ui->checkBox_hideUndocRelations, true);
    saveGroupbox("HAVE_DOT", ui->groupBox_haveDot, true);
    if(ui->groupBox_haveDot->isChecked())
    {
        saveSpinbox_("DOT_NUM_THREADS", ui->spinBox_dotNumThreads, 0);
        saveFontCbox("DOT_FONTNAME", ui->fontComboBox_dotFontName, "Helvetica");
        saveSpinbox_("DOT_FONTSIZE", ui->spinBox_dotFontsize, 10);
        saveLineedit("DOT_FONTPATH", ui->lineEdit_dotFontpath);
        saveCheckbox("CLASS_GRAPH", ui->checkBox_classGraph, true);
        saveCheckbox("COLLABORATION_GRAPH", ui->checkBox_collaborationGraph, true);
        saveCheckbox("GROUP_GRAPHS", ui->checkBox_groupGraphs, true);
        saveCheckbox("UML_LOOK", ui->checkBox_umlLook, false);
        saveSpinbox_("UML_LIMIT_NUM_FIELDS", ui->spinBox_umlLimitNumFields, 10);
        saveCheckbox("TEMPLATE_RELATIONS", ui->checkBox_templateRelations, false);
        saveCheckbox("INCLUDE_GRAPH", ui->checkBox_includeGraph, true);
        saveCheckbox("INCLUDED_BY_GRAPH", ui->checkBox_includedByGraph, true);
        saveCheckbox("CALL_GRAPH", ui->checkBox_callGraph, false);
        saveCheckbox("CALLER_GRAPH", ui->checkBox_callerGraph, false);
        saveCheckbox("GRAPHICAL_HIERARCHY", ui->checkBox_graphicalHierarchy, true);
        saveCheckbox("DIRECTORY_GRAPH", ui->checkBox_directoryGraph, true);
        saveCombobox("DOT_IMAGE_FORMAT", ui->comboBox_dotImageFormat, "png");
        saveCheckbox("INTERACTIVE_SVG", ui->checkBox_interactiveSvg, false);
        saveLineedit("DOT_PATH", ui->lineEdit_dotPath);
        saveLineedit("DOTFILE_DIRS", ui->lineEdit_dotfileDirs);
        saveSpinbox_("DOT_GRAPH_MAX_NODES", ui->spinBox_dotGraphMaxNodes, 50);
        saveSpinbox_("MAX_DOT_GRAPH_DEPTH", ui->spinBox_maxDotGraphDepth);
        saveCheckbox("DOT_TRANSPARENT", ui->checkBox_dotTransparent, false);
        saveCheckbox("DOT_MULTI_TARGETS", ui->checkBox_dotMultiTargets, false);
        saveCheckbox("GENERATE_LEGEND", ui->checkBox_generateLegend, true);
        saveCheckbox("DOT_CLEANUP", ui->checkBox_dotCleanup, true);
    }
    saveLineedit("MSCFILE_DIRS", ui->lineEdit_mscfileDirs);
    saveLineedit("DIAFILE_DIRS", ui->lineEdit_diafileDirs);
    saveLineedit("PLANTUML_JAR_PATH", ui->lineEdit_plantumlJarPath);
    saveLineedit("PLANTUML_CFG_FILE", ui->lineEdit_plantumlCfgFile);
    saveLineedit("PLANTUML_INCLUDE_PATH", ui->lineEdit_plantumlIncludePath);
    *m_stream << endl;
}

/**
 * @param key Le mot clé de l'option de configuration de Doxygen
 * @param checkbox L'objet QCheckBox associé à l'option
 * @param default_value La valeur par défaut de l'option
 *
 * Fonction d'enregistrement spécifique aux widgets QCheckBox.@n
 * Cette fonction enregistre l'état de la case @c checkbox correspondant au mot clé
 * @c key seulement si celui-ci diffère de la valeur par défaut @c default_value.
 */
void TabDoxygen::saveCheckbox(const QString& key, QCheckBox* checkbox, bool default_value)
{
    if((checkbox->isChecked() && default_value)
       || (!checkbox->isChecked() && !default_value))
    {
        return;
    }

    *m_stream << key << "=";
    if(checkbox->isChecked())
    {
        *m_stream << DOC_YES;
    }
    else
    {
        *m_stream << DOC_NO;
    }
    *m_stream << endl;
}

/**
 * @param key Le mot clé de l'option de configuration de Doxygen
 * @param groupbox L'objet QGroupBox associé à l'option
 * @param default_value La valeur par défaut de l'option
 *
 * Fonction d'enregistrement spécifique aux widgets QGroupBox.@n
 * Cette fonction enregistre l'état de la section @c groupbox correspondant au mot clé
 * @c key seulement si celui-ci diffère de la valeur par défaut @c default_value.
 */
void TabDoxygen::saveGroupbox(const QString& key, QGroupBox* groupbox, bool default_value)
{
    if((groupbox->isChecked() && default_value)
       || (!groupbox->isChecked() && !default_value))
    {
        return;
    }

    *m_stream << key << "=";
    if(groupbox->isChecked())
    {
        *m_stream << DOC_YES;
    }
    else
    {
        *m_stream << DOC_NO;
    }
    *m_stream << endl;
}

/**
 * @param key Le mot clé de l'option de configuration de Doxygen
 * @param combobox L'objet QComboBox associé à l'option
 * @param default_value La valeur par défaut de l'option
 *
 * Fonction d'enregistrement spécifique aux widgets QComboBox.@n
 * Cette fonction enregistre la valeur de la liste déroulante @c combobox correspondant au mot clé
 * @c key seulement si celle-ci diffère de la valeur par défaut @c default_value et n'est pas vide.
 */
void TabDoxygen::saveCombobox(const QString& key, QComboBox* combobox, const QString& default_value /*= ""*/)
{
    if(combobox->currentText() != QString("")
       && combobox->currentText() != default_value)
    {
        *m_stream << key << "=" << combobox->currentText() << endl;
    }
}

/**
 * @param key Le mot clé de l'option de configuration de Doxygen
 * @param fontcombobox L'objet QFontComboBox associé à l'option
 * @param default_value La valeur par défaut de l'option
 *
 * Fonction d'enregistrement spécifique aux widgets QFontComboBox.@n
 * Cette fonction enregistre la valeur de la liste de polices @c fontcombobox correspondant au mot clé
 * @c key seulement si celle-ci diffère de la valeur par défaut @c default_value et n'est pas vide.
 */
void TabDoxygen::saveFontCbox(const QString& key, QFontComboBox* fontcombobox, const QString& default_value /*= ""*/)
{
    if(fontcombobox->currentText() != QString("")
       && fontcombobox->currentText() != default_value)
    {
        *m_stream << key << "=" << fontcombobox->currentText() << endl;
    }
}

/**
 * @param key Le mot clé de l'option de configuration de Doxygen
 * @param lineedit L'objet QLineEdit associé à l'option
 * @param default_value La valeur par défaut de l'option
 *
 * Fonction d'enregistrement spécifique aux widgets QLineEdit.@n
 * Cette fonction enregistre la valeur de la ligne d'édition @c lineedit correspondant au mot clé
 * @c key seulement si celle-ci diffère de la valeur par défaut @c default_value et n'est pas vide.
 */
void TabDoxygen::saveLineedit(const QString& key, QLineEdit* lineedit, const QString& default_value /*= ""*/)
{
    if(lineedit->text() != QString("")
       && lineedit->text() != default_value)
    {
        *m_stream << key << "=" << lineedit->text() << endl;
    }
}

/**
 * @param key Le mot clé de l'option de configuration de Doxygen
 * @param spinbox L'objet QSpinBox associé à l'option
 * @param default_value La valeur par défaut de l'option
 *
 * Fonction d'enregistrement spécifique aux widgets QSpinBox.@n
 * Cette fonction enregistre la valeur du sélecteur d'entier @c spinbox correspondant au mot clé
 * @c key seulement si celui-ci diffère de la valeur par défaut @c default_value.
 */
void TabDoxygen::saveSpinbox_(const QString& key, QSpinBox* spinbox, int default_value /*= 0*/)
{
    if(spinbox->value() != default_value)
    {
        *m_stream << key << "=" << spinbox->value() << endl;
    }
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection de logo de projet. Il appelle la fonction getOpenFile()
 * avec comme argument la ligne d'édition correspondant au chemin vers le logo du
 * projet.
 */
void TabDoxygen::on_toolButton_projectLogo_clicked()
{
    getOpenFile(ui->lineEdit_projectLogo);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection du dossier de sortie. Il appelle la fonction getDir()
 * avec comme argument la ligne d'édition correspondant au chemin vers le dossier de
 * sortie.
 */
void TabDoxygen::on_toolButton_outputDir_clicked()
{
    getDir(ui->lineEdit_outputDir);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection de filtre de version. Il appelle la fonction getOpenFile()
 * avec comme argument la ligne d'édition correspondant au chemin vers lefiltre de
 * version.
 */
void TabDoxygen::on_toolButton_fileVersionFilter_clicked()
{
    getOpenFile(ui->lineEdit_fileVersionFilter);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection de fichier de structure. Il appelle la fonction getOpenFile()
 * avec comme argument la ligne d'édition correspondant au chemin vers le fichier de
 * structure.
 */
void TabDoxygen::on_toolButton_layoutFile_clicked()
{
    getOpenFile(ui->lineEdit_layoutFile);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection de fichiers bibliographiques. Il appelle la fonction
 * getOpenFiles() avec comme argument la ligne d'édition correspondant aux
 * chemins vers les fichiers bibliographiques.
 */
void TabDoxygen::on_toolButton_citeBibFiles_clicked()
{
    getOpenFiles(ui->lineEdit_citeBibFiles);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection du fichier de log. Il appelle la fonction getSaveFile()
 * avec comme argument la ligne d'édition correspondant au chemin vers le fichier de
 * log pour les warnings.
 */
void TabDoxygen::on_toolButton_warnLogfile_clicked()
{
    getSaveFile(ui->lineEdit_warnLogfile);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection des fichiers exemples. Il appelle la fonction getOpenFiles()
 * avec comme argument la ligne d'édition correspondant aux chemins vers les fichiers
 * exemples.
 */
void TabDoxygen::on_toolButton_examplePath_clicked()
{
    getOpenFiles(ui->lineEdit_examplePath);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection des images. Il appelle la fonction getOpenFiles() avec
 * comme argument la ligne d'édition correspondant aux chemins vers les images.
 */
void TabDoxygen::on_toolButton_imagePath_clicked()
{
    getOpenFiles(ui->lineEdit_imagePath);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection du filtre d'entrée. Il appelle la fonction getOpenFile()
 * avec comme argument la ligne d'édition correspondant au chemin vers le filtre
 * d'entrée.
 */
void TabDoxygen::on_toolButton_inputFilter_clicked()
{
    getOpenFile(ui->lineEdit_inputFilter);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection de fichier Mdfile pour la page principale. Il appelle la fonction
 * getOpenFile() avec comme argument la ligne d'édition correspondant au
 * chemin vers le fichier Mdfile.
 */
void TabDoxygen::on_toolButton_useMdfileAsMainpage_clicked()
{
    getOpenFile(ui->lineEdit_useMdfileAsMainpage);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection du header HTML. Il appelle la fonction getOpenFile()
 * avec comme argument la ligne d'édition correspondant au chemin vers le header HTML.
 */
void TabDoxygen::on_toolButton_htmlHeader_clicked()
{
    getOpenFile(ui->lineEdit_htmlHeader);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection du footer HTML. Il appelle la fonction getOpenFile()
 * avec comme argument la ligne d'édition correspondant au chemin vers le footer HTML.
 */
void TabDoxygen::on_toolButton_htmlFooter_clicked()
{
    getOpenFile(ui->lineEdit_htmlFooter);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection de la feuille de style HTML. Il appelle la fonction getOpenFile()
 * avec comme argument la ligne d'édition correspondant au chemin vers la feuille de style HTML.
 */
void TabDoxygen::on_toolButton_htmlStylesheet_clicked()
{
    getOpenFile(ui->lineEdit_htmlStylesheet);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection de la feuille de style HTML supplémentaire. Il appelle la fonction
 * getOpenFile() avec comme argument la ligne d'édition correspondant au
 * chemin vers la feuille de style HTM supplémentaire.
 */
void TabDoxygen::on_toolButton_htmlExtraStylesheet_clicked()
{
    getOpenFile(ui->lineEdit_htmlExtraStylesheet);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection du compilateur de l'aide HTML. Il appelle la fonction
 * getOpenFile() avec comme argument la ligne d'édition correspondant au
 * chemin vers le compilateur de l'aide HTML.
 */
void TabDoxygen::on_toolButton_hhcLocation_clicked()
{
    getOpenFile(ui->lineEdit_hhcLocation);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection du compilateur de l'aide Qt, qhelpgenerator. Il appelle la fonction
 * getOpenFile() avec comme argument la ligne d'édition correspondant au
 * chemin vers le compilateur de l'aide Qt.
 */
void TabDoxygen::on_toolButton_qhgLocation_clicked()
{
    getOpenFile(ui->lineEdit_qhgLocation);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection du fichier de script MathJax. Il appelle la fonction
 * getOpenFile() avec comme argument la ligne d'édition correspondant au
 * chemin vers le fichier de script MathJax.
 */
void TabDoxygen::on_toolButton_mathjaxCodefile_clicked()
{
    getOpenFile(ui->lineEdit_mathjaxCodefile);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection du header LaTeX. Il appelle la fonction getOpenFile()
 * avec comme argument la ligne d'édition correspondant au chemin vers le header LaTeX.
 */
void TabDoxygen::on_toolButton_latexHeader_clicked()
{
    getOpenFile(ui->lineEdit_latexHeader);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection du footer LaTeX. Il appelle la fonction getOpenFile()
 * avec comme argument la ligne d'édition correspondant au chemin vers le footer LaTeX.
 */
void TabDoxygen::on_toolButton_latexFooter_clicked()
{
    getOpenFile(ui->lineEdit_latexFooter);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection de la feuille de style LaTeX supplémentaire. Il appelle la fonction
 * getOpenFile() avec comme argument la ligne d'édition correspondant au
 * chemin vers le la feuille de style LaTeX supplémentaire.
 */
void TabDoxygen::on_toolButton_latexExtraStylesheet_clicked()
{
    getOpenFile(ui->lineEdit_latexExtraStylesheet);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection des fichiers LaTeX supplémentaire. Il appelle la fonction
 * getOpenFiles() avec comme argument la ligne d'édition correspondant au
 * chemin vers les fichiers LaTeX supplémentaire.
 */
void TabDoxygen::on_toolButton_latexExtraFiles_clicked()
{
    getOpenFiles(ui->lineEdit_latexExtraFiles);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection de la feuille de style RTF. Il appelle la fonction getOpenFile()
 * avec comme argument la ligne d'édition correspondant au chemin vers la feuille de
 * style RTF.
 */
void TabDoxygen::on_toolButton_rtfStylesheetFile_clicked()
{
    getOpenFile(ui->lineEdit_rtfStylesheetFile);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection du fichier d'extension RTF. Il appelle la fonction getOpenFile()
 * avec comme argument la ligne d'édition correspondant au chemin vers le fichier
 * d'extension RTF.
 */
void TabDoxygen::on_toolButton_rtfExtensionsFile_clicked()
{
    getOpenFile(ui->lineEdit_rtfExtensionsFile);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection du script interpréteur Perl. Il appelle la fonction getDir()
 * avec comme argument la ligne d'édition correspondant au chemin vers le script interpréteur
 * Perl.
 */
void TabDoxygen::on_toolButton_perlPath_clicked()
{
    getDir(ui->lineEdit_perlPath);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection du dossier de l'outil MsGen Tool. Il appelle la fonction getDir()
 * avec comme argument la ligne d'édition correspondant au chemin vers le dossier de l'outil
 * MsGen Tool.
 */
void TabDoxygen::on_toolButton_mscgenPath_clicked()
{
    getDir(ui->lineEdit_mscgenPath);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection du dossier de l'outil Dia. Il appelle la fonction getDir()
 * avec comme argument la ligne d'édition correspondant au chemin vers le dossier de
 * l'outil Dia.
 */
void TabDoxygen::on_toolButton_diaPath_clicked()
{
    getDir(ui->lineEdit_diaPath);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection du dossier des polices d'écriture pour DOT. Il appelle la fonction
 * getDir() avec comme argument la ligne d'édition correspondant au
 * chemin vers le dossier des polices d'criture pour DOT.
 */
void TabDoxygen::on_toolButton_dotFontpath_clicked()
{
    getDir(ui->lineEdit_dotFontpath);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection du dossier de l'outil DOT. Il appelle la fonction getDir()
 * avec comme argument la ligne d'édition correspondant au chemin vers le dossier de l'outil
 * DOT.
 */
void TabDoxygen::on_toolButton_dotPath_clicked()
{
    getDir(ui->lineEdit_dotPath);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection du dossier de l'exécutable de PlantUML. Il appelle la fonction
 * getDir() avec comme argument la ligne d'édition correspondant au
 * chemin vers le dossier de l'exécutable de PlantUML.
 */
void TabDoxygen::on_toolButton_plantumlJarPath_clicked()
{
    getOpenFile(ui->lineEdit_plantumlJarPath);
}

/**
 * Ce connecteur est activé par un clic souris de l'utilisateur sur le bouton outil
 * de sélection du dossier de configuration de l'exécutable de PlantUML. Il appelle la
 * fonction getDir() avec comme argument la ligne d'édition correspondant
 * au chemin vers le dossier de configuration de l'exécutable de PlantUML.
 */
void TabDoxygen::on_toolButton_plantumlCfgFile_clicked()
{
    getOpenFile(ui->lineEdit_plantumlCfgFile);
}

/**
 * @param lineedit Ligne d'édition QLineEdit associée
 *
 * Ouvre une fenêtre de dialogue pour indiquer un fichier. Si un fichier est
 * sélectionné, appelle la méthode writePath() avec comme arguments le
 * chemin vers le fichier sélectionné et @c lineedit.@n
 */
void TabDoxygen::getSaveFile(QLineEdit* lineedit)
{
    QString result = "";
    result = QFileDialog::getSaveFileName(this,
                                          "Enregistrer sous",
                                          qCtx->lastSearch());
    if(result != QString(""))
    {
        QFileInfo fileInfo(result);
        qCtx->setLastSearch(fileInfo.absoluteFilePath());
        writePath(fileInfo.absoluteFilePath(), lineedit);
    }
}

/**
 * @param lineedit Ligne d'édition QLineEdit associée
 *
 * Ouvre une fenêtre de dialogue pour recherché un fichier éxistant. Si un
 * fichier est sélectionné, appelle la méthode writePath() avec comme
 * arguments le chemin vers le fichier sélectionné et @c lineedit.
 */
void TabDoxygen::getOpenFile(QLineEdit* lineedit)
{
    QString result = "";
    result = QFileDialog::getOpenFileName(this,
                                          "Fichier",
                                          qCtx->lastSearch());
    if(result != QString(""))
    {
        QFileInfo fileInfo(result);
        qCtx->setLastSearch(fileInfo.absoluteDir().path());
        writePath(fileInfo.absoluteFilePath(), lineedit);
    }
}

/**
 * @param lineedit Ligne d'édition QLineEdit associée
 *
 * Ouvre une fenêtre de dialogue pour recherché plusieurs fichiers éxistants.
 * Si au moins un fichier est sélectionné, appelle la méthode writePath()
 * avec comme arguments les chemins vers les fichiers sélectionnés séparés par
 * des espaces et @c lineedit.
 */
void TabDoxygen::getOpenFiles(QLineEdit* lineedit)
{
    QStringList result;
    result = QFileDialog::getOpenFileNames(this,
                                           "Fichiers",
                                           qCtx->lastSearch());
    if(result.length() > 0)
    {
        for(int i = 0; i < result.length(); i++)
        {
            QString tmp = result[i];
            QFileInfo fileInfo(tmp);
            tmp = fileInfo.absolutePath();
            if(tmp.contains(QChar(' ')))
            {
                tmp.prepend(QChar('"'));
                tmp.append(QChar('"'));
            }
            result[i] = tmp;
            qCtx->setLastSearch(fileInfo.absolutePath());
        }
        writePath(result.join(QChar(' ')), lineedit);
    }
}

/**
 * @param lineedit Ligne d'édition QLineEdit associée
 *
 * Ouvre une fenêtre de dialogue pour recherché un dossier éxistant. Si un
 * fichier est sélectionné, appelle la méthode writePath() avec comme
 * arguments le chemin vers le dossier sélectionné et @c lineedit.
 */
void TabDoxygen::getDir(QLineEdit* lineedit)
{
    QString result = "";
    result = QFileDialog::getExistingDirectory(this,
                                               "Dossier",
                                               qCtx->lastSearch());
    if(result != QString(""))
    {
        QFileInfo fileInfo(result);
        qCtx->setLastSearch(fileInfo.absoluteFilePath());
        writePath(fileInfo.absoluteFilePath(), lineedit);
    }
}

/**
 * @param path Chemin vers un ou plusieurs fichier(s)/dossier(s)
 * @param lineedit Ligne d'édition QLineEdit associée
 *
 * Ecrit le ou les chemin(s) passé(s) en argument @c path dans la ligne
 * d'édition @c lineedit.
 */
void TabDoxygen::writePath(const QString& path, QLineEdit* lineedit)
{
    lineedit->setText(path);
}

/**
 * Ce connecteur est activé lors d'un clic souris par l'utilisateur sur le
 * bouton Appliquer.@n
 * Il appelle la fonction save() pour enregistrer les modifications
 * qui ont été apportées.
 */
void TabDoxygen::on_pushButton_apply_clicked()
{
    save();
}

/**
 * Ce connecteur est activé lors d'un clic souris par l'utilisateur sur le
 * bouton Défaut.@n
 * Demande à l'utilisateur s'il est sur de vouloir remettre les valeur par
 * défaut sur cet onglet. S'il répond "OUI", efface le fichier de configuration
 * de Doxygen avec la fonction createDoxyfile() et réinitialise cet
 * onglet avec la fonction init().
 */
void TabDoxygen::on_pushButton_default_clicked()
{
    QMessageBox::StandardButton res;
    res = QMessageBox::question(this,
                                "Remise à zéro",
                                "Êtes vous sûr de vouloir réinitialiser\nle fihcier Doxygen ?",
                                QMessageBox::Yes | QMessageBox::No,
                                QMessageBox::Yes);
    if(res == QMessageBox::Yes)
    {
        createDoxyfile();
        init();
    }
}

/**
 * Ce connecteur est activé lors d'un clic souris par l'utilisateur sur le
 * bouton "Générer Templates".@n
 * Exécute les commandes de génération des templates Doxygen dans le dossier
 * spécifié dans l'instance Settings à partir du dossier de configuration
 * de Doxygen.
 * @sa Context::doxygenTemplateDir().
 */
void TabDoxygen::on_pushButton_generateFiles_clicked()
{
    QFileInfo infos(m_doxyfile);
    QString dir = infos.absoluteDir().absolutePath();
    if(!dir.endsWith('/')) dir.append('/');

    try
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        // Create Dir
        dir += qCtx->doxygenTemplateDir();
        if(!dir.endsWith('/')) dir.append('/');
        command("mkdir " + dir, ".");
        command("mkdir rtf", dir);
        command("mkdir html", dir);
        command("mkdir latex", dir);
        command("doxygen -l layout.xml", dir);
        command("doxygen -w rtf styleSheetFile", dir + "rtf");
        command("doxygen -e rtf extensionsFile", dir + "rtf");
        command("doxygen -w html header.html footer.html stylesheet.css", dir + "html");
        command("doxygen -w latex header.html footer.html stylesheet.css", dir + "latex");
        QApplication::restoreOverrideCursor();
        QMessageBox::information(this,
                                 "Création des templates",
                                 "Les templates ont été créés dans le dossier\n" + dir);
        command("browse", dir);
    }
    catch(QString msg)
    {
        QMessageBox::critical(this, "Erreur", msg);
    }
}

/**
 * Ce connecteur est activé lors d'un clic souris par l'utilisateur sur le
 * bouton "Générer Doc".@n
 * Enregistre les modifications apportées par l'utilisateur puis exécute la
 * commande de génération de la documentation du projet. La dernière sortie
 * de la génération de la documentation se trouve dans les fichiers
 * doxygen.log et doxygen.err. Si des erreurs sont détectées, affiche une
 * popup avec un lien vers le fichier d'erreur, sinon, la popup affiche un
 * message de réussite.
 * @sa Context::doxyfile(), save().
 */
void TabDoxygen::on_pushButton_generateDoc_clicked()
{
    this->setEnabled(false);
    save();
    QStringList errList;
    for(const QString& projectFile : qCtx->subProjects())
    {
        QString err = generateDocFromDir(QFileInfo(projectFile).absoluteDir(), QFileInfo(projectFile).baseName());
        if(err != "")
        {
            errList << err;
        }
    }

    QString result;
    if(errList.length() == 0)
    {
        result = "Aucune erreur détectée.";
    }
    else
    {
        result = "<br/>Des erreurs ont été détectées :<br/>"
                 + errList.join("<br/>");
    }
    this->setEnabled(true);
    QMessageBox::information(this,
                             "Doxygen",
                             "<p>La documentation a été générée." + result + "</p>");
}

/**
 * @param cmd Commande à exécuter
 * @param workingDir Dossier de travail
 *
 * Cette fonction exécute la commande @c cmd dans le dossier @c workingDir
 * à l'aide d'un objet QProcess.
 */
void TabDoxygen::command(const QString& cmd, const QString& workingDir)
{
    qLog->debug("TabDoxygen - Commande (" + workingDir + ") : " + cmd);
    QProcess process;
    process.setWorkingDirectory(workingDir);
    process.start(cmd);
    if(!process.waitForFinished())
    {
        throw QString("Erreur pour la commande : " + cmd);
    }
}

/**
 * @param dir Dossier du projet à documenter
 * @param projectName Nom du projet à documenter
 * @return Chaîne de caractères contenant un lien vers le fichier d'erreur si des erreurs
 * ont été détectées. Une chaîne de caractères vide sinon.
 *
 * Copie le fichier Doxyfile du projet vers le sous-projet à documenter. L'outil Doxygen est
 * ensuite appelé pour générer la documentation. En cas d'erreur fatale lors de cette génération,
 * une popup d'erreur apparaît.
 */
QString TabDoxygen::generateDocFromDir(const QDir &dir, const QString& projectName)
{
    try
    {
        // Copie du fichier "Doxyfile"
        QString destFile = dir.absoluteFilePath("Doxyfile");
        if(QFile::exists(destFile))
        {
            QFile::remove(destFile);
        }
        if(QFile::copy(qCtx->doxyfile(), destFile))
        {
            // Remplacement des informations de projet
            QFile doxyfile(destFile);
            if(doxyfile.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream streamR(&doxyfile);
                streamR.setCodec("UTF-8");
                QStringList lines = streamR.readAll().split('\n');
                doxyfile.close();

                if(doxyfile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
                {
                    QTextStream streamW(&doxyfile);
                    streamW.setCodec("UTF-8");
                    for(const QString& line : lines)
                    {
                        if(line.trimmed().startsWith("OUTPUT_DIRECTORY"))
                        {
                            streamW << line << "/" << projectName;
                        }
                        else if(line.trimmed().startsWith("PROJECT_NAME"))
                        {
                            streamW << "PROJECT_NAME=" << projectName;
                        }
                        else
                        {
                            streamW << line;
                        }
                        streamW << endl;
                    }
                    doxyfile.close();
                }
                else
                {
                    throw QString("Impossible de modifier le fichier Doxyfile !");
                }
            }
            else
            {
                throw QString("Impossible de modifier le fichier Doxyfile !");
            }

            // Génération de la doc
            QProcess process;
            process.setWorkingDirectory(dir.absolutePath());
            process.setStandardOutputFile(dir.absoluteFilePath("doxygen.log"));
            process.setStandardErrorFile(dir.absoluteFilePath("doxygen.err"));
            process.start("doxygen", QStringList() << "Doxyfile");
            if(process.waitForFinished())
            {
                QFile err_file(dir.absoluteFilePath("doxygen.err"));
                QString extra_info = "";
                if(err_file.open(QIODevice::Text | QIODevice::ReadOnly))
                {
                    QString text = err_file.readAll();
                    if(text.simplified() == "")
                    {
                        extra_info += "";
                    }
                    else
                    {
                        QStringList ligns = text.split('\n');
                        extra_info += projectName + " - " +
                                      QString::number(ligns.length()-1) + " erreurs ("
                                      "Voir les erreurs : <a href=\"" + dir.absoluteFilePath("doxygen.err") + "\">"
                                      + dir.absoluteFilePath("doxygen.err") + "</a>)";
                    }
                    err_file.close();
                }
                return extra_info;
            }
            else
            {
                throw QString("Erreur lors de la génération de la Doc");
            }
        }
        else
        {
            throw QString("Impossible de copier le fichier Doxyfile vers " + dir.absolutePath());
        }
    }
    catch(QString msg)
    {
        QMessageBox::critical(this, "Doxygen",  msg);
    }
    return "";
}
