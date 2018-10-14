#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define NELEM  15

void insertion_sort(int s[], int n)
{
   for(int i=0; i<n; i++) {
      int j=i;
      while((j>0) && (s[j] < s[j-1])) {
         int tmp = s[j-1];
         s[j-1] = s[j];
         s[j] = tmp;
         j = j-1;
      }
   }
}

void selectionSort(int data[], int count)
{
   int min, temp;
   for(int i = 0; i < count - 1; i++) {
      min = i;
      for(int j = i+1; j < count; j++)
         if(data[j] < data[min])
            min = j;
      temp = data[i];
      data[i] = data[min];
      data[min] = temp;
   }
}

void q_sort(int numbers[], int left, int right)
{
   int pivot, l_hold, r_hold;
   l_hold = left;
   r_hold = right;
   pivot = numbers[left];
   while (left < right) {
      while ((numbers[right] >= pivot) && (left < right))
         right--;
      if(left != right) {
         numbers[left] = numbers[right];
         left++;
      }
      while((numbers[left] <= pivot) && (left < right))
         left++;
      if(left != right) {
         numbers[right] = numbers[left];
         right--;
      }
   }
   numbers[left] = pivot;
   pivot = left;
   left = l_hold;
   right = r_hold;
   if(left < pivot)
      q_sort(numbers, left, pivot-1);
   if(right > pivot)
      q_sort(numbers, pivot+1, right);
}

void quick_sort(int numbers[], int array_size)
{
  q_sort(numbers, 0, array_size - 1);
}

bool merge (int list1[], int size1, int list2[], int size2, int list3[])
{
  int i1, i2, i3;

  if (size1+size2 > NELEM) {
    return false;
  }
  i1 = 0; i2 = 0; i3 = 0;
  while (i1 < size1 && i2 < size2) {
    if (list1[i1] < list2[i2]) {
      list3[i3++] = list1[i1++];
    } else {
      list3[i3++] = list2[i2++];
    }
  }
  while (i1 < size1) {
    list3[i3++] = list1[i1++];
  }
  while (i2 < size2) {
    list3[i3++] = list2[i2++];
  }
}

void mergeSort (int array[], int size)
{
  int temp[NELEM], mid, i;

  if (size < 2) {
    return;
  } else {
    mid = size / 2;
    mergeSort(array, mid);
    mergeSort(array + mid, size - mid);
    merge (array, mid, array + mid, size - mid, temp);
    for (i = 0; i < size; i++) {
      array[i] = temp[i];
    }
  }
}

int main()
{
   int s[NELEM+2] = {2,4,5,10,19,28,1,2,3,4,5,31,32,34,100};

   //insertion_sort(s,NELEM);
   //selectionSort(s,NELEM);
   //quickSort(s,NELEM-1);
   mergeSort(s, NELEM);

   for(int i=0; i<NELEM; i++)
  {printf("%d ",s[i]);
}
      printf("\n");
   return 0;
}
