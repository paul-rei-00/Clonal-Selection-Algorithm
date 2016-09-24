#include "Cell.h"

#ifndef ANTIGENE_H
#define ANTIGENE_H

class Antigene : public Cell
{
public:
	Antigene(std::initializer_list<int> cell);
	Antigene(size_t size);
	Antigene() = delete;
};

#endif

