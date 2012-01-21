#ifndef FAST_TEMPLATES_H
#define FAST_TEMPLATES_H

class UserInterface;
class QDomElement;
#include <QApplication>
#include <QObjectList>
#include <QxtGui/QxtGui>


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
    void connectAll();
    void enableHotkey(QString key);

    UserInterface *_gui;
    QObjectList _templates;
    QxtGlobalShortcut hotkeyHandle;
};

#endif // FAST_TEMPLATES_H
