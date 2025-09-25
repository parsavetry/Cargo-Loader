#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <forward_list>

using namespace std;
const int MAXLOAD737 = 46000;
const int MAXLOAD767 = 116000;

class Cargo   ///now an abstract due to pure virtual function
{
protected:
    string uldtype;
    string abbrev;
    string uldid;
    int aircraft;
    double weight;
    string destination;

public:
    ///Default constructor prototype
    Cargo();

    ///Full constructor prototype
    Cargo(const string& uldtype,
        const string& abbrev,
        const string& uldid,
        const int& aircraft,
        const double& weight,
        const string& destination);

    ///Copy constructor prototype
    Cargo(const Cargo& unit);

    ///Destructor prototype
    ~Cargo();

    ///Mutator (setters) prototypes
    void setuldtype(string);
    void setabbrev(string);
    void setuldid(string);
    void setaircraft(int);
    void setweight(double);
    void setdestination(string);

    ///Accessor (getters) prototypes
    string getuldtype() const;
    string getabbrev() const;
    string getuldid() const;
    int getaircraft() const;
    double getweight() const;
    string getdestination() const;

    virtual void maxweight(double&, double) = 0;  ///to be overridden

}; ///end of Cargo class

class Boeing737 : public Cargo  ///derived from Cargo
{
    using Cargo::Cargo;

private:
    int total737wt;
public:
    void maxweight(double&, double)override; ///overridden from Cargo class
};
class Boeing767 : public Cargo   ///derived from Cargo
{
    using Cargo::Cargo;

private:
    int total767wt;
public:
    void maxweight(double&, double)override;
};
void output(Cargo&);
void input();
void checkPlane(int);
void checkType(string);
void checkAbrv(string, string, int);
void listPrint(forward_list<Boeing737>& B737list, forward_list<Boeing767>& B767list);

int main()
{
    //Cargo badObj;
    input();
    return 0;
}
Cargo::Cargo()
{
    uldtype = "XXX";
    abbrev = " ";
    uldid = "xxxxxIB";
    aircraft = 700;
    weight = 0.0;
    destination = "NONE";
}
Cargo::Cargo(const string& uld,
    const string& abrv,
    const string& id,
    const int& craft,
    const double& wt,
    const string& dest)
{
    uldtype = uld;
    abbrev = abrv;
    uldid = id;
    aircraft = craft;
    weight = wt;
    destination = dest;
}

Cargo::Cargo(const Cargo& unit1)
{
    uldtype = unit1.uldtype;
    abbrev = unit1.abbrev;
    uldid = unit1.uldid;
    aircraft = unit1.aircraft;
    weight = unit1.weight;
    destination = unit1.destination;
}
Cargo::~Cargo()
{
    //cout << "Cargo destructor called\n\n";
}
void Cargo::setuldtype(string type)
{
    uldtype = type;
}
void Cargo::setabbrev(string abrv)
{
    abbrev = abrv;
}
void Cargo::setuldid(string id)
{
    uldid = id;
}
void Cargo::setaircraft(int air)
{
    aircraft = air;
}
void Cargo::setweight(double wt)
{
    weight = wt;
}
void Cargo::setdestination(string dest)
{
    destination = dest;
}
string Cargo::getuldtype() const
{
    return uldtype;
}
string Cargo::getabbrev() const
{
    return abbrev;
}
string Cargo::getuldid() const
{
    return uldid;
}
int Cargo::getaircraft() const
{
    return aircraft;
}
double Cargo::getweight() const
{
    return weight;
}
string Cargo::getdestination() const
{
    return destination;
}
void load737(forward_list<Boeing737> &B737list,
                 const string type,
                 const string abrv,
                 const string id,
                 const int craft,
                 const double wt,
                 const string dest,
                 double &totwt737)    ///added for use by maxweight, note not const so can be changed
{
    Boeing737 unitobj737(type,abrv,id,craft,wt,dest); ///constructor from Boeing737 class
    unitobj737.maxweight(totwt737,wt); ///call to overridden function, if too heavy, throw exception
    B737list.push_front(unitobj737);
}

void load767(forward_list<Boeing767>& B767list,
    const string type,
    const string abrv,
    const string id,
    const int craft,
    const double wt,
    const string dest,
    double& totwt767)
{
    Boeing767 unitobj767(type, abrv, id, craft, wt, dest); ///constructor from Boeing737 class
    unitobj767.maxweight(totwt767, wt); ///call to overridden function, if too heavy, throw exception
    B767list.push_front(unitobj767);
}

void Boeing737::maxweight(double& totwt737, double wt) {
    if (totwt737 > MAXLOAD737) {
        totwt737 -= wt; ///remove if overweight
        throw runtime_error("too heavy for 737, removed\n\n");
    }
}
void Boeing767::maxweight(double& totwt767, double wt) {
    if (totwt767 > MAXLOAD767) {
        totwt767 -= wt; ///remove if overweight
        throw runtime_error("too heavy for 767, removed\n\n");
    }
}
void output(Cargo& unit)
{
    cout << fixed << showpoint << setprecision(2);
    cout << "***********************************************************\n";
    cout << setw(19) << "Unit load type: " << unit.getuldtype() << endl;
    cout << setw(19) << "Unit abbreviation: " << unit.getabbrev() << endl;
    cout << setw(19) << "Unit identifier: " << unit.getuldid() << endl;
    cout << setw(19) << "Aircraft type: " << unit.getaircraft() << endl;
    cout << setw(19) << "Unit weight: " << unit.getweight() << " pounds" << endl;
    cout << setw(19) << "Destination code: " << unit.getdestination() << endl;
    cout << "***********************************************************\n";
}
void input()
{
    string cargostring;
    string type1;
    string type2;
    string abrv;
    string uld;
    int plane;
    double weight;
    string dest;
    string datafile;
    ifstream inputFile;
    double totwt737 = 0;
    double totwt767 = 0;
    forward_list<Boeing737> B737list;
    forward_list<Boeing767> B767list;
    ///******************************************************************
    ///file open and verification
    do {
        try {
            inputFile.clear();
            cout << "\nWhat's the name of your data file?\n";
            getline(cin, datafile);
            inputFile.open(datafile);
            if (!inputFile)
                throw runtime_error(datafile + " Bad filename\n");
            cout << endl;
        }
        catch (runtime_error& excpt) {
            cout << datafile << " " << excpt.what();
        }
    } while (!inputFile);
    ///************************************************************************
    ///file read/parse
    while (getline(inputFile, cargostring))   ///read in one line
    {
        try
        {
            istringstream cargoISS(cargostring); ///place line in the input string stream
            cargoISS >> type1 >> type2;
            if (type1.compare("Combo") == 0)
            {
                cargoISS >> abrv >> uld >> plane >> weight >> dest;
                type1 = type1 + " " + type2;
            }
            else
            {
                abrv = type2;
                cargoISS >> uld >> plane >> weight >> dest;
            }
        }
        catch (runtime_error& excpt) {
            cout << excpt.what();
        }
        ///************************************************************************
        ///data validation
        try {
            checkType(type1);///check for Container, Pallet
            checkPlane(plane);///737 or 767
            if (plane == 737) {
                checkAbrv(type1, abrv, plane);
                totwt737 += weight;
                load737(B737list, type1, abrv, uld, plane, weight, dest, totwt737);
            }
            if (plane == 767) {
                checkAbrv(type1, abrv, plane);
                totwt767 += weight;
                load767(B767list, type1, abrv, uld, plane, weight, dest, totwt767);
            }
        }
        catch (runtime_error& excpt) {
            cout << excpt.what();
        }
    }
    inputFile.close();
    ///************************************************************************
    listPrint(B737list, B767list);
    cout << "total weight for 737 load is " << totwt737 << endl;
    cout << "total weight for 767 load is " << totwt767 << endl;
}
///*************************************************************************
void checkType(string type1) {
    if (type1 != "Container" && type1 != "Pallet" && type1 != "Combo Flat")
        throw runtime_error(type1 + " is a bad type, not Container, Pallet or Combo Flat\n\n");
}

void checkPlane(int air) {
    if (air != 737 && air != 767)
        throw runtime_error((to_string(air)) + " " + "bad plane type\n\n");
}

void checkAbrv(string type1, string abrv, int plane) {
    if (plane == 737) {
        if (type1 == "Container" &&
            abrv != "AYF" &&
            abrv != "AYK" &&
            abrv != "AAA" &&
            abrv != "AYY"
            )
            throw runtime_error(type1 + " " + abrv + " bad type for 737\n\n");
        if (type1 == "Pallet" &&
            abrv != "PAG" &&
            abrv != "PMC" &&
            abrv != "PLA"
            )
            throw runtime_error(type1 + " " + abrv + " bad type for 737\n\n");
        if (type1 == "Combo Flat" &&
            abrv != "CFE" &&
            abrv != "CFK" &&
            abrv != "CFM"
            )
            throw runtime_error(type1 + " " + abrv + " bad type for 737\n\n");
    }
    if (plane == 767) {
        if (type1 == "Container" &&
            abrv != "AKE" &&
            abrv != "APE" &&
            abrv != "AKC" &&
            abrv != "AQP" &&
            abrv != "AQF" &&
            abrv != "AAP"
            )
            throw runtime_error(type1 + " " + abrv + " bad type for 767\n\n");
        if (type1 == "Pallet" &&
            abrv != "P1P" &&
            abrv != "P6P"
            )
            throw runtime_error(type1 + " " + abrv + " bad type for 767\n\n");
        if (type1 == "Combo Flat" &&
            abrv != "CFQ" &&
            abrv != "CFM" &&
            abrv != "CFP"
            )
            throw runtime_error(type1 + " " + abrv + " bad type for 767\n\n");
    }
}

void listPrint(forward_list<Boeing737>& B737list, forward_list<Boeing767>& B767list) {
    int i = 0;
    for (Cargo& out737 : B737list) {
        cout << "737 Unit# " << ++i << endl;
        output(out737);
    }

    cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

    i = 0;
    for (Cargo& out767 : B767list) {
        cout << "767 Unit# " << ++i << endl;
        output(out767);
    }
}

