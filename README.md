# Projeto integrado Sistemas Embarcados/Linguagem de programação - 1º Trimestre

## Descrição Geral
Um jogo da memória eletrônico, implementado no microcontrolador STM32, utilizando o
display e botoeiras da placa. O jogo consiste em virar pares de cartas em um tabuleiro e tentar
encontrar combinações idênticas. Quando o jogador encontra duas cartas iguais, elas permanecem
viradas. Caso erre, elas voltam à posição oculta. O jogo termina quando todos os pares forem
encontrados.

## Escopo de jogabilidade
- O tabuleiro deve conter uma grade de 4x4 posições (ou outra dimensão viável com número par de
casas), onde cada posição representa uma “carta” oculta.
1
- O jogador deve navegar entre as posições utilizando as botoeiras da placa: cima, baixo, esquerda e
direita.
- A seleção da carta (ação de virar) será feita por um botão separado (Ex: botão “OK”).
- Ao selecionar duas cartas, o sistema deve compará-las:
  - Se forem iguais, permanecem viradas e inativas.
  - Se forem diferentes, devem ser ocultadas novamente após um breve intervalo.
- O jogo termina quando todos os pares forem encontrados.
- Deve haver uma tela inicial (menu) com as seguintes informações:
  - Botão “Iniciar Jogo”
  - Contador de recorde (menor número de tentativas até então)
- O tempo ou número de tentativas deve ser acumulado e mostrado ao final da partida.
- O recorde deve ser armazenado enquanto a energia da placa estiver mantida (sem reinicializar o
microcontrolador).
- Utilize cores ou símbolos para diferenciar os pares.

### DESAFIOS EXTRAS (Valem pontos bônus):
- Tela de vitória animada, com efeitos visuais e parabenização.
(Concluido)
- Múltiplos níveis de dificuldade (por ex: 4x4, 6x6). (Concluido)
- Modo de dois jogadores, com pontuação separada. (Concluido)
