#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// magic numbers 
#define BUFFER_SIZE 30 
#define FAILED -1

typedef struct _cliente{
    char nome[BUFFER_SIZE];
    int idade;
} cliente;

typedef struct _lista{
    cliente info;
    struct _lista * prox;
} lista;

void inicializar(lista ** lst){
    //*lst ==> l
    *lst = NULL;
}

int inserirInicio(lista ** lst, cliente c){
    lista * aux;
    aux = (lista*) calloc(1,sizeof(lista));
    aux->info = c;
    //*lst ==> l
    aux->prox = *lst;
    *lst = aux;
    return 0;
}

void mostrarPrimeiro(lista * l){
    printf("Nome: %s\n",l->info.nome);
    printf("Idade: %d\n\n",l->info.idade);
}

void mostrarTodos(lista * l){
    lista * aux=l;
    while(aux!=NULL){
        printf("Nome: %s\n", aux->info.nome);
        printf("Idade: %d\n", aux->info.idade);
        aux = aux->prox;
    }
}

int eliminar(lista ** lst, int n){
    int i;
    lista * aux = *lst;
    lista * excluir;

    if((n == 0) && (aux != NULL)){ // eliminar raiz da lista 
        *lst = aux->prox;
        free(aux);
        return 0;
    }else{
        for(i = 0; i < n-1; ++i){ // andar até antes do elemento que vamos eliminar 
            aux = aux->prox;
            if(aux == NULL) break;
        }
        if((aux != NULL) && (aux->prox != NULL)){
            excluir = aux->prox; // proximo elemento é o escolhido 
            aux->prox = excluir->prox; // reajeitar ponteiros anteriores
            free(excluir); // eliminar elemento escolhido 
            return 0;
        }
        return FAILED;
    }
}

void destruir(lista ** lst){
    lista * aux = *lst;
    lista * excluir;

    while(aux!=NULL){
        excluir = aux;
        aux = aux->prox;
        free(excluir);
    }

    *lst = NULL;
}

void mostrarN(lista * l, int n){ 
    // se n == 0, mostrar o primeiro
    // se n == 1, mostrar o segundo
    // ...
    lista * aux = l;
    int i = 0;

    while(aux!=NULL){
        if(i==n){
            printf("Nome: %s\n",aux->info.nome);
            printf("Idade: %d\n",aux->info.idade);
        }
        aux = aux->prox;
        i+=1;
    }
}

int inserirPosicao(lista ** lst, int n, cliente c){
    lista * aux = *lst;
    lista * aux2;
    int i=0;
    if(n==0) return inserirInicio(lst, c); 

    for(i = 0; i < n-1; ++i){
        if(aux->prox == NULL){
            printf("Posicao invalida.\n");
            return FAILED;
        }
        aux = aux->prox;
    }

    aux2 = (lista *) calloc(1,sizeof(lista));
    aux2->info = c;
    aux2->prox = aux->prox;
    aux->prox = aux2;
    return 0;
}

cliente* acessar(lista * l, int n){
    int i;
    lista * aux = l;
    for(i = 0; i < n; ++i){
        if(aux==NULL) break;
        aux = aux->prox;
    }
    if(aux!=NULL) return &aux->info;
    return NULL;
}

int buscar(lista * lst, char nome[]){
    int i=0;
    lista * aux = lst;

    while(aux != NULL){
        if(strcmp(nome, aux->info.nome)==0) break;
        aux = aux->prox;
        i++;
    }
    if(aux==NULL) return FAILED;
    return i;
}

int tamanho(lista * lst){
    int i=0;
    lista * aux = lst;
    while(aux!=NULL){
        aux = aux->prox;
        i++;
    }
    return i;
}

int inserirFinal(lista ** lst, cliente c){
    lista * aux = *lst;
    lista * aux2;
    if(aux==NULL){
        return inserirInicio(lst, c);
    }
    while(aux->prox != NULL) {
        aux = aux->prox;
    }
    aux2 = (lista *) calloc(1,sizeof(lista));
    aux2->info = c;
    aux2->prox = aux->prox;
    aux->prox = aux2;
    return 0;
}

void showOptions(){
    printf("1- Inserir no inicio\n");
    printf("2- Inserir na posição\n");
    printf("3- Inserir no final\n");
    printf("4- Acessar cliente\n");
    printf("5- Eliminar\n");
    printf("6- Listar\n");
    printf("7- Buscar\n");
    printf("8- Inverter\n"); 
    printf("9- Adicionar clientes por ordem de idade\n");
    printf("10- Sair\n");
}

void populateCliente(cliente* client){
    printf("Insira o nome do Cliente \n");
    fflush(stdin);
    scanf("%s", &client->nome);

    printf("Insira a idade de %s:\n", client->nome);
    fflush(stdin);
    scanf("%d", &client->idade);
    printf("Registrado com sucesso\n");
}

int showClient(cliente* client){
    if(client == NULL){
        printf("Cliente não existe\n");
        return FAILED;
    }
    printf("Nome: %s\n", client->nome);
    printf("Idade: %d\n", client->idade);
    return 0;
}

size_t getPosFromUser(){
    size_t pos;
    printf("Insira a posicao: ");
    fflush(stdin);
    scanf("%d", &pos);
    return pos;
}


void populateList(lista* list, size_t n){
    cliente client;
    cliente* p_client = &client;
    unsigned i;
    for(i = 0; i < n; ++i){
        populateCliente(p_client);
        inserirFinal(&list, client);
    }
}

int definirTamanho(lista* p_list){
    size_t numNewClients;
    printf("Insira o numero de clientes a serem adicionados:\n");
    fflush(stdin);
    scanf("%d", &numNewClients);
    p_list = (lista*)calloc(numNewClients, sizeof(cliente));
    return numNewClients; 
}

void orderByIdade(lista* list){
    lista listaToBeAdded; 
    lista* p_listaToBeAdded = &listaToBeAdded;
    size_t numNewClients = 0;
    populateList(p_listaToBeAdded, numNewClients);
}

void pushInAgeOrder(lista** lst, cliente client) {
    // Crie uma função que recebe uma lista e adiciona novos clientes em ordem  
    // crescente de idade 
    lista* aux = *lst;
    lista* next;
    lista* newL;

    if (aux == NULL) {
        newL = (lista*) calloc(1,sizeof(lista));
        newL->info = client;
        newL->prox = aux;
        *lst = newL;
        return;
    }
    if (client.idade <= aux->info.idade) {
        newL = (lista*) calloc(1,sizeof(lista));
        newL->info = client;
        newL->prox = aux;
        *lst = newL;
        return;
    }
    next= aux->prox;
    while (next != NULL) {
        if (client.idade <= next->info.idade) {
            newL = (lista*) calloc(1,sizeof(lista));
            newL->info = client;
            newL->prox = next;
            aux->prox = newL;
            return;
        } else {
            aux = aux->prox;
            newL = aux->prox;
        }
    }

    newL = (lista*) calloc(1,sizeof(lista));
    newL->info = client;
    newL->prox = NULL;
    aux->prox = newL;
}


int invertList(lista** list){
    // Crie uma função que recebe uma lista e inverte ela (apenas mudando os ponteiros 
    lista* prev = NULL;
    lista* actual = *list; 
    lista* next = NULL;
    while(actual != NULL){
        next = actual->prox;
        actual->prox = prev; 
        prev = actual; 
        actual = next;
    }
    *list = prev;
    return 0;
}

int main(void){
    enum options{ // The exit option is not necessary
        UNSHIFT = 1, SPLICE, CONCAT, ACCESS, ELIMINATE, LIST, SEARCH, INVERT, PUSH_AGE_ORDER
    };

    lista listaAux;
    lista * p_list = &listaAux;
    cliente clienteAux;
    cliente * p_cliente = &clienteAux;

    lista listaAux2;
    lista* p_listaAux2 = &listaAux2;

    int option;
    size_t size;
    size_t pos;
    char idade;
    char nome[BUFFER_SIZE];

    inicializar(&p_list);

    // menu segment
    for(;;){
        showOptions();
        scanf("%d", &option);
        fflush(stdin);


        switch(option){
            case UNSHIFT: 
                populateCliente(p_cliente);
                inserirInicio(&p_list, clienteAux);
                printf("Inserido com sucesso\n");
                break;
            case SPLICE:
                populateCliente(p_cliente);  
                pos = getPosFromUser();
                if(inserirPosicao(&p_list, pos, clienteAux) == 0)
                    printf("%s inserido com sucesso na posicao %d.\n", clienteAux.nome, pos);
                break;
            case CONCAT:
                populateCliente(p_cliente);  
                if(inserirFinal(&p_list, clienteAux) == 0)
                    printf("%s inserido com sucesso no final da lista.\n", clienteAux.nome);
                break;
            case ACCESS:
                pos = getPosFromUser();
                showClient(acessar(p_list, pos));
                break;
            case ELIMINATE:
                pos = getPosFromUser();
                if(eliminar(&p_list, pos) == 0)
                    printf("Posicao %d eliminada com sucesso\n", pos);
                break;
            case LIST:
                mostrarTodos(p_list);
                break;
            case SEARCH:
                printf("Insira um nome a ser procurado: \n");
                fflush(stdin);
                scanf("%s", nome);
                showClient(acessar(p_list, buscar(p_list, nome)));
                break;
            case INVERT: 
                if(invertList(&p_list) == 0)
                    printf("Invertido com sucesso\n");
                break;
            case PUSH_AGE_ORDER: 
                populateCliente(p_cliente);
                pushInAgeOrder(&p_list, clienteAux);

                break; 
            default:
                return 0;
        }
    }
    return 0;
}



