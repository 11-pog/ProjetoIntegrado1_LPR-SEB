#ifndef _ANDERY_FUNCTIONS_H
#define _ANDERY_FUNCTIONS_H

#include <stdlib.h>
#include "Funcoes.h"

void IniciarJogo(char diff, char mode);
void MainGame(size_t size, char field[size][size][2]);
void GerarParesAleatorios(char fieldSize, char cardField[fieldSize][fieldSize][2]);
void NavegarCursor(signed char directionX, signed char directionY, size_t size);
void SelecionarCarta(size_t size, char field[size][size][2]);
void CompararPares(size_t size, char field[size][size][2]);
char VerificarFimDeJogo(char size, char cardField[size][size][2]);
void AtualizarTentativas(void);
void AtualizarRecorde(void);
void ExibirFimDeJogo(void);



#endif
