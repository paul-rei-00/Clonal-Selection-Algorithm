#include "Antigene.h"

Antigene::Antigene(std::initializer_list<int> cell)
	: Cell(cell)
{}

Antigene::Antigene(size_t size)
	: Cell(size)
{}

