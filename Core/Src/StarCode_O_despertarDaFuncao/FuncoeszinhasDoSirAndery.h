#ifndef ANDERYFUNCOES_H
#define ANDERYFUNCOES_H

#include <stdlib.h>
#include "Funcoes.h"]

int record;

void IniciarJogo(char diff, char mode);
void GerarParesAleatorios(char fieldSize, char cardField[fieldSize][fieldSize][2]);
void NavegarCursor(void);
void SelecionarCarta(void);
void CompararPares(void);
void VerificarFimDeJogo(void);
void AtualizarTentativas(void);
void AtualizarRecorde(int amounts);
void ExibirFimDeJogo(void);

#endif
