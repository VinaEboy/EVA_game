# Trabalho de Programação 2: EVA
# Jogo do gênero Run'n Gun

**Autor:** Vinícius Gregorio Fucci  
**GRR20241272**

Para rodar o jogo é necessário ter a biblioteca Allegro e a linguagem C.
Na pasta em que está o makefile, use o comando "make" no terminal. Após isso, execute o programa fazendo:
./EVA
Caso queira limpar a pasta dos executáveis, faça "make clean"


Este projeto implementa um jogo com física, plataformas e mecânica de atirar, parecido com Metal Slug e fortemente inspirado na saga Megaman e Megaman X, na linguagem C usando a biblioteca Allegro.

O nome do jogo é Evangelion Versus Angels: EVA. A temática do jogo é inspirado no anime Neon Genesis Evangelion, que conta a história de colegiais que lutam contra entidades desconhecidas (chamadas de Anjos) em um mecha robótico (chamada de EVAs).

## Gameplay do Jogo

![ Gameplay do Jogo em gif](gameplay/gameplay.gif)

## Sessão: Funcionamento do Main

Além de carregar e inicializar variáveis do Allegro, a main é responsável por cuidar de qual etapa o jogo está rodando. O dado game_state nos informa em qual parte o jogador está: se é na tela principal, no menu de opções, em algum level...
E com base nisso o main, caso a parte do jogo não tenha sido inicializada, isso é, carregado as imagens necessárias e criado a struct com informações iniciais daquela parte, é inicializado e executado. A única execução mais complicada é as do levels, que é quando o jogador está interagindo mais, por isso é usado funções do joystick para captar os eventos contínuos e não contínuos, assim como atualizar a fase.
As etapas do jogo são divididas em inicializar a etapa e em mostrar no display aquela etapa.

## Sessão: Arquivos e diretórios da entrega

- `main.c` Função principal do programa
- `MAKEFILE` Script para gerar executável do programa
- `README.md`
- `/credits` Diretório dedicado aos créditos autorais de imagens utilizadas no projeto
- `/entities` Diretório com implementação do Player, dos inimigos (Jet Alones e Sachiel), e da mecânica de tiro (Buster é o "Pistol" e Bullet são as balas)
- `/fonts` Diretório que contém a fonte utilizada para escrever no jogo
- `/gameflow` Diretório que contém a implementação das etapas em que o jogo pode estar, como "Pause" ou "Game_over". Além disso, contém dois arquivos cabeçalhos de informação que é o Game_state.h (estado de jogo, como progresso do jogador, etapa do jogo e mapeamento de tecla) e Assets.h (Agrupamento de sprites necessários para o jogo)
- `/images` Diretório com imagens utilizadas no jogo, para sprites e telas de fundo
- `/mechanics` Diretório com implementação de algumas mecânicas do jogo, como o Joystick, a lógica de collisões (do jogador e inimigos com plataformas, balas...)
- `/save_data` Diretório destino dos arquivos de escrita para salvar o jogo e carregar o jogo
- `/sounds` Diretório com os sons utilizados no jogo

## Sessão: Estruturas de dados Gerais utilizadas

A principal estrutura utilizada para gerenciar o funcionamento do jogo é a struct game_state state. Ela é responsável por falar a etapa atual do jogo e por guardas informações personalizadas do jogo, como o progresso do jogo (Vidas, Chefes derrotados...) e mapeamento de teclas.

Outra estrutura utilizada é a de *_info, isto é, * é a etapa atual do jogo. Por exemplo, title_screen_info é a estrutura da etapa do menu inicial e contém informações como qual opção o jogador está selecionando. Para as partes do jogo que são de menu, esses arquivos são parecidos.

E para centralizar essas estruturas com informações da etapa, foi criado o Assets, que é inicializado na main como NULL e que é carregado a imagem no inicializar de cada etapa e descarregado quando sai da etapa. Além disso, o Assets guarda as imagens de sprites necessários para as fases.

## Sessão: Implementação das Fases

A estrutura de informação das fases é mais complexo, contendo o player, um vetor de ponteiros para inimigos, plataformas. A implementação da fase funciona com um update baseado nos eventos de tempo de Allegro que atualiza posições das entidades, e que faz verificações para spawnar inimigos. As fases também podem ter checkpoints. Toda vez que o jogador morre na fase, a fase é descarregada e carregada novamente com base no checkpoint que o jogador alcançou, e caso não tenha mais vida, é direcionado para a tela de Game Over.

As fases são criadas com base em um vetor escrito em código com informações das plataformas (posições, tamanhos), informações dos inimigos (posições, probabilidades de agachar, distancia que fica do player). 

## Sessão: Implementação do Draw

O arquivo Draw.c é um arquivo genérico que ajuda a desenhar as dinâmicas da fase. Então existem funções gerais para qualquer fase (como desenhar o player, desenhar o inimigo JA) e outras funções mais específicas (como desenhar o background da fase 1, porque tem um padrão diferente das outras fases). Também desenha barra de vida do jogador e do Boss final.

Implementação do Rolling Background: Na 1° Fase, tem 2 tipos de imagem no cenário: O background normal e o background do chefão. As 6 primeiras telas de fundo (com tamanho X_SCREEN, ou seja, com o tamanho do monitor da pessoa que estiver jogando) são a primeira imagem alternanto se está espelhado ou não. E a última é o cenário do chefão. Na hora de desenhar o cenário, ele desenha apenas o que está na tela (culling) e 

Desenho do tiro: O tiro pode ter ser para esquerda, direita e para cima. Quando é só para esquerda e direita, bastava a flag de inverter horizontalmente. Mas com a possibilidade de atirar para cima, foi necessário usar a função de desenho de rotação al_draw_tinted_scaled_rotated_bitmap_region() que usa o grau de rotação em radianos.

Mecanismo para piscar o player enquanto ele está carregando tiro: Para ter o feedback visual de que o player está carregando o tiro, foi feito uma "mistura" na tintura que se desenha o player. Uma pulsação com base no relógio do computador, junto da função seno (que oscila) do math.h, indica o quão forte vai ser o brilho do pulso com base no tempo.

## Sessão: Funcionalidades extras implementadas

Foram implementados as seguintes funcionalidades extras:
[1 – 10 pontos] Implementar, pelo menos, um ataque especial, com animações (sprites) dedicadas para o personagem principal. Foi implementado o tiro carregado, em que o jogador aperta o botão de atirar e segura, tendo 3 níveis de tiro carregado: Normal, carregado e super carregado.

[3 – 5 pontos] Implementar um botão de pausa para a
batalha.

[4 – 10 pontos] Implementar a função de “abaixar” e
“atirar abaixado”.

[6 – 20 pontos] Implementar um mecanismo de salvar e
carregar o jogo.

[8 - 10 pontos] Remapeamento livre de teclas de ação no
menu de opções.

[5 - 9 pontos] Dificuldade ajustável no menu de opções
(Fácil, Médio e Díficil).

[7 - 10 pontos] Trilha sonora na tela principal, seleção
de fase e na fase, com ajustador de volume no menu de
opções.

[10 - 11 pontos] Tela de seleção de fase análoga a do
Megaman (ou seja, implementar sistema de fases não
lineares e menu de seleção para escolher as mesmas – pelo
menos uma ramificação)

## Sessão: Erros e problemas conhecidos

- Em uma plataforma muito pequena de largura, não foi testado se o inimigo Jet Alone detecta a borda corretamente (a função de detectar borda verifica se ele está na borda esquerda, borda direita ou em nenhuma, nesse caso, como ele estaria nas duas bordas, fica ambíguo)

- A tela na hora de travar no chefão da fase 1 pode não travar se o jogador não avançar o suficiente (avançar 40% da tela horizontal)

- As fases 2 ... 8 são apenas demonstrações de que o jogo não é linear, mas elas não tem um conteúdo em si (não implementei por falta de tempo e criatividade)

- Quando você reinicia a fase, a música começa de volta do começo, o que pode ser meio irritante.

- Não é um erro, mas é uma falta de implementação. Para deletar um slot de jogo salvo é necessário deletar manualmente o arquivo na pasta ou sobrescrevê-lo com outro save.

- Não é um erro, mas se o jogador estiver no meio da fase e trocar a dificuldade ou o volume do jogo, só será trocado quando clicar em "APPLY" ou quando ele resetar a fase (seja morrendo ou saindo da fase). E quando ele APPLY ele reinicia a fase, com o mesmo tanto de vida, do último checkpoint. Ou seja, ele pode ficar "resetando" a fase infinitamente, o que pode ser considerado trapaça.