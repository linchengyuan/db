#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <vector>

const unsigned int PRODUCT_NAME_LENGTH = 64;
const unsigned int DATE_LENGTH = 8;
const unsigned int ROLE_NAME_LENGTH = 16;
const unsigned int EXPRESS_NAME_LENGTH = 16;
const unsigned int REMARK_LENGTH = 256;
const unsigned int PHONE_NUM_LENGTH = 11;
const unsigned int ADDRESS_LENGTH = 128;

enum ROLE_TYPE
{
    DEFAULT,
    SUPPLIER,
    CUSTOMER,
    BOSS,
};

struct Express
{
    unsigned int id;
    char name[EXPRESS_NAME_LENGTH];
};

struct ExpressOrder
{
    unsigned int id;
    Express *express;
    int count;
    double price;

    char name[ROLE_NAME_LENGTH];
    char phone[PHONE_NUM_LENGTH];
    char address[ADDRESS_LENGTH];
};

struct Role
{
    unsigned int id;
    ROLE_TYPE type;
    char name[ROLE_NAME_LENGTH];
};

struct Product
{
    unsigned int id;
    char mark[4];
    int rate;
    char name[PRODUCT_NAME_LENGTH];
};

struct ProductOrder
{
    unsigned int id;
    Product *product;
    int count;
    double price;
    double inPrice;
};

struct BuyOrder
{
    unsigned int id;
    char date[DATE_LENGTH];
    Role *supplier;
    Role *transactor;
    std::vector<ProductOrder*> products;
    char remark[REMARK_LENGTH];
};


struct OneSaleOrder
{
    unsigned int id;
    Role *customer;
    std::vector<ProductOrder*> products;
    ExpressOrder *expressOrder;

};

struct SaleOrder
{
    unsigned int id;
    char date[DATE_LENGTH];

    std::vector<OneSaleOrder*> detail;
    char remark[REMARK_LENGTH];
};




#endif // DATASTRUCT_H
