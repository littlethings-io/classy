#pragma once
#include <vector>
#include <string>

namespace cc
{


/**
Examensopgaver:
opgave 1:
Deklarer overloading af + operatoren for klassen matrix_1 ved en const klasse metode

opgave 2:
Implementer overloading af + operatoren i filen matrix_1 
Plus operatoren skal implementeres ved at den resulterende matrix er indexvis summen af de to matricer der adderes

opgave 3:
Implementer en test af + operatoren i modules_main.cpp
Lav to matrix'er - udskrev summen (vha to_string()) medtoden med std::cout << m.to_string() << std::endl;
**/

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



/***
    Lav en dynamic allokeret array med størrelse 20 i en default constructor
    Lav en funktion der giver et index og et tal, således at den bliver placeres i array
    Husk i funktionen at teste for længden af array i forhold til den index du indsætter som argument
    (Den må ikke være større end array størrelse!)
    Lav en funktion der returnerer ponteren til array'et.
    Husk at lave en destructor!
*/
class Dynamic {
    public:
    private:
};

} // namespace cc