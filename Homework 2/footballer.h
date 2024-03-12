#pragma once

#include <iostream>
#include <string>
class Footballer
{
private:
	std::string first_name;
	std::string last_name;
	int scored;
	double pay_rate;
public:
	Footballer();
	Footballer(const std::string& N, const std::string& SN, int s = 0);
	Footballer(const Footballer& F);
	Footballer& operator = (const Footballer& F);
	int goals() const;
	void setPayRate(double r);
	double AnnualIncome() const;
	void printOn(std::ostream& os = std::cout) const;
	void readFrom(std::istream& is);
};
std::ostream& operator << (std::ostream& os, Footballer& F);
std::istream& operator >> (std::istream& is, Footballer& F);
