//
//  Dice.hpp
//  Risk Dice Roller
//
//  Created by Nik Delgado on 7/31/21.
//

#ifndef Dice_hpp
#define Dice_hpp

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

class dice {
public:
    dice();
    int diceRoll();
    void simulationSetup();
    void attackerInput();
    void defenderInput();
    void simulateRound();
    void sort(int *arr, int n);
    
private:
    int attackerSize;
    int attackerDice;
    int defenderSize;
    int defenderDice;
    int attackerHand[3];
    int defenderHand[2];
    bool defenderWin = false;
    bool attackerWin = false;
};

#endif /* Dice_hpp */
