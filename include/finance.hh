#ifndef FINANCE
#define FINANCE
using namespace std;
#include <string>

class finance
{
private:
    int id;
    string buyerName;
    string sellerName;
    string itemName; //vehicle registration number;
    int itemPrice;
    int itemQuantity;
    int money;
    bool isProfitable;

public:
    finance();
    void fillMap();
    void saveMap();
    void addBill(string bName, string sName, string iName, int iPrice, int iQuantity, int money, bool iP);
    void printFinanceDetails();
    int getMoney();
    bool getIsProfitable();
};
#endif // !FINANCE