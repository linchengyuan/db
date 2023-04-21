#ifndef DATAPOOL_H
#define DATAPOOL_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "DataStruct.h"
#include <QString>
#include <QStringList>

class DataPool
{
private:
    static DataPool *ptr;
    QSqlDatabase db;

    QSqlQuery *idQuery;
    QSqlQuery *checkTableExitsQuery;
    QSqlQuery *createTableQuery;
    QSqlQuery *roleTypeQuery;
    QSqlQuery *roleNameQuery;
    QSqlQuery *buyOrderQuery;
    QSqlQuery *productOrderQuery;       //  插入product_order
    QSqlQuery *productTypeQuery;        //  从product选择 type 类型的 mark + name
    QSqlQuery *productMarkQuery;        //  从product选择对应 mark 的 product
    QSqlQuery *productNameQuery;        //  从product选择对应 name 的 product
    QSqlQuery *productAddQuery;         //  添加商品种类
    QSqlQuery *stockAddQuery;
    QSqlQuery *stockQuery;
    QSqlQuery *stockUpdateQuery;

private:
    DataPool();

    void initDB();
    void initQuery();
    bool isTableExits(QString name);
    void createTable(QString name, QString sql);


public:
    static DataPool *GetInstance();
    static void DeleteInstance();

    //  id
    int GetLastID(const char *name);

    //  角色
    QStringList GetRoles(ROLE_TYPE type);
    Role *GetRole(char *name);
    bool AddRole(Role *r);

    //  商品
    QStringList GetProductList(PRODUCT_TYPE type);
    QStringList GetProductMarkList(PRODUCT_TYPE type);
    Product *GetProductByMarkID(char *mark);
    Product *GetProductByName(char *name);
    void SaveProductOrder(ProductOrder *order);
    void AddProduct(Product *p);
    void AddProductList(std::vector<Product*> products);

    //  快递
    QStringList GetExpressList();
    Express *GetExpressByName(char *name);

    //  buy order
    void SaveBuyOrder(BuyOrder *order);


    //  库存
    void AddToStock(Product *p);
    void UpdateStock(ProductOrder *order);
    void GetStockProduct(int id, int &count, double &price);


    //  db
    void Open();
    void  Close();
};

#endif // DATAPOOL_H
