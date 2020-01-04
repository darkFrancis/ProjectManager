#ifndef GITSTATUS_HPP
#define GITSTATUS_HPP

    #include <QWidget>
    #include <QLabel>

    namespace Ui {
        class GitStatus;
    }

    struct sGitStatus
    {
        char status_index;
        char status_worktree;
    };
    typedef struct sGitStatus sGitStatus;

    class GitStatus : public QWidget
    {
        Q_OBJECT

        public:
            explicit GitStatus(QWidget *parent = nullptr, QString line = "");
            ~GitStatus();
            void newLine(QString line);
            QString file();
            QString statusStr();
            sGitStatus status();
            void setChecked(bool checked = true);
            bool isChecked();

        private:
            Ui::GitStatus *ui;
            sGitStatus m_status;
            QString m_status_str;
            void setFile(QString file);
            void setStatus(QString status);
            void setStatusName(char status, QLabel* label);
    };

#endif // GITSTATUS_HPP
