#ifndef DATA_USERS_H
#define DATA_USERS_H

#include <QString>


    void enableWriteAccess(const QString &filePath);
    void disableWriteAccess(const QString &filePath);
    void enableReadAccess(const QString &filePath);
    void disableReadAccess(const QString &filePath);
    bool createUser(const QString &filePath, const QString &login, const QString &password, const QString &name);
    bool userExists(const QString &filePath, const QString &login, const QString &password);
    bool userExists(const QString &filePath, const QString &login);


#endif // DATA_USERS_H
