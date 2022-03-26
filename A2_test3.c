//Closest Pair of points

#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#include <time.h>


typedef struct point{
    int x;
    int y;
}point;

void merge_sort(point *array, int low, int high, int corFlag){
    int mid;
    if (low < high)
    {
        mid=(low+high)/2;
        merge_sort(array, low, mid,corFlag);
        merge_sort(array, mid + 1, high,corFlag);
        merge(array, low, high, mid,corFlag);
    }
    else{
        return;
    }
}

void merge(point *array, int low, int high, int mid,int corFlag)
{
    int m=(mid-low)+1;
    int n=high-mid;
    point *left=malloc(m*sizeof(point));
    point *right=malloc(n*sizeof(point));

    for(int i=0; i<m;i++){
        left[i]=array[low+i];
    }

    for (int j=0; j<n; j++){
        right[j]=array[(mid+1)+j];
    }

    int i = 0, j = 0;
    int k = low;
    if(corFlag==0){
        //Sort by x
        while (i < m && j < n) {
        if (left[i].x <= right[j].x) {
            array[k] = left[i++];
        } 
            else {
                array[k] = right[j++];
            }
            k++;
    }
    }
    else{
        //Sort by y
        while (i < m && j < n) {
        if (left[i].y <= right[j].y) {
            array[k] = left[i++];
        } 
            else {
                array[k] = right[j++];
            }
            k++;
    }
    }

    while (i < m) {
    array[k++] = left[i++];
  }

  while (j < n) {
    array[k++] = right[j++];
  }

} 

float baseCase(point p[],point *p1, point *p2, long long length){
    *p1 = p[0];
    *p2 = p[1];
    
    float min = sqrt(((p[0].x - p[1].x)*(p[0].x - p[1].x))+((p[0].y - p[1].y)*(p[0].y - p[1].y)));
    float temp;

    for (long long i=1; i< length; i++)
    {
      for (long long j=i+1; j < length; j++)
      {
        temp = sqrt(((p[i].x - p[j].x)*(p[i].x - p[j].x))+((p[i].y - p[j].y)*(p[i].y - p[j].y)));
        if (temp < min)
        {
          min = temp;
          *p1 = p[i];
          *p2 = p[j];
        }
      }
    }
    return min;
}

float RectanglePoints(point c[],long long pointsInStrip, float stripmin,point *p1, point *p2){
    float temp;
    for(long long i=0; i<pointsInStrip;i++){
        for(long long j=i+1; ((stripmin>=(c[j].y-c[i].y))&&j<pointsInStrip); j++){
            temp=sqrt(((c[i].x - c[j].x)*(c[i].x - c[j].x))+((c[i].y - c[j].y)*(c[i].y - c[j].y)));
            if(temp<stripmin){
                stripmin=temp;
                *p1=c[i];
                *p2=c[j];
            }
        }
    }
    return stripmin;
}

float stripMin(point p[], point *p1, point *p2,long long length, float lrmin,long long mid){
    
    float stripmin=lrmin;
    long long pointsInStrip=0;
    point c[length];

    for(long long i=0; i< length;i++){
        if(lrmin>abs(p[mid].x - p[i].x)){
            pointsInStrip++;
            c[pointsInStrip]=p[i];
        }
    }
    merge_sort(c,0,pointsInStrip,1); //Sort by y
    return RectanglePoints(c,pointsInStrip,stripmin,&p1,&p2);


}

long long findLocation(point p[], long long xcor, long long ycor, long long length){
    for(long long i=0; i<length; i++){
        if(p[i].x==xcor && p[i].y==ycor){
            return i;
        }
    }
    return 0;
}

float ClosestPair(point p[],point *p1, point *p2, long long length){

    float lrmin,globalmin=0;
    int flag=0;
    long long mid=length/2;

    point l1,l2,r1,r2,lr1,lr2;
    
    if(length<4){
        
        float min=baseCase(p,&p1, &p2, length);
        return min;
    }
    float leftmin=ClosestPair(p,&l1,&l2,mid);
    float rightmin=ClosestPair(mid+p,&r1, &r2,length-mid);
    if(leftmin<=rightmin){
        lrmin=leftmin;
        flag=0;
    }
    else{
        lrmin=rightmin;
        flag=1;
    }

    if(flag==1){
        lr1=r1;
        lr2=r2;
    }
    else{
        lr1=l1;
        lr2=l2;
    }
    float strip=stripMin(p, &p1,&p2, length, lrmin,mid);
    if(lrmin<=strip){
        globalmin=lrmin;
        flag=0;
    }
    else{
        globalmin=strip;
        flag=1;
    }
    if(flag==0){
        *p1=lr1;
        *p2=lr2;
    }
    return globalmin;

}

void test_data1(){
    long int n=10000;
    point *t1=malloc(n * sizeof(point));
    point pt1, pt2, pt3, pt4;
    for(int i=0; i<n; i++)
    {
        t1[i].x= n- i;
        t1[i].y= n- i;
    }
    clock_t begin = clock();
    merge_sort(t1, 0, n-1,0);
    float min =ClosestPair(t1,&pt1, &pt2,n);
    long long location1=findLocation(t1,pt1.x, pt1.y,n);
    long long location2=findLocation(t1,pt2.x, pt2.y,n);
    clock_t end = clock();
    printf("Divide & Conquer for the test data 1: \n");
    printf(" %lld %lld %f\n",location1, location2, min);
    printf("Execution time: %f\n", ((double)(end - begin) / CLOCKS_PER_SEC));
    begin = clock();
    min=baseCase(t1,&pt3,&pt4,n);
    location1=findLocation(t1,pt3.x, pt3.y,n);
    location2=findLocation(t1,pt4.x, pt4.y,n);
    end = clock();
    printf("--------------------------------------\n");
    
    printf("Brute Force for the test data 1:\n");
    printf(" %lld %lld %f\n",location1, location2, min);
   printf("Execution time: %f\n", ((double)(end - begin) / CLOCKS_PER_SEC));
    
}

long long findNumLines(FILE *fp) {

  long long numLines = 0;
  char str[100];

  while(!feof(fp)) {
    fgets(str, 100, fp);
    numLines++;
  }
  
  numLines--;//the above increments count even when EOF reached
  
  if(fseek(fp, 0L, SEEK_SET) == EOF) {
    perror("Error while seeking to begining of file");
    exit(0);
  }

  return numLines;
}

int main(int argc, char *argv[]){
    test_data1();

    FILE *inputFile;
    FILE *outputFile;
    char string[100];
    point p[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    long long length=6;
    
    /*if (argc!=3){
        printf("Usage: progname <input_file> <output_file>");
        exit(0);
    }
    inputFile=fopen(argv[1],"r");
    if(inputFile==NULL){
         perror("Error opening input file");
         exit(1);
    }

    long long length = findNumLines(inputFile);*/

    point p1;
	point p2;
    point p3,p4;

    //point *p=malloc(length *sizeof(point));
    point *ind=malloc(length *sizeof(point));
	ind=p;

    /*for(long long i=0; i<length; i++){
        fgets(string, 100, inputFile);
        sscanf(string, "%lld %lld", &(p[i].x),&(p[i]).y );
        sscanf(string, "%lld %lld", &(ind[i].x), &(ind[i].y));
    }
    fclose(inputFile);*/

    /*outputFile=fopen(argv[2],"w");
    if(outputFile==NULL){
        perror("Error opening output file");
        exit(0);
    }*/



    
    clock_t begin = clock();
    merge_sort(p,0,length,0); //Sorting by x
    float min=ClosestPair(p,&p1, &p2, length);
    long long location1=findLocation(p,p1.x, p1.y,length);
    long long location2=findLocation(p,p2.x, p2.y,length);
    clock_t end = clock();
    printf("\nDivide & Conquer\n");
    printf(" %lld %lld %f\n",location1, location2, min);
    printf("\nExecution time: %f\n", ((double)(end - begin) / CLOCKS_PER_SEC));
    begin = clock();
    min=baseCase(p,&p3,&p4,length);
    location1=findLocation(ind,p3.x, p3.y,length);
    location2=findLocation(ind,p4.x, p4.y,length);
    end = clock();
    printf("--------------------------------------\n");
    
    printf("Brute Force\n");
    printf(" %lld %lld %f\n",location1, location2, min);
   printf("Execution time: %f\n", ((double)(end - begin) / CLOCKS_PER_SEC));
}
