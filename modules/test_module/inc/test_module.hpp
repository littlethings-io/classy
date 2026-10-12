#pragma once
#include <stdio.h>
#include <string>

namespace cc
{
// Lav en class Weapon
// I class Weapon lav en default constructor.
// I clas Weapon lav en privat variable int type_;
// Sæt den til 0
// Lav en variable til int power_
// I class Weapon lav en constructor som tager int some type og sætter type_ til den
// Lav getters og setters for type_ og power_

// Lav en class Player (bare her i samme fil under class Weapon)
// I class Player lav en constructor som tager en pointer til Weapon
// Ha' en private variable til Weapon i Player og sæt den til pointeren du får fra constructor
// I player lav function Shoot
// Shoot skal tage en pointer til "int health".
// Shoot skal så tage den værdi som den får som argument og trække weapons power fra.
// Shoot skal ikke returnere noget, da health skal ændres via pointeren

// Prøve det af i modules_main

} // namespace cc