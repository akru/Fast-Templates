#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <QObjectList>
#include <QSystemTrayIcon>
#include <QMenu>

class UserInterface
        : public QObject
{
    Q_OBJECT
public:
    explicit UserInterface();
    void createMainMenu(const QObjectList & model);
    
signals:
    void closed();
    
public slots:
    void close();
    void showMenu();

private:
    void createTrayIcon();
    void createTrayIconMenu();
    void createMenu(const QObjectList &model, QMenu &menu);

    QSystemTrayIcon trayIcon;
    QMenu trayIconMenu;
    QMenu mainMenu;
};

#endif // USER_INTERFACE_H
