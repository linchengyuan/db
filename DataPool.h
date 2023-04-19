#ifndef DATAPOOL_H
#define DATAPOOL_H

#include "DataStruct.h"
#include <QString>
#include <QStringList>

class DataPool
{
private:
    static DataPool *ptr;

private:
    DataPool();

public:
    static DataPool *GetInstance();
    static void DeleteInstance();

    //  角色
    QStringList GetRoles(ROLE_TYPE type);
    Role *GetRole(char *name);
    bool AddRole(Role *r);

    //  商品
    QStringList GetProductStringList();
    Product *GetProductByMarkID(char *mark);
    Product *GetProductByName(char *name);

    //  快递
    QStringList GetExpress();

    //
};

#endif // DATAPOOL_H
