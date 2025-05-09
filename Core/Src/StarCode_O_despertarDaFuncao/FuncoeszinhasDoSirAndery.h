#ifndef _ANDERY_FUNCTIONS_H
#define _ANDERY_FUNCTIONS_H

#include <stdlib.h>
#include "Funcoes.h"

void IniciarJogo(char diff);
void MainGameLoop(size_t size, char field[size][size][3]);
void GerarParesAleatorios(char fieldSize, char cardField[fieldSize][fieldSize][3]);
void NavegarCursor(signed char directionX, signed char directionY, size_t size);
void SelecionarCarta(size_t size, char field[size][size][3]);
void CompararPares(size_t size, char field[size][size][3]);
char VerificarFimDeJogo(char size, char cardField[size][size][3]);
void AtualizarTentativas(void);
void AtualizarRecorde(void);
void ExibirFimDeJogo(void);



#endif
