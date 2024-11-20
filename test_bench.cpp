#include "HashTable.h"
#include <iostream>
using std::cout;

void TestSearch(HashTable<int>& table, string search_target);
//bool IsPrime(int i);

int main()
{
	HashTable<int> user_ages(5);

	user_ages.Insert("Chad", 34);
	user_ages.Insert("Corey", 29);
	user_ages.Insert("Dustin", 32);
	user_ages.Insert("April", 27);
	user_ages.Insert("Jessica", 45);
	user_ages.Update("Dustin", 31);

	//test overloaded bracket
	user_ages["Corey"] = 30;

	user_ages["Stephanie"] = 19;
}

void TestSearch(HashTable<int>& table, string search_target)
{
	int result;

	if (table.Search(search_target, result))
		cout << "Key \"" << search_target << "\" is paired with " << result << "\n";
	else
		cout << "Key \"" << search_target << "\" could not be found." << "\n";
}

