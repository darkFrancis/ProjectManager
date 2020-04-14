#include "conflictwindow.hpp"
#include "ui_conflictwindow.h"

#include <QMessageBox>
#include <QTextBrowser>
#include <QFile>
#include <QDebug>

ConflictWindow::ConflictWindow(QWidget *parent, QStringList files) :
    QMainWindow(parent),
    ui(new Ui::ConflictWindow)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_QuitOnClose);
    this->setWindowModality(Qt::ApplicationModal);

    m_modified = false;

    // Init list
    ui->listWidget_files->addItems(files);

    /* Pour test */
    addDocument("/home/francis/dev/test/test_merge");
    /* Fin test */
}

ConflictWindow::~ConflictWindow()
{
    delete ui;
}

void ConflictWindow::on_listWidget_files_itemClicked(QListWidgetItem *item)
{
    addDocument(item->text());
}

void ConflictWindow::on_textBrowser_conflict_highlighted(const QString &arg1)
{
    showTooltip(arg1);
}

void ConflictWindow::addDocument(QString file_name)
{
    if(m_modified)
    {
        QMessageBox::StandardButtons rep;
        rep = QMessageBox::question(this,
                                    "Attention",
                                    "Êtes vous sûr de vouloir ouvrir un nouveau fichier ?"
                                    "Les modifications de celui-ci seront perdues.");
        if(rep != QMessageBox::Yes)
            return;
    }

    // Reset text_edit
    ui->textBrowser_conflict->clear();

    QString html = "<!DOCTYPE HTML>\n"
                   "<html><head>\n"
                   "<style>\n"
                   + getStyle() +
                   "</style></head><body>";

    QString current_branch = "";
    QString text_tmp = "";
    bool inConflict = false;

    QFile file(file_name);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString text = file.readAll();
        for(QString line : text.split('\n'))
        {
            line = line.simplified();

            // Gestion des mots clés de conflits
            QString tmp = line.left(KEY_LENGTH);
            if(tmp == KEY_CURRENT)
            {
                current_branch = line.split(' ').last();
                text_tmp = "";
                inConflict = true;
            }
            else if(tmp == KEY_CONTROL)
            {
                html += addLink(text_tmp, current_branch, true);
                text_tmp = "";
            }
            else if(tmp == KEY_TOMERGE)
            {
                current_branch = line.split(' ').last();
                html += addLink(text_tmp, current_branch, false);
                text_tmp = "";
                inConflict = false;
            }
            else
            {
                line = line.replace('<', "&lt;").replace('>', "&gt;").replace(' ', "&nbsp;") + "<br/>\n";
                if(inConflict) text_tmp += line;
                else html += line;
            }
        }
        html += "</body></html>";
        ui->textBrowser_conflict->setHtml(html);
        m_modified = false;
    }
    else
    {
        QMessageBox::critical(this,
                              "Erreur",
                              "Impossible d'ouvrir le fichier " + file_name);
    }
}

void ConflictWindow::showTooltip(QString link)
{
    if(link != "")
    {
        int idx = link.indexOf('!');
        QString style = "QToolTip"
                        "{"
                        "   padding:2px;"
                        "   border-width:2px;"
                        "   border-style:solid;"
                        "   border-radius:4px;"
                        "   background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 ";
        style += (link.left(idx) == CLASS_CURRENT ? "rgba(0,200,0,0.8)" : "rgba(0,0,200,0.8)");
        style += ", stop:1 rgba(0, 0, 0, 0));";
        style += "; }";
        this->setStyleSheet(style);
        QToolTip::showText(QCursor::pos(), link.right(link.length()-idx-1), this);
    }
}

QString ConflictWindow::addLink(QString text, QString branch, bool is_current)
{
    QString class_name = is_current ? CLASS_CURRENT : CLASS_TOMERGE;
    QString link = "<a class = \"" + class_name + "\""
                   "href=\"" + class_name + "!" + branch + "\">\n"
                   + text + "</a>\n";
    return link;
}

QString ConflictWindow::getStyle()
{
    QString style = "";

    // Style général
    style += "body"
             "{"
             "  background-color: rgb(150,150,150);"
             "  color: white;"
             "}\n";

    // Style des liens
    style += "a"
             "{"
             "  text-decoration: none;"
             "  color: white;"
             "}\n";

    // Style de la branche courante
    style += "." + CLASS_CURRENT +
             "{"
             "  background-color: rgba(0,150,0,0.7);"
             "}\n";

    // Style de la branche de merge
    style += "." + CLASS_TOMERGE +
             "{"
             "  background-color: rgba(0,0,150,0.7);"
             "}\n";

    return style;
}

void ConflictWindow::on_textBrowser_conflict_anchorClicked(const QUrl &arg1)
{
    QMessageBox::information(this,
                             "Link",
                             arg1.toString());
}
