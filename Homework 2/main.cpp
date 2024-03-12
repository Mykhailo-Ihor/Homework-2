#include "club.h"
#include "footballer.h"
#include <fstream>
using namespace std;

int main()
{
	const size_t n = 3;
	Club* arr = new Club[n];
	arr[0] = Club("Real Madrid", 2000);
	arr[1] = Club("Barcelona", 1800);
	arr[2] = Club("Manchester United", 1500);
	distributePlayers(arr, "Text.txt");
	for (size_t i = 0; i < n; ++i)
	{
		arr[i].sortByGoals();
		arr[i].print();
		cout << "Total goals: " << arr[i].TotalScore() << endl;
		cout << "Total payment: " << arr[i].TotalPayment() << endl;
	}
	cout << "\nThe most payment club: " << findMost(arr, n, &Club::TotalPayment);
	cout << "\nThe most goals club: "  << findMost(arr, n, &Club::TotalScore);
	return 0;
}