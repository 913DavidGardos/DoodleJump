#include "Grid.h"

template<typename T>
inline Grid<T>::Grid(size_t rows, size_t cols) :
	rows(rows), cols(cols), data(cols* rows) {}

template<typename T>
T& Grid<T>::at(size_t row, size_t col)
{
	return data.at(row * col + col);
}
