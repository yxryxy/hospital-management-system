#ifndef WARD
#define WARD
using namespace std;
#include <string>
#include <vector>

#include "./nurse.hh"
class patient;

class ward
{
private:
    int id;
    int remain;
    vector<patient> pGroup;
    nurse *N;

public:
    ward();
    void fillMap();
    void saveMap();
    void addWard();
    void printDetails();
    void getDetails(int rec = 0);
    void allocateWard(patient p);
    void recycleWard(patient p);
    void removeWard();
};
#endif // !WARD