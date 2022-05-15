#include <stdio.h>
#include <string.h>

int max(int a, int b){
    return (a<b) ? b:a;
}

void print_lcs(char string1[100], char string2[100],int LCS[strlen(string1)+1][strlen(string2)+1]){
    
    int len1=strlen(string1);
    int len2=strlen(string2);
    int ind=LCS[len1][len2];
    char lcs_string[LCS[len1][len2]];
    int a=len1;
    int b=len2;
    while (a>0 && b>0){
        if (string1[a-1] == string2[b-1]){
            lcs_string[ind-1] = string2[b-1]; 
            a--;
            b--;
            ind--; 
            }
        else if (LCS[a-1][b] <= LCS[a][b-1]){
            b--;
        }
        else{
            a--;
        }
    }
    printf("Sequence is: %s", lcs_string);


}

void lcs(char string1[100], char string2[100]){

    int len1=strlen(string1);
    int len2=strlen(string2);
    int LCS[len1+1][len2+1];

    for(int i=0; i<=len1;i++){
        LCS[i][0]=0;
    }
    for(int j=0; j<=len2;j++){
        LCS[0][j]=0;
    }
    
    for(int i=1; i<=len1;i++){
        for(int j=1;j<=len2;j++){
            if(string1[i-1]==string2[j-1]){
                LCS[i][j]=1+LCS[i-1][j-1];
            }
            else{
                LCS[i][j]=max(LCS[i-1][j],LCS[i][j-1]);
            }
        }
    }

    printf("LCS length is: %d\n", LCS[len1][len2]);

    print_lcs(string1, string2,LCS);

    
}

void main(){
    char string1[] = "6541254939322816220209974565477289648317";
    char string2[] = "3142522751761601737419090933147067701840";
    
    lcs(string1,string2);
}