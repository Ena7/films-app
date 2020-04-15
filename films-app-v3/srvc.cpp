#include "srvc.h"

const vector<Film>& ServiceCart::getCart() const noexcept {
	return repoc.getCart();
}

void ServiceCart::clearCartSV() noexcept{
	repoc.clearCart();
}

void ServiceCart::addToCartSV(const string& title) {
	repoc.addToCart(title);
}

void ServiceCart::generateSV(const int& number) {
	repoc.generate(number);
}

void ServiceCart::exportSV(const string& filename) {
	repoc.exportR(filename);
}
