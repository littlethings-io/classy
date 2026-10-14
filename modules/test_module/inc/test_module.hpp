#pragma once
#include <vector>
#include <string>

namespace cc
{
class matrix_1 {
public:
    matrix_1(unsigned int rows, unsigned int cols);

    void set(unsigned int, unsigned int, double);
    double get(unsigned int, unsigned int) const;
    
    std::string to_string() const;

    // matrix_1 opretor+(const matrix_1& o) const;

private:
    unsigned int rows_;
    unsigned int cols_;
    std::vector<double> data_;
};

} // namespace cc