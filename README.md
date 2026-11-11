# Estoque de tomates — UTFPR

Trabalho de Algoritmos e Fundamentos de Programação em **C**, para executar no
console do Code::Blocks com compilador GCC.

O programa controla até **20 tipos de tomate**. Cada cadastro contém código
positivo e único, nome de até 49 caracteres, quantidade inteira de caixas e
preço em reais por caixa. Os dados ficam em memória e são perdidos ao encerrar.

## Abrir no Code::Blocks

1. Use uma instalação do Code::Blocks com GCC/MinGW configurado.
2. Acesse **File → New → Project → Console application** e selecione **C**.
3. Remova o `main.c` gerado da lista de arquivos do projeto.
4. Use **Project → Add files** para adicionar `estoque_tomates.c`.
5. Se necessário, em **Project → Build options → Compiler settings**, habilite
   o padrão **C99**, ou adicione `-std=c99` em **Other compiler options**.
6. Pressione **F9 (Build and run)**.

Mantenha apenas um arquivo com `main` no projeto. As mensagens do programa usam
caracteres sem acentos para facilitar a exibição no console do Windows.

Também é possível compilar em um terminal com GCC:

```sh
gcc -std=c99 -Wall -Wextra -pedantic estoque_tomates.c -o estoque_tomates
./estoque_tomates
```

No Windows, o executável será `estoque_tomates.exe`.

## Menu e regras

| Opção | Operação |
| --- | --- |
| 1 | Cadastrar um tipo de tomate; bloqueia códigos repetidos e o 21º cadastro. |
| 2 | Listar todos os cadastros, com um separador a cada cinco registros. |
| 3 | Buscar pelo código e mostrar todos os campos do cadastro. |
| 4 | Registrar entrada ou saída de caixas, sem permitir estoque negativo. |
| 5 | Mostrar total de caixas, valor do estoque, maior preço, média e reposições. |
| 6 | Limpar o estoque, apagando todos os cadastros e liberando as 20 vagas. |
| 0 | Encerrar o programa. |

- Digite **uma resposta por linha** e use ponto nos preços, como `35.50`.
- A quantidade inicial pode ser zero; o preço deve ser positivo.
- Entradas e saídas exigem quantidade inteira maior que zero.
- Códigos e quantidades respeitam o limite de `int` informado na tela; entradas
  que ultrapassariam esse limite de estoque são bloqueadas.
- Nomes podem conter espaços, mas não podem ficar vazios ou exceder 49 caracteres.
  Para nomes acentuados, o limite é de 49 bytes na codificação do console.
- Letras em campos numéricos, números fracionados em quantidades e conteúdo
  extra na mesma linha são rejeitados, com nova solicitação da entrada.
- Código inexistente, estoque insuficiente e falta de cadastros geram mensagens
  informativas. O fim da entrada encerra o programa; cadastros incompletos não
  são contabilizados.

O valor do estoque é a soma de `quantidade × preço`. A média é esse valor
dividido pelo total de caixas disponíveis. Sem caixas, a média é informada como
indisponível. O maior preço considera todos os cadastros, inclusive os sem
estoque; em empate, permanece o primeiro cadastrado. A reposição lista os tipos
com quantidade zero.

A opção **6 — Limpar estoque** apaga todos os cadastros da execução atual,
incluindo códigos, nomes, quantidades e preços. Depois dela, é possível começar
novamente e reutilizar os códigos. A limpeza é feita zerando `total_cadastros`:
as posições antigas deixam de ser consultadas e são sobrescritas pelos novos
cadastros. Não é necessário percorrer e zerar cada vetor.

## Exemplo para conferir

Cadastre `1 / Tomate Italiano / 10 / 30.00`,
`2 / Tomate Cereja / 5 / 50.00` e `3 / Tomate Saladete / 0 / 20.00`,
digitando cada campo em uma linha na opção 1.

O relatório deverá mostrar **15 caixas**, **R$ 550.00** em estoque,
**Tomate Cereja** com maior preço (**R$ 50.00**), média de **R$ 36.67** por caixa
e **1 tipo sem estoque**, o Tomate Saladete.

Registre uma entrada de 3 caixas do Italiano: o saldo passa a 13. Uma saída de
4 passa o saldo a 9. Uma tentativa de saída de 10 é recusada, mantendo as 9
caixas. Após essas operações, o relatório deve indicar 14 caixas e R$ 520.00.

## Estruturas utilizadas

Toda a lógica está em `main`, com `printf` e `scanf`. O programa usa `if/else`,
`switch-case`, `do-while`, `for`, `while`, vetores de tamanho fixo e matriz de
caracteres. O contador `total_cadastros` delimita as posições válidas.

Cadastro, consulta e movimentação compartilham a leitura e a busca por código.
Um `for` lê os dois campos numéricos do cadastro ou da movimentação, reduzindo
a repetição das validações.

Não há funções próprias além de `main`, structs, variáveis ponteiro, alocação
dinâmica ou gravação de dados em arquivos. O `&` em `scanf` é necessário para
ler as variáveis, conforme o uso básico de entrada de dados em C.

As entradas numéricas são lidas em uma variável `double` para conferir a faixa
e rejeitar frações antes da conversão para `int`. O limite inteiro é definido
pela constante `LIMITE_INTEIRO`, com valor 2147483647 para o GCC/MinGW usado no
Code::Blocks. Não há uso de `limits.h`. `float.h` fornece o limite do preço.
Os preços são armazenados em `float`; os totais usam `double` e são exibidos
com duas casas decimais.

## Entrega

Preencha **nome completo, R.A. e turma** no comentário inicial e ajuste a data
se necessário. Para a entrega no ambiente virtual, envie somente
**`estoque_tomates.c`**, conforme o enunciado.
