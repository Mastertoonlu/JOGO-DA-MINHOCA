#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

//constantes
#define ALTURA 10
#define LARGURA 10
#define POSICAO 5

//inicializa fun��o menu
int menu(void);

//apresenta��o do jogo
void preview(char *prt);

//A��o de colocar obstaculo
void colocarObstaculo(char tabuleiro[ALTURA][LARGURA]);

//A��o para selecionar posi��o inicial
void selecinarPosicaoInicial(char tabuleiro[ALTURA][LARGURA]);

//A��o para o restante do corpo para a minhoca
void Criarcorpo(char tabuleiro[ALTURA][LARGURA]);

//A��o de reiniciar tabuleiro
void reiniciarTabuleiro(char *prt);

//verifica se a minhoca j� foi inicializada
void verificaminhoca(char tabuleiro[ALTURA][LARGURA]);

//Start game
void jogo(char tabuleiro[ALTURA][LARGURA]);

//detecta quantos '*' est� ao lado da calda
int finaldocorpo(char tabuleiro[ALTURA][LARGURA],int x,int y);

void substituiCalda(char tabuleiro[ALTURA][LARGURA],int x,int y);

int CabecaAnda(char tabuleiro[ALTURA][LARGURA],int x,int y,char WASD, int movimento, int k);

int casasVisitadas(char tabuleiro[ALTURA][LARGURA]);

int main(void)
{
    int selecao = -1;
    char tabuleiro[ALTURA][LARGURA];

    setlocale(LC_ALL, "Portuguese");

//preenche tabuleiro com *
    for(int i=0; i<ALTURA; i++)
    {
        for(int j=0; j<LARGURA; j++)
        {
            tabuleiro[i][j]='~';
        }
    }


//exibe menu enquanto usu�rio n�o selecionar a Op�ao 0
    while(selecao != 0)
    {
        system("cls");
        preview(&tabuleiro[0][0]);
        selecao = menu();
        switch ( selecao )
        {

        case 1 :
            colocarObstaculo(tabuleiro);
            break;
        case 2 :
            selecinarPosicaoInicial(tabuleiro);

            Criarcorpo(tabuleiro);

            break;
        case 3 :
            verificaminhoca(tabuleiro);

            jogo(tabuleiro);
            break;
        case 4 :
            reiniciarTabuleiro(&tabuleiro[0][0]);
            break;
        }
    }
    return 0;
}




//Fun��o exibi��o do tabuleiro
void preview(char *prt)
{
    int c=0;
    printf("    0  1  2  3  4  5  6  7  8  9\n");
    for(int i=0; i<ALTURA*LARGURA; i++)
    {
        if(i%10 == 0)
        {
            printf(" \n %i", c);
            c++;
        }
        printf("  %c",prt[i]);


    }
}


//fun��o de interface para exibi�ao do menu
int menu(void)
{
    int selecao;

    printf("\n\nEscolha uma das op��es abaixo\n");
    printf("1 -- OBST�CULOS\n");
    printf("2 -- POSI��O INICIAL DA MINHOCA\n");
    printf("3 -- JOGUE AGORA\n");
    printf("4 -- REINICIAR TABULEIRO\n");
    printf("SAIR 0\n");
    scanf("%d",&selecao);
    return selecao;
}


//Fun��o obstaculo
void colocarObstaculo(char tabuleiro[ALTURA][LARGURA])
{
    int x,y;

    printf("Digite a posi��o do obst�culo que deseja adicionar (ex: 5 7)\n");
    scanf("%i %i", &x,&y);

    while(tabuleiro[x][y]=='X' || tabuleiro[x][y]=='C' || x>=ALTURA || x<0 || y>=LARGURA || y<0)
    {

        system("cls");
        preview(&tabuleiro[0][0]);
        printf("\n\nDigite uma posi��o v�lida e sem obstaculos (ex: 5 7)\n");
        scanf("%i %i", &x,&y);
    }
    tabuleiro[x][y] = 'X';
}


//Fun��o para selecionar posi��o inicial da minhoca
void selecinarPosicaoInicial(char tabuleiro[ALTURA][LARGURA])
{
    char *ponteiro;
    int x,y;

    ponteiro = &tabuleiro[0][0];

    for(int i=0; i<ALTURA*LARGURA; i++) //apaga a minhoca anterior se houver
    {
        if(ponteiro[i]=='C' || ponteiro[i]=='*' ||ponteiro[i]=='.')
        {
            ponteiro[i]='~';
        }
    }
    printf("Digite a posi��o inicial da minhoca (ex: 5 7)\n");
    scanf("%i %i", &x,&y);
    while(tabuleiro[x][y]=='X' || x>=ALTURA || x<0 || y>=LARGURA || y<0)
    {

        system("cls");
        preview(&tabuleiro[0][0]);
        printf("\n\nDigite uma posi��o v�lida e sem obstaculos (ex: 5 7)\n");
        scanf("%i %i", &x,&y);
    }
    tabuleiro[x][y] = 'C';

    system("cls");
    preview(&tabuleiro[0][0]);

}


//Fun��o reiniciar tabuleiro
void reiniciarTabuleiro(char *prt)
{

    for(int i=0; i<ALTURA*LARGURA; i++)
    {
        prt[i]='~';
    }

}

//Insere o restante do corpo da minhoca
void Criarcorpo(char tabuleiro[ALTURA][LARGURA])
{

    int x,y;
    int aux,auxy;



    for(int i=0; i<ALTURA; i++)
    {
        for(int j=0; j<LARGURA; j++)
        {
            if(tabuleiro[i][j]=='C')
            {
                aux=i;    //procura c
                auxy=j;
            }
        }
    }
    for(int k=1; k<=3; k++)
    {
        printf("\n\nDigite a posi��o %i do corpo da minhoca\n",k);
        scanf("%i %i", &x,&y);

        while(tabuleiro[x][y]=='X'|| tabuleiro[x][y]=='C' || tabuleiro[x][y]=='*' || x>=ALTURA || x<0 || y>=LARGURA || y<0 || (x!=aux && y!=auxy) || x>(aux+1) || x<(aux-1) || y<(auxy-1) || y>(auxy+1))
        {

            system("cls");
            preview(&tabuleiro[0][0]);
            printf("\n\nDigite uma posi��o v�lida e sem obstaculos para uma minhoca\n");
            scanf("%i %i", &x,&y);
        }
        tabuleiro[x][y] = '*';

        system("cls");
        preview(&tabuleiro[0][0]);

        aux = x;
        auxy = y;
    }




    printf("\nDigite a posi��o da ponta da cauda\n");
    scanf("%i %i", &x,&y);
    while(tabuleiro[x][y]=='X' || tabuleiro[x][y]=='C' || tabuleiro[x][y]=='*' || x>=ALTURA || x<0 || y>=LARGURA || y<0|| (x!=aux && y!=auxy) || x>(aux+1) || x<(aux-1) || y<(auxy-1) || y>(auxy+1))
    {

        system("cls");
        preview(&tabuleiro[0][0]);
        printf("\n\nDigite uma posi��o v�lida e sem obstaculos para uma minhoca\n");
        scanf("%i %i", &x,&y);
    }
    tabuleiro[x][y] = '.';

}


void jogo(char tabuleiro[ALTURA][LARGURA])
{

    system("cls");
    preview(&tabuleiro[0][0]);
    int movimento = 0;
    char WASD;
    int corpo[99];
    int aux, auxy;
    int x, y;
    int acu, contador=1;//acumulador;contador j� � 1 por causa da posi��o inicial da cabe�a

    //rastreio de casas utilizadas; quando passar por uma casa nova o corpo receber� 1
    for(int q=0; q<=99; q++)
    {

        {
            corpo[q]=0;//nunca passou por aqui
        }
    }


    printf("\n\nDigite quantos movimentos deseja que a minhoca  fa�a?\n");

    scanf("%d",&movimento);

    system("cls");
    preview(&tabuleiro[0][0]);
    printf("\n\nUse W, A, S, D para movimentos para cima, esquerda, baixo e direita,respectivamente. Em seguida digite ENTER para que ocorra o movimento\n");

    scanf("%c",&WASD);


    for(int k=0; k<movimento; k++)
    {

        while(WASD !='w' && WASD!='a' && WASD !='s' && WASD !='d' )
        {

            printf("\n\nDigite uma dire��o v�lida\n");
            scanf("%c",&WASD);
        }

        for(int i=0; i<ALTURA; i++)
        {
            for(int j=0; j<LARGURA; j++)
            {
                if(tabuleiro[i][j]=='.')
                {
                    aux=i;    //procura '.'
                    auxy=j;
                }
            }
        }

        acu = finaldocorpo(tabuleiro,aux,auxy);// identifica onde est� o �ltimo '*' do corpo

        for(int i=0; i<ALTURA; i++)
        {
            for(int j=0; j<LARGURA; j++)
            {
                if(tabuleiro[i][j]=='C')
                {
                    x=i;    //procura 'C'
                    y=j;
                    break;
                }
            }
        }

        if(acu!=1)//houver mais de '*'do corpo ao lado do .
        {


            for(int i=x-1; i<x+2; i++) //todos os '*' ao redos de C(cabe�a) recebem um valor inv�lido
            {
                for(int j=y-1; j<y+2; j++)
                {
                    if(tabuleiro[i][j]=='*')
                    {
                        tabuleiro[i][j]='F';
                    }
                }
            }


        }


        substituiCalda(tabuleiro,aux,auxy);//primeiro subtitui a calda para depois andar com a cabe�a
        for(int i=0; i<ALTURA; i++)
        {
            for(int j=0; j<LARGURA; j++)
            {
                if(tabuleiro[i][j]=='F')
                {
                    tabuleiro[i][j]='*';   //recebe os valores valodos novamente
                }
            }
        }



        k = CabecaAnda(tabuleiro,x,y,WASD,movimento,k);//agora sim a cabe�a anda

        if(k!=movimento)
        {

            corpo[x*10+y] = 1;
        }


        system("cls");
        preview(&tabuleiro[0][0]);


        scanf("%c",&WASD);


    }

    for(int i=0; i<100; i++)
    {
        if(corpo[i]==1)
        {
            contador++;
        }
    }
    if(contador != 1)
    {
        printf("\n\nA minhoca passou por %i casas, portanto ela n�o passou por %i casas\n\n",contador,100- contador);
        system("pause");
    }



}

int finaldocorpo(char tabuleiro[ALTURA][LARGURA],int x,int y)
{

    int acu=0;

    if(tabuleiro[x][y+1]=='*')
    {
        acu++;   //direita
    }
    if(tabuleiro[x][y-1]=='*')
    {
        acu++;   //esquerda
    }
    if(tabuleiro[x+1][y]=='*')
    {
        acu++;   //baixo
    }
    if(tabuleiro[x-1][y]=='*')
    {
        acu++;   //cima
    }

    return acu;
}


void substituiCalda(char tabuleiro[ALTURA][LARGURA],int x,int y)// a calda entra no ultimo '*' do corpo
{

    if(tabuleiro[x][y+1]=='*')
    {
        tabuleiro[x][y+1]='.';
    }
    if(tabuleiro[x][y-1]=='*')
    {
        tabuleiro[x][y-1]='.';
    }
    if(tabuleiro[x+1][y]=='*')
    {
        tabuleiro[x+1][y]='.';
    }
    if(tabuleiro[x-1][y]=='*')
    {
        tabuleiro[x-1][y]='.';
    }
    tabuleiro[x][y]= '~';//onde era a calda volta a ser o mapa

}


int CabecaAnda(char tabuleiro[ALTURA][LARGURA],int x,int y,char WASD,int movimento,int k)
{

    int fim;

    if(WASD=='w') //cima
    {

        if(tabuleiro[x-1][y]!='~' || (x-1<0))
        {
            printf("Fim de jogo!\n\n     Digite qualquer n�mero para voltar ao menu(ex: 0)");
            scanf("%i",&fim);
            return movimento;
        }

        tabuleiro[x][y] = '*';
        tabuleiro[x-1][y] = 'C';

        return k;
    }

    if(WASD=='a') //esquerda
    {
        if(tabuleiro[x][y-1]!='~' || (y-1<0))
        {
            printf("Fim de jogo!\n\n)");
            system("pause");
            return movimento;
        }

        tabuleiro[x][y] = '*';
        tabuleiro[x][y-1] = 'C';
        return k;
    }

    if(WASD=='s') //baixo
    {

        if(tabuleiro[x+1][y]!='~' || (x+1>9))
        {
            printf("Fim de jogo!\n\n");
            system("pause");
            return movimento;
        }

        tabuleiro[x][y] = '*';
        tabuleiro[x+1][y] = 'C';

        return k;
    }

    if(WASD=='d') //direita
    {

        if(tabuleiro[x][y+1]!='~' || (y+1>9))
        {
            printf("Fim de jogo!\n\n");
            system("pause");
            return movimento;
        }

        tabuleiro[x][y] = '*';
        tabuleiro[x][y+1] = 'C';
        return k;
    }

    return movimento;
}


void verificaminhoca(char tabuleiro[ALTURA][LARGURA])
{

    int verifica=0;

    for(int i=0; i<ALTURA; i++)
    {
        for(int j=0; j<LARGURA; j++)
        {
            if(tabuleiro[i][j]=='*')
            {
                verifica ++;

            }
        }
    }


    if(verifica != 3)//significa que voce bateu em um obstaculo e a cobra est� deformada
    {
        selecinarPosicaoInicial(tabuleiro);

        Criarcorpo(tabuleiro);
    }

}
// professora d� um CTRL C na msg abaixo para facilitar a posic�ao inicial da minhoca
// 8 3 8 2 7 2 7 1 8 1
