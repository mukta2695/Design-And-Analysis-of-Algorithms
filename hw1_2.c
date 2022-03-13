#include<stdio.h>
int find_max (int arr[], int num){
   int max = arr[0];
   for (int i = 1; i < num; i++)
      if (arr[i] > max){
          max = arr[i];
      }
   return max;
}

void countingSort(int array[], int size, int place) {
  int output[size];
  int count[10];

  for (int i = 0; i < 10; ++i){
        count[i] = 0;
  }
  
  for (int i = 0; i < size; i++){
        int last=(array[i] / place) % 10;
        count[last]++;
    }
    
  for (int i = 1; i < 10; i++){
        count[i] += count[i-1];
    }


  // Place elements in every pass
  for (int i = size-1 ; i >= 0; i--) {
        int last=(array[i] / place) % 10;
        output[count[last] - 1] = array[i];
        count[last]--;
    }

  for (int i = 0; i < size; i++)
    array[i] = output[i];
}

void radixsort(int array[], int size) {

  int max = find_max(array, size);

  for (int place = 1; max / place > 0; place *= 10)
    countingSort(array, size, place);
}

int binary_search(int arr[], int first, int index,int element) {
  if(index >= first){
      int mid = (first + index) / 2;
        if (arr[mid] == element) {
            return mid;
        }
        else if (arr[mid]<element){
            return binary_search(arr, mid + 1, index,element);
        }
        else{
            return binary_search(arr, first, mid - 1, element);
        }
  }
  return -1;
}

void iterater(int arr[],int i,int begin,int key){
    
    for (int j = 0; j < i; j++) {
        int difference=key - arr[j];
        int flag =binary_search(arr, begin, i, difference);

        if (flag > 0 && arr[j] != (key - arr[j])) {
            printf("%d : (%d,%d)\n", key, arr[j],difference);
            }  
    }    
}

void find_summation(int arr[], int begin, int arr_size) {
    for (int i = 0; i < arr_size; i++) {
        iterater(arr,i,begin,arr[i]);
    }
}

int main()
{
	int arr[] = {1,2,3,7,15,22};
	int arr_size = sizeof(arr) / sizeof(arr[0]);
	radixsort(arr, arr_size);
    find_summation(arr,0,arr_size);
}
