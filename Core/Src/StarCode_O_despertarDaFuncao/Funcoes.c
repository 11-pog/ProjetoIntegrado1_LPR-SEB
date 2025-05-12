#include "Funcoes.h"

void Menu(void) {
	ST7789_WriteString(90, 60, "MENU", Font_16x26, WHITE, BLACK);
	ST7789_WriteString(60, 120, "New Game", Font_11x18, WHITE, BLACK);

	char result[12];
	sprintf(result, "Record: %i", GameRecord);
	ST7789_WriteString(60, 140, result, Font_11x18, WHITE, BLACK);

	ST7789_WriteString(36, 180, "Pressione qualquer botao", Font_7x10, WHITE,
	BLACK);
	ST7789_WriteString(82, 190, "Pra comecar", Font_7x10, WHITE, BLACK);

	AwaitForAnyButton();
}

void PrintSelectDifficulty(char selection) {
	ST7789_WriteString(20, 30, "Selecione uma\ndificuldade:", Font_11x18, WHITE,
	BLACK);

	switch (selection) {
	case 0:
		ST7789_WriteString(10, 120, "- 4x4", Font_11x18, YELLOW, BLACK);
		ST7789_WriteString(10, 140, "- 6x6", Font_11x18, WHITE, BLACK);
		break;
	case 1:
		ST7789_WriteString(10, 120, "- 4x4", Font_11x18, WHITE, BLACK);
		ST7789_WriteString(10, 140, "- 6x6", Font_11x18, YELLOW, BLACK);
		break;
	default:
		break;
	}
}

char SelectDifficulty(void) {
	ST7789_Fill_Color(BLACK);
	PrintSelectDifficulty(0);

	char btns[3];
	const char UsingBtns[3] = { 10, 11, 12 };

	char selection = SIZE4X4;

	do {
		DetectButtonPress((char*) UsingBtns, btns, 3);

		if (btns[0] == 0 || btns[2] == 0) {
			selection++;
			selection %= 2;
		}

		PrintSelectDifficulty(selection);
	} while (btns[1] != PRESSED);

	return selection;
}

void PrintSelectMode(char selection) {
	ST7789_WriteString(20, 30, "Modo de Jogo: ", Font_11x18, WHITE, BLACK);
	switch (selection) {
	case 0:
		ST7789_WriteString(10, 120, "Singleplayer", Font_11x18, YELLOW, BLACK);
		ST7789_WriteString(10, 140, "Multiplayer", Font_11x18, WHITE, BLACK);
		break;
	case 1:
		ST7789_WriteString(10, 120, "Singleplayer", Font_11x18, WHITE, BLACK);
		ST7789_WriteString(10, 140, "Multiplayer", Font_11x18, YELLOW, BLACK);
		break;
	default:
		break;
	}
}

char SelectMode(void) {
	ST7789_Fill_Color(BLACK); //limpa a tela
	PrintSelectMode(0); //mostra a opção inicialmente com single player selecionado
	char btns[3]; //armazena o estado dos botões
	const char UsingBtns[3] = { 10, 11, 12 }; //botões usados

	char selection = SINGLEPLAYER; //Começa com single player selecionado

	do {
		DetectButtonPress((char*) UsingBtns, btns, 3); // espera a entrada de um jogador 

		if (btns[0] == 0 || btns[2] == 0) { //verifica se o botão da esquerda ou direita foi pressionado
			selection++;
			selection %= 2; //altera entre 0 e 1
		}

		PrintSelectMode(selection); //atualiza a tela 
	} while (btns[1] != PRESSED); //sai do loop quando o botão for pressionado

	return selection;
}

void PrintGameScreen(size_t size, char cardField[size][size][3]) { //desenha todas as cartas na tela 
	const char cardGapY = CalcCardGap(size, CARD_HEIGHT); //calcula espaço na vertical entre as cartas
	const char cardGapX = CalcCardGap(size, CARD_WIDTH); //calcula espaço na horizontal entre as cartas

	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			if (UpdateCardImage(x, y, cardField[y][x]) == 1) { // verifica se a carta precisa ser redesehada
				PrintCard(x, y, cardGapX, cardGapY, size, cardField[y][x]); //desenha a carta
				cardField[y][x][GRAPHIC_UPDATE_STATUS] = STANDBY; //não precisa atualizar
			}
		}
	}

	LastSelectedX = SelectedX; //atualiza a seleção de carta selecionada anteriormente
	LastSelectedY = SelectedY;
}

char UpdateCardImage(uint8_t x, uint8_t y, char card[3]) { //verifica se a imagem da carta precisa ser atualizada
	if ((SelectedX == x && SelectedY == y)
			|| (LastSelectedX == x && LastSelectedY == y))
		return 1; //atualiza se for a carta atual ou anterior

	if (IsUnpaired(card) == 1)
		return 1; //atualiza se a carta não foi pareda

	if (card[GRAPHIC_UPDATE_STATUS] == UPDATE)
		return 1; //atualiza status grafico 

	return 0; //não atualiza status grafico
}

void PrintCard(uint8_t cardX, uint8_t cardY, uint8_t GapX, uint8_t GapY, size_t size, char card[3]) {
	const uint8_t x = CalcCardPos(GapX, CARD_WIDTH, cardX); //calcula a posição x da carta
	const uint8_t y = CalcCardPos(GapY, CARD_HEIGHT, cardY); //calcula a posição y da carta

	switch (card[REVEAL_ATTR]) {
	case UNREVEALED: //carta virada
		if (cardX == SelectedX && cardY == SelectedY)
			ST7789_DrawImage(x, y, CARD_WIDTH, CARD_HEIGHT, //imagem de seleção
					(uint16_t*) SelectedCard);
		else
			ST7789_DrawImage(x, y, CARD_WIDTH, CARD_HEIGHT, //imagem do verso
					(uint16_t*) CardBackemon);
		break;

	case REVEALED: //carta revelada temporariamnete
	case PAIRED: //carta revelada permantente
		DrawRevealedCard(x, y, cardX, cardY, card[NUMBER_ATTR], WHITE); //fundo branco
		break;

	case RED_PAIR:
		DrawRevealedCard(x, y, cardX, cardY, card[NUMBER_ATTR], RED); //fundo vermelho
		break;

	case BLUE_PAIR:
		DrawRevealedCard(x, y, cardX, cardY, card[NUMBER_ATTR], BLUE); //fundo azul
		break;
	}
}

//desenha uma carta revelada com seu numero 
void DrawRevealedCard(uint8_t x, uint8_t y, uint8_t cardX, uint8_t cardY, char cardValue, uint16_t bgColor)
{
	if (cardX == SelectedX && cardY == SelectedY) 
		ST7789_DrawFilledRectangle(x, y, CARD_WIDTH - 1, CARD_HEIGHT - 1, //destaque para carta selecionada
		YELLOW);
	else
		ST7789_DrawFilledRectangle(x, y, CARD_WIDTH - 1, CARD_HEIGHT - 1, // fundo com a cor atual
		bgColor);

	char NumString[2]; //string para exibir o numero da carta
	sprintf(NumString, "%i", cardValue); //converte o valor para string

	ST7789_WriteString(x, y + 5, NumString, Font_11x18, BLACK, WHITE); //escreve o numero na tela
}

void ReadButtons(char *out) { // le os estados do pino e armazena num array
	out[0] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9);
	out[1] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10);
	out[2] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11);
	out[3] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12);
}

void AwaitForAnyButton(void) {
	char buttons[4]; //armazena os estados do botão

	do {
		ReadButtons(buttons); //lê os estados do botão
	} while (!Contains(4, buttons, PRESSED)); //continua lenda até que um botão seja pressionado
}

void DetectAnyButtonPress(char *out) {
	const unsigned int MultiButtonCaptureWindowMs = 200; // detecta multiplos botões pressionados
	char buttons[4]; //armazena estado atual dos botões

	for (int i = 0; i < 4; ++i) //inicializa todos os botões como não pressionados
		out[i] = UNPRESSED;

	do { //aguarda até que um botão seja pressionado
		ReadButtons(buttons);
	} while (!Contains(4, buttons, PRESSED));

	long btnPressTime = HAL_GetTick();  //armazena o tempo de inicio da detecção
	//registra os botões pressionados
	do {
		for (int i = 0; i < 4; ++i)
			if (out[i] == UNPRESSED)
				out[i] = buttons[i];

		ReadButtons(buttons);
	} while (HAL_GetTick() - btnPressTime < MultiButtonCaptureWindowMs); //atualiza a leitura dos botão
}

void DetectButtonPress(char buttons[], char *out, size_t amount) {
	char btnValues[4]; //armazena os valores de 4 botão
	char end = 0; //termina a detecção
	do {
		DetectAnyButtonPress(btnValues); // detecta qualquer botão pressionado

		uint8_t outIndex = 0; //escrita no vetor de saida
		for (uint8_t i = 0; i < 4; i++) {
			if (Contains(amount, buttons, i + 9)) { //verifica se um botão foi pressionado
				if (btnValues[i] == PRESSED)
					end = 1; //se o botão for pressionado, termina
				out[outIndex] = btnValues[i]; //salva o valor do botão num vetor de saida
				outIndex++;
			}
		}
	} while (end == 0); //repete até que um botão seja pressionado
}

void InitFieldMatrix(size_t size, char matrix[size][size][3]) {
	//inicializa cada carta na matriz
	for (int y = 0; y < size; y++) // Percorre sobre toda linha na matriz
		for (int x = 0; x < size; x++) { // Percorre sobre toda coluna na matriz
			matrix[y][x][NUMBER_ATTR] = 0; // Inicializa o numero da carta como 0 (não atribuido)
			matrix[y][x][REVEAL_ATTR] = UNREVEALED; // Inicializa a carta como Não Revelado
			matrix[y][x][GRAPHIC_UPDATE_STATUS] = UPDATE; //marca para atualizar o grafico da carta
		};
}

void Pair(size_t size, char field[size][size][3], uint8_t x, uint8_t y) {
	if (GameMode == MULTIPLAYER) { //se o modo de jogo for multiplayer
		if (PlayerTurn == BLUE_TURN) { //vez do jogador azul
			field[SelectedY][SelectedX][REVEAL_ATTR] = BLUE_PAIR; //marca a carta selecionada como par azul
			field[y][x][REVEAL_ATTR] = BLUE_PAIR; //marca a outra carta como azul
			BlueScore++; //incrementa pontuação no jogador azul
		} else {
			field[SelectedY][SelectedX][REVEAL_ATTR] = RED_PAIR; //marca como carta selecionada como paz vermelho
			field[y][x][REVEAL_ATTR] = RED_PAIR; //merca outra carta como vermelho
			RedScore++; //incrementa pontuação para o jogador vermelho
		}
	} else { // se for singleplayer
		field[SelectedY][SelectedX][REVEAL_ATTR] = PAIRED; //ambas as cartas como par encontrado
		field[y][x][REVEAL_ATTR] = PAIRED;
	}

	field[SelectedY][SelectedX][GRAPHIC_UPDATE_STATUS] = UPDATE; // marca as duas cartas para atualização grafica
	field[y][x][GRAPHIC_UPDATE_STATUS] = UPDATE;
}

void SwitchTurn(void) {
	PlayerTurn++; //avança para o proximo jogador
	PlayerTurn %= 2; //altera entre os 2 jogadores

	ShowTurn(); 
}

void ShowTurn(void) {
	if (PlayerTurn == BLUE_TURN) {
		ST7789_DrawFilledRectangle(0, 0, 5, 240, BLUE); //mostra faixa azul na esquerda
		ST7789_DrawFilledRectangle(235, 0, 5, 240, BLACK); //apaga a faixa da direita
	} else {
		ST7789_DrawFilledRectangle(0, 0, 5, 240, BLACK); //apaga a faixa da esquerda
		ST7789_DrawFilledRectangle(235, 0, 5, 240, RED); //mostra faixa vermelha na direita
	}
}

void TestPrint(size_t fieldSize, char field[fieldSize][fieldSize][3]) {
	for (int y = 0; y < fieldSize; y++) //percorre linhas 
		for (int x = 0; x < fieldSize; x++) { //percorre colunas
			char ToWrite[2]; //string do numero da carta
			sprintf(ToWrite, "%i", field[y][x][NUMBER_ATTR]); //converte o numero da carta para string

			ST7789_WriteString(x * 36, y * 36, ToWrite, Font_11x18, WHITE, //escreve numero na tela
			BLACK);
		};
}


char IsUnpaired(char card[3])
{
	if (card[REVEAL_ATTR] == UNREVEALED // verifica se a carta esta revalada ou virada mas sem par
			|| card[REVEAL_ATTR] == REVEALED)
		return 1; //sem par
	return 0; // tem par
}

char Contains(size_t size, char Iterable[size], char Contains) {
	int recurrence = 0; // contador de ocorrencias

	for (int i = 0; i < size; i++) {
		if (Iterable[i] == Contains) { //valor atual é igual ao valor procurado
			recurrence++; //incrementa ao contador
		}
	}
	return recurrence; // retorna a quantidade de vezes que foi encontrada
}

char ContainsVector2(size_t size, char Iterable[size][size][3], char Contains,
		uint8_t attr) {
	int recurrence = 0; // contador de ocorencias

	for (uint8_t y = 0; y < size; y++) { // itera pelas linhas
		for (uint8_t x = 0; x < size; x++) { // itera pelas colunas
			if (Iterable[y][x][attr] == Contains) { // verifica o atributo da carta
				recurrence++; // incrementa se for igual ao valor procurado
			}
		}
	}
	return recurrence; //retorna ao total de incremencias
}
