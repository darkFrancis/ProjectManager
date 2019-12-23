#include "tabdoxygen.hpp"
#include "ui_tabdoxygen.h"
#include <QFile>
#include <QTextStream>
#include "context.hpp"

TabDoxygen::TabDoxygen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabDoxygen)
{
    ui->setupUi(this);
}

TabDoxygen::~TabDoxygen()
{
    delete ui;
}

void TabDoxygen::init()
{
    m_doxyfile = Context::Instance()->doxyfile();
    if(!QFile::exists(m_doxyfile))
    {
        createDoxyfile();
    }

    QFile file(m_doxyfile);
    if(file.open(QIODevice::Text | QIODevice::ReadOnly))
    {

    }
    else
    {

    }
}

void TabDoxygen::save()
{

}

void TabDoxygen::createDoxyfile()
{
    QFile doxyfile(m_doxyfile);
    if(doxyfile.open(QIODevice::Text | QIODevice::Truncate | QIODevice::WriteOnly))
    {
        QTextStream stream(&doxyfile);
        stream << "# Configuration du projet" << endl;
        stream << "DOXYFILE_ENCODING=UTF-8" << endl;
        stream << "PROJECT_NAME=\"My Project\"" << endl;
        stream << "PROJECT_NUMBER=" << endl;
        stream << "PROJECT_BRIEF=" << endl;
        stream << "PROJECT_LOGO=" << endl;
        stream << "OUTPUT_DIRECTORY=" << endl;
        stream << "CREATE_SUBDIRS=NO" << endl;
        stream << "ALLOW_UNICODE_NAMES=NO" << endl;
        stream << "OUTPUT_LANGUAGE=English" << endl;
        stream << "BRIEF_MEMBER_DESC=YES" << endl;
        stream << "REPEAT_BRIEF=YES" << endl;
        stream << "ABBREVIATE_BRIEF=\"The $name class\" \"The $name widget\" \"The $name file\" is provides specifies contains represents a an the" << endl;
        stream << "ALWAYS_DETAILED_SEC=NO" << endl;
        stream << "INLINE_INHERITED_MEMB=NO" << endl;
        stream << "FULL_PATH_NAMES=YES" << endl;
        stream << "STRIP_FROM_PATH=" << endl;
        stream << "STRIP_FROM_INC_PATH=" << endl;
        stream << "SHORT_NAMES=NO" << endl;
        stream << "JAVADOC_AUTOBRIEF=NO" << endl;
        stream << "QT_AUTOBRIEF=NO" << endl;
        stream << "MULTILINE_CPP_IS_BRIEF=NO" << endl;
        stream << "INHERIT_DOCS=YES" << endl;
        stream << "SEPARATE_MEMBER_PAGES=NO" << endl;
        stream << "TAB_SIZE=4" << endl;
        stream << "ALIASES=" << endl;
        stream << "TCL_SUBST=" << endl;
        stream << "OPTIMIZE_OUTPUT_FOR_C=NO" << endl;
        stream << "OPTIMIZE_OUTPUT_JAVA=NO" << endl;
        stream << "OPTIMIZE_FOR_FORTRAN=NO" << endl;
        stream << "OPTIMIZE_OUTPUT_VHDL=NO" << endl;
        stream << "EXTENSION_MAPPING=" << endl;
        stream << "MARKDOWN_SUPPORT=YES" << endl;
        stream << "TOC_INCLUDE_HEADINGS=0" << endl;
        stream << "AUTOLINK_SUPPORT=YES" << endl;
        stream << "BUILTIN_STL_SUPPORT=NO" << endl;
        stream << "CPP_CLI_SUPPORT=NO" << endl;
        stream << "SIP_SUPPORT=NO" << endl;
        stream << "IDL_PROPERTY_SUPPORT=YES" << endl;
        stream << "DISTRIBUTE_GROUP_DOC=NO" << endl;
        stream << "GROUP_NESTED_COMPOUNDS=NO" << endl;
        stream << "SUBGROUPING=YES" << endl;
        stream << "INLINE_GROUPED_CLASSES=NO" << endl;
        stream << "INLINE_SIMPLE_STRUCTS=NO" << endl;
        stream << "TYPEDEF_HIDES_STRUCT=NO" << endl;
        stream << "LOOKUP_CACHE_SIZE=0" << endl;
        stream << endl;
        stream << "# Configuration de build" << endl;
        stream << "EXTRACT_ALL=NO" << endl;
        stream << "EXTRACT_PRIVATE=NO" << endl;
        stream << "EXTRACT_PACKAGE=NO" << endl;
        stream << "EXTRACT_STATIC=NO" << endl;
        stream << "EXTRACT_LOCAL_CLASSES=YES" << endl;
        stream << "EXTRACT_LOCAL_METHODS=NO" << endl;
        stream << "EXTRACT_ANON_NSPACES=NO" << endl;
        stream << "HIDE_UNDOC_MEMBERS=NO" << endl;
        stream << "HIDE_UNDOC_CLASSES=NO" << endl;
        stream << "HIDE_FRIEND_COMPOUNDS=NO" << endl;
        stream << "HIDE_IN_BODY_DOCS=NO" << endl;
        stream << "INTERNAL_DOCS=NO" << endl;
        stream << "CASE_SENSE_NAMES=YES" << endl;
        stream << "HIDE_SCOPE_NAMES=NO" << endl;
        stream << "HIDE_COMPOUND_REFERENCE=NO" << endl;
        stream << "SHOW_INCLUDE_FILES=YES" << endl;
        stream << "SHOW_GROUPED_MEMB_INC=NO" << endl;
        stream << "FORCE_LOCAL_INCLUDES=NO" << endl;
        stream << "INLINE_INFO=YES" << endl;
        stream << "SORT_MEMBER_DOCS=YES" << endl;
        stream << "SORT_BRIEF_DOCS=NO" << endl;
        stream << "SORT_MEMBERS_CTORS_1ST=NO" << endl;
        stream << "SORT_GROUP_NAMES=NO" << endl;
        stream << "SORT_BY_SCOPE_NAME=NO" << endl;
        stream << "STRICT_PROTO_MATCHING=NO" << endl;
        stream << "GENERATE_TODOLIST=YES" << endl;
        stream << "GENERATE_TESTLIST=YES" << endl;
        stream << "GENERATE_BUGLIST=YES" << endl;
        stream << "GENERATE_DEPRECATEDLIST=YES" << endl;
        stream << "ENABLED_SECTIONS=" << endl;
        stream << "MAX_INITIALIZER_LINES=30" << endl;
        stream << "SHOW_USED_FILES=YES" << endl;
        stream << "SHOW_FILES=YES" << endl;
        stream << "SHOW_NAMESPACES=YES" << endl;
        stream << "FILE_VERSION_FILTER=" << endl;
        stream << "LAYOUT_FILE=" << endl;
        stream << "CITE_BIB_FILES=" << endl;
        stream << endl;
        stream << "# Configuration des messages" << endl;
        stream << "QUIET=NO" << endl;
        stream << "WARNINGS=YES" << endl;
        stream << "WARN_IF_UNDOCUMENTED=YES" << endl;
        stream << "WARN_IF_DOC_ERROR=YES" << endl;
        stream << "WARN_NO_PARAMDOC=NO" << endl;
        stream << "WARN_AS_ERROR=NO" << endl;
        stream << "WARN_FORMAT=\"$file:$line:$text\"" << endl;
        stream << "WARN_LOGFILE=" << endl;
        stream << endl;
        stream << "# Configuration des entrées" << endl;
        stream << "INPUT=" << endl;
        stream << "INPUT_ENCODING=UTF-8" << endl;
        stream << "FILE_PATTERNS=*.c *.cc *.cxx *.cpp *.c++ *.java *.ii *.ixx *.ipp *.i++ *.inl *.idl *.ddl *.odl *.h *.hh *.hxx *.hpp *.h++ *.cs *.d *.php *.php4 *.php5 *.phtml *.inc *.m *.markdown *.md *.mm *.dox *.py *.pyw *.f90 *.f95 *.f03 *.f08 *.f *.for *.tcl *.vhd *.vhdl *.ucf *.qsf" << endl;
        stream << "RECURSIVE=NO" << endl;
        stream << "EXCLUDE=" << endl;
        stream << "EXCLUDE_SYMLINKS=NO" << endl;
        stream << "EXCLUDE_PATTERNS=" << endl;
        stream << "EXCLUDE_SYMBOLS=" << endl;
        stream << "EXAMPLE_PATH=" << endl;
        stream << "EXAMPLE_PATTERNS=*" << endl;
        stream << "EXAMPLE_RECURSIVE=NO" << endl;
        stream << "IMAGE_PATH=" << endl;
        stream << "INPUT_FILTER=" << endl;
        stream << "FILTER_PATTERNS=" << endl;
        stream << "FILTER_SOURCE_FILES=NO" << endl;
        stream << "FILTER_SOURCE_PATTERNS=" << endl;
        stream << "USE_MDFILE_AS_MAINPAGE=" << endl;
        stream << endl;
        stream << "# Configurartion de la recherche de sources" << endl;
        stream << "SOURCE_BROWSER=NO" << endl;
        stream << "INLINE_SOURCES=NO" << endl;
        stream << "STRIP_CODE_COMMENTS=YES" << endl;
        stream << "REFERENCED_BY_RELATION=NO" << endl;
        stream << "REFERENCES_RELATION=NO" << endl;
        stream << "REFERENCES_LINK_SOURCE=YES" << endl;
        stream << "SOURCE_TOOLTIPS=YES" << endl;
        stream << "USE_HTAGS=NO" << endl;
        stream << "VERBATIM_HEADERS=YES" << endl;
        stream << "CLANG_ASSISTED_PARSING=NO" << endl;
        stream << "CLANG_OPTIONS=" << endl;
        stream << endl;
        stream << "# Configuration de l'index alphabétique" << endl;
        stream << "ALPHABETICAL_INDEX=YES" << endl;
        stream << "COLS_IN_ALPHA_INDEX=5" << endl;
        stream << "IGNORE_PREFIX=" << endl;
        stream << endl;
        stream << "# Configuration de sortie HTML" << endl;
        stream << "GENERATE_HTML=YES" << endl;
        stream << "HTML_OUTPUT=html" << endl;
        stream << "HTML_FILE_EXTENSION=.html" << endl;
        stream << "HTML_HEADER=" << endl;
        stream << "HTML_FOOTER=" << endl;
        stream << "HTML_STYLESHEET=" << endl;
        stream << "HTML_EXTRA_STYLESHEET=" << endl;
        stream << "HTML_EXTRA_FILES=" << endl;
        stream << "HTML_COLORSTYLE_HUE=220" << endl;
        stream << "HTML_COLORSTYLE_SAT=100" << endl;
        stream << "HTML_COLORSTYLE_GAMMA=80" << endl;
        stream << "HTML_TIMESTAMP=NO" << endl;
        stream << "HTML_DYNAMIC_SECTIONS=NO" << endl;
        stream << "HTML_INDEX_NUM_ENTRIES=100" << endl;
        stream << "GENERATE_DOCSET=NO" << endl;
        stream << "DOCSET_FEEDNAME=\"Doxygengenerateddocs\"" << endl;
        stream << "DOCSET_BUNDLE_ID=org.doxygen.Project" << endl;
        stream << "DOCSET_PUBLISHER_ID=org.doxygen.Publisher" << endl;
        stream << "DOCSET_PUBLISHER_NAME=Publisher" << endl;
        stream << "GENERATE_HTMLHELP=NO" << endl;
        stream << "CHM_FILE=" << endl;
        stream << "HHC_LOCATION=" << endl;
        stream << "GENERATE_CHI=NO" << endl;
        stream << "CHM_INDEX_ENCODING=" << endl;
        stream << "BINARY_TOC=NO" << endl;
        stream << "TOC_EXPAND=NO" << endl;
        stream << "GENERATE_QHP=NO" << endl;
        stream << "QCH_FILE=" << endl;
        stream << "QHP_NAMESPACE=org.doxygen.Project" << endl;
        stream << "QHP_VIRTUAL_FOLDER=doc" << endl;
        stream << "QHP_CUST_FILTER_NAME=" << endl;
        stream << "QHP_CUST_FILTER_ATTRS=" << endl;
        stream << "QHP_SECT_FILTER_ATTRS=" << endl;
        stream << "QHG_LOCATION=" << endl;
        stream << "GENERATE_ECLIPSEHELP=NO" << endl;
        stream << "ECLIPSE_DOC_ID=org.doxygen.Project" << endl;
        stream << "DISABLE_INDEX=NO" << endl;
        stream << "GENERATE_TREEVIEW=NO" << endl;
        stream << "ENUM_VALUES_PER_LINE=4" << endl;
        stream << "TREEVIEW_WIDTH=250" << endl;
        stream << "EXT_LINKS_IN_WINDOW=NO" << endl;
        stream << "FORMULA_FONTSIZE=10" << endl;
        stream << "FORMULA_TRANSPARENT=YES" << endl;
        stream << "USE_MATHJAX=NO" << endl;
        stream << "MATHJAX_FORMAT=HTML-CSS" << endl;
        stream << "MATHJAX_RELPATH=http://cdn.mathjax.org/mathjax/latest" << endl;
        stream << "MATHJAX_EXTENSIONS=" << endl;
        stream << "MATHJAX_CODEFILE=" << endl;
        stream << "SEARCHENGINE=YES" << endl;
        stream << "SERVER_BASED_SEARCH=NO" << endl;
        stream << "EXTERNAL_SEARCH=NO" << endl;
        stream << "SEARCHENGINE_URL=" << endl;
        stream << "SEARCHDATA_FILE=searchdata.xml" << endl;
        stream << "EXTERNAL_SEARCH_ID=" << endl;
        stream << "EXTRA_SEARCH_MAPPINGS=" << endl;
        stream << endl;
        stream << "# Configuration de sortie LaTeX" << endl;
        stream << "GENERATE_LATEX=YES" << endl;
        stream << "LATEX_OUTPUT=latex" << endl;
        stream << "LATEX_CMD_NAME=latex" << endl;
        stream << "MAKEINDEX_CMD_NAME=makeindex" << endl;
        stream << "COMPACT_LATEX=NO" << endl;
        stream << "PAPER_TYPE=a4" << endl;
        stream << "EXTRA_PACKAGES=" << endl;
        stream << "LATEX_HEADER=" << endl;
        stream << "LATEX_FOOTER=" << endl;
        stream << "LATEX_EXTRA_STYLESHEET=" << endl;
        stream << "LATEX_EXTRA_FILES=" << endl;
        stream << "PDF_HYPERLINKS=YES" << endl;
        stream << "USE_PDFLATEX=YES" << endl;
        stream << "LATEX_BATCHMODE=NO" << endl;
        stream << "LATEX_HIDE_INDICES=NO" << endl;
        stream << "LATEX_SOURCE_CODE=NO" << endl;
        stream << "LATEX_BIB_STYLE=plain" << endl;
        stream << "LATEX_TIMESTAMP=NO" << endl;
        stream << endl;
        stream << "# Configuration de sortie RTF" << endl;
        stream << "GENERATE_RTF=NO" << endl;
        stream << "RTF_OUTPUT=rtf" << endl;
        stream << "COMPACT_RTF=NO" << endl;
        stream << "RTF_HYPERLINKS=NO" << endl;
        stream << "RTF_STYLESHEET_FILE=" << endl;
        stream << "RTF_EXTENSIONS_FILE=" << endl;
        stream << "RTF_SOURCE_CODE=NO" << endl;
        stream << endl;
        stream << "# Configuration de sortie MAN" << endl;
        stream << "GENERATE_MAN=NO" << endl;
        stream << "MAN_OUTPUT=man" << endl;
        stream << "MAN_EXTENSION=.3" << endl;
        stream << "MAN_SUBDIR=" << endl;
        stream << "MAN_LINKS=NO" << endl;
        stream << endl;
        stream << "# Configuration de sortie XML" << endl;
        stream << "GENERATE_XML=NO" << endl;
        stream << "XML_OUTPUT=xml" << endl;
        stream << "XML_PROGRAMLISTING=YES" << endl;
        stream << endl;
        stream << "# Configuration de sortie DocBook" << endl;
        stream << "GENERATE_DOCBOOK=NO" << endl;
        stream << "DOCBOOK_OUTPUT=docbook" << endl;
        stream << "DOCBOOK_PROGRAMLISTING=NO" << endl;
        stream << endl;
        stream << "# Configuration des définitions AutoGen" << endl;
        stream << "GENERATE_AUTOGEN_DEF=NO" << endl;
        stream << endl;
        stream << "# Configuration du module Perl" << endl;
        stream << "GENERATE_PERLMOD=NO" << endl;
        stream << "PERLMOD_LATEX=NO" << endl;
        stream << "PERLMOD_PRETTY=YES" << endl;
        stream << "PERLMOD_MAKEVAR_PREFIX=" << endl;
        stream << endl;
        stream << "# Configuration du processeur" << endl;
        stream << "ENABLE_PREPROCESSING=YES" << endl;
        stream << "MACRO_EXPANSION=NO" << endl;
        stream << "EXPAND_ONLY_PREDEF=NO" << endl;
        stream << "SEARCH_INCLUDES=YES" << endl;
        stream << "INCLUDE_PATH=" << endl;
        stream << "INCLUDE_FILE_PATTERNS=" << endl;
        stream << "PREDEFINED=" << endl;
        stream << "EXPAND_AS_DEFINED=" << endl;
        stream << "SKIP_FUNCTION_MACROS=YES" << endl;
        stream << endl;
        stream << "# Configuration des références externes" << endl;
        stream << "TAGFILES=" << endl;
        stream << "GENERATE_TAGFILE=" << endl;
        stream << "ALLEXTERNALS=NO" << endl;
        stream << "EXTERNAL_GROUPS=YES" << endl;
        stream << "EXTERNAL_PAGES=YES" << endl;
        stream << "PERL_PATH=/usr/bin/perl" << endl;
        stream << endl;
        stream << "# Configuration de l'outil DOT" << endl;
        stream << "CLASS_DIAGRAMS=YES" << endl;
        stream << "MSCGEN_PATH=" << endl;
        stream << "DIA_PATH=" << endl;
        stream << "HIDE_UNDOC_RELATIONS=YES" << endl;
        stream << "HAVE_DOT=YES" << endl;
        stream << "DOT_NUM_THREADS=0" << endl;
        stream << "DOT_FONTNAME=Helvetica" << endl;
        stream << "DOT_FONTSIZE=10" << endl;
        stream << "DOT_FONTPATH=" << endl;
        stream << "CLASS_GRAPH=YES" << endl;
        stream << "COLLABORATION_GRAPH=YES" << endl;
        stream << "GROUP_GRAPHS=YES" << endl;
        stream << "UML_LOOK=NO" << endl;
        stream << "UML_LIMIT_NUM_FIELDS=10" << endl;
        stream << "TEMPLATE_RELATIONS=NO" << endl;
        stream << "INCLUDE_GRAPH=YES" << endl;
        stream << "INCLUDED_BY_GRAPH=YES" << endl;
        stream << "CALL_GRAPH=NO" << endl;
        stream << "CALLER_GRAPH=NO" << endl;
        stream << "GRAPHICAL_HIERARCHY=YES" << endl;
        stream << "DIRECTORY_GRAPH=YES" << endl;
        stream << "DOT_IMAGE_FORMAT=png" << endl;
        stream << "INTERACTIVE_SVG=NO" << endl;
        stream << "DOT_PATH=" << endl;
        stream << "DOTFILE_DIRS=" << endl;
        stream << "MSCFILE_DIRS=" << endl;
        stream << "DIAFILE_DIRS=" << endl;
        stream << "PLANTUML_JAR_PATH=" << endl;
        stream << "PLANTUML_CFG_FILE=" << endl;
        stream << "PLANTUML_INCLUDE_PATH=" << endl;
        stream << "DOT_GRAPH_MAX_NODES=50" << endl;
        stream << "MAX_DOT_GRAPH_DEPTH=0" << endl;
        stream << "DOT_TRANSPARENT=NO" << endl;
        stream << "DOT_MULTI_TARGETS=NO" << endl;
        stream << "GENERATE_LEGEND=YES" << endl;
        stream << "DOT_CLEANUP=YES" << endl;
        doxyfile.close();
    }
    else
    {
        throw(QString("Impossible de créer le fichier Doxyfile"));
    }
}
