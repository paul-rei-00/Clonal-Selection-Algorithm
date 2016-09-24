#include "Cell.h"

#ifndef ANTIBODY_H
#define ANTIBODY_H

class Antibody : public Cell
{
public:
	Antibody(std::initializer_list<int> cell);
	Antibody(size_t size);
	Antibody() = delete;
	Antibody* copy() override;
};

#endif

