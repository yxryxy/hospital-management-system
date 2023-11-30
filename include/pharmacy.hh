#ifndef PHARMACY
#define PHARMACY
using namespace std;
#include <string>

#include "./patient.hh"
#include "./finance.hh"

class pharmacy 
{
private:
    int id;
    string drugName;
    int price;
    int quantity;

public:
    pharmacy();
    void fillMap();
    void saveMap();
    void printDetails();
    void getDetails(int rec = 0);
    void sellDrugs();
    void purchaseDrugs(string supplier = "Abbott Laboratories Ltd");
};
#endif // !PHARMACY
