#ifndef ANDERYFUNCOES_H
#define ANDERYFUNCOES_H

#include "stdlib.h"
#include "Funcoes.h"

void IniciarJogo(void);
void GerarParesAleatorios(char fieldSize, char cardField[fieldSize][fieldSize][2]);
void NavegarCursor(void);
void SelecionarCarta(void);
void CompararPares(void);
void VerificarFimDeJogo(void);
void AtualizarTentativas(void);
int AtualizarRecorde(void);
void ExibirFimDeJogo(void);

#endif
