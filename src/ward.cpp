using namespace std;
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

#include "./../include/global.hh"
#include "./../include/ward.hh"
#include "./../include/hospital.hh"

ward::ward()
{
    id = -1;
    N = NULL;
}

void ward::fillMap()
{
    fstream f;
    f.open("./data/wards.csv", ios::in);
    string temp;
    // Skipping the first row containing column headers;
    getline(f >> ws, temp);
    // Analyzing each entry afterwards;
    while (getline(f >> ws, temp))
    {
        ward w;
        // Creating a string stream object to read from string 'temp';
        stringstream s(temp);
        string s1, s2, s3, s4, s5, s6;
        // Reading from the string stream object 's';
        getline(s, s1, ',');
        getline(s, s2, ',');
        getline(s, s3, ',');
        getline(s, s4, ',');
        getline(s, s5, ',');
        getline(s, s6, ',');
        w.id = strToNum(s1);
        w.remain = strToNum(s2);
        if(atoi(s3.c_str()) != -1)
        {
            w.pGroup.push_back(hospital::patientsList[strToNum(s3)]);
        }
        if(atoi(s4.c_str()) != -1)
        {
            w.pGroup.push_back(hospital::patientsList[strToNum(s4)]);
        }
        if(atoi(s5.c_str()) != -1)
        {
            w.pGroup.push_back(hospital::patientsList[strToNum(s5)]);
        }
        if(atoi(s6.c_str()) != -1)
        {
            w.N = &hospital::nursesList[strToNum(s6)];
        }
        hospital::wardsList[w.id] = w;
    }
    f.close();
}    

void ward::saveMap()
{
    fstream f;
    f.open("./data/temp.csv", ios::out);
    // `le first line conataining column headers:
    f << "wardId,remain,patient1Id,patient2Id,patient3Id,nurseId\n";
    for (auto i : hospital::wardsList)
    {
        f << i.second.id << "," << i.second.remain << "," ;
        if(i.second.remain == 3)
        {
            f << "-1,-1,-1,-1" << endl;
        }
        else if(i.second.remain == 2)
        {
            cout << "enter" <<endl;
            f << i.second.pGroup[0].id << ",";
            f << "-1,-1,";
            f << i.second.N->id << endl;
        }
        else if(i.second.remain == 1)
        {
            f << i.second.pGroup[0].id << ",";
            f << i.second.pGroup[1].id << ",";
            f << "-1,";
            f << i.second.N->id << endl;
        }
        else if(i.second.remain == 0)
        {
            f << i.second.pGroup[0].id << ",";
            f << i.second.pGroup[1].id << ",";
            f << i.second.pGroup[2].id << ",";
            f << i.second.N->id << endl;
        }
    }
    f.close();
    remove("./data/wards.csv");
    rename("./data/temp.csv", "./data/wards.csv");
}

void ward::addWard()
{
    if (hospital::wardsList.size() == hospital::wardsLimit)
    {
        cout << "\n\nWards limit reached, can't add more!\n\n";
        return;
    }
    remain = 3;
    N = NULL;
    if (hospital::wardsList.rbegin() != hospital::wardsList.rend())
        id = ((hospital::wardsList.rbegin())->first) + 1;
    else
        id = 1;
    hospital::wardsList[id] = *this;

    // Creating a fstream object to read/write from/to files;
    fstream f;
    // Creating a record in wardsHistory.csv;
    f.open("./data/wardsHistory.csv", ios::app);
    f << id << endl;
    f.close();

    cout << "\n"
         << " ward added successfully!\n";
    cout << "Its ID is: " << id << "\n";
}

void ward::printDetails()
{
    if (id == -1)
        return;
    cout << "Details:\n";
    cout << "wardID              : " << id << "\n";
    cout << "remain            : " << remain << "\n";
    if(remain == 2)
    {
        cout << "patient1ID          :" << pGroup[0].id << "\n";
        cout << "nurseID             :" << N->id << "\n";
    }
    else if(remain == 1)
    {
        cout << "patient1ID          :" << pGroup[0].id << "\n";
        cout << "patient2ID          :" << pGroup[1].id << "\n";
        cout << "nurseID             :" << N->id << "\n";
    }
    else if(remain == 0)
    {
        cout << "patient1ID          :" << pGroup[0].id << "\n";
        cout << "patient2ID          :" << pGroup[1].id << "\n";
        cout << "patient3ID          :" << pGroup[2].id << "\n";
        cout << "nurseID             :" << N->id << "\n";
    }
    else
    {
        cout << "No patients have been admitted!" << "\n";
    }
    return;
}

void ward::getDetails(int rec)
{
    int opt = 0;
    cout << "\nOPTIONS:\n[1]: Filter by ID\n\n";
    cin >> opt;
    while (opt != 1)
        cout << "Option 1 or 2?\n", cin >> opt;

    // 1: Filter by ID;
    if (opt == 1)
    {
        int reqId;
        cout << "\nEnter ID:\n";
        cin >> reqId;
        if (hospital::wardsList.find(reqId) != hospital::wardsList.end())
            *this = hospital::wardsList[reqId];
        else
            cout << "\nNo matching record found!\n";
    }
    return;
}

void ward::allocateWard(patient p)
{
    for(auto i : hospital::wardsList)
    {
        if(i.second.remain == 0)
            continue;
        else if(i.second.remain == 3)
        {
            i.second.pGroup.push_back(p);
            i.second.remain -= 1;
            for(auto j : hospital::nursesList)
            {
                //the default number of nurses is sufficient
                if(j.second.idle == true)
                {
                    hospital::nursesList[j.second.id].idle = false;
                    hospital::wardsList[i.second.id].N = &hospital::nursesList[j.second.id];
                    break;
                }
            }
            hospital::wardsList[i.second.id].remain = i.second.remain;
            for(int x = 0; x < i.second.pGroup.size(); x++)
            {
                hospital::wardsList[i.second.id].pGroup.push_back(i.second.pGroup[x]);
            }
            cout << p.id << " patient has been hospitalized in " << i.second.id << " ward!" << "\n";
            break;
        }
        else
        {
            hospital::wardsList[i.second.id].pGroup.push_back(p);
            hospital::wardsList[i.second.id].remain -= 1;
            cout << p.id << " patient has been hospitalized in " << i.second.id << " ward!" << "\n";
            break;
        }
    }
    return;
}

void ward::recycleWard(patient p)
{
    bool isFind = false;
    for(auto i : hospital::wardsList)
    {
        if(i.second.remain == 3)
            continue;
        else
        {
            vector<patient>::iterator it = hospital::wardsList[i.second.id].pGroup.begin();
            for(;it!=hospital::wardsList[i.second.id].pGroup.end();it++)
            {
                if((*it).id == p.id)
                {
                    hospital::wardsList[i.second.id].pGroup.erase(it);
                    hospital::wardsList[i.second.id].remain += 1;
                    i.second.remain += 1;
                    isFind = true;
                    break;
                }
            }
            if(i.second.remain == 3)
            {
                for(auto j : hospital::nursesList)
                {
                    if(j.second.id == i.second.N->id)
                    {
                        hospital::nursesList[j.second.id].idle = true;
                        hospital::wardsList[i.second.id].N = NULL;
                        break;
                    }
                }
            }
        }
        if(isFind)
        {
            cout << p.id << " patient has removed from " << i.second.id << " ward" << endl;
            break;
        }
    }
    return;
}

void ward::removeWard()
{
    cout << "\nSearch for the ward you want to remove.\n";
    getDetails();
    if (id == -1)
        return;
    hospital::wardsList.erase(id);

    cout << id << " ward removed successfully!\n";
}