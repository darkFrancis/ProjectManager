#ifndef NEWPROJECT_HPP
#define NEWPROJECT_HPP

#include <QMainWindow>

namespace Ui {
    class NewProject;
}

class NewProject : public QMainWindow
{
        Q_OBJECT

    public:
        explicit NewProject(QWidget *parent, QString file);
        ~NewProject();

    signals:

    private slots:
        void on_toolButton_mainGitDir_clicked();
        void on_toolButton_doxyfile_clicked();
        void on_pushButton_cancel_clicked();
        void on_pushButton_create_clicked();

    private:
        Ui::NewProject *ui;
        QString m_file;
};

#endif // NEWPROJECT_HPP
