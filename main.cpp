#include <iostream>
#include "Pokemon.h"
using namespace std;

int main() {
    Pokemon pokemon1 = Pokemon("YODAMAN", POKEMON_TYPE::WATER, 50);
    Pokemon pokemon2 = Pokemon("PIKACHU", POKEMON_TYPE::FIRE, 20);
    Attack a ("HYDRO FLURRY", "Shoots an abundance of water pellets at the opponent", 50);
    pokemon1.RegisterAttack(a);
    pokemon1.ExecuteAttack(pokemon2, "Hydro Flurry");
    return 0;
}
