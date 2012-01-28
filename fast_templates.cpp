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

    parseHeader(root, 0);
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
            if (node.toElement().tagName() == "template")
                new TemplateModel(
                        node.toElement().attribute("description", "NaN"),
                        parent, node.toElement().text());
        }
        if (!parent)
            _templates << templ;
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
