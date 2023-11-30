using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "./../include/global.hh"
#include "./../include/pharmacy.hh"
#include "./../include/hospital.hh"

pharmacy::pharmacy()
{
    id = -1;
}

void pharmacy::fillMap()
{
    fstream f;
    f.open("./data/pharmacies.csv", ios::in);
    string temp;
    // Skipping the first row containing column headers
    getline(f >> ws, temp);
    // Analyzing each entry afterwards
    while (getline(f >> ws, temp))
    {
        pharmacy p;
        // Creating a string stream object to read from the string 'temp'
        stringstream s(temp);
        string s1,s3,s4;
        // Reading from the string stream object 's'
        getline(s, s1, ',');
        getline(s, p.drugName, ',');
        getline(s, s3, ',');
        getline(s, s4, ',');
        p.id = strToNum(s1);
        p.price = strToNum(s3);
        p.quantity = strToNum(s4);
        hospital::pharmaciesList[p.id] = p;
    }
    f.close();
}

void pharmacy::saveMap()
{
    fstream f;
    f.open("./data/temp.csv", ios::out);
    // First line containing column headers
    f << "drugId,drugName,price,quantity\n";
    for (auto i : hospital::pharmaciesList)
    {
        f << i.second.id << "," << i.second.drugName << "," << i.second.price << "," << i.second.quantity << "\n";
    }
    f.close();
    remove("./data/pharmacies.csv");
    rename("./data/temp.csv", "./data/pharmacies.csv");
}

void pharmacy::printDetails()
{
    if (id == -1)
        return;
    cout << "Details:\n";
    cout << "drugID         : " << id << "\n";
    cout << "drugName       : " << drugName << "\n";
    cout << "Price          : $" << price << "\n";
    cout << "Quantity       : " << quantity << "\n";
    return;
}

void pharmacy::getDetails(int rec)
{
    int opt = 0;
    cout << "\nOPTIONS:\n[1]: Filter by drugID\n[2]: Filter by drugName\n\n";
    cin >> opt;
    while (opt != 1 && opt != 2)
        cout << "Option 1 or 2?\n", cin >> opt;

    // 1: Filter by drugID
    if (opt == 1)
    {
        int reqId;
        cout << "\nEnter drugID:\n";
        cin >> reqId;
        if (hospital::pharmaciesList.find(reqId) != hospital::pharmaciesList.end())
            *this = hospital::pharmaciesList[reqId];
        else
            cout << "\nNo matching record found!\n";
    }
    // 2: Filter by Drug Name
    else if (opt == 2)
    {
        string reqName;
        cout << "\nEnter drugName:\n";
        getline(cin >> ws, reqName);
        vector<pharmacy> matchingRecords;
        for (auto i : hospital::pharmaciesList)
        {
            if (i.second.drugName == reqName)
                matchingRecords.push_back(i.second);
        }
        cout << "\n";
        cout << matchingRecords.size() << " matching record(s) found!\n";
        for (auto i : matchingRecords)
            i.printDetails();
        char tt = 'N';
        if (matchingRecords.size() > rec)
        {
            do
            {
                int reqId;
                cout << "\nEnter the ID of the required drug: ";
                cin >> reqId;
                if (hospital::pharmaciesList.find(reqId) != hospital::pharmaciesList.end())
                    *this = hospital::pharmaciesList[reqId];
                else
                {
                    cout << "\nInvalid ID!\nTry again? (Y = Yes || N = No)\n";
                    cin >> tt;
                    while (tt != 'Y' && tt != 'N')
                        cout << "Y or N?\n", cin >> tt;
                }
            } while (tt == 'Y');
        }
    }
    return;
}

void pharmacy::sellDrugs()
{
    if (hospital::pharmaciesList.empty()) {
        cout << "\nNo drugs available in the pharmacy!\n";
        return;
    }

    // Display available drugs
    cout << "\nAvailable Drugs:\n";
    for (auto i : hospital::pharmaciesList) {
        cout << "drugID: " << i.first << "\ndrugName: " << i.second.drugName << "\nQuantity: " << i.second.quantity << endl;
    }

    int buyerId;
    cout << "\nEnter the Patient ID who buy: ";
    cin >> buyerId;
    // Check if the entered patientID exists
    if (hospital::patientsList.find(buyerId) == hospital::patientsList.end()) {
        cout << "\nInvalid Patient ID!\n";
        return;
    }

    // Gather details of the drug to sell
    int drugId;
    cout << "\nEnter the Drug ID to sell: ";
    cin >> drugId;
    // Check if the entered drug ID exists
    if (hospital::pharmaciesList.find(drugId) == hospital::pharmaciesList.end()) {
        cout << "\nInvalid Drug ID!\n";
        return;
    }

    // Gather quantity to sell
    int drugQuantity;
    cout << "Enter the Quantity to sell: ";
    cin >> drugQuantity;
    // Check if the entered quantity is available
    if (drugQuantity > hospital::pharmaciesList[drugId].quantity) {
        cout << "\nInsufficient quantity!\n";
        return;
    }

    // Update the stock after selling drugs
    *this = hospital::pharmaciesList[drugId];
    hospital::pharmaciesList[drugId].quantity -= drugQuantity;
    

    //creating a fstream object to read/write from/to files;
    fstream f;
    //creating a record in pharmaciesHistory.csv;
    f.open("./data/pharmaciesHistory.csv",ios::app);
    f << drugName << "," << price << "," << quantity << endl;
    f.close();
    //creating a bill in finance;
    finance a;
    a.addBill(hospital::patientsList[buyerId].getFirstName() + " " + hospital::patientsList[buyerId].getLastName(), "hospital", drugName, price, drugQuantity, price*drugQuantity, true);

    cout << "\n"
         << drugName << "sell successfully\n";
    cout << "Its ID is: " << id << "\n";
}

void pharmacy::purchaseDrugs(string supplier)
{
    if (hospital::pharmaciesList.size() == hospital::pharmaciesLimit)
    {
        cout<<"\n\nPharmacies limit reached, can't purchase more!\n\n";
        return;
    }
    //getting the basic details of the pharmacy from the user side;
    cout << "\nEnter Name of the drug:\n";
    getline(cin >> ws, drugName);
    cout << "\nEnter Price of the drug:\n";
    cin >> price;
    cout << "\nEnter Quantity of the drug:\n";
    cin >> quantity;
    int tmpQuantity = quantity;
    if(hospital::pharmaciesList.rbegin()!=hospital::pharmaciesList.rend())
        for(auto i : hospital::pharmaciesList)
        {
            if(i.second.drugName == drugName)
            {
                id = i.first;
                quantity += i.second.quantity;
                break;
            }
        }
        //id = ((hospital::pharmaciesList.rbegin())->first) + 1;
    else
        id = 1;
    hospital::pharmaciesList[id] = *this;

    //creating a fstream object to read/write from/to files;
    fstream f;
    //creating a record in pharmaciesHistory.csv;
    f.open("./data/pharmaciesHistory.csv",ios::app);
    f << drugName << "," << price << "," << tmpQuantity << endl;
    f.close();
    //creating a bill in finance;
    finance a;
    a.addBill("hospital", "Abbott Laboratories Ltd", drugName, price, tmpQuantity, price*tmpQuantity, false);

    cout << "\n"
         << drugName << "purchased successfully\n";
    cout << "Its ID is: " << id << "\n";
}