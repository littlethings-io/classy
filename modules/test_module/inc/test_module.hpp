#pragma once
#include <iostream>

namespace cc {

    // Prøv selv at lave en vector klasse med template således at den kan tage enhver type ind og 
    // lave et array af dem. Dette array skal være dynamis allokeret (husk destruktoren!).
    // Eftersom den er dynamisk alloceret kan du i constructoren fortælle hvor lang den skal være
    // så du kan kalde Vector<T>(10) vector; Så behøver du kun ha typen i template og ingen længde
    // Lav dernæst en function der hedder "AddItem" lad den function returnere en index til hvor i 
    // array den blev placeret. Vi gør det med lidt snyd her for øvelsens skyld, så bare lav en klasse variable
    // der tæller op når du tilføjer en type til array.
    // Du skal også lave en function der hedder "Get(int index)" så du kan få en pointer tilbage til den box du prøver
    // at få ud
    

    // Lav en klasse der hedder Box. Der skal vi have længde, brede og dybde.
    // Lav så en test i modules_main hvor ud laver et array af Box (længde 10 fx).
    // Laver et par instancer af Box, sæt forskellige længder/breder/dybder 
    // og så adder dem til vectoren. 
    // Brug så den index du fik til en boxene til at finde den i vectoren (Get(...)) og print dens 
    // dimensioner for at se om det er den rigtige box du fik ud.
    // Husk at tjekke for index i Get så den ikke overskrider længden du satte array'et til at være
    // Hvis den gør, returnér en nullptr.
    // Husk at tjekke om det er en nullptr du får tilbage når du laver Get(index)
}