#include "copy_action.h"
#include <QApplication>
#include <QClipboard>

CopyAction::CopyAction(const QString &name, const QString &text, QObject *parent)
    : QAction(name, parent), _text(text)
{
    connect(this, SIGNAL(triggered()), SLOT(copyText()));
}

void CopyAction::copyText()
{
    QApplication::clipboard()->setText(_text);
}
