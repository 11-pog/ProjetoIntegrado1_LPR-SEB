#ifndef PRIV_FUNCTIONS_H
#define PRIV_FUNCTIONS_H

#include <stdio.h>
#include <stdbool.h>

#include "../ST7789/st7789.h"
#include "ImagensOfTheGame.h"

// Define
#define SIZE4X4 0
#define SIZE6X6 1

#define SINGLEPLAYER 0
#define MULTIPLAYER 1

#define PRESSED 0
#define NOTPRESSED 1

#define CARD_HEIGHT 30
#define CARD_WDTH 21

// Macro
#define AlignText(w, len) ((ST7789_WIDTH/2) - ((len*w)/2))
#define CalcSize(i) (4+i*2)
#define CalcPossibilities(Size) (Size*Size/2)

#define CalcCardGap(size, cardSize) ((ST7789_HEIGHT - size * cardSize) / (size * 2))
#define CalcCardPos(cardGap, cardSize, pos) (cardGap*(pos+1)*2 + (cardSize*pos) - cardGap)


typedef uint16_t ceru;
typedef uint8_t alu;
typedef uint64_t ex;

// Var
signed char SelectedX;
signed char SelectedY;

signed char LastSelectedX;
signed char LastSelectedY;

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

void PrintGameScreen(size_t size, char cardField[size][size][2]);
void DrawCard(char x, char y, int CardX, int CardY, size_t size, char field[size][size][2]);

// Testes
void TestPrint(size_t fieldSize, char field[fieldSize][fieldSize][2]);

// Other/Util
char Contains(size_t size, char Iterable[size], char Contains);
char ContainsVector2(size_t size, char Iterable[size][size][2], char Contains, char attr);

// Pokemon
char mander(void);
char meleon(void);
char izard(void);
char cadet(void);
ceru ledge(void);
int elion(void);
float zel(void);
alu card(void);
ex calibur(void);

// que(rosene)
int ernet(void);
bool AAAAAAAA(void);

#endif
