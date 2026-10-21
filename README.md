# Mini Compilador Robô

Mini compilador em C++ para uma linguagem de comandos de um robô. Faz análise léxica, análise sintática (descendente recursiva) e análise semântica com tabela de símbolos.

Projeto da atividade de Compiladores (Aula 06).

## O que ele faz

O programa lê uma linha de código-fonte e passa por três etapas:

1. **Análise léxica:** divide o texto em tokens e mostra a lista completa.
2. **Análise sintática:** confere se a sequência de tokens segue a gramática da linguagem.
3. **Análise semântica:** confere o uso das variáveis (declaração, tipos e duplicidade) usando uma tabela de símbolos, mostrada no final.

Quando encontra um erro, o programa informa o tipo (léxico, sintático ou semântico) e o que esperava encontrar.

## A linguagem

Um programa começa com `inicio`, tem as declarações de variáveis, depois os comandos, e termina com `fim`. Todo comando e toda declaração termina com `;`.

### Tipos de variável

| Tipo      | Valores aceitos      |
|-----------|----------------------|
| `numero`  | inteiros (ex.: `5`)  |
| `direcao` | `direita`, `esquerda`|

### Comandos

| Comando             | Argumento                                    |
|---------------------|----------------------------------------------|
| `andar`             | número ou variável do tipo `numero`          |
| `esperar`           | número ou variável do tipo `numero`          |
| `desviar`           | número ou variável do tipo `numero`          |
| `virar`             | `direita`, `esquerda` ou variável `direcao`  |
| `parar`             | nenhum                                       |
| `variavel = valor`  | valor compatível com o tipo da variável      |

### Gramática

```
programa    -> inicio { declaracao } { comando } fim
declaracao  -> ( numero | direcao ) IDENTIFICADOR ;
comando     -> IDENTIFICADOR = valor ;
             | andar ( NUMERO | IDENTIFICADOR ) ;
             | esperar ( NUMERO | IDENTIFICADOR ) ;
             | desviar ( NUMERO | IDENTIFICADOR ) ;
             | virar ( direita | esquerda | IDENTIFICADOR ) ;
             | parar ;
```

### Exemplo

```
inicio numero x; direcao d; x = 5; d = direita; andar x; esperar 2; desviar 3; virar d; parar; fim
```

Saída (resumo):

```
ANALISE LEXICA: OK
ANALISE SINTATICA: OK
Analise Semantica: ok

Tabela de Simbolos
Nome           Tipo           Valor
d              direcao        direita
x              numero         5

PROGRAMA ACEITO!
```

## Tokens

`INICIO`, `FIM`, `ANDAR`, `VIRAR`, `DIREITA`, `ESQUERDA`, `ESPERAR`, `PARAR`, `DESVIAR`, `TIPO_NUMERO`, `TIPO_DIRECAO`, `IDENTIFICADOR`, `NUMERO`, `IGUAL`, `PONTO_VIRGULA` (e `INVALIDO` para uso interno).

## Erros detectados

| Tipo      | Exemplo                                  | Mensagem                                          |
|-----------|------------------------------------------|---------------------------------------------------|
| Léxico    | `inicio andar 5 @ fim`                   | Simbolo nao reconhecido                           |
| Sintático | `inicio andar 5 fim` (falta `;`)         | Esperado: PONTO_VIRGULA                           |
| Sintático | `inicio esperar; fim`                    | Esperado: NUMERO ou IDENTIFICADOR                 |
| Semântico | `numero x; numero x;`                    | Identificador 'x' ja declarado                    |
| Semântico | `y = 3;` sem declarar                    | Identificador 'y' nao declarado                   |
| Semântico | `numero x; x = direita;`                 | A variavel 'x' espera um valor numerico           |
| Semântico | `direcao d; andar d;`                    | 'andar' espera uma variavel do tipo numero        |

## Estrutura do projeto

```
aula6robo/
├── aula6.cpp        # main: lê a entrada, mostra tokens e resultado
├── lexer.h / .cpp   # análise léxica (tokens)
├── parser.h / .cpp  # análise sintática e semântica
├── symtable.h / .cpp# tabela de símbolos (nome, tipo, valor)
└── CMakeLists.txt
```

## Como compilar e executar

Requisitos: g++ com suporte a C++17.

Dentro da pasta do projeto (onde estão os `.cpp`):

```
g++ -std=c++17 aula6.cpp lexer.cpp parser.cpp symtable.cpp -o aula6
```

Executar:

```
.\aula6.exe        # Windows (PowerShell)
./aula6            # Linux / macOS
```

Com CMake:

```
cmake -S . -B build
cmake --build build
```

Digite o programa inteiro em **uma única linha** e aperte Enter.

## Limitações

- A entrada é lida com um único `getline`, então o programa precisa estar em uma linha.
- Identificadores aceitam apenas letras (sem números ou `_`).
- As declarações devem vir antes de todos os comandos.
- Usar uma variável que ainda não recebeu valor é aceito (ela aparece com `-` na tabela).
- Não há geração de código nem execução: o programa só valida o código.

## Autoria

Preencha com nome(s), curso e instituição.
