#ifndef TEMPLATE_MODEL_H
#define TEMPLATE_MODEL_H

#include <QObject>
#include <QString>

class TemplateModel
        : public QObject
{
public:
    TemplateModel(const QString &description,
                  QObject *parent = 0, const QString &text = 0)
        : QObject(parent), _description(description), _text(text)
    {}
    inline const QString & getText() const
    {
        return _text;
    }
    inline const QString & getDesc() const
    {
        return _description;
    }

private:
    QString _description, _text;
};

#endif // TEMPLATE_MODEL_H
