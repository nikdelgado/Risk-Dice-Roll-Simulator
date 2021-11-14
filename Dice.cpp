//
//  Dice.cpp
//  Risk Dice Roller
//
//  Created by Nik Delgado on 7/31/21.
//
#include <iostream>
#include <random>
#include <limits>
#include "Dice.hpp"

using namespace std;
static random_device rd;
static mt19937 gen(rd());

//class constructor
dice::dice() {
}

//This function generates a random number from 1-6.
int dice::diceRoll() {
    uniform_int_distribution<> dis(1,6);
    int num = dis(gen);
    return num;
}

//This function sets the whole dice simulation up. And continues the simulation rounds if the user choses to do so.
void dice::simulationSetup() {
    attackerInput();
    defenderInput();
    simulateRound();
    
    int input = 1;
    
    while (input == 1) {
        if (defenderWin == true || attackerWin == true) {
            return;
        }
        
        cout << "\n\nWould you like to roll another round?" << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;
        cin >> input;
        
        //Exception handling for user input
        while (1) {
            try {
                if (cin.fail()) {
                    throw 0;
                } else {
                    break;
                }
            }
            catch (int error){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Would you like to roll another round?" << endl;
                cin >> input;
            }
        }
        
        simulateRound();
        
    }
    
    
}

//This function gets the input for the attacker army size and desired quantity of dice to use from user
void dice::attackerInput() {
    cout << "Enter the attacker army size: " << endl;
    cin >> attackerSize;
    
    
    //Attacker Army Size Exception Handling
    while (1) {
        try {
            if (cin.fail()) {
                throw 0;
            } else {
                break;
            }
        }
        catch (int error){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Enter the attacker army size: " << endl;
            cin >> attackerSize;
        }
    }

    cout << "Enter how many dice you would like to attack with (1-3):" << endl;
    cin >> attackerDice;
    
    //Attaker Dice Roll Exception Handling
    while (1) {
        try {
            if (cin.fail()) {
                throw 0;
            } else {
                break;
            }
        }
        catch (int error){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Enter how many dice you would like to attack with (1-3):" << endl;
            cin >> attackerDice;
        }
    }
    
    //Conditional Checker Logic
    
    if (attackerSize <= 3 && attackerDice == 3) {
        cout << "You do not have a large enough army." << endl;
        attackerDice = 0;
        attackerInput();
    }
    
    if(attackerSize <= 2 && attackerDice == 2) {
        cout << "You do not have a large enough army." << endl;
        attackerDice = 0;
        attackerInput();
    }
    
    if(attackerSize <= 1 && attackerDice == 1) {
        cout << "You do not have a large enough army." << endl;
        attackerDice = 0;
        attackerInput();
    }
    
}

//This function gets the input for the defender army size and desired quantity of dice to use from user
void dice::defenderInput() {
    cout << "Enter the defender army size: " << endl;
    cin >> defenderSize;
    
    //Defender Army Size Exception Handling
    while (1) {
        try {
            if (cin.fail()) {
                throw 0;
            } else {
                break;
            }
        }
        catch (int error){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Enter the defender army size: " << endl;
            cin >> defenderSize;
        }
    }
    
    cout << "Enter how many dice you would like to defend with (1-2):" << endl;
    cin >> defenderDice;
   
    
    //Defender Dice Input Exception Handling
    while (1) {
        try {
            if (cin.fail()) {
                throw 0;
            } else {
                break;
            }
        }
        catch (int error){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Enter how many dice you would like to defend with (1-3):" << endl;
            cin >> defenderDice;
        }
    }
    
    //Conditional Checker Logic
    if (defenderSize < 2 && defenderDice == 2) {
        cout << "You do not have a large enough army." << endl;
        defenderInput();
    }
    
    if (defenderDice != 1 && defenderDice != 2) {
        cout << "Incorrect input. Please enter the correct amount of dice" << endl;
        defenderInput();
    }
}

//This function rolls the attackers and defenders dice and determines who wins the round
void dice::simulateRound() {
    
    //Check Attacker Dice
    if (attackerDice < 1) {
        cout << "You no longer have enough units to attack" << endl;
        defenderWin = true;
        return;
    }
    
    //Check Defender Dice
    if (defenderDice < 1) {
        cout << "The attacker wins the battle" << endl;
        attackerWin = true;
        return;
    }
    
    //Generate Dice rolls for Attacker
    cout << "\nThe attacker rolls: " << endl;
    for (int i = 0; i < attackerDice; i++) {
        attackerHand[i] = diceRoll();
    }
    
    sort(attackerHand, attackerDice);
    
    for (int i = 0; i < attackerDice; i++) {
        cout << attackerHand[i] << endl;
    }
    
    //Generate Dice Rolls for Defender
    
    cout << "\nThe defender rolls: " << endl;
    for (int i = 0; i < defenderDice; i++) {
        defenderHand[i] = diceRoll();
    }
    
    sort(defenderHand, defenderDice);
    
    for (int i = 0; i < defenderDice; i++) {
        cout << defenderHand[i] << endl;
    }
    
    //Determine who wins
    int attackerLoss = 0;
    int defenderLoss = 0;
    
    for (int i = 0; i < defenderDice; i++) {
        if (defenderHand[i] >= attackerHand[i]) {
            attackerSize--;
            attackerLoss++;
        }
        else {
            defenderSize--;
            defenderLoss++;
        }
    }
    
    cout << "Results of the battle: " << endl;
    
    if (attackerLoss > 0) {
        cout << "The attackers lost " << attackerLoss << " unit(s)" << endl;
        cout << "Attacker army now has " << attackerSize << " unit(s)" << endl;
    }
    
    if (defenderLoss > 0) {
        cout << "The defenders lost " << defenderLoss << " unit(s)" << endl;
        cout << "Defender army now has " << defenderSize << " unit(s)" << endl;
    }
    
    // Adjust attackerDice and defenderDice if needed
    if (attackerSize <= 3) {
        attackerDice--;
    }
    if (attackerSize <= 2) {
        attackerDice--;
    }
    
    if (attackerSize <= 1) {
        attackerDice--;
        defenderWin = true;
        cout << "The defenders win." << endl;
    }
    
    if (defenderSize < 2) {
        defenderDice--;
    }
    
    if (defenderSize < 1) {
        defenderDice--;
        attackerWin = true;
        cout << "The attackers win." << endl;
    }
    
    
}

//This function is a simple bubble algorithim that sorts an array parameter
void dice::sort(int *arr, int n) {
    
    if (n == 1)
        return;
    
    for (int i = 0; i < n-1; i++) {
        if (arr[i] < arr[i+1]) {
            swap(arr[i], arr[i+1]);
        }
    }
    
    sort(arr, n - 1);
    
}



