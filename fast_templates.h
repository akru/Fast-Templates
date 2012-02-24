#ifndef FAST_TEMPLATES_H
#define FAST_TEMPLATES_H

class QDomElement;
#include <QApplication>
#include <QObjectList>
#include <QxtGui/QxtGui>
#include "user_interface.h"


class FastTemplates
        : public QApplication
{
    Q_OBJECT
public:
    explicit FastTemplates(int &ac, char **av);
    ~FastTemplates();

private:
    bool loadConfig(const QString &filename);
    void parseHeader(const QDomElement &element, QObject *parent);
    void connectAll() const;
    void enableHotkey(QString key);

    UserInterface gui;
    QObjectList templates;
    QxtGlobalShortcut hotkeyHandle;
};

#endif // FAST_TEMPLATES_H
