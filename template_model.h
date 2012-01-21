#ifndef TEMPLATE_MODEL_H
#define TEMPLATE_MODEL_H

#include <QObject>
#include <QString>

class TemplateModel
        : public QObject
{
public:
    TemplateModel(const QString &text, QObject *parent = 0)
        : QObject(parent), _text(text)
    {}
    inline QString & getText()
    {
        return _text;
    }
private:
    QString _text;
};

#endif // TEMPLATE_MODEL_H
