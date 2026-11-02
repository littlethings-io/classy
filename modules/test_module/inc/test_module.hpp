#pragma once
#include <vector>
#include <string>


// Opgave 2 i Eksamen_sommeren_2026_opgaver.pdf

/**
    I denne opgave skal du implementere den samme matrix konstruktion som i opgave 1 men med den forskel at data
    nu skal opbevares i et array af doubles. Det p˚agældende array skal dynamisk allokeres.
    Da klassen allokerer memory dynamisk skal der ligeledes implementeres en destructor.

    Klassen er delvist deklareret her og implementeret i .cpp filen.

    Der er en funktion i modules_main.cpp "test_matrix()" som skal implementeres direkte i modules_main.cpp

    Sp1:
    Implementer en constructor, som dynamisk allokerer et array med længde n×m hvor n,m er matricens dimensioner.

    Sp2:
    Deklarer her en destructor for klassen matrix_2

    Sp3:
    Implementer i cpp filen en destructor som deallokerer det allokerede array

    Sp4:
    I funktionen test_matrix() i filen modules_main.cpp skal der implementeres en test af matrix implementations set, get
    og to_string() metode.
    I denne test skal matricen instantieres ved dynamisk allokering of deallokeres inden testen afsluttes
*/

class matrix_2 {
public:
    matrix_2(unsigned int rows, unsigned int cols);
    void set(unsigned int, unsigned int, double);
    double get(unsigned int, unsigned int) const;
    std::string to_string() const;

private:
    unsigned int rows_;
    unsigned int cols_;
    double *data_;
};