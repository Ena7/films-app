#pragma once

#include <string>
using std::string;

class DTO {
private:
	string genre;
	int count;
public:
	DTO() : genre{ "" }, count{ -1 } {}
	DTO(const string g) : genre{ g }, count{ 0 } {}

	//gettere
	string getGenre() const;
	int getCount() const noexcept;

	void setCount(int newcount) noexcept;
};