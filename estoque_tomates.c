#include <stdio.h>
#include <float.h>

#define TAM_MAX 20
#define LIMITE_INTEIRO 2147483647 /* Limite do int no GCC/MinGW do Code::Blocks. */

int main(void)
{
    int codigo[TAM_MAX], quantidade[TAM_MAX], total_cadastros = 0;
    int unidade[TAM_MAX]; /* 0 = caixas; 1 = kg (quantidade guardada em gramas). */
    char nome[TAM_MAX][50], caractere;
    char tipos[5][50] = {"Italiano", "Cereja", "Saladete", "Santa Cruz", "Debora"};
    char unidades[2][7] = {"caixas", "kg"};
    char medida[2][6] = {"caixa", "kg"};
    float preco[TAM_MAX];
    int opcao = -1, i, j, posicao, codigo_busca, campo, movimento = 0;
    int quantidade_lida = 0, quantidade_movimento = 0;
    int entrada_valida, nome_preenchido, tipo, fim_entrada = 0;
    int maior_preco[2], sem_estoque;
    double numero, valor_total, subtotal, quantidade_convertida, quantidade_exibida;
    double total_quantidade[2], valor_unidade[2];

    printf("GESTAO DE ESTOQUE DE TOMATES\n");
    printf("Caixas inteiras ou kg com ate 3 casas decimais.\n");
    printf("Use ponto nos pesos e precos (ex.: 2.500 kg e R$ 35.50).\n");
    do {
        printf("\n1 - Cadastrar\n2 - Listar\n3 - Buscar por codigo\n"
               "4 - Entrada ou saida\n5 - Relatorio\n"
               "6 - Limpar estoque (apagar todos os cadastros)\n"
               "7 - Apagar um cadastro por codigo\n0 - Sair\n");
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
                printf("Opcao invalida. Digite um inteiro de 0 a 7.\n");
            }
        } while (entrada_valida != 1);
        if (fim_entrada) break;

        switch (opcao) {
            case 1:
            case 3:
            case 4:
            case 7:
                /* Estas acoes compartilham a leitura e a busca do codigo. */
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
                    posicao = total_cadastros;
                    codigo[total_cadastros] = codigo_busca;
                    printf("\nEscolha um tipo pronto ou digite outro nome pela opcao 6:\n");
                    for (i = 0; i < 5; i++) printf("%d - %s\n", i + 1, tipos[i]);
                    printf("6 - Digitar outro nome\n");
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
                            printf("Digite o nome desejado (ate 49 caracteres): ");
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
                    if (fim_entrada) break;
                    do {
                        printf("Unidade: 1 - Caixas | 2 - Quilogramas (kg)\nEscolha: ");
                        entrada_valida = scanf("%lf", &numero);
                        if (entrada_valida == EOF) {
                            fim_entrada = 1;
                            break;
                        }
                        while (scanf("%c", &caractere) == 1 && caractere != '\n') {
                            if (caractere != ' ' && caractere != '\t' && caractere != '\r')
                                entrada_valida = 0;
                        }
                        if (entrada_valida == 1 && (numero == 1 || numero == 2)) {
                            unidade[posicao] = (int)numero - 1;
                        } else {
                            entrada_valida = 0;
                            printf("Unidade invalida. Digite 1 para caixas ou 2 para kg.\n");
                        }
                    } while (entrada_valida != 1);
                } else {
                    if (posicao == -1) {
                        printf("Codigo nao encontrado.\n");
                        break;
                    }
                    printf("Codigo: %d\nNome: %s\n", codigo[posicao], nome[posicao]);
                    if (unidade[posicao] == 0)
                        printf("Caixas em estoque: %d\n", quantidade[posicao]);
                    else
                        printf("Peso em estoque: %.3f kg\n", quantidade[posicao] / 1000.0);
                    printf("Preco por %s: R$ %.2f\n", medida[unidade[posicao]], preco[posicao]);
                    if (opcao == 3) break;
                    if (opcao == 7) {
                        /* Desloca todos os campos para preencher a vaga apagada. */
                        for (i = posicao; i < total_cadastros - 1; i++) {
                            codigo[i] = codigo[i + 1];
                            quantidade[i] = quantidade[i + 1];
                            unidade[i] = unidade[i + 1];
                            preco[i] = preco[i + 1];
                            for (j = 0; nome[i + 1][j] != '\0'; j++)
                                nome[i][j] = nome[i + 1][j];
                            nome[i][j] = '\0';
                        }
                        total_cadastros--;
                        printf("Cadastro de codigo %d apagado.\n", codigo_busca);
                        break;
                    }
                }
                if (fim_entrada) break;

                /* Cadastro: quantidade/preco. Movimentacao: tipo/quantidade. */
                for (campo = 0; campo < 2 && fim_entrada == 0; campo++) {
                    do {
                        if (opcao == 1) {
                            if (campo == 0) printf("Quantidade inicial (%s): ", unidades[unidade[posicao]]);
                            else printf("Preco por %s (R$): ", medida[unidade[posicao]]);
                        } else {
                            if (campo == 0) printf("1 - Entrada\n2 - Saida\nMovimento: ");
                            else printf("Quantidade a movimentar (%s): ", unidades[unidade[posicao]]);
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
                            if (opcao == 4 && campo == 0) {
                                if (entrada_valida == 1 && (numero == 1 || numero == 2)) {
                                    movimento = (int)numero;
                                } else {
                                    entrada_valida = 0;
                                    printf("Movimento invalido. Digite 1 ou 2.\n");
                                }
                            } else {
                                quantidade_convertida = numero;
                                if (unidade[posicao] == 1) quantidade_convertida *= 1000;
                                if (entrada_valida == 1 && quantidade_convertida >= 0
                                    && quantidade_convertida <= LIMITE_INTEIRO) {
                                    quantidade_lida = (int)quantidade_convertida;
                                    if (unidade[posicao] == 1) {
                                        /* Corrige apenas o erro binario da conversao kg -> gramas. */
                                        quantidade_lida = (int)(quantidade_convertida + 0.000001);
                                        if (quantidade_convertida - quantidade_lida > 0.000001
                                            || quantidade_lida - quantidade_convertida > 0.000001
                                            || (numero > 0 && quantidade_lida == 0))
                                            entrada_valida = 0;
                                    } else if (quantidade_convertida != quantidade_lida) {
                                        entrada_valida = 0;
                                    }
                                } else {
                                    entrada_valida = 0;
                                }
                                if (entrada_valida == 1 && (opcao == 1 || quantidade_lida > 0)) {
                                    if (opcao == 1) quantidade[total_cadastros] = quantidade_lida;
                                    else quantidade_movimento = quantidade_lida;
                                } else {
                                    entrada_valida = 0;
                                    if (unidade[posicao] == 0)
                                        printf("Quantidade invalida. Use caixas inteiras de 0 a %d.\n", LIMITE_INTEIRO);
                                    else
                                        printf("Quantidade invalida. Use kg de 0 a %.3f, com ate 3 casas decimais.\n",
                                               LIMITE_INTEIRO / 1000.0);
                                    printf("Para movimentar, a quantidade deve ser maior que zero.\n");
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
                    if (quantidade_movimento <= LIMITE_INTEIRO - quantidade[posicao]) {
                        quantidade[posicao] += quantidade_movimento;
                        if (unidade[posicao] == 0)
                            printf("Entrada registrada. Saldo atual: %d caixas.\n", quantidade[posicao]);
                        else
                            printf("Entrada registrada. Saldo atual: %.3f kg.\n", quantidade[posicao] / 1000.0);
                    } else {
                        printf("Entrada nao realizada: o saldo ultrapassaria o limite permitido.\n");
                    }
                } else {
                    if (quantidade_movimento <= quantidade[posicao]) {
                        quantidade[posicao] -= quantidade_movimento;
                        if (unidade[posicao] == 0)
                            printf("Saida registrada. Saldo atual: %d caixas.\n", quantidade[posicao]);
                        else
                            printf("Saida registrada. Saldo atual: %.3f kg.\n", quantidade[posicao] / 1000.0);
                    } else {
                        if (unidade[posicao] == 0)
                            printf("Estoque insuficiente. Disponivel: %d caixas.\n", quantidade[posicao]);
                        else
                            printf("Estoque insuficiente. Disponivel: %.3f kg.\n", quantidade[posicao] / 1000.0);
                    }
                }
                break;

            case 2:
                if (total_cadastros == 0) {
                    printf("Nenhum tipo de tomate cadastrado.\n");
                    break;
                }
                printf("\n%-10s | %-49s | %12s | %-6s | %14s\n",
                       "Codigo", "Nome", "Quantidade", "Unid.", "Preco/unid. R$");
                for (i = 0; i < total_cadastros; i++) {
                    printf("%-10d | %-49s | ", codigo[i], nome[i]);
                    if (unidade[i] == 0) printf("%12d", quantidade[i]);
                    else printf("%12.3f", quantidade[i] / 1000.0);
                    printf(" | %-6s | %14.2f\n", unidades[unidade[i]], preco[i]);
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
                printf("\n--- RELATORIO DO ESTOQUE ---\n");
                valor_total = 0;
                for (j = 0; j < 2; j++) {
                    total_quantidade[j] = 0;
                    valor_unidade[j] = 0;
                    maior_preco[j] = -1;
                }
                sem_estoque = 0;
                for (i = 0; i < total_cadastros; i++) {
                    quantidade_exibida = quantidade[i];
                    if (unidade[i] == 1) quantidade_exibida /= 1000;
                    subtotal = quantidade_exibida * preco[i];
                    printf("Codigo: %d | Nome: %s\n", codigo[i], nome[i]);
                    if (unidade[i] == 0) printf("Caixas: %d", quantidade[i]);
                    else printf("Peso: %.3f kg", quantidade_exibida);
                    printf(" | Preco/%s: R$ %.2f | Subtotal: R$ %.2f\n\n",
                           medida[unidade[i]], preco[i], subtotal);
                    valor_total += subtotal;
                    j = unidade[i];
                    total_quantidade[j] += quantidade_exibida;
                    valor_unidade[j] += subtotal;
                    if (maior_preco[j] == -1 || preco[i] > preco[maior_preco[j]]) maior_preco[j] = i;
                    if (quantidade[i] == 0) sem_estoque++;
                }
                printf("--- RESUMO DO ESTOQUE ---\n");
                printf("Tipos de tomate cadastrados: %d\n", total_cadastros);
                printf("Total de caixas: %.0f\nTotal em kg: %.3f\n", total_quantidade[0], total_quantidade[1]);
                printf("Valor total do estoque: R$ %.2f\n", valor_total);
                /* Precos e medias sao comparados somente dentro da mesma unidade. */
                for (j = 0; j < 2; j++) {
                    if (maior_preco[j] != -1) {
                        i = maior_preco[j];
                        printf("Maior preco por %s: %s (codigo %d) - R$ %.2f\n",
                               medida[j], nome[i], codigo[i], preco[i]);
                        if (total_quantidade[j] > 0)
                            printf("Valor medio por %s: R$ %.2f\n", medida[j], valor_unidade[j] / total_quantidade[j]);
                        else
                            printf("Valor medio por %s: indisponivel (estoque zerado).\n", medida[j]);
                    }
                }
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
                printf("Opcao invalida. Escolha uma opcao de 0 a 7.\n");
                break;
        }
    } while (opcao != 0 && fim_entrada == 0);
    if (fim_entrada) printf("\nEntrada encerrada.\n");
    printf("Sistema encerrado. Obrigado!\n");
    return 0;
}
