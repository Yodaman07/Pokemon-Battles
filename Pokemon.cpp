//
// Created by Ayaan Irshad on 11/22/23.
//

#include "Pokemon.h"
#include <iostream>
#include <sstream>
#include <iomanip>
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

void Pokemon::ExecuteAttack(Pokemon &target, const string& attack_name) {
    stringstream stream1;
    float e_constant = EffectivenessConstant(target.TYPE);
    stream1 << fixed << setprecision(1) << e_constant;
    string constant_string = stream1.str();

    //https://stackoverflow.com/questions/29200635/convert-float-to-string-with-precision-number-of-decimal-digits-specified
    Attack *attack = nullptr;
    for (int i = 0; i < 3; ++i) {
        if (lowerString(attacks[i]->NAME) == lowerString(attack_name)){
            attack = attacks[i];
            break;
        }
    }

    stringstream stream2;
    float damage = attack->DAMAGE * e_constant;
    stream2 << fixed << setprecision(1) << damage;
    string damage_string = stream2.str();


    cout << this->NAME + " Used " + attack->NAME + " on " + target.NAME << endl;
    cout << "It did " + damage_string  + " Damage (x" + constant_string + ")" << endl;
    cout << "It was " + EffectivenessText(e_constant) << endl;
    cout << "" << endl;

    target.TakeDamage(damage);
}

void Pokemon::TakeDamage(float damage) {
    this->HEALTH -= damage;
    if (this->HEALTH <= 0){
        cout << this->NAME + " has been defeated" << endl;
    }
}

string Pokemon::AttackDialogue(Pokemon target){
    cout << target.NAME + "|" + to_string(target.HEALTH) + "hp" << endl;

    for (int i = 0; i < 3; ++i) {
        cout << to_string(i+1) + ". ";
        cout << attacks[i]->NAME;
        cout << "(" + to_string(attacks[i]->DAMAGE) + " dmg)" << endl;
    }
    int result;
    cin >> result;
    return attacks[result-1]->NAME;
}

float Pokemon::EffectivenessConstant(const POKEMON_TYPE &target) {
    POKEMON_TYPE playerType = this->TYPE;
    float effectiveness = 1.0;
    vector<float> effectivenessChart; // 6 long because there are 6 types
    switch (playerType) {
        //Pokemon info from: https://pokemondb.net/type (calculating from the attacking perspective)
        case POKEMON_TYPE::WATER: //order is: water, fire, electric, ground, ice, normal, fairy
            effectivenessChart = {0.5f, 2.0, 1.0, 2.0, 1.0, 1.0};
            break;
        case POKEMON_TYPE::FIRE:
            effectivenessChart = {0.5f, 0.5f, 1.0, 1.0, 2.0, 1.0, 1.0};
            break;
        case POKEMON_TYPE::ElECTRIC:
            effectivenessChart = {2.0, 1.0, 0.5f, 0.0, 1.0, 1.0, 1.0};
            break;
        case POKEMON_TYPE::GROUND:
            effectivenessChart = {1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0};
            break;
        case POKEMON_TYPE::ICE:
            effectivenessChart = {0.5f, 0.5f, 1.0, 2.0, 0.5, 1.0, 1.0};
            break;
        case POKEMON_TYPE::NORMAL:
            effectivenessChart = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
            break;
        case POKEMON_TYPE::FAIRY:
            effectivenessChart = {1.0, 0.5f, 1.0, 1.0, 1.0, 1.0, 1.0};
            break;
    }
    //https://stackoverflow.com/questions/16747591/how-to-get-an-element-at-specified-index-from-c-list
    effectiveness = effectivenessChart[int(target)];
    return effectiveness;
}

string Pokemon::EffectivenessText(const float &effectivenessConstant){
    string text = "";
    if (effectivenessConstant == 1.0){
        text = "Normal";
    }else if(effectivenessConstant == 2.0){
        text = "Very Effective";
    } else if (effectivenessConstant == 0.5f){
        text = "Weak";
    }else{
        text = "Negated";
    }
    return text;
}