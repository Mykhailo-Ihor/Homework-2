#pragma once
#include "footballer.h"

class Club
{
private:
	size_t size;
	size_t capacity;
	std::string name;
	double club_rate;
	int resize_counter;
	Footballer* arr;
	void checkSize();
	void checkIndex(int i) const;
	
public:
	class WrongIndex : public std::out_of_range
	{
	public:
		int index;
		WrongIndex(int i) : out_of_range("Index is out of range\n"), index(i) {}
	};
	Club();
	Club(const std::string& N, double cr, int s = 5);
	Club(const Club& C);
	~Club();
	Club& operator = (const Club& C);
	Footballer& operator[] (int i);
	const Footballer& operator[] (int i) const;
	void insert(Footballer F);
	void insert(Footballer F,int index);
	void sortByGoals();
	double TotalScore();
	double TotalPayment();
	void print(std::ostream& os = std::cout);
	
};
void distributePlayers(Club* arr, const std::string& filename);
std::string findMost(Club* arr, size_t n, double (Club::* m)());