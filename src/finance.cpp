using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "./../include/global.hh"
#include "./../include/finance.hh"
#include "./../include/hospital.hh"

finance::finance()
{
    id = -1;
}

void finance::fillMap()
{
    fstream f;
    f.open("./data/finance.csv", ios::in);
    string temp;
    //skipping the first row containing column headers;
    getline(f >> ws, temp);
    //analyzing each entry afterwards;
    while (getline(f >> ws, temp))
    {
        finance a;
        //creating a string stream object to read from string 'temp';
        stringstream s(temp);
        string s1, s5, s6, s7, s8;
        //reading from the string stream object 's';
        getline(s, s1, ',');
        getline(s, a.buyerName, ',');
        getline(s, a.sellerName, ',');
        getline(s, a.itemName, ',');
        getline(s, s5, ',');
        getline(s, s6, ',');
        getline(s, s7, ',');
        getline(s, s8, ',');
        a.id = strToNum(s1);
        a.itemPrice = strToNum(s5);
        a.itemQuantity = strToNum(s6);
        a.money = strToNum(s7);
        a.isProfitable = (s8 == "Y");
        hospital::financeList[a.id] = a;
    }
    f.close();
    return;
}

void finance::saveMap()
{
    fstream f;
    f.open("./data/temp.csv", ios::out);
    // `le first line conataining column headers:
    f << "billId,buyerName,sellerName,itemName,itemPrice,itemQuantity,money,isProfitable\n";
    for (auto i : hospital::financeList)
    {
        f << i.second.id << "," << i.second.buyerName << "," << i.second.sellerName << "," << i.second.itemName
          << "," << i.second.itemPrice << "," << i.second.itemQuantity << "," <<i.second.money << "," << i.second.isProfitable <<"\n";
    }
    f.close();
    remove("./data/finance.csv");
    rename("./data/temp.csv", "./data/finance.csv");
    return;
}

void finance::addBill(string bName, string sName, string iName, int iPrice, int iQuantity, int sumMoney, bool iP)
{
    buyerName = bName;
    sellerName = sName;
    itemName = iName;
    itemPrice = iPrice;
    itemQuantity = iQuantity;
    money = sumMoney;
    isProfitable = iP;
    if (hospital::financeList.size() == hospital::financeLimit)
    {
        cout<<"\n\nFinance limit reached, can't add more!\n\n";
        return;
    }
    if (hospital::financeList.rbegin() != hospital::financeList.rend())
        id = ((hospital::financeList.rbegin())->first) + 1;
    else
        id = 1;
    hospital::financeList[id] = *this;

    //creating a fstream object to read/write from/to files;
    fstream f;
    //creating a record in ambulancesHistory.csv;
    f.open("./data/financeHistory.csv", ios::app);
    f << bName << "," << sName << "," << iName << "," << iPrice << "," << iQuantity << "," << sumMoney << "," << iP << endl;
    f.close();
}

void finance::printFinanceDetails()
{
    if (id == -1)
        return;
    cout << "Details:\n";
    cout << "billId              : " << id << "\n";
    cout << "buyerName           : " << buyerName << "\n";
    cout << "sellerName          : " << sellerName << "\n";
    cout << "itemName            : " << itemName << "\n";
    cout << "itemPrice           : " << itemPrice << "\n";
    cout << "itemQuantity        : " << itemQuantity << "\n";
    cout << "tradeMoney          : " << money << "\n";
    return;
}

int finance::getMoney()
{
    return money;
}

bool finance::getIsProfitable()
{
    return isProfitable;
}