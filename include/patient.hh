#ifndef PATIENT
#define PATIENT
using namespace std;

#include "./person.hh"
#include "./ward.hh"

class appointment;
class patient : public person
{
private:
    int height; //in cms;
    int weight; //in pounds;
    bool hospitalized;
    bool alive;
    friend class appointment;
    friend class ward;

public:
    patient();
    void fillMap();
    void saveMap();
    void addPerson();
    void printDetails();
    void printDetailsFromHistory(string extraDetails = "");
    void getDetails(int rec = 0);
    void getDetailsFromHistory();
    void hospitalize();
    void reportADeath();
    void removePerson();
    string getFirstName();
    string getLastName();
};
#endif // !PATIENT