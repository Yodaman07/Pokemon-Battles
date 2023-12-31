//
// Created by Ayaan Irshad on 11/22/23.
//

#ifndef POKEMON_BATTLES_POKEMON_H
#define POKEMON_BATTLES_POKEMON_H

#include <iostream>
using namespace std;

enum class POKEMON_TYPE{
    WATER,
    FIRE,
    ElECTRIC,
    GROUND,
    ICE,
    NORMAL,
    FAIRY
};

class Attack{
public:
    string NAME;
    string DESCRIPTION;
    int DAMAGE;
    Attack(string name, string description, int damage);
};

class Pokemon {
    public:
        string NAME;
        POKEMON_TYPE TYPE;
        int HEALTH;
        Attack *attacks[3] = {nullptr, nullptr, nullptr};
        Pokemon(string name, POKEMON_TYPE type, int health);

    void RegisterAttack(Attack a);

    void ExecuteAttack(Pokemon& target, const string& attack_name);
    string AttackDialogue(Pokemon target);
    void TakeDamage(float damage);

    float EffectivenessConstant(const POKEMON_TYPE &target);
    static string EffectivenessText(const float &effectivenessConstant);
};


#endif //POKEMON_BATTLES_POKEMON_H
