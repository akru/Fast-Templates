#include "fast_templates.h"
#include "user_interface.h"
#include "template_model.h"
#include <QtXml>

FastTemplates::FastTemplates(int &ac, char **av)
    : QApplication(ac, av),
      _gui(new UserInterface)
{
    if (arguments().count() != 2)
    {
        qWarning("Usage: fastt [config]");
        quick_exit(1);
    }
    if (loadConfig(arguments().at(1)))
        quick_exit(1);

    _gui->createMainMenu(_templates);

    QString hotKey = "Alt+A";
    enableHotkey(hotKey);

    connectAll();
}

FastTemplates::~FastTemplates()
{
    delete _gui;
}

bool FastTemplates::loadConfig(const QString &filename)
{
    QFile config(filename);
    QString errorStr;
    int errorLine;
    int errorColumn;
    QXmlInputSource source(&config);
    QDomDocument doc;
    if (!doc.setContent(&source, true, &errorStr, &errorLine,
                        &errorColumn))
    {
        qWarning(QString("Config :: Line %1, column %2: %3")
                 .arg(QString::number(errorLine),
                      QString::number(errorColumn), errorStr).toAscii());
        return 1;
    }

    QDomElement root = doc.documentElement();
    if (root.tagName() != "fastt")
    {
        qWarning("Config :: This is not a fastt config file");
        return 1;
    }

    QDomNode node = root.firstChild();
    while (!node.isNull())
    {
        if (node.toElement().tagName() == "header")
        {
            _templates << (QObject *) new TemplateModel(
                              node.toElement().attribute("description", "NaN"));
            parseHeader(node.toElement(), _templates.last());
        }
        node = node.nextSibling();
    }
    return 0;
}

void FastTemplates::parseHeader(const QDomElement &element, QObject *parent)
{
    QDomNode node = element.firstChild();
    while (!node.isNull())
    {
        QObject *templ;
        if (node.toElement().tagName() == "header")
        {
            templ = (QObject *) new TemplateModel(
                        node.toElement().attribute("description", "NaN"), parent);
            parseHeader(node.toElement(), templ);
        }
        else
        {
            new TemplateModel(node.toElement().text(), parent);
        }
        node = node.nextSibling();
    }
}

void FastTemplates::connectAll()
{
    connect(_gui, SIGNAL(closed()), this, SLOT(quit()));
    connect(&hotkeyHandle, SIGNAL(activated()), _gui, SLOT(showMenu()));
}

void FastTemplates::enableHotkey(QString key)
{
    hotkeyHandle.setShortcut(QKeySequence(key));
    hotkeyHandle.setEnabled(true);
}
