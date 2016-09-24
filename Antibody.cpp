#include "Antibody.h"

Antibody::Antibody(std::initializer_list<int> cell)
	: Cell(cell)
{}

Antibody::Antibody(size_t size)
	: Cell(size)
{}

Antibody* Antibody::copy() {
	return static_cast<Antibody*>(Cell::copy());
}

