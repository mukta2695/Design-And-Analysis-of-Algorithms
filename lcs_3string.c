#include <stdio.h>
#include <string.h>

int max(int a, int b){
    return (a<b) ? b:a;
}

void print_lcs(char string1[100], char string2[100],char string3[100],int LCS[strlen(string1)+1][strlen(string2)+1][strlen(string3)+1]){
    
    int len1=strlen(string1);
    int len2=strlen(string2);
    int len3=strlen(string3);
    int ind=LCS[len1][len2][len3];
    char lcs_string[LCS[len1][len2][len3]+1];
    lcs_string[ind]='\0';
    int a=len1;
    int b=len2;
    int c=len3;
    while (a>0 && b>0 && c>0){
        if (string1[a-1] == string2[b-1] && string1[a-1] == string3[c-1]){
            lcs_string[ind-1] = string2[b-1]; 
            a--;
            b--;
            c--;
            ind--; 
            }
        else if (LCS[a-1][b][c] <= LCS[a][b-1][c] && LCS[a][b][c-1] <= LCS[a][b-1][c]){
            b--;
        }
        else if(LCS[a-1][b][c] < LCS[a][b][c-1] && LCS[a][b-1][c] < LCS[a][b][c-1]){
            c--;
        }
        else{
            a--;
        }
    }
    printf("Sequence is: %s", lcs_string);


}

void lcs(char string1[100], char string2[100],char string3[100]){

    int len1=strlen(string1);
    int len2=strlen(string2);
    int len3=strlen(string3);

    int LCS[len1+1][len2+1][len3+1];

    for(int i=0; i<=len1;i++){
        for(int j=0;j<=len2;j++){
            for(int k=0; k<=len3; k++){
                if (i == 0 || j == 0||k==0){
                    LCS[i][j][k] = 0;
                }
                else if(string1[i-1]==string2[j-1] && string1[i-1]==string3[k-1]){
                    LCS[i][j][k]=1+LCS[i-1][j-1][k-1];
                }
                else{
                    LCS[i][j][k]=max(max(LCS[i-1][j][k],LCS[i][j-1][k]),LCS[i][j][k-1]);
                }
            }
        }
    }

    printf("LCS length is: %d\n", LCS[len1][len2][len3]);

    print_lcs(string1, string2,string3, LCS);

    
}

void main(){
    char string1[] = "6541254939322816220209974565477289648317";
    char string2[] = "3142522751761601737419090933147067701840";
    char string3[] = "28070305612903542595135701601 62463275171";
    lcs(string1,string2,string3);
}