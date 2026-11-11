/*
 * Estudante(s): PREENCHER NOME COMPLETO
 * R.A.: PREENCHER
 * Turma: PREENCHER
 * Data: 11/11/2026
 * Tema: gestao de estoque de tomates em caixas inteiras.
 * Cadastro, listagem, busca, movimentacao e relatorio em memoria.
 */

#include <stdio.h>
#include <limits.h>
#include <float.h>

#define TAM_MAX 20
#define TAM_NOME 50

int main(void)
{
    /* O mesmo indice representa o mesmo tipo de tomate em todos os vetores. */
    int codigo[TAM_MAX];
    char nome[TAM_MAX][TAM_NOME];
    int quantidade[TAM_MAX];
    float preco[TAM_MAX];
    int total_cadastros = 0;

    int opcao = -1;
    int i, posicao, codigo_busca, movimento, caixas;
    int entrada_valida, leitura, nome_preenchido;
    int fim_entrada = 0;
    int maior_preco, sem_estoque;
    char caractere;
    double numero, valor_total, total_caixas;

    printf("GESTAO DE ESTOQUE DE TOMATES\n");
    printf("Quantidades em caixas inteiras. Precos em reais por caixa.\n");
    printf("Use ponto nos precos, por exemplo: 35.50.\n");

    do {
        printf("\n========== MENU PRINCIPAL ==========\n");
        printf("1 - Cadastrar tipo de tomate\n");
        printf("2 - Listar cadastros\n");
        printf("3 - Buscar por codigo\n");
        printf("4 - Registrar entrada ou saida de caixas\n");
        printf("5 - Gerar relatorio\n");
        printf("0 - Sair\n");

        do {
            printf("Opcao: ");
            entrada_valida = scanf("%lf", &numero);
            if (entrada_valida == EOF) {
                fim_entrada = 1;
                break;
            }

            /* Descarta a linha e rejeita texto depois do numero, como 2abc. */
            leitura = scanf("%c", &caractere);
            while (leitura == 1 && caractere != '\n') {
                if (caractere != ' ' && caractere != '\t' && caractere != '\r') {
                    entrada_valida = 0;
                }
                leitura = scanf("%c", &caractere);
            }

            /* Confere a faixa antes de converter para int, sem perder fracoes. */
            if (entrada_valida == 1 && numero >= 0 && numero <= INT_MAX
                && numero == (int)numero) {
                opcao = (int)numero;
            } else {
                entrada_valida = 0;
                printf("Opcao invalida. Digite um numero inteiro de 0 a 5.\n");
            }
        } while (entrada_valida != 1);

        if (fim_entrada) {
            break;
        }

        switch (opcao) {
            case 1:
                if (total_cadastros >= TAM_MAX) {
                    printf("Capacidade esgotada: o limite e de %d cadastros.\n", TAM_MAX);
                    break;
                }

                printf("\n--- CADASTRAR TIPO DE TOMATE ---\n");
                do {
                    printf("Codigo (inteiro positivo): ");
                    entrada_valida = scanf("%lf", &numero);
                    if (entrada_valida == EOF) {
                        fim_entrada = 1;
                        break;
                    }

                    leitura = scanf("%c", &caractere);
                    while (leitura == 1 && caractere != '\n') {
                        if (caractere != ' ' && caractere != '\t' && caractere != '\r') {
                            entrada_valida = 0;
                        }
                        leitura = scanf("%c", &caractere);
                    }

                    if (entrada_valida == 1 && numero > 0 && numero <= INT_MAX
                        && numero == (int)numero) {
                        codigo_busca = (int)numero;
                        posicao = -1;
                        i = 0;
                        while (i < total_cadastros && posicao == -1) {
                            if (codigo[i] == codigo_busca) {
                                posicao = i;
                            }
                            i++;
                        }
                        if (posicao != -1) {
                            entrada_valida = 0;
                            printf("Codigo ja cadastrado. Escolha outro codigo.\n");
                        } else {
                            codigo[total_cadastros] = codigo_busca;
                        }
                    } else {
                        entrada_valida = 0;
                        printf("Codigo invalido. Digite um inteiro entre 1 e %d.\n", INT_MAX);
                    }
                } while (entrada_valida != 1);

                if (fim_entrada) {
                    break;
                }

                do {
                    printf("Nome do tipo de tomate (ate 49 caracteres): ");
                    /* Sem espaco antes de %: uma linha vazia deve ser rejeitada. */
                    entrada_valida = scanf("%49[^\n]", nome[total_cadastros]);
                    if (entrada_valida == EOF) {
                        fim_entrada = 1;
                        break;
                    }

                    nome_preenchido = 0;
                    if (entrada_valida == 1) {
                        for (i = 0; nome[total_cadastros][i] != '\0'; i++) {
                            if (nome[total_cadastros][i] != ' '
                                && nome[total_cadastros][i] != '\t'
                                && nome[total_cadastros][i] != '\r') {
                                nome_preenchido = 1;
                            }
                        }
                        /* Retira o retorno de carro de uma entrada com CRLF. */
                        if (i > 0 && nome[total_cadastros][i - 1] == '\r') {
                            nome[total_cadastros][i - 1] = '\0';
                        }
                    }

                    /* Se sobrou texto, o nome excedeu o limite do vetor. */
                    leitura = scanf("%c", &caractere);
                    while (leitura == 1 && caractere != '\n') {
                        if (caractere != '\r') {
                            entrada_valida = 0;
                        }
                        leitura = scanf("%c", &caractere);
                    }
                    if (entrada_valida != 1 || nome_preenchido == 0) {
                        entrada_valida = 0;
                        printf("Nome invalido. Digite de 1 a 49 caracteres, sem deixar em branco.\n");
                    }
                } while (entrada_valida != 1);

                if (fim_entrada) {
                    break;
                }

                do {
                    printf("Quantidade inicial de caixas (0 a %d): ", INT_MAX);
                    entrada_valida = scanf("%lf", &numero);
                    if (entrada_valida == EOF) {
                        fim_entrada = 1;
                        break;
                    }

                    leitura = scanf("%c", &caractere);
                    while (leitura == 1 && caractere != '\n') {
                        if (caractere != ' ' && caractere != '\t' && caractere != '\r') {
                            entrada_valida = 0;
                        }
                        leitura = scanf("%c", &caractere);
                    }
                    if (entrada_valida == 1 && numero >= 0 && numero <= INT_MAX
                        && numero == (int)numero) {
                        quantidade[total_cadastros] = (int)numero;
                    } else {
                        entrada_valida = 0;
                        printf("Quantidade invalida. Digite um numero inteiro nao negativo.\n");
                    }
                } while (entrada_valida != 1);

                if (fim_entrada) {
                    break;
                }

                do {
                    printf("Preco por caixa (R$): ");
                    entrada_valida = scanf("%lf", &numero);
                    if (entrada_valida == EOF) {
                        fim_entrada = 1;
                        break;
                    }

                    leitura = scanf("%c", &caractere);
                    while (leitura == 1 && caractere != '\n') {
                        if (caractere != ' ' && caractere != '\t' && caractere != '\r') {
                            entrada_valida = 0;
                        }
                        leitura = scanf("%c", &caractere);
                    }
                    if (entrada_valida == 1 && numero > 0 && numero <= FLT_MAX
                        && (float)numero > 0) {
                        preco[total_cadastros] = (float)numero;
                    } else {
                        entrada_valida = 0;
                        printf("Preco invalido. Digite um valor positivo com ponto decimal.\n");
                    }
                } while (entrada_valida != 1);

                if (fim_entrada) {
                    break;
                }

                /* Somente um cadastro completo passa a ocupar uma posicao. */
                total_cadastros++;
                printf("Cadastro realizado com sucesso!\n");
                break;

            case 2:
                if (total_cadastros == 0) {
                    printf("Nenhum tipo de tomate cadastrado.\n");
                    break;
                }

                printf("\n--- TIPOS DE TOMATE CADASTRADOS ---\n");
                printf("%-10s | %-49s | %10s | %14s\n",
                       "Codigo", "Nome", "Caixas", "Preco/caixa R$");
                for (i = 0; i < total_cadastros; i++) {
                    printf("%-10d | %-49s | %10d | %14.2f\n",
                           codigo[i], nome[i], quantidade[i], preco[i]);
                    if ((i + 1) % 5 == 0) {
                        printf("--------------------------------------------------------------------------------------------\n");
                    }
                }
                printf("Total de cadastros: %d de %d.\n", total_cadastros, TAM_MAX);
                break;

            case 3:
            case 4:
                /* Consulta e movimentacao comecam pela mesma busca por codigo. */
                if (total_cadastros == 0) {
                    printf("Nenhum tipo de tomate cadastrado.\n");
                    break;
                }

                do {
                    printf("\nCodigo do tipo de tomate: ");
                    entrada_valida = scanf("%lf", &numero);
                    if (entrada_valida == EOF) {
                        fim_entrada = 1;
                        break;
                    }

                    leitura = scanf("%c", &caractere);
                    while (leitura == 1 && caractere != '\n') {
                        if (caractere != ' ' && caractere != '\t' && caractere != '\r') {
                            entrada_valida = 0;
                        }
                        leitura = scanf("%c", &caractere);
                    }
                    if (entrada_valida == 1 && numero > 0 && numero <= INT_MAX
                        && numero == (int)numero) {
                        codigo_busca = (int)numero;
                    } else {
                        entrada_valida = 0;
                        printf("Codigo invalido. Digite um inteiro entre 1 e %d.\n", INT_MAX);
                    }
                } while (entrada_valida != 1);

                if (fim_entrada) {
                    break;
                }

                posicao = -1;
                i = 0;
                while (i < total_cadastros && posicao == -1) {
                    if (codigo[i] == codigo_busca) {
                        posicao = i;
                    }
                    i++;
                }
                if (posicao == -1) {
                    printf("Codigo nao encontrado.\n");
                    break;
                }

                printf("\nCodigo: %d\n", codigo[posicao]);
                printf("Nome: %s\n", nome[posicao]);
                printf("Caixas em estoque: %d\n", quantidade[posicao]);
                printf("Preco por caixa: R$ %.2f\n", preco[posicao]);
                if (opcao == 3) {
                    break;
                }

                do {
                    printf("1 - Entrada de caixas\n2 - Saida de caixas\nMovimento: ");
                    entrada_valida = scanf("%lf", &numero);
                    if (entrada_valida == EOF) {
                        fim_entrada = 1;
                        break;
                    }

                    leitura = scanf("%c", &caractere);
                    while (leitura == 1 && caractere != '\n') {
                        if (caractere != ' ' && caractere != '\t' && caractere != '\r') {
                            entrada_valida = 0;
                        }
                        leitura = scanf("%c", &caractere);
                    }
                    if (entrada_valida == 1 && (numero == 1 || numero == 2)) {
                        movimento = (int)numero;
                    } else {
                        entrada_valida = 0;
                        printf("Movimento invalido. Digite 1 ou 2.\n");
                    }
                } while (entrada_valida != 1);

                if (fim_entrada) {
                    break;
                }

                do {
                    printf("Quantidade de caixas a movimentar: ");
                    entrada_valida = scanf("%lf", &numero);
                    if (entrada_valida == EOF) {
                        fim_entrada = 1;
                        break;
                    }

                    leitura = scanf("%c", &caractere);
                    while (leitura == 1 && caractere != '\n') {
                        if (caractere != ' ' && caractere != '\t' && caractere != '\r') {
                            entrada_valida = 0;
                        }
                        leitura = scanf("%c", &caractere);
                    }
                    if (entrada_valida == 1 && numero > 0 && numero <= INT_MAX
                        && numero == (int)numero) {
                        caixas = (int)numero;
                    } else {
                        entrada_valida = 0;
                        printf("Quantidade invalida. Digite um numero inteiro positivo.\n");
                    }
                } while (entrada_valida != 1);

                if (fim_entrada) {
                    break;
                }

                if (movimento == 1) {
                    if (caixas <= INT_MAX - quantidade[posicao]) {
                        quantidade[posicao] = quantidade[posicao] + caixas;
                        printf("Entrada registrada. Saldo atual: %d caixas.\n", quantidade[posicao]);
                    } else {
                        printf("Entrada nao realizada: o saldo ultrapassaria o limite de %d caixas.\n", INT_MAX);
                    }
                } else {
                    if (caixas <= quantidade[posicao]) {
                        quantidade[posicao] = quantidade[posicao] - caixas;
                        printf("Saida registrada. Saldo atual: %d caixas.\n", quantidade[posicao]);
                    } else {
                        printf("Estoque insuficiente. Disponivel: %d caixas.\n", quantidade[posicao]);
                    }
                }
                break;

            case 5:
                if (total_cadastros == 0) {
                    printf("Nenhum tipo de tomate cadastrado.\n");
                    break;
                }

                valor_total = 0;
                total_caixas = 0;
                maior_preco = 0;
                sem_estoque = 0;
                for (i = 0; i < total_cadastros; i++) {
                    /* double evita que o calculo intermediario fique limitado a float. */
                    valor_total = valor_total + (quantidade[i] * (double)preco[i]);
                    total_caixas = total_caixas + quantidade[i];
                    if (preco[i] > preco[maior_preco]) {
                        maior_preco = i;
                    }
                    if (quantidade[i] == 0) {
                        sem_estoque++;
                    }
                }

                printf("\n--- RELATORIO DO ESTOQUE ---\n");
                printf("Tipos de tomate cadastrados: %d\n", total_cadastros);
                printf("Total de caixas: %.0f\n", total_caixas);
                printf("Valor total do estoque: R$ %.2f\n", valor_total);
                printf("Maior preco por caixa: %s (codigo %d) - R$ %.2f\n",
                       nome[maior_preco], codigo[maior_preco], preco[maior_preco]);
                if (total_caixas > 0) {
                    printf("Valor medio por caixa: R$ %.2f\n", valor_total / total_caixas);
                } else {
                    printf("Valor medio por caixa: indisponivel (nenhuma caixa em estoque).\n");
                }
                printf("Tipos de tomate sem estoque: %d\n", sem_estoque);
                if (sem_estoque > 0) {
                    printf("Reposicao necessaria:\n");
                    for (i = 0; i < total_cadastros; i++) {
                        if (quantidade[i] == 0) {
                            printf("- Codigo %d: %s\n", codigo[i], nome[i]);
                        }
                    }
                }
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida. Escolha uma opcao de 0 a 5.\n");
                break;
        }
    } while (opcao != 0 && fim_entrada == 0);

    if (fim_entrada) {
        printf("\nEntrada encerrada.\n");
    }
    printf("Sistema encerrado. Obrigado!\n");
    return 0;
}
