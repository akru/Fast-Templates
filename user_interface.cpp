#include "user_interface.h"
#include "template_model.h"
#include "copy_action.h"
#include <QObjectList>
#include <QAction>
#include <QApplication>


UserInterface::UserInterface()
{
    createTrayIcon();
}

void UserInterface::createTrayIcon()
{
    createTrayIconMenu();
    trayIcon.setIcon(QIcon(":/tray_icon.svg"));
    trayIcon.setContextMenu(&trayIconMenu);
    trayIcon.show();
}

void UserInterface::createTrayIconMenu()
{
    QAction *exitAction = new QAction(tr("Exit"), this);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    trayIconMenu.addAction(exitAction);
}

void UserInterface::createMainMenu(const QObjectList &model)
{
    mainMenu.setWindowFlags(Qt::FramelessWindowHint);
    createMenu(model, mainMenu);
}

void UserInterface::createMenu(const QObjectList &model, QMenu &menu)
{
    QFont bold; bold.setBold(true);
    QObjectList::const_iterator it;
    for (it = model.constBegin(); it != model.constEnd(); ++it)
    {
        if ((*it)->children().count())
        {
            QMenu *submenu = menu.addMenu(((TemplateModel *)(*it))->getDesc());
            submenu->menuAction()->setFont(bold);
            createMenu((*it)->children(), *submenu);
        }
        else
        {
            CopyAction *act =
                    new CopyAction(
                        ((TemplateModel *)(*it))->getDesc(),
                        ((TemplateModel *)(*it))->getText(), &menu);
            menu.addAction(act);
        }
    }
}

void UserInterface::close()
{
    emit closed();
}

void UserInterface::showMenu()
{
    mainMenu.popup(QCursor::pos());
}
