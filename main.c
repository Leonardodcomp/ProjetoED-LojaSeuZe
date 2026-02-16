/*
 PROJETO DE ESTRUTURAS DE DADOS EM C

 Autores: Leonardo Souza Silva; João Pedro

                            Assistencia técnica e Serviços de Hardware Seu Zé!

Vamos explicar abaixo como Seu Zé montou o sistema para sua loja e serviços de Hardware Seu Zé.

 */


// Aqui vamos puxar as bibliotecas padrão, stdio é padrão, stdlib para usarmos a biblioteca básica e string para fazermos operações com string em variáveis dinâmicas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Começamos definindo a struct "main", vamos chamar ela de Produto

typedef struct {
    int id;
    char nome[50];
    char categoria[30]; 
    float preco;
} Produto;

// Atendendo a um dos critérios seu Zé fez uma LISTA ENCADEADA, vamos usar ela para implementar o estoque.
typedef struct NoLista {
    Produto dado;
    struct NoLista* prox;
} NoLista;

// Atendendo ao critério da FILA (QUEUE - FIFO), seu Zé implementou o suporte técnico.
typedef struct NoFila {
    char cliente[50];
    char servico[50];
    struct NoFila* prox;
} NoFila;

typedef struct {
    NoFila* inicio;
    NoFila* fim;
} FilaSuporte;

// Atendendo ao critério da PILHA (STACK - LIFO), seu Zé implementou o histórico de consultas.
typedef struct NoPilha {
    int id_produto;
    struct NoPilha* prox;
} NoPilha;

// Atendendo ao critério da ARRAY, seu Zé implementou o relatório de vendas (estático)
#define MAX_VENDAS 50
typedef struct {
    float valores[MAX_VENDAS];
    int qtd;
} RelatorioVendas;

// Seu Zé começou a lógica da LISTA ENCADEADA, lembrando que vamos usar a struct da linha 29, o NoLista

NoLista* adicionar_produto(NoLista* lista, int id, char* nome, char* cat, float preco) {

    // Criação da variável dinâmica:

    NoLista* novo = (NoLista*) malloc(sizeof(NoLista));
    if(novo == NULL) {
        printf("ERRO: Falha na alocacao de memoria!\n");
        return lista;
    }
    novo->dado.id = id;
    strcpy(novo->dado.nome, nome);
    strcpy(novo->dado.categoria, cat);
    novo->dado.preco = preco;
    
    // Inserção no início (calculo de complexidade mais eficiente, como titia Kenia explicou é BIG O(1))
    novo->prox = lista;
    printf("SUCESSO: Produto '%s' adicionado ao estoque.\n", nome);
    return novo;
}

void listar_estoque(NoLista* lista) {
    printf("\n--- ESTOQUE ATUAL (LISTA) ---\n");
    if(lista == NULL) {
        printf("Estoque vazio.\n");
        return;
    }
    NoLista* aux = lista;
    while(aux != NULL) {
        printf("ID: %d | Hardware: %-15s | Tipo: %-10s | R$ %.2f\n", 
               aux->dado.id, aux->dado.nome, aux->dado.categoria, aux->dado.preco);
        aux = aux->prox;
    }
}

// Função para limpar memória da Lista (Free)
void liberar_lista(NoLista* lista) {
    NoLista* atual = lista;
    NoLista* prox;
    while (atual != NULL) {
        prox = atual->prox;
        free(atual); // Libera cada nó
        atual = prox;
    }
}

// Aqui Seu Zé começou a lógica da FILA, e consequentemente do Suporte Técnico

void iniciar_fila(FilaSuporte* f) {
    f->inicio = NULL;
    f->fim = NULL;
}

void entrar_fila(FilaSuporte* f, char* cliente, char* servico) {
    NoFila* novo = (NoFila*) malloc(sizeof(NoFila));
    strcpy(novo->cliente, cliente);
    strcpy(novo->servico, servico);
    novo->prox = NULL;

    if (f->fim != NULL) {
        f->fim->prox = novo;
    } else {
        f->inicio = novo;
    }
    f->fim = novo;
    printf("FILA: Cliente %s aguardando montagem/suporte.\n", cliente);
}

void atender_cliente(FilaSuporte* f) {
    if (f->inicio == NULL) {
        printf("FILA: Ninguem na fila de espera.\n");
        return;
    }
    NoFila* temp = f->inicio;
    printf("ATENDIMENTO: Processando: %s (Servico: %s)\n", temp->cliente, temp->servico);
    
    f->inicio = f->inicio->prox;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    free(temp); // Libera memória do cliente atendido
}

void liberar_fila(FilaSuporte* f) {
    while(f->inicio != NULL) {
        atender_cliente(f); // Reaproveita a lógica de remover para limpar
    }
}

// Aqui Seu Zé começou usa lógica da PILHA para montar o histórico

NoPilha* empilhar(NoPilha* topo, int id) {
    NoPilha* novo = (NoPilha*) malloc(sizeof(NoPilha));
    novo->id_produto = id;
    novo->prox = topo;
    return novo; // O novo nó se torna o topo
}

void mostrar_historico(NoPilha* topo) {
    printf("\n--- HISTORICO DE CONSULTAS (PILHA LIFO) ---\n");
    if(topo == NULL) {
        printf("Nenhuma consulta recente.\n");
        return;
    }
    NoPilha* aux = topo;
    while(aux != NULL) {
        printf("Consultado ID: %d\n", aux->id_produto);
        aux = aux->prox;
    }
}

void liberar_pilha(NoPilha* topo) {
    NoPilha* atual = topo;
    NoPilha* prox;
    while (atual != NULL) {
        prox = atual->prox;
        free(atual);
        atual = prox;
    }
}

// Por ultimo, mas não menos importante seu Zé faz um relatório de vendas simples, estático, com o ARRAY

void registrar_venda(RelatorioVendas* r, float valor) {
    if (r->qtd < MAX_VENDAS) {
        r->valores[r->qtd] = valor;
        r->qtd++;
        printf("VENDAS: Venda de R$ %.2f registrada.\n", valor);
    } else {
        printf("ERRO: Memoria do relatorio diario cheia!\n");
    }
}

void exibir_relatorio(RelatorioVendas* r) {
    float total = 0;
    printf("\n--- RELATORIO DE VENDAS (ARRAY) ---\n");
    for(int i = 0; i < r->qtd; i++) {
        printf("Venda %d: R$ %.2f\n", i+1, r->valores[i]);
        total += r->valores[i];
    }
    printf("TOTAL DO DIA: R$ %.2f\n", total);
}

// Com toda a lógica declarada, seu Zé parte para o MAIN para fazer tudo funcionar em conjunto.

int main() {
    // Seu Zé da play em tudo para rodar todas as estruturas:
    NoLista* estoque = NULL;
    FilaSuporte fila;
    iniciar_fila(&fila);
    NoPilha* historico = NULL;
    RelatorioVendas relatorio = { .qtd = 0 };

    int opcao, id;
    char nome[50], cat[30], cli[50], serv[50];
    float preco;

    // Seu Zé não curte frontend e fez um negocinho no terminal mesmo com a função do
    do {
        printf("\n========================================\n");
        printf("   SISTEMA DE HARDWARE - LOJA DO SEU ZÉ   \n");
        printf("========================================\n");
        printf("1. [LISTA] Adicionar Componente ao Estoque\n");
        printf("2. [LISTA] Listar Estoque\n");
        printf("3. [FILA]  Solicitar Assistencia (Entrar)\n");
        printf("4. [FILA]  Realizar Atendimento (Sair)\n");
        printf("5. [PILHA] Consultar Produto (Historico)\n");
        printf("6. [PILHA] Ver Historico de Consultas\n");
        printf("7. [ARRAY] Registrar Venda\n");
        printf("8. [ARRAY] Relatorio do Dia\n");
        printf("0. SAIR (Libera memoria)\n");
        printf("Escolha: ");
        
        if (scanf("%d", &opcao) != 1) { // Validação básica de seu Zé
            while(getchar() != '\n'); // Limpa buffer
            opcao = -1; // -1 é pra dizer que não tem na computação e também cai no default do switch abaixo
        }

        switch(opcao) {
            case 1:
                printf("ID do Produto: "); scanf("%d", &id);
                printf("Nome (sem espacos): "); scanf("%s", nome);
                printf("Categoria (GPU/CPU/RAM): "); scanf("%s", cat);
                printf("Preco: "); scanf("%f", &preco);
                estoque = adicionar_produto(estoque, id, nome, cat, preco);
                break;
            case 2:
                listar_estoque(estoque);
                break;
            case 3:
                printf("Nome Cliente: "); scanf("%s", cli);
                printf("Tipo Servico: "); scanf("%s", serv);
                entrar_fila(&fila, cli, serv);
                break;
            case 4:
                atender_cliente(&fila);
                break;
            case 5:
                printf("Digite o ID para consulta: "); scanf("%d", &id);
                // Simula busca e joga na pilha
                historico = empilhar(historico, id);
                printf("Produto %d consultado e salvo no historico.\n", id);
                break;
            case 6:
                mostrar_historico(historico);
                break;
            case 7:
                printf("Valor da Venda: "); scanf("%f", &preco);
                registrar_venda(&relatorio, preco);
                break;
            case 8:
                exibir_relatorio(&relatorio);
                break;
            case 0:
                printf("Encerrando sistema, seu Zé agradece!\n");
                liberar_lista(estoque);
                liberar_fila(&fila);
                liberar_pilha(historico);
                printf("Memoria liberada com sucesso. Volte sempre para loja do Seu Zé!\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    return 0;
}

// E assim seu Zé termina a lógica do seu Sistema para seu negócio! 