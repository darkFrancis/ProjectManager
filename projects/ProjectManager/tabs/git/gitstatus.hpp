#ifndef GITSTATUS_HPP
#define GITSTATUS_HPP

    #include <QWidget>

    #define GIT_NOTUPDATED
    #define GIT_INDEXUPDATED
    #define GIT_NOTUPDATED
    #define GIT_NOTUPDATED
    #define GIT_NOTUPDATED
    #define GIT_NOTUPDATED


    namespace Ui {
        class GitStatus;
    }

    enum eGitStatus
    {
        NotUpdated,
        IndexUpdated,
        IndexAdded,
        IndexDeleted,
        IndexRenamed,
        IndexCopied,
        IndexAndWorkTreeMatches,
        WorkTreeChanged,
        WorkTreeDeleted,
        WorkTreeRenamed,
        WorkTreeCopied,
        UnmergedBothDeleted,
        UnmergedAddedByUs,
        UnmergedDeletedByThem,
        UnmergedAddedByThem,
        UnmergedDeletedByUs,
        UnmergedBothAdded,
        UnmergedBothModified,
        Untracked,
        Ignored
    };

    class GitStatus : public QWidget
    {
        Q_OBJECT

        public:
            explicit GitStatus(QWidget *parent = nullptr);
            ~GitStatus();
            void setFile(QString file);
            QString file();
            void setStatus(QString status);
            QString statusStr();
            eGitStatus status();
            void setChecked(bool checked = true);
            bool isChecked();

        private:
            Ui::GitStatus *ui;
            eGitStatus m_status;
            QString m_status_str;
    };

#endif // GITSTATUS_HPP
