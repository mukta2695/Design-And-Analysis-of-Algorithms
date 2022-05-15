#include <stdio.h>
#include <string.h>
#define inf 99999

int min(int a, int b){
    return (a>b) ? b:a;
}
int get_index(char places[11][100],char place[100]){
    int index=99999;
    for (int i = 0; i <11; i++){
        int compare=strcmp(places[i], place);
        if(compare==0){
            index=i;
        }
    }
    return index;
}
void floyd_algo(int map[11][11],char places[11][100]){
    int D[11][11];

    for(int i=0;i<11;i++){
        for(int j=0;j<11;j++){
            D[i][j]=map[i][j];
        }
    }

    for(int k=0;k<11;k++){
        for(int i=0;i<11;i++){
            for(int j=0;j<11;j++){
                D[i][j]=min(D[i][k] + D[k][j],D[i][j]);
            }
        }
    }
   
   /*
   //This code is to display the final D matrix. Uncomment the code to see the matrix values.

    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            if (D[i][j] == inf)
                printf("%s\t", "inf");
            else
                printf ("%d\t", D[i][j]);
        }
        printf("\n");
    }*/

    char place1[100]="New York City";
    char place2[100]="Toronto";
    int index1=get_index(places,place1);
    int index2=get_index(places,place2);

    //printf("%d",NY_index);
    

    printf("The shortest path between New York City to Toronto is %d miles.", D[index1][index2]);

}

int main(){
    char places[11][100]={"Toronto", "Kingston","Montreal","Buffalo","Rochester","Syracuse","Albany",
                         "Binghamton","Scranton","New York City","Allentown"};
    

    int map_graph[11][11]={{0,180,inf,100,inf,inf,inf,inf,inf,inf,inf},
                           {180,0,160,inf,inf,65,inf,inf,inf,inf,inf},
                           {inf,160,0,inf,inf,inf,130,inf,inf,inf,inf},
                           {100,inf,inf,0,60,inf,inf,inf,inf,inf,inf},
                           {inf,inf,inf,60,0,70,inf,inf,inf,inf,inf},
                           {inf,65,inf,inf,70,0,100,70,inf,inf,inf},
                           {inf,inf,130,inf,inf,100,0,inf,inf,140,inf},
                           {inf,inf,inf,inf,inf,70,inf,0,60,180,inf},
                           {inf,inf,inf,inf,inf,inf,inf,60,0,100,65},
                           {inf,inf,inf,inf,inf,inf,140,180,100,0,70},
                           {inf,inf,inf,inf,inf,inf,inf,inf,65,70,0}
                           };
    floyd_algo(map_graph,places);
            
    return 0;

}
