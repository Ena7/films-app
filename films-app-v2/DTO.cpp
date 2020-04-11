#include "DTO.h"

string DTO::getGenre() const{
	return genre;
}

int DTO::getCount() const noexcept{
	return count;
}

void DTO::inc() noexcept{
	count++;
}
