#include <iostream>
#include <string>
#include <ctime>
#include <cctype>

bool isLeap(int y) {
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int daysInMonth(int y, int m) {
	static const int days[12] = { 31, 28 , 31, 30,  31, 30, 31, 31, 30, 31, 30, 31 };
	if (m == 2) return days[1] + (isLeap(y) ? 1 : 0);
	return days[m - 1];
}
bool parseDate(const std::string& s, int& y, int& m, int& d) {
	//Expect format YYYY-MM-DD
	if (s.size() != 10 || s[4] != '-' || s[7] != '-') return false;
	for (size_t i : {0u, 1u, 2u, 3u, 5u, 6u, 8u, 9u}) {
		if (!std::isdigit(static_cast<unsigned char>(s[i]))) return false;
	}
	y = std::stoi(s.substr(0, 4));
	m = std::stoi(s.substr(5, 2));
	d = std::stoi(s.substr(8, 2));
	if (y < 1900 || m < 1 || m > 12) return false;
	int dim = daysInMonth(y, m);
	if (d < 1 || d > dim) return false;
	return true;
}

void currentYMD(int& y, int& m, int& d) {
	std::time_t t = std::time(nullptr);
	std::tm It{};
#if defined(_WIN32) 
	localtime_s(&It, &t);
#else
	It = *std::localtime(&t);
#endif
	y = It.tm_year + 1900;
	m = It.tm_mon + 1;
	d = It.tm_mday;
}
int computeAge(int by, int bm, int bd, int cy, int cm, int cd) {
	int age = cy - by;
	if (cm < bm || (cm == bm && cd < bd)) {
		age -= 1;
	}
	return age;
}

int main() {
	std::cout << "Enter your birthday (YYYY-MM-DD):";
	std::string input;
	std::getline(std::cin, input);

	int by, bm, bd;
	if (!parseDate(input, by, bm, bd)) {
        std::cerr << "Invalid date format or value. Use YYYY-MM-DD (e.g., 2001-02-28).\n";
		return 1;
	}

	int cy, cm, cd;
	currentYMD(cy, cm, cd);

	// Sanity check: birthday should not be in the future
	if (by > cy || (by == cy && (bm > cm || (bm == cm && bd > cd)))) {
		std::cerr << "Birthday is in the future.\n";
		return 1;
    }

	int age = computeAge(by, bm, bd, cy, cm, cd);
	std::cout << "You age " << age << "years old.\n";
	return 0;
}



