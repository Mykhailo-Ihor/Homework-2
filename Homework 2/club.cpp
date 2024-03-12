#include "club.h"
#include <fstream>
#include <sstream>
using namespace std;
void Club::checkSize()
{
	if (capacity == size)
	{
        if (resize_counter < 3) 
        {
            size += 5;
        }
        else 
        {
            size *= 2; 
        }
        Footballer* newArray = new Footballer[size];
        for (int i = 0; i < capacity; ++i) 
        {
            newArray[i] = arr[i];
        }
        delete[] arr; 
        arr = newArray;
        ++resize_counter;
	}
}

void Club::checkIndex(int i) const
{
    if (i < 0 || i >= capacity) throw WrongIndex(i);
}

Club::Club() :size(5), capacity(0), name("No name club"), club_rate(1), arr(new Footballer[size]), resize_counter(0)
{
}

Club::Club(const std::string& N, double cr, int s) : size(s), capacity(0), name(N), club_rate(cr), arr(new Footballer[size]),resize_counter(0)
{
}

Club::Club(const Club& C) :size(C.size), capacity(C.capacity), name(C.name), club_rate(C.club_rate),  arr(new Footballer[C.size]), resize_counter(0)
{
    for (size_t i = 0; i < capacity; ++i)
    {
        arr[i] = C.arr[i];
    }
}

Club::~Club()
{
	delete[] arr;
}

Club& Club::operator=(const Club& C)
{
    if (this != &C)
    {
        delete[] arr;
        capacity = C.capacity;
        size = C.size;
        name = C.name;
        resize_counter = C.resize_counter;
        club_rate = C.club_rate;
        arr = new Footballer[size];
        for (size_t i = 0; i < capacity; ++i)
        {
            arr[i] = C.arr[i];
        }
    }
    return *this;
}

Footballer& Club::operator[](int i)
{
    checkIndex(i);
    return arr[i];
}

const Footballer& Club::operator[](int i) const
{
    checkIndex(i);
    return arr[i];
}

void Club::insert(Footballer F)
{
    checkSize();
    arr[capacity] = F;
    arr[capacity].setPayRate(club_rate);
    ++capacity;
}

void Club::insert(Footballer F,int index)
{
    checkIndex(index);
    checkSize();
    for (size_t i = capacity; i > index; --i) arr[i] = arr[i - 1];
    arr[index] = F;
    arr[index].setPayRate(club_rate);
    ++capacity;
}

void Club::sortByGoals()
{
    for (size_t i = 1; i < capacity; ++i)
    {
        Footballer key = arr[i];
        size_t j = i - 1;
        while (j >= 0 && arr[j].goals() < key.goals()) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

double Club::TotalScore()
{
    int res = 0;
    for (size_t i = 0; i < capacity; ++i)
    {
        res += arr[i].goals();
    }
    return res;
}

double Club::TotalPayment()
{
    double res = 0;
    for (size_t i = 0; i < capacity; ++i)
    {
        res += arr[i].AnnualIncome();
    }
    return res;
}

void Club::print(ostream& os)
{
    os << "Club: " << name << ", Club ratio: " << club_rate << endl;
    if (capacity > 0)
    {
        os << "Players:\n";
        for (size_t i = 0; i < capacity; ++i)
        {
            arr[i].printOn(os);
        }
    }
    
}

void distributePlayers(Club* arr, const std::string& filename)
{
    fstream fin(filename);
    size_t size;
    fin >> size;
    string club;
    Footballer F;
    for (size_t i = 0; i < size; ++i)
    {   
        fin.get();
        getline(fin, club, '*');
        fin >> F;
        if (club == "Real Madrid")
        {
            arr[0].insert(F);
        }
        else if (club == "Barcelona")
        {
            arr[1].insert(F);
        }
        else
        {
            arr[2].insert(F);
        }
    }
}

string findMost(Club* arr, size_t n, double (Club::* m)())
{
    Club find = arr[0]; 
    for (size_t i = 1; i < n; ++i) 
    {
        if ((find.*m)() < (arr[i].*m)()) 
        {
            find = arr[i];
        }
    }
    
    std::ostringstream oss;
    find.print(oss); 
    std::string result = oss.str(); 
    size_t pos = result.find(",");
    if (pos != std::string::npos) 
    {
        return result.substr(6, pos - 6); 
    }
    return result;
}
