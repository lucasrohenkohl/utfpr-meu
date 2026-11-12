/*
 * Estudante(s): PREENCHER NOME COMPLETO
 * R.A.: PREENCHER
 * Turma: PREENCHER
 * Data: 11/11/2026
 * Tema: gestao de estoque de tomates em caixas inteiras.
 * Cadastro, consulta, movimentacao, relatorio e limpeza em memoria.
 */
#include <stdio.h>
#include <float.h>

#define TAM_MAX 20
#define LIMITE_INTEIRO 2147483647 /* Limite do int no GCC/MinGW do Code::Blocks. */

int main(void)
{
    int codigo[TAM_MAX], quantidade[TAM_MAX], total_cadastros = 0;
    char nome[TAM_MAX][50], caractere;
    char tipos[5][50] = {"Italiano", "Cereja", "Saladete", "Santa Cruz", "Debora"};
    float preco[TAM_MAX];
    int opcao = -1, i, posicao, codigo_busca, campo, movimento = 0, caixas = 0;
    int entrada_valida, nome_preenchido, tipo, fim_entrada = 0;
    int maior_preco, sem_estoque;
    double numero, valor_total, total_caixas;

    printf("GESTAO DE ESTOQUE DE TOMATES\n");
    printf("Caixas inteiras. Precos em reais por caixa, com ponto (ex.: 35.50).\n");
    do {
        printf("\n1 - Cadastrar\n2 - Listar\n3 - Buscar por codigo\n"
               "4 - Entrada ou saida\n5 - Relatorio\n"
               "6 - Limpar estoque (apagar todos os cadastros)\n0 - Sair\n");
        do {
            printf("Opcao: ");
            entrada_valida = scanf("%lf", &numero);
            if (entrada_valida == EOF) {
                fim_entrada = 1;
                break;
            }
            /* Descarta a linha e rejeita texto depois do numero. */
            while (scanf("%c", &caractere) == 1 && caractere != '\n') {
                if (caractere != ' ' && caractere != '\t' && caractere != '\r')
                    entrada_valida = 0;
            }
            if (entrada_valida == 1 && numero >= 0 && numero <= LIMITE_INTEIRO
                && numero == (int)numero) {
                opcao = (int)numero;
            } else {
                entrada_valida = 0;
                printf("Opcao invalida. Digite um inteiro de 0 a 6.\n");
            }
        } while (entrada_valida != 1);
        if (fim_entrada) break;

        switch (opcao) {
            case 1:
            case 3:
            case 4:
                /* As tres acoes compartilham a leitura e a busca do codigo. */
                if (opcao == 1 && total_cadastros == TAM_MAX) {
                    printf("Capacidade esgotada: o limite e de %d cadastros.\n", TAM_MAX);
                    break;
                }
                if (opcao != 1 && total_cadastros == 0) {
                    printf("Nenhum tipo de tomate cadastrado.\n");
                    break;
                }
                do {
                    printf("Codigo do tipo de tomate: ");
                    entrada_valida = scanf("%lf", &numero);
                    if (entrada_valida == EOF) {
                        fim_entrada = 1;
                        break;
                    }
                    while (scanf("%c", &caractere) == 1 && caractere != '\n') {
                        if (caractere != ' ' && caractere != '\t' && caractere != '\r')
                            entrada_valida = 0;
                    }
                    /* A faixa e conferida antes da conversao para int. */
                    if (entrada_valida == 1 && numero > 0 && numero <= LIMITE_INTEIRO
                        && numero == (int)numero) {
                        codigo_busca = (int)numero;
                        posicao = -1;
                        i = 0;
                        while (i < total_cadastros && posicao == -1) {
                            if (codigo[i] == codigo_busca) posicao = i;
                            i++;
                        }
                        if (opcao == 1 && posicao != -1) {
                            entrada_valida = 0;
                            printf("Codigo ja cadastrado. Escolha outro codigo.\n");
                        }
                    } else {
                        entrada_valida = 0;
                        printf("Codigo invalido. Digite um inteiro de 1 a %d.\n", LIMITE_INTEIRO);
                    }
                } while (entrada_valida != 1);
                if (fim_entrada) break;

                if (opcao == 1) {
                    codigo[total_cadastros] = codigo_busca;
                    printf("\nEscolha o tipo de tomate:\n");
                    for (i = 0; i < 5; i++) printf("%d - %s\n", i + 1, tipos[i]);
                    printf("6 - Outro (digitar nome)\n");
                    do {
                        printf("Tipo: ");
                        entrada_valida = scanf("%lf", &numero);
                        if (entrada_valida == EOF) {
                            fim_entrada = 1;
                            break;
                        }
                        while (scanf("%c", &caractere) == 1 && caractere != '\n') {
                            if (caractere != ' ' && caractere != '\t' && caractere != '\r')
                                entrada_valida = 0;
                        }
                        if (entrada_valida == 1 && numero >= 1 && numero <= 6
                            && numero == (int)numero) {
                            tipo = (int)numero;
                        } else {
                            entrada_valida = 0;
                            printf("Tipo invalido. Escolha um numero inteiro de 1 a 6.\n");
                        }
                    } while (entrada_valida != 1);
                    if (fim_entrada) break;

                    if (tipo <= 5) {
                        /* Copia o nome escolhido usando somente matriz e for. */
                        for (i = 0; tipos[tipo - 1][i] != '\0'; i++)
                            nome[total_cadastros][i] = tipos[tipo - 1][i];
                        nome[total_cadastros][i] = '\0';
                    } else {
                        do {
                            printf("Nome do tipo de tomate (ate 49 caracteres): ");
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
                                        && nome[total_cadastros][i] != '\r')
                                        nome_preenchido = 1;
                                }
                                if (i > 0 && nome[total_cadastros][i - 1] == '\r')
                                    nome[total_cadastros][i - 1] = '\0';
                            }
                            /* Texto restante indica um nome maior que o permitido. */
                            while (scanf("%c", &caractere) == 1 && caractere != '\n') {
                                if (caractere != '\r') entrada_valida = 0;
                            }
                            if (entrada_valida != 1 || nome_preenchido == 0) {
                                entrada_valida = 0;
                                printf("Nome invalido. Use de 1 a 49 caracteres, sem deixar em branco.\n");
                            }
                        } while (entrada_valida != 1);
                    }
                } else {
                    if (posicao == -1) {
                        printf("Codigo nao encontrado.\n");
                        break;
                    }
                    printf("Codigo: %d\nNome: %s\nCaixas em estoque: %d\nPreco por caixa: R$ %.2f\n",
                           codigo[posicao], nome[posicao], quantidade[posicao], preco[posicao]);
                    if (opcao == 3) break;
                }
                if (fim_entrada) break;

                /* Cadastro: quantidade/preco. Movimentacao: tipo/quantidade. */
                for (campo = 0; campo < 2 && fim_entrada == 0; campo++) {
                    do {
                        if (opcao == 1) {
                            if (campo == 0) printf("Quantidade inicial de caixas: ");
                            else printf("Preco por caixa (R$): ");
                        } else {
                            if (campo == 0) printf("1 - Entrada\n2 - Saida\nMovimento: ");
                            else printf("Quantidade de caixas a movimentar: ");
                        }
                        entrada_valida = scanf("%lf", &numero);
                        if (entrada_valida == EOF) {
                            fim_entrada = 1;
                            break;
                        }
                        while (scanf("%c", &caractere) == 1 && caractere != '\n') {
                            if (caractere != ' ' && caractere != '\t' && caractere != '\r')
                                entrada_valida = 0;
                        }
                        if (opcao == 1 && campo == 1) {
                            if (entrada_valida == 1 && numero > 0 && numero <= FLT_MAX
                                && (float)numero > 0) {
                                preco[total_cadastros] = (float)numero;
                            } else {
                                entrada_valida = 0;
                                printf("Preco invalido. Digite um valor positivo com ponto decimal.\n");
                            }
                        } else {
                            if (entrada_valida != 1 || !(numero >= 0 && numero <= LIMITE_INTEIRO)) {
                                entrada_valida = 0;
                            } else if (numero != (int)numero) {
                                entrada_valida = 0;
                            }
                            if (opcao == 4 && campo == 0) {
                                if (entrada_valida == 1 && (numero == 1 || numero == 2)) {
                                    movimento = (int)numero;
                                } else {
                                    entrada_valida = 0;
                                    printf("Movimento invalido. Digite 1 ou 2.\n");
                                }
                            } else {
                                if (entrada_valida == 1 && (opcao == 1 || numero > 0)) {
                                    if (opcao == 1) quantidade[total_cadastros] = (int)numero;
                                    else caixas = (int)numero;
                                } else {
                                    entrada_valida = 0;
                                    printf("Quantidade invalida. Use caixas inteiras de 0 a %d;\n"
                                           "para movimentar, a quantidade deve ser maior que zero.\n", LIMITE_INTEIRO);
                                }
                            }
                        }
                    } while (entrada_valida != 1);
                }
                if (fim_entrada) break;

                if (opcao == 1) {
                    /* O contador aumenta somente depois de preencher todos os campos. */
                    total_cadastros++;
                    printf("Cadastro realizado com sucesso!\n");
                } else if (movimento == 1) {
                    if (caixas <= LIMITE_INTEIRO - quantidade[posicao]) {
                        quantidade[posicao] += caixas;
                        printf("Entrada registrada. Saldo atual: %d caixas.\n", quantidade[posicao]);
                    } else {
                        printf("Entrada nao realizada: limite de %d caixas.\n", LIMITE_INTEIRO);
                    }
                } else {
                    if (caixas <= quantidade[posicao]) {
                        quantidade[posicao] -= caixas;
                        printf("Saida registrada. Saldo atual: %d caixas.\n", quantidade[posicao]);
                    } else {
                        printf("Estoque insuficiente. Disponivel: %d caixas.\n", quantidade[posicao]);
                    }
                }
                break;

            case 2:
                if (total_cadastros == 0) {
                    printf("Nenhum tipo de tomate cadastrado.\n");
                    break;
                }
                printf("\n%-10s | %-49s | %10s | %14s\n", "Codigo", "Nome", "Caixas", "Preco/caixa R$");
                for (i = 0; i < total_cadastros; i++) {
                    printf("%-10d | %-49s | %10d | %14.2f\n", codigo[i], nome[i], quantidade[i], preco[i]);
                    if ((i + 1) % 5 == 0)
                        printf("--------------------------------------------------------------------------------------------\n");
                }
                printf("Total de cadastros: %d de %d.\n", total_cadastros, TAM_MAX);
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
                    valor_total += quantidade[i] * (double)preco[i];
                    total_caixas += quantidade[i];
                    if (preco[i] > preco[maior_preco]) maior_preco = i;
                    if (quantidade[i] == 0) sem_estoque++;
                }
                printf("\n--- RELATORIO DO ESTOQUE ---\n");
                printf("Tipos de tomate cadastrados: %d\nTotal de caixas: %.0f\n", total_cadastros, total_caixas);
                printf("Valor total do estoque: R$ %.2f\n", valor_total);
                printf("Maior preco por caixa: %s (codigo %d) - R$ %.2f\n",
                       nome[maior_preco], codigo[maior_preco], preco[maior_preco]);
                if (total_caixas > 0)
                    printf("Valor medio por caixa: R$ %.2f\n", valor_total / total_caixas);
                else
                    printf("Valor medio por caixa: indisponivel (nenhuma caixa em estoque).\n");
                printf("Tipos de tomate sem estoque: %d\n", sem_estoque);
                if (sem_estoque > 0) {
                    printf("Reposicao necessaria:\n");
                    for (i = 0; i < total_cadastros; i++) {
                        if (quantidade[i] == 0) printf("- Codigo %d: %s\n", codigo[i], nome[i]);
                    }
                }
                break;

            case 6:
                if (total_cadastros == 0) {
                    printf("Nenhum tipo de tomate cadastrado.\n");
                } else {
                    /* Com o contador zerado, nenhuma posicao antiga e consultada. */
                    total_cadastros = 0;
                    printf("Todos os cadastros foram apagados.\n");
                }
                break;

            case 0:
                break;
            default:
                printf("Opcao invalida. Escolha uma opcao de 0 a 6.\n");
                break;
        }
    } while (opcao != 0 && fim_entrada == 0);
    if (fim_entrada) printf("\nEntrada encerrada.\n");
    printf("Sistema encerrado. Obrigado!\n");
    return 0;
}
