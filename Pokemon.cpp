//
// Created by Ayaan Irshad on 11/22/23.
//

#include "Pokemon.h"
#include <iostream>
#include <list>
using namespace std;

string lowerString(string str){
    string final;
    for (int i = 0; i < str.length(); ++i) {
        //https://stackoverflow.com/questions/30182731/tolower-is-returning-a-number-instead-of-a-the-lowercase-form
        final+= tolower(str.at(i), locale());
    }
    return final;
}

Attack::Attack(string name, string description, int damage) {
    NAME = name;
    DESCRIPTION = description;
    DAMAGE = damage;
}

Pokemon::Pokemon(string name, POKEMON_TYPE type, int health) {
    NAME = name;
    TYPE = type;
    HEALTH = health;
}

void Pokemon::RegisterAttack(Attack a) {
    for (int i = 0; i < 3; ++i) {
        if (attacks[i] == nullptr){
            attacks[i] = &a;
            break;
        }
    }
}

void Pokemon::ExecuteAttack(Pokemon target, const string& attack_name) {
    cout << Effectiveness(target.TYPE) << endl;
    Attack *attack = nullptr;
    for (int i = 0; i < 3; ++i) {
        if (lowerString(attacks[i]->NAME) == lowerString(attack_name)){
            attack = attacks[i];
            break;
        }
    }

    cout << this->NAME + " Used " + attack->NAME + " on " + target.NAME << endl;
    cout << "It did " + to_string(attack->DAMAGE)  + " Damage" << endl;
    cout << "It was [EFFECTIVE LEVEL]" << endl;
}

float Pokemon::Effectiveness(const POKEMON_TYPE &target) {
    POKEMON_TYPE playerType = this->TYPE;
    float effectiveness = 1.0;
    vector<float> effectivenessChart; // 6 long because there are 6 types
    switch (playerType) {
        //Pokemon info from: https://pokemondb.net/type (calculating from the attacking perspective)
        case POKEMON_TYPE::WATER: //order is: water, fire, electric, ground, ice, normal
            effectivenessChart = {0.5f, 2.0, 1.0, 2.0, 1.0, 1.0};
            break;
        case POKEMON_TYPE::FIRE:
            effectivenessChart = {0.5f, 0.5f, 1.0, 1.0, 2.0, 1.0};
            break;
        case POKEMON_TYPE::ElECTRIC:
            effectivenessChart = {2.0, 1.0, 0.5f, 0.0, 1.0, 1.0};
            break;
        case POKEMON_TYPE::GROUND:
            effectivenessChart = {1.0, 2.0, 2.0, 1.0, 1.0, 1.0};
            break;
        case POKEMON_TYPE::ICE:
            effectivenessChart = {0.5f, 0.5f, 1.0, 2.0, 0.5, 1.0};
            break;
        case POKEMON_TYPE::NORMAL:
            effectivenessChart = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
            break;
    }
    //https://stackoverflow.com/questions/16747591/how-to-get-an-element-at-specified-index-from-c-list
    effectiveness = effectivenessChart[int(target)];
    return effectiveness;
}
