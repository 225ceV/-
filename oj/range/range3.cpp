#include<iostream>
using namespace std;
void merge( float *_elem, int lo, int mid, int hi )
{
   float* A=_elem+lo; float* B=new float[mid-lo]; float* C=_elem+mid;
   int i,j,k; i=j=k=0;
   int la=hi-lo, lb=mid-lo, lc=hi-mid;
   while (lo+j<mid)
      B[j++]=_elem[lo+j];
   j=0;
   //while (i<la)
   while(j<lb||k<lc)
      //(j<lb && (!k<lc || B[j]<=C[k])) ? A[i++]=B[j++] : A[i++]=C[k++];
      (j<lb && (!(k<lc) || B[j]<=C[k])) ? A[i++]=B[j++] : A[i++]=C[k++];//!的优先级很高
   delete []B;
}

void mergeSort( float *_elem, int lo, int hi)
{
    if(hi==lo+1) return;
    int mid=(lo+hi)>>1;
    mergeSort(_elem, lo, mid); mergeSort(_elem, mid, hi);
    merge(_elem, lo, mid, hi);
}

int binSearchF( float e, float* arr, int lo, int hi )
{
   while (hi>lo)
   {
      int mid=(hi+lo)>>1;
      e>arr[mid] ? lo=mid+1 : hi=mid;
   }
   return lo;
}

int binSearchB( float e, float* arr, int lo, int hi )
{
   while (hi>lo)
   {
      int mid=(hi+lo)>>1;
      e<arr[mid] ? hi=mid : lo=mid+1;
   }
   return --lo;
}

int main(int argc, char const *argv[])
{
   setvbuf(stdin,  new char[1<<20], _IOFBF, 1<<20);
   setvbuf(stdout, new char[1<<20], _IOFBF, 1<<20);
   int num, qu;
   scanf("%d%d", &num, &qu);
   float* arr = new float[num];
   for(int i=0; i<num; i++) scanf("%f", arr+i);
   mergeSort(arr, 0, num);
   float a[qu],b[qu];

   for(int i=0; i<qu; i++) scanf("%f%f", &a[i], &b[i]);
   for(int i=0; i<qu; i++) printf("%d\n", binSearchB(b[i], arr, 0, num)-binSearchF(a[i], arr, 0, num)+1);
   return 0;
}
