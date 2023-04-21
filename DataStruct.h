#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <QMetaType>
#include <vector>

const unsigned int PRODUCT_NAME_LENGTH = 64;
const unsigned int DATE_LENGTH = 8;
const unsigned int ROLE_NAME_LENGTH = 64;
const unsigned int EXPRESS_NAME_LENGTH = 16;
const unsigned int REMARK_LENGTH = 256;
const unsigned int PHONE_NUM_LENGTH = 11;
const unsigned int ADDRESS_LENGTH = 128;
const unsigned int MARK_LENGTH = 4;



enum ROLE_TYPE
{
    DEFAULT = 1,
    SUPPLIER,
    CUSTOMER,
    BOSS,
};

enum PRODUCT_TYPE
{
    CIGARETTE = 1,
    MISC,
};

enum ORDER_TYPE
{
    BUY = 1,
    SALE,
};

struct Express
{
    const char *tableName = "express";
    unsigned int id;
    char name[EXPRESS_NAME_LENGTH + 1];
};

struct Role
{
    const char *tableName = "role";
    unsigned int id;
    ROLE_TYPE type;
    char name[ROLE_NAME_LENGTH + 1];
};

struct ExpressOrder
{
    const char *tableName = "express_order";
    unsigned int id;
    Express *express;
    int count;
    double price;

    char name[ROLE_NAME_LENGTH + 1];
    char phone[PHONE_NUM_LENGTH + 1];
    char address[ADDRESS_LENGTH + 1];
};

struct Product
{
    const char *tableName = "product";
    unsigned int id;
    PRODUCT_TYPE type;
    char mark[MARK_LENGTH + 1];
    int rate;
    char name[PRODUCT_NAME_LENGTH + 1];
};

struct ProductOrder
{
    const char *tableName = "product_order";
    unsigned int id;
    ORDER_TYPE order_type;
    unsigned int order_id;
    Product *product;
    int count;
    double price;
    double inPrice;
};

struct BuyOrder
{
    const char *tableName = "buy_order";
    unsigned int id;
    char date[DATE_LENGTH + 1];
    Role *supplier;
    Role *transactor;
    std::vector<ProductOrder*> products;
    char remark[REMARK_LENGTH + 1];
};


struct OneSaleOrder
{
    const char *tableName = "one_sale_order";
    unsigned int id;
    Role *customer;
    std::vector<ProductOrder*> products;
    ExpressOrder *expressOrder;


};

struct SaleOrder
{
    const char *tableName = "sale_order";
    unsigned int id;
    char date[DATE_LENGTH + 1];

    std::vector<OneSaleOrder*> detail;
    char remark[REMARK_LENGTH + 1];
};



Q_DECLARE_METATYPE(Express)
Q_DECLARE_METATYPE(Role)
Q_DECLARE_METATYPE(ExpressOrder)
Q_DECLARE_METATYPE(Product)
Q_DECLARE_METATYPE(ProductOrder)
Q_DECLARE_METATYPE(BuyOrder)
Q_DECLARE_METATYPE(OneSaleOrder)
Q_DECLARE_METATYPE(SaleOrder)


#endif // DATASTRUCT_H
