#include<unistd.h>
#include "Pokemon.h"
using namespace std;

int main() {
    unsigned int microsecond = 1000000;

    Pokemon pokemon1 = Pokemon("YODAMAN", POKEMON_TYPE::WATER, 50);
    Pokemon pokemon2 = Pokemon("PIKACHU", POKEMON_TYPE::FIRE, 200);
    Attack flurry ("HYDRO FLURRY", "Shoots an abundance of water pellets at the opponent", 50);
    Attack tsunami ("Tsunami", "Generates a giant tsunami towards your opponent ", 100);
    Attack splash ("Splash", "Splashes your opponent with cold water ", 30);
    pokemon1.RegisterAttack(flurry);
    pokemon1.RegisterAttack(tsunami);
    pokemon1.RegisterAttack(splash);

    //Sleep is unix only
    //https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program
    while (pokemon2.HEALTH > 0){
        pokemon1.ExecuteAttack(pokemon2, pokemon1.AttackDialogue(pokemon2));
        usleep(int(0.5 * microsecond));
    }

    return 0;
}
