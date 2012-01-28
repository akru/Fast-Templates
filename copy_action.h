#ifndef COPY_ACTION_H
#define COPY_ACTION_H

#include <QAction>
#include <QString>

class CopyAction
        : public QAction
{
    Q_OBJECT
public:
    explicit CopyAction(const QString &name,
                        const QString &text, QObject *parent = 0);

private slots:
    void copyText();

private:
    QString _text;
    
};

#endif // COPY_ACTION_H
