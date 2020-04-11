#pragma once

#include <string>
using std::string;

class DTO {
private:
	string genre;
	int count;
public:
	DTO(): genre{ "" }, count{ 0 } {}
	DTO(const string g) : genre{ g }, count{ 1 } {}
	
	//gettere
	string getGenre() const;
	int getCount() const noexcept;
	
	//incrementeaza frecventa
	void inc() noexcept;
};