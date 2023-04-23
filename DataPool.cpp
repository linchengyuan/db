#include "DataPool.h"
#include <QCoreApplication>

DataPool *DataPool::ptr = new DataPool();

DataPool::DataPool()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("test.db");
    }

    initDB();
}

void DataPool::initDB()
{
    bool success = db.open();
    if(!success)
    {
        qDebug() << "打开数据库失败";
        return;
    }

    initQuery();

    QSqlQuery query;
    QStringList sqls;

    sqls << "buy_order";
    sqls <<  "CREATE TABLE [buy_order]("
             "[id] INTEGER PRIMARY KEY AUTOINCREMENT, "
             "[date] CHAR(8), "
             "[supplier_id] INTEGER REFERENCES [role]([id]), "
             "[transactor_id] INTEGER REFERENCES [role]([id]), "
             "[product_order_id] INTEGER REFERENCES [product_order]([id]), "
             "[remark] CHAR(256));";

    sqls << "express";
    sqls << "CREATE TABLE [express]("
            "[id] INTEGER NOT NULL, "
            "[name] CHAR(16));";

    sqls << "express_order";
    sqls << "CREATE TABLE [express_order]("
            "[id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
            "[sale_order_id] INTEGER, "
            "[express_id] INTEGER REFERENCES [express]([id]), "
            "[count] INTEGER, "
            "[price] DOUBLE, "
            "[customer_name] CHAR(64), "
            "[customer_phone] CHAR(11), "
            "[customer_address] CHAR(128));";

    sqls << "one_sale_order";
    sqls << "CREATE TABLE [one_sale_order]("
            "[id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
            "[customer_id] INTEGER REFERENCES [role]([id]), "
            "[product_order_id] INTEGER REFERENCES [product_order]([id]), "
            "[express_order_id] INTEGER REFERENCES [express_order]([id]));";

    sqls << "product";
    sqls << "CREATE TABLE [product]("
            "[id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
            "[mark] CHAR(4), "
            "[rate] INTEGER, "
            "[name] CHAR(64));";

    sqls << "product_order";
    sqls << "CREATE TABLE [product_order]("
            "[id] INTEGER PRIMARY KEY AUTOINCREMENT, "
            "[product_id] INTEGER REFERENCES [product]([id]), "
            "[count] INTEGER, "
            "[price] DOUBLE, "
            "[in_price] DOUBLE);";

    sqls << "role";
    sqls << "CREATE TABLE [role]("
            "[id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
            "[type_id] INTEGER REFERENCES [role_type]([id]), "
            "[name] CHAR(64));";

    sqls << "role_type";
    sqls << "CREATE TABLE [role_type]("
            "[id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
            "[name] CHAR(16));";

    sqls << "sale_order";
    sqls << "CREATE TABLE [sale_order]("
            "[id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
            "[date] CHAR(8), "
            "[order_id] INTEGER REFERENCES [one_sale_order]([id]), "
            "[remark] CHAR(256));";

    sqls << "stock";
    sqls << "CREATE TABLE [stock]("
            "[id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
            "[product_id] INTEGER REFERENCES [product]([id]), "
            "[count] INTEGER, "
            "[price] DOUBLE);";

    QString tableName, sql;
    for(int i = 0; i < sqls.count(); i += 2)
    {
        tableName = sqls[i];
        sql = sqls[i + 1];
        createTable(tableName, sql);
    }
}

void DataPool::initQuery()
{
    bool success = false;

    createTableQuery = new QSqlQuery();

    idQuery = new QSqlQuery();
    success = idQuery->prepare("SELECT seq FROM sqlite_sequence WHERE name = :name");
    if(!success)
    {
        delete idQuery;
        idQuery = nullptr;
        qDebug() << "idQuery创建失败";
    }

    checkTableExitsQuery = new QSqlQuery();
    success = checkTableExitsQuery->prepare("SELECT count(*) FROM sqlite_master "
                                        "WHERE type = 'table' AND name = :name");
    if(!success)
    {
        delete checkTableExitsQuery;
        checkTableExitsQuery = nullptr;
        qDebug() << "checkTableExitsQuery创建失败";
    }

    //  role
    {
        roleTypeQuery = new QSqlQuery();
        success = roleTypeQuery->prepare("SELECT name FROM role "
                                     "WHERE type_id = :type_id");
        if(!success)
        {
            delete roleTypeQuery;
            roleTypeQuery = nullptr;
            qDebug() << "roleTypeQuery创建失败";
        }

        roleNameQuery = new QSqlQuery();
        success = roleNameQuery->prepare("SELECT id, type_id FROM role "
                                     "WHERE name = :name LIMIT 1");
        if(!success)
        {
            delete roleNameQuery;
            roleNameQuery = nullptr;
            qDebug() << "roleNameQuery创建失败";
        }
    }


    //  express
    {
        expressQuery = new QSqlQuery();
        success = expressQuery->prepare("SELECT id, name FROM express");
        if(!success)
        {
            delete expressQuery;
            expressQuery = nullptr;
            qDebug() << "expressQuery创建失败";
        }
    }


    //  buy order
    {
        buyOrderQuery = new QSqlQuery();
        success = buyOrderQuery->prepare("INSERT INTO buy_order "
                               "(date, supplier_id, transactor_id, remark) "
                               "VALUES(:data, :supplier_id, :transactor_id, :remark)");
        if(!success)
        {
            delete buyOrderQuery;
            buyOrderQuery = nullptr;
            qDebug() << "buyOrderQuery创建失败";
        }
    }


    //  product
    {
        productOrderQuery = new QSqlQuery();
        success = productOrderQuery->prepare("INSERT INTO product_order "
                                   "(order_type, order_id, product_id, count, price, in_price) "
                                   "VALUES(:order_type, :order_id, :product_id, :count, :price, :in_price)");
        if(!success)
        {
            delete productOrderQuery;
            productOrderQuery = nullptr;
            qDebug() << "productOrderQuery创建失败";
        }

        productTypeQuery = new QSqlQuery();
        success = productTypeQuery->prepare("SELECT mark, name FROM product WHERE type_id = :type");
        if(!success)
        {
            delete productTypeQuery;
            productTypeQuery = nullptr;
            qDebug() << "productTypeQuery创建失败";
        }

        productMarkQuery = new QSqlQuery();
        success = productMarkQuery->prepare("SELECT id, type_id, rate, name FROM product WHERE mark = :mark LIMIT 1");
        if(!success)
        {
            delete productMarkQuery;
            productMarkQuery = nullptr;
            qDebug() << "productMarkQuery创建失败";
        }

        productNameQuery = new QSqlQuery();
        success = productNameQuery->prepare("SELECT id, type_id, rate, mark FROM product WHERE name = :name LIMIT 1");
        if(!success)
        {
            delete productNameQuery;
            productNameQuery = nullptr;
            qDebug() << "productNameQuery创建失败";
        }

        productAddQuery = new QSqlQuery();
        success = productAddQuery->prepare("INSERT INTO product "
                                           "(type_id, mark, rate, name) "
                                           "VALUES(:type_id, :mark, :rate, :name)");
        if(!success)
        {
            delete productAddQuery;
            productAddQuery = nullptr;
            qDebug() << "productAddQuery创建失败";
        }
    }


    //  stock
    {
        stockAddQuery = new QSqlQuery();
        success = stockAddQuery->prepare("INSERT INTO stock "
                                         "(product_id, count, price) "
                                         "VALUES(:product_id, :count, :price)");
        if(!success)
        {
            delete stockAddQuery;
            stockAddQuery = nullptr;
            qDebug() << "stockAddQuery创建失败";
        }

        stockQuery = new QSqlQuery();
        success = stockQuery->prepare("SELECT count, price FROM stock WHERE product_id = :id LIMIT 1");
        if(!success)
        {
            delete stockQuery;
            stockQuery = nullptr;
            qDebug() << "stockQuery创建失败";
        }

        stockUpdateQuery = new QSqlQuery();
        success = stockUpdateQuery->prepare("UPDATE stock SET count = :count, price = :price WHERE product_id = :product_id");
        if(!success)
        {
            delete stockUpdateQuery;
            stockUpdateQuery = nullptr;
            qDebug() << "stockUpdateQuery创建失败";
        }
    }
}

bool DataPool::isTableExits(QString name)
{
    if(checkTableExitsQuery)
    {
        checkTableExitsQuery->bindValue(0, name);
        if(!checkTableExitsQuery->exec())
        {
            qDebug() << "查询表是否存在出错";
            return false;
        }

        if(checkTableExitsQuery->next())
        {
            if(checkTableExitsQuery->value(0).toInt() > 0)
            {
                return true;
            }
        }
    }


    return false;
}

void DataPool::createTable(QString name, QString sql)
{
    bool success = false;

    if(!isTableExits(name))
    {
        if(createTableQuery)
        {
            success = createTableQuery->exec(sql);
            if(!success)
            {
                qDebug() << name << "表创建失败";
            }
        }
    }
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

int DataPool::GetLastID(const char *name)
{
    if(idQuery)
    {
        idQuery->bindValue(0, name);
        idQuery->exec();
        if(idQuery->next())
        {
            return idQuery->value(0).toInt();
        }

    }
    return 0;
}

QStringList DataPool::GetRoles(ROLE_TYPE type)
{
    QStringList res;

    if(roleTypeQuery)
    {
        roleTypeQuery->bindValue(0, type);
        roleTypeQuery->exec();
        while(roleTypeQuery->next())
        {
           res << roleTypeQuery->value(0).toString();
        }

    }

    return res;
}

Role *DataPool::GetRole(char *name)
{
    Role *res = nullptr;

    if(roleNameQuery)
    {
        roleNameQuery->bindValue(0, name);
        roleNameQuery->exec();
        if(roleNameQuery->next())
        {
            res = new Role();
            res->id = roleNameQuery->value(0).toInt();
            res->type = (ROLE_TYPE)roleNameQuery->value(1).toInt();
            memcpy_s(res->name, ROLE_NAME_LENGTH, name, strlen(name));
        }
    }

    return res;
}

QStringList DataPool::GetProductList(PRODUCT_TYPE type)
{
    QStringList res;

    if(productTypeQuery)
    {
        productTypeQuery->bindValue(0, type);
        productTypeQuery->exec();
        while(productTypeQuery->next())
        {
            res << productTypeQuery->value(1).toString();
        }
    }

    return res;
}

QStringList DataPool::GetProductMarkList(PRODUCT_TYPE type)
{
    QStringList res;

    if(productTypeQuery)
    {
        productTypeQuery->bindValue(0, type);
        productTypeQuery->exec();
        while(productTypeQuery->next())
        {
            res << productTypeQuery->value(0).toString();
        }
    }

    return res;
}

Product *DataPool::GetProductByMarkID(char *mark)
{
    Product *res = nullptr;

    if(productMarkQuery)
    {
        productMarkQuery->bindValue(0, mark);
        productMarkQuery->exec();
        if(productMarkQuery->next())
        {
            res = new Product();
            res->id = productMarkQuery->value(0).toInt();
            res->rate = productMarkQuery->value(2).toInt();
            res->type = (PRODUCT_TYPE)productMarkQuery->value(1).toInt();
            memcpy_s(res->mark, MARK_LENGTH, mark, strlen(mark));
            std::string name = productMarkQuery->value(3).toString().toStdString();
            memcpy_s(res->name, PRODUCT_NAME_LENGTH, name.data(), name.length());
        }
    }

    return res;
}

Product *DataPool::GetProductByName(char *name)
{
    Product *res = nullptr;

    if(productNameQuery)
    {
        productNameQuery->bindValue(0, name);
        productNameQuery->exec();
        if(productNameQuery->next())
        {
            res = new Product();
            res->id = productNameQuery->value(0).toInt();
            res->rate = productNameQuery->value(2).toInt();
            res->type = (PRODUCT_TYPE)productNameQuery->value(1).toInt();
            memcpy_s(res->name, PRODUCT_NAME_LENGTH, name, strlen(name));
            std::string mark = productNameQuery->value(3).toString().toStdString();
            memcpy_s(res->mark, MARK_LENGTH, mark.data(), mark.length());
        }
    }
    return res;
}

void DataPool::SaveProductOrder(ProductOrder *order)
{
    if(productOrderQuery)
    {
        productOrderQuery->bindValue(0, order->order_type);
        productOrderQuery->bindValue(1, order->order_id);
        productOrderQuery->bindValue(2, order->product->id);
        productOrderQuery->bindValue(3, order->count);
        productOrderQuery->bindValue(4, order->price);
        productOrderQuery->bindValue(5, order->inPrice);

        productOrderQuery->exec();
    }
}

void DataPool::AddProduct(Product *p)
{
    if(productAddQuery)
    {
        productAddQuery->bindValue(0, p->type);
        productAddQuery->bindValue(1, p->mark);
        productAddQuery->bindValue(2, p->rate);
        productAddQuery->bindValue(3, p->name);
        int success = productAddQuery->exec();
        if(success)
        {
            AddToStock(p);
        }
    }

}

void DataPool::AddProductList(std::vector<Product *> products)
{
    for(int i = 0; i < products.size(); i++)
    {
        AddProduct(products[i]);
    }
}

QStringList DataPool::GetExpressList()
{
    QStringList res;

    if(expressQuery)
    {
        expressQuery->exec();
        while(expressQuery->next())
        {
            res << expressQuery->value(1).toString();
        }
    }

    return res;
}

Express *DataPool::GetExpressByName(char *name)
{

}

void DataPool::SaveBuyOrder(BuyOrder *order)
{
    if(buyOrderQuery)
    {
        buyOrderQuery->bindValue(0, order->date);
        buyOrderQuery->bindValue(1, order->supplier->id);
        buyOrderQuery->bindValue(2, order->transactor->id);
        buyOrderQuery->bindValue(3, order->remark);

        buyOrderQuery->exec();
        order->id = GetLastID(order->tableName);

        if(productOrderQuery)
        {
            for(int i = 0; i < order->products.size(); i++)
            {
                order->products[i]->order_id = order->id;
                SaveProductOrder(order->products[i]);
                UpdateStock(order->products[i]);
            }
        }
    }
}

void DataPool::AddToStock(Product *p)
{
    if(stockAddQuery && stockQuery)
    {
        stockQuery->bindValue(0, p->id);
        stockQuery->exec();
        if(!stockQuery->next())
        {
            stockAddQuery->bindValue(0, p->id);
            stockAddQuery->bindValue(1, 0);
            stockAddQuery->bindValue(2, 0.0);
            stockAddQuery->exec();
        }
    }
}

void DataPool::UpdateStock(ProductOrder *order)
{
    if(stockUpdateQuery)
    {
        int count = order->count;
        int price = order->price;
        int curCount = 0;
        double curPrice = 0.0;

        GetStockProduct(order->product->id, curCount, curPrice);

        if(order->order_type == ORDER_TYPE::BUY)
        {
            count += curCount;
            price += curPrice;
        }
        else if(order->order_type == ORDER_TYPE::SALE)
        {
            count -= curCount;
            price -= curPrice;
        }
        else
        {

        }

        //  需要保证库存包含该商品
        stockUpdateQuery->bindValue(0, count);
        stockUpdateQuery->bindValue(1, price);
        stockUpdateQuery->bindValue(2, order->product->id);
        stockUpdateQuery->exec();
    }
}

void DataPool::GetStockProduct(int id, int &count, double &price)
{
    if(stockQuery)
    {
        stockQuery->bindValue(0, id);
        stockQuery->exec();
        if(stockQuery->next())
        {
            count = stockQuery->value(0).toInt();
            price = stockQuery->value(1).toDouble();
        }
    }
}
