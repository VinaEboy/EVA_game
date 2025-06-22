# Trabalho de Programação 2: EVA
# Jogo do gênero Run'n Gun

**Autor:** Vinícius Gregorio Fucci  
**GRR20241272**

Este projeto implementa um jogo com física, plataformas e mecânica de atirar, parecido com Metal Slug e fortemente inspirado na saga Megaman e Megaman X, na linguagem C usando a biblioteca Allegro.

O nome do jogo é Evangelion Versus Angels: EVA. A temática do jogo é inspirado no anime Neon Genesis Evangelion, que conta a história de colegiais que lutam contra entidades desconhecidas (chamadas de Anjos) em um mecha robótico (chamada de EVAs).

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

[10 - 11 pontos] Tela de seleção de fase análoga a do
Megaman (ou seja, implementar sistema de fases não
lineares e menu de seleção para escolher as mesmas – pelo
menos uma ramificação)

## Sessão: Erros conhecidos

- Se o jogador estiver no meio da fase e trocar a dificuldade, a dificuldade só será realmente trocada quando ele morrer e renascer ou quando ele sair da fase. Isso acontece porque os inimigos tem seus parâmetros criados ao inicializar a fase então trocar no meio não vai reinicializar os inimigos. Uma opção seria forçar o player a renascer para trocar a dificuldade.

- Não é um erro, mas é uma falta de implementação. Para deletar um slot de jogo salvo é necessário deletar o arquivo na pasta ou sobrescrevê-lo com outro save.