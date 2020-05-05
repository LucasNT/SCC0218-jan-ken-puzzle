/**
 * Lucas Nobuyuki Takahashi
 * 10295670
 */
#include <unordered_map>
#include <cstdio>
#include <cstdlib>

using namespace std;

/**
 * struct que representa o tabuleiro em que ira ocorrer o jogo.
 *
 * mapa variável de 64 bits que representa o mapa.
 * linha variável que guarda quantas linhas tem o mapa.
 * coluna variável que guarda quantas colunas tem o mapa.
 * qtdPeca variável que guarda quantas peças tem no mapa.
 */
typedef struct tabuleiro tabuleiro_t;

/**
 * struct que guarda coordenadas do tabuleiro.
 * usada para pegar as peças do tabuleiro como também para definir uma peça na posição
 * (l,c);
 *
 * l variável que guarda o valor da linha.
 * c variável que guarda o valor da coluna.
 * qtdPeca variável que recebe qual peça está naquela coordenada
 */
typedef struct coord coordenada_t;

/**
 * struct que guarda as soluções do jogo atual.
 *
 * vec vetor que irá armazenar todas as soluções do jogo.
 * qtdElem indica quantos elementos existe no vec.
 * sol marca quantas soluções foram adicionadas, independente de repetição.
 */
typedef struct solucao solucao_t;

struct tabuleiro{
    uint64_t mapa;
    int linha;
    int coluna;
    int qtdPeca;
};

struct coord{
    int l;
    int c;
    int peca;
};

struct solucao{
    coordenada_t *vec;
    int qtdElem;
    uint64_t sol;
};

/**
 * aloca e inicializa as variáveis da struct tabuleiro.
 *
 * Retorno:
 *  um ponteiro para o tabuleiro alocado.
 */
tabuleiro_t *cria_tabuleiro();

/**
 * pega uma peça que será a primeira da busca usada, sempre procura de linha e linha,
 * começando na linha 0 e depois para a linha 1.
 *
 * Parâmetros:
 *  tab ponteiro do tabuleiro onde será usado o algoritmo.
 *  coord ponteiro que vai receber a coordenada e a peça.
 */
void getPrimeiraPeca_tabuleiro(tabuleiro_t*tab , coordenada_t *coord);

/**
 * Pega uma peça do tabuleiro, salva na propria coordenada passada e retorna a peça também.
 *
 * Parâmetros:
 *  tab ponteiro do tabuleiro onde será usado o algoritmo.
 *  coord ponteiro que vai conter as coordenadas da peça, e a peça.
 * Retorno:
 *  a peça da coordenada passada.Caso seja uma peça inacessível irá retornar -1.
 */
int getPeca_tabuleiro(tabuleiro_t*tab , coordenada_t *coord);

/**
 * Retorna um vetor de quatros posições que contem as coordenadas e as peças adjacentes
 * a peça passada.
 * caso haja uma posição adjacente ela será inclusa no vetor com l ou c negativos ou
 * acima do tamanho do tabuleiro  e peça igual a -1.
 *
 * Parâmetros:
 *  tab ponteiro do tabuleiro onde será usado o algoritmo.
 *  coord coordenada em que será usada a busca
 *
 * Retorno:
 *  Vetor de 4 posições contendo as coordenadas e peças da posições adjacentes a
 *  coordenada passada.
 */
coordenada_t *getPecasAdj_tabuleiro(tabuleiro_t *tab , coordenada_t *coord , coordenada_t *vecAdj);

/**
 * define uma peça no tabuleiro.
 *
 * Parâmetros:
 *  tab ponteiro do tabuleiro onde será usado o algoritmo.
 */
void setPeca_tabuleiro(tabuleiro_t *tab , coordenada_t *coord);

/**
 * Faz a parte da programação dinâmica divida em duas partes, uma em que é passada o tabuleiro
 * e as soluções e essa que recebe o tabuleiro e as soluções mais a tabela da programação
 * dinâmica
 *
 * Parâmetros:
 *  t ponteiro do tabuleiro onde será usado o algoritmo.
 *  sol ponteiro que contém as soluções encontradas pelo programa.
 *  tabela é a tabela usada pela programação dinâmica.
 *
 * Retorno:
 *  retorna a quantidade de soluções possíveis para um estado do mapa.
 */
uint64_t programacao_dinamica_recursivo(tabuleiro_t *t , solucao_t *sol , unordered_map<uint64_t , uint64_t> &tabela);

/**
 * Faz a parte da programação dinâmica divida em duas partes, essa  em que é passada o tabuleiro
 * e as soluções e uma que recebe o tabuleiro e as soluções mais a tabela da programação
 * dinâmica
 *
 * Parâmetros:
 *  t ponteiro do tabuleiro onde será usado o algoritmo.
 *  sol ponteiro que contém as soluções encontradas pelo programa.
 */
void programacao_dinamica(tabuleiro_t *t , solucao_t *sol);

/**
 * Faz a DFS para encotnrar ilhas no tabuleiro.
 *
 * Parâmetros:
 *  tab ponteiro do tabuleiro que será usado o algoritmo.
 *  coord coordenada onde está a DFS.
 */
void tem_ilhas_recursivo(tabuleiro_t *tab , coordenada_t *coord);

/**
 * Define onde a DFS irá começar.
 *
 * Parâmetros:
 *  tab ponteiro do tabuleiro onde será usado o algoritmo.
 *
 * Retorno:
 *  valor booleano se for true tem ilhas, se não não apresenta ilhas.
 */
bool tem_ilhas(tabuleiro_t *tab);

/**
 * Libera a memória usada pelo tabuleiro.
 *
 * Parâmetros:
 *  t ponteiro para um ponteiro que aponta para um tabuleiro.
 */
void libera_tabuleiro(tabuleiro_t **t);

/**
 * Aloca a memória usada por uma solução.
 *
 * Retorno:
 *  ponteiro para a memória alocada.
 */
solucao_t *cria_Solucao();

/**
 * adiciona uma solução ao vetor de soluções.
 * incrementa as duas variaveis que indica a quantidade de soluções adicionadas e
 * o tamanho do vetor.
 *
 * Parâmetros:
 *  coord coordenada da peça vencedora do jogo.
 *  sol ponteiro para a estrutura que armazena as soluções.
 */
void addSol_solucao(coordenada_t* coord,solucao_t *sol);

/**
 * adiciona a quantidade de soluções, util para caso você tenha como armazenar a quantidade
 * de soluções de um estado atual do mapa.
 *
 * Parâmetros:
 *  qtdSol indica a quantidade  que vai ser somada.
 *  sol ponteiro para a estrutura que armazena as soluções.
 */
void addQtdSol_solucao(uint64_t qtdSol, solucao_t *sol);

/**
 * libera a memória ocupada pelas soluções.
 *
 * Parâmetros:
 *  sol ponteiro para um ponteiro que aponta para a memória que vai ser liberada.
 */
void libera_solucao(solucao_t **sol);

/**
 * função para comparar duas coordenadas.
 *
 * Parâmetros:
 *  c1 ponteiro para a primeira coordenada
 *  c2 ponteiro para a segunda  coordenada
 *
 * Retorno:
 *  a função retorna um inteiro menor , igual ou maior que 0 se c1 for menor , igual ou
 *  maior que c2 respectivamente.
 */
int compareCoordenadas(const coordenada_t *c1 , const coordenada_t *c2);


solucao_t *cria_Solucao(){
    solucao_t *sol = (solucao_t*) malloc(sizeof(solucao_t));
    sol->qtdElem = 0;
    sol->sol = 0;
    sol->vec = 0;
    return sol;
}

void addSol_solucao(coordenada_t* coord , solucao_t *sol){
    sol->qtdElem++;
    sol->sol++;
    sol->vec = (coordenada_t*) realloc(sol->vec , sizeof(coordenada_t) * sol->qtdElem);
    sol->vec[sol->qtdElem-1] = *coord;
}

void addQtdSol_solucao(uint64_t qtdSol, solucao_t *sol){
    sol->sol += qtdSol;
}

void libera_solucao(solucao_t **sol){
    free((*sol)->vec);
    free(*sol);
    *sol = NULL;
}

tabuleiro_t *cria_tabuleiro(){
    tabuleiro_t *tab = (tabuleiro_t*) malloc(sizeof(tabuleiro_t));
    tab->linha = tab->coluna = tab->qtdPeca = 0;
    tab->mapa = 0;
    return tab;
}

int getPeca_tabuleiro(tabuleiro_t*tab , coordenada_t *coord){
    if(coord->l  >= tab->linha || coord->c >=  tab->coluna || coord->c < 0 || coord->l < 0){
        coord->peca = -1;
        return 0 ;
    }
    coord->peca = (tab->mapa >> ((coord->l * tab->coluna + coord->c) * 2)) & 3;
    return coord->peca;
}

void getPrimeiraPeca_tabuleiro(tabuleiro_t*tab , coordenada_t *coord){
    uint64_t mapaAux = tab->mapa;
    int cont = 0;
    while((mapaAux & 3) == 0){
        cont++;
        mapaAux = mapaAux >> 2;
    }
    coord->c = cont % tab->coluna;
    coord->l = cont / tab->coluna;
    coord->peca = mapaAux&3;
}

void setPeca_tabuleiro(tabuleiro_t *tab , coordenada_t *coord){
    if(coord->l  >= tab->linha || coord->c >=  tab->coluna || coord->c < 0 || coord->l < 0)
        return;
    if( (tab->mapa>>((coord->l * tab->coluna + coord->c) * 2) & 3)  != 0 && coord->peca == 0){
        tab->qtdPeca--;
    }else if((tab->mapa>>((coord->l * tab->coluna + coord->c) * 2) & 3) == 0 && coord->peca != 0){
        tab->qtdPeca++;
    }
    tab->mapa = tab->mapa & (~(((uint64_t)3) << ((coord->l * tab->coluna + coord->c) * 2)));
    tab->mapa = tab->mapa | (((uint64_t)coord->peca) << ((coord->l * tab->coluna + coord->c) * 2));
}

coordenada_t *getPecasAdj_tabuleiro(tabuleiro_t *tab , coordenada_t *coord , coordenada_t *vecAdj){
    vecAdj[0].c = coord->c;
    vecAdj[0].l = coord->l-1;
    getPeca_tabuleiro(tab,vecAdj);

    vecAdj[1].c = coord->c+1;
    vecAdj[1].l = coord->l;
    getPeca_tabuleiro(tab,vecAdj+1);

    vecAdj[2].c = coord->c;
    vecAdj[2].l = coord->l+1;
    getPeca_tabuleiro(tab,vecAdj+2);

    vecAdj[3].c = coord->c-1;
    vecAdj[3].l = coord->l;
    getPeca_tabuleiro(tab,vecAdj+3);

    return vecAdj;
}

void libera_tabuleiro(tabuleiro_t **t){
    free(*t);
    *t = NULL;
}

void tem_ilhas_recursivo(tabuleiro_t *tab , coordenada_t *coord){
    if(coord->peca > 0){
        coordenada_t adj[4];
        coord->peca =0;
        setPeca_tabuleiro(tab , coord);
        getPecasAdj_tabuleiro(tab , coord ,adj);
        for(int i = 0 ; i < 4 ; i++){
            tem_ilhas_recursivo(tab,adj+i);
        }
    }
}

bool tem_ilhas(tabuleiro_t *tab){
    /*
     * a função cria uma copia do tabuleiro, e faz a DFS nessa copia, a cada casa com peça
     * visitada ele remove a peça para saber que ja andou por lá, se no final não houver
     * mais peças no tabuleiro então quer dizer que não há ilhas.
     */
    tabuleiro_t tabAUx;
    tabAUx.coluna = tab->coluna;
    tabAUx.linha = tab->linha;
    tabAUx.qtdPeca = tab->qtdPeca;
    tabAUx.mapa = tab->mapa;
    coordenada_t coord;
    getPrimeiraPeca_tabuleiro(&tabAUx , &coord);
    tem_ilhas_recursivo(&tabAUx,&coord);
    bool aux = tabAUx.qtdPeca != 0;
    return aux;
}

uint64_t programacao_dinamica_recursivo(tabuleiro_t *t , solucao_t *sol , unordered_map<uint64_t , uint64_t> &tabela){
    uint64_t contador = 0;
    if(tabela.find(t->mapa) != tabela.end()){// teste para ver se já percorreu esse ramo da árvore
        contador += tabela[t->mapa];
        addQtdSol_solucao(contador , sol);
    }else{
        if(t->qtdPeca > 1){// teste para ver se é uma solução.
            if(tem_ilhas(t)){ // teste para ilhas
                tabela[t->mapa] = 0;
                return 0;
            }
            uint64_t mapaAux = t->mapa; // cria uma mapa aux para iterar mais rapidamente pelo mapa.
            int posi = 0;
            coordenada_t coord;
            while(mapaAux != 0){
                if((mapaAux & 3) != 0){
                    coordenada_t adj[4];
                    coord.c = posi % t->coluna;
                    coord.l = posi / t->coluna;
                    coord.peca = mapaAux & 3;
                    getPecasAdj_tabuleiro(t , &coord , adj);
                    for(int i = 0 ; i < 4 ; i++){
                        if(adj[i].peca > 0 && ((coord.peca % 3 + 1) == adj[i].peca)){
                            // faz a peça atual comer a sua adjacente.
                            int pecaAux = coord.peca;
                            coord.peca = 0;
                            setPeca_tabuleiro(t , &coord);
                            coord.peca = pecaAux;
                            pecaAux = adj[i].peca;
                            adj[i].peca = coord.peca;
                            setPeca_tabuleiro(t, adj + i);
                            adj[i].peca = pecaAux;
                            contador += programacao_dinamica_recursivo(t , sol , tabela);

                            // faz a peça atual vomitar a peça devorada.
                            setPeca_tabuleiro(t , &coord);
                            setPeca_tabuleiro(t , adj +i);
                        }
                    }
                }
                mapaAux = mapaAux>> 2;
                posi++;
            }
        }else{ // salva a solução
            coordenada_t peca;
            getPrimeiraPeca_tabuleiro(t , &peca);
            addSol_solucao(&peca , sol);
            contador++;
        }
    }
    // salva no mapa atual na tabela.
    tabela[t->mapa] = contador;
    return contador;
}

void programacao_dinamica(tabuleiro_t *t, solucao_t *sol){
    unordered_map<uint64_t , uint64_t> *tabela = new unordered_map<uint64_t , uint64_t>();
    programacao_dinamica_recursivo(t , sol , *tabela);
    delete tabela;
}

int compareCoordenadas(const coordenada_t *c1 , const coordenada_t *c2){
    if(c1->l < c2->l){
        return -1;
    }else if (c1->l == c2->l){
        if(c1->c < c2->c){
            return -1;
        }else if(c1->c == c2->c){
            if(c1->peca < c2->peca){
                return -1;
            }else if(c1->peca == c2->peca){
                return 0;
            }
        }
    }
    return 1;
}

int main (int argc , char* argv[]){
    tabuleiro_t *t = cria_tabuleiro();
    solucao_t *s = cria_Solucao();
    scanf("%d%d", &t->linha , &t->coluna);
    coordenada_t coord;
    for(coord.l = 0 ; coord.l < t->linha ; coord.l++){
        for(coord.c = 0 ; coord.c < t->coluna ; coord.c++){
            scanf("%d" , &coord.peca);
            setPeca_tabuleiro(t , &coord);
        }
    }
    programacao_dinamica(t,s);
    std::qsort(s->vec ,s->qtdElem, sizeof(coordenada_t), (int(*)(const void* , const void*))compareCoordenadas);
    printf("%lu\n%d\n" , s->sol , s->qtdElem);
    for(int i = 0 ; i < s->qtdElem ; i++){
        printf("%d %d %d\n" , s->vec[i].l+1 , s->vec[i].c+1 , s->vec[i].peca);
    }
    free(t);
    free(s->vec);
    free(s);
    return 0;
}
