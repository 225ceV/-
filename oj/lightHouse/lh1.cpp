#include <cstdio>
long long count=0;
void mergeCount(int *y, int lo, int mid, int hi)
{
    int *A=y+lo, *B=new int[mid-lo], *C=y+mid;
    int i,j,k; i=j=k=0;
    int la=hi-lo, lb=mid-lo, lc=hi-mid;
    for(; i<mid-lo; i++, j++) B[i]=A[j];
    i=j=0;
    while (i<la)
    {
        if(k<lc&&(!(j<lb)||C[k]<B[j])){
            A[i]=C[k];
            i++; k++;
            count+=j;
        }else{
            A[i]=B[j];
            i++; j++;    
        }
    }
}
void mgSortCount(int *y, int lo, int hi)
{
    if(hi==lo+1) return;
    int mid=(lo+hi)>>1;
    mgSortCount(y, lo, mid); mgSortCount(y, mid, hi);
    mergeCount(y, lo, mid, hi);
}
void mergeXY(int *x, int *y, int lo, int mid, int hi)
{
    int *A=x+lo, *B=new int[mid-lo], *C=x+mid;
    int *L=y+lo, *M=new int[mid-lo], *N=y+mid;
    int i,j,k; i=j=k=0;
    int la=hi-lo, lb=mid-lo, lc=hi-mid;
    for(; i<mid-lo; i++, j++) {B[i]=A[j]; M[i]=L[j];}
    i=j=0;
    while (j<lb||k<lc)
    {
        if(k<lc && (!(j<lb)||C[k]<B[j])){
            A[i]=C[k]; L[i]=N[k];
            i++; k++;
        }else{
            A[i]=B[j]; L[i]=M[j];
            i++; j++;    
        }
    }
}
void mgSortXY( int *x, int *y, int lo, int hi)
{
    if(hi==lo+1) return;
    int mid=(lo+hi)>>1;
    mgSortXY(x, y, lo, mid); mgSortXY(x, y, mid, hi);
    mergeXY(x, y, lo, mid, hi);
}
int main(int argc, char const *argv[])
{
    long long n;
    scanf("%lld", &n);
    int x[n], y[n];
    for(int i=0; i<n; i++) scanf("%d %d", x+i, y+i);
    mgSortXY(x, y, 0, n);
    // for(int i=0; i<n; i++) printf("%d ", x[i]);
    // printf("\n");
    // for(int i=0; i<n; i++) printf("%d ", y[i]);
    // printf("\n");

    mgSortCount(y, 0, n);
    printf("%lld\n", count);
    return 0;
}
