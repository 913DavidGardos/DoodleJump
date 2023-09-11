#pragma once
#include <vector>
template<typename T>
class Grid
{
public:
	Grid() = default;
	Grid(size_t rows, size_t cols);
	T& at(size_t row, size_t col);

private:
	size_t rows;
	size_t cols;
	std::vector<T> data;

};

