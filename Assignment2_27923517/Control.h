#ifndef CONTROL_H
#define CONTROL_H

#include <iostream>
#include "GameRules.h"

GameRules GameInit(void);
void HumanTurn(int playerIndex);
void AITurn(int playerIndex);

#endif
