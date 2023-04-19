#include "DataPool.h"

DataPool *DataPool::ptr = new DataPool();

DataPool::DataPool()
{

}

DataPool *DataPool::GetInstance()
{
    return ptr;
}

void DataPool::DeleteInstance()
{
    if(ptr)
    {
        delete ptr;
        ptr = nullptr;
    }
}

QStringList DataPool::GetRoles(ROLE_TYPE type)
{

}

Role *DataPool::GetRole(char *name)
{

}

QStringList DataPool::GetProductStringList()
{

}

Product *DataPool::GetProductByMarkID(char *mark)
{

}

Product *DataPool::GetProductByName(char *name)
{

}

QStringList DataPool::GetExpress()
{

}
