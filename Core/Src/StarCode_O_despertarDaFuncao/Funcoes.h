#ifndef PRIV_FUNCTIONS_H
#define PRIV_FUNCTIONS_H

#include "../ST7789/st7789.h"
#include "stdio.h"
#include "stdbool.h"

// Define
#define SIZE4X4 0
#define SIZE6X6 1

#define SINGLEPLAYER 0
#define MULTIPLAYER 1

#define PRESSED 0
#define NOTPRESSED 1

// Macro
#define AlignText(x, w, len) ((ST7789_WIDTH/2) - ((len*w)/2))
#define CalcSize(i) (4+i*2)
#define CalcPossibilities(Size) (Size*Size/2)


// Functions
// Button Detection
void AwaitForAnyButton(void);
void ReadButtons(char *out);
void DetectAnyButtonPress(char *out);
void DetectButtonPress(char buttons[], char *out, size_t amount);

// Screens
void Menu(int record);

void PrintSelectDifficulty(char selection);
char SelectDifficulty(void);

void PrintSelectMode(char selection);
char SelectMode(void);

void PrintGameScreen(char CardField);

// Testes
void TestPrint(size_t fieldSize, char field[fieldSize][fieldSize][2]);

// Other/Util
char Contains(size_t size, char Iterable[size], char Contains);
char ContainsVector2(size_t size, char Iterable[size][size][2], char Contains);


// Pokemon
char mander(void);
char meleon(void);
char izard(void);
char cadet(void);
int elion(void);
float zel(void);

// que(rosene)
int ernet(void);
bool AAAAAAAA(void);

#endif
