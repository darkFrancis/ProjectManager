#include "conflictwindow.hpp"
#include "ui_conflictwindow.h"

#include <QMessageBox>
#include <QDebug>

ConflictTextEdit::ConflictTextEdit(QWidget *parent) :
    QTextEdit(parent)
{
    setReadOnly(true);
    setAcceptDrops(false);
}

void ConflictTextEdit::mousePressEvent(QMouseEvent *e)
{
    m_clicked_anchor = (e->button() & Qt::LeftButton) ? anchorAt(e->pos()) : QString();
    QTextEdit::mousePressEvent(e);
}

void ConflictTextEdit::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() & Qt::LeftButton
        && !m_clicked_anchor.isEmpty()
        && anchorAt(e->pos()) == m_clicked_anchor)
    {
        emit linkActivated(m_clicked_anchor);
    }
    QTextEdit::mouseReleaseEvent(e);
}

void ConflictTextEdit::addDocument(QString file_name)
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
    this->clear();

    QString html = "<!DOCTYPE html>"
                   "<html><style>"
                   ".current { background-color:\"lime\" }"
                   "a:hover a { opacity: 1; }"
                   "</style><body>";

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
                line = line.replace('<', "&lt;").replace('>', "&gt;").replace(' ', "&nbsp;") + "<br/>";
                if(inConflict) text_tmp += line;
                else html += line;
            }
        }
        html += "</body></html>";

        qDebug() << html;
        this->setText(html);

        m_modified = false;
    }
    else
    {
        QMessageBox::critical(this,
                              "Erreur",
                              "Impossible d'ouvrir le fichier " + file_name);
    }
}

QString ConflictTextEdit::addLink(QString text, QString branch, bool is_current)
{
    QString link = "<span title=\"" + branch + "\">";
    link += "<a class=\"";
    link += is_current ? "current" : "to_merge";
    link += "\" href=\"" + branch + "\">" + text + "</a>";
    link += "</span>";
    return link;
}

ConflictWindow::ConflictWindow(QWidget *parent, QStringList files) :
    QMainWindow(parent),
    ui(new Ui::ConflictWindow)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_QuitOnClose);
    this->setWindowModality(Qt::ApplicationModal);

    // Init list
    ui->listWidget->addItems(files);

    // Init text edit
    m_text_edit = new ConflictTextEdit(this);
    ui->layout_textEdit->addWidget(m_text_edit);
    connect(m_text_edit, &ConflictTextEdit::linkActivated, this, &ConflictWindow::linkClicked);

    /* Pour test */
    m_text_edit->addDocument("/home/francis/dev/test/test_merge");
    /* Fin test */
}

ConflictWindow::~ConflictWindow()
{
    delete ui;
}

void ConflictWindow::linkClicked(QString link)
{
    QMessageBox::information(this,
                             "Clic sur lien",
                             link);
}

void ConflictWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{

}
