#include "footballer.h"
#include <string>
using namespace std;

Footballer::Footballer(): first_name("No"), last_name("Name"), scored(0), pay_rate(1)
{
}

Footballer::Footballer(const string& N, const string& SN, int s) : first_name(N), last_name(SN), scored(s), pay_rate(1)
{
}


Footballer::Footballer(const Footballer& F) : first_name(F.first_name) , last_name(F.last_name), scored(F.scored), pay_rate(F.pay_rate)
{
}

Footballer& Footballer::operator=(const Footballer& F) 
{
	first_name = F.first_name;
	last_name = F.last_name;
	scored = F.scored;
	pay_rate = F.pay_rate;
	return *this;
}


int Footballer::goals() const
{
	return scored;
}

void Footballer::setPayRate(double r)
{
	if (r > 0)
	{
		pay_rate = r;
	}
	else
	{
		cerr << "Payment ratio can't be less then 0,field value is unchanged\n";
	}
}

double Footballer::AnnualIncome() const
{
	return scored * pay_rate;
}

void Footballer::printOn(ostream& os) const
{
	os << first_name << ' ' << last_name << " this year scored " << scored; scored == 1 ? os << " goal" : os << " goals"
	   << ", salary is: " << AnnualIncome() << endl;
}

void Footballer::readFrom(std::istream& is)
{
	is >> first_name >> last_name >> scored;
}

std::ostream& operator<<(std::ostream& os, Footballer& F)
{
	F.printOn(os);
	return os;
}

std::istream& operator>>(std::istream& is, Footballer& F)
{
	F.readFrom(is);
	return is;
}
