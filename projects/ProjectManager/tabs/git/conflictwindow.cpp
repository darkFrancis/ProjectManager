#include "conflictwindow.hpp"
#include "ui_conflictwindow.h"

#include <QMessageBox>

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

    ConflictArea eArea = OutSide;
    QString current_branch = "";

    QFile file(file_name);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString text = file.readAll();
        for(QString line : text.split('\n'))
        {
            line = line.simplified();
            QString tmp = line.left(KEY_LENGTH);
            if(tmp == KEY_CURRENT)
            {
                eArea = CurrentBranch;
                current_branch = line.remove(0, KEY_LENGTH+1);
            }
            else if(tmp == KEY_CONTROL)
            {

            }
        }

        m_modified = false;
    }
    else
    {
        QMessageBox::critical(this,
                              "Erreur",
                              "Impossible d'ouvrir le fichier " + file_name);
    }
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
    ui->layout_textEdit->addWidget(m_text_edit);
    connect(m_text_edit, &ConflictTextEdit::linkActivated, this, &ConflictWindow::linkClicked);

    /* Pour test */
    m_text_edit->append("Ceci est un text<br/>"
               "Ceci est un text<br/>"
               "<a href=\"lien.txt\">Ceci est un lien</a><br/>"
               "Ceci est encore du texte");
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
