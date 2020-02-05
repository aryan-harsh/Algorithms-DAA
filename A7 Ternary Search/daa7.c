
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void merge(int arr[], int l, int m, int r) 
{ 
	int i, j, k; 
	int n1 = m - l + 1; 
	int n2 = r - m; 
	int L[n1], R[n2]; 
	for (i = 0; i < n1; i++) 
		L[i] = arr[l + i]; 
	for (j = 0; j < n2; j++) 
		R[j] = arr[m + 1+ j]; 
	i = 0; 
	j = 0; 
	k = l; 
	while (i < n1 && j < n2) 
	{ 
		if (L[i] <= R[j]) 
		{ 
			arr[k] = L[i]; 
			i++; 
		} 
		else
		{ 
			arr[k] = R[j]; 
			j++; 
		} 
		k++; 
	} 
	while (i < n1) 
	{ 
		arr[k] = L[i]; 
		i++; 
		k++; 
	} 
	while (j < n2) 
	{ 
		arr[k] = R[j]; 
		j++; 
		k++; 
	} 
}
void mergeSort(int arr[], int l, int r) 
{ 
	if (l < r) 
	{ 
		int m = l+(r-l)/2;
		mergeSort(arr, l, m); 
		mergeSort(arr, m+1, r); 

		merge(arr, l, m, r); 
	} 
}
void ternerySearch(int ar[],int l,int r,int key)
{
	if(l<=r)
	{
		int mid1=l+(r-l)/3;
		int mid2=r-(r-l)/3;
		if(key==ar[mid1])
		{
			printf("\nElement found at ");
			printf("%dth position \n",mid1+1);
		}
		if(key==ar[mid2])
		{
			printf("\nElement found at ");
			printf("%dth position \n",mid2+1);
		}
		if(key<ar[mid1])
		{
			ternerySearch(ar,l,mid1-1,key);
		}
		else if(key>ar[mid2])
		{
			ternerySearch(ar,mid2+1,r,key);
		}
		else if(key>=ar[mid1] && key<=ar[mid2])
		{
			ternerySearch(ar,mid1+1,mid2-1,key);
		}
		else
		{
			printf("\nSorry Not Found :(\n");
		}
	}
}



/*

THIS IS THE ITERATIVE APPROACH, THE RECURSIVE APPROACH IS PREFERRED OVER THE ITERATIVE APPROACH HENCE IT IS NOT USED HERE.

int ternarySearch(int l, int r, int key, int ar[]) 
  
{ 
    while (r >= l) { 
  
        int mid1 = l + (r - l) / 3; 
        int mid2 = r - (r - l) / 3; 
  
        if (ar[mid1] == key) { 
            return mid1; 
        } 
        if (ar[mid2] == key) { 
            return mid2; 
        } 
  
        
        if (key < ar[mid1]) { 
  
            r = mid1 - 1; 
        } 
        else if (key > ar[mid2]) { 
  
            l = mid2 + 1; 
        } 
        else { 
  
            l = mid1 + 1; 
            r = mid2 - 1; 
        } 
    } 
  
    return -1; 
}

*/


int main()
{
	int n;
	int flag1=0;
	int flag2=0;
	printf("Enter the size of array : ");
	scanf("%d",&n);
	int ar[n];
	int i=0;
	printf("\nEnter The Array : ");
	for(i=0;i<n;i++)
	{
		scanf("%d",&ar[i]);
	}
	for(i=0;i<n-1;i++)
	{
		if(ar[i]>ar[i+1])
		{
			flag1++;
		}
		else if(ar[i]<ar[i+1])
		{
			flag2++;
		}
	}
	if(flag1==n-1 || flag2==n-1)
	{
		printf("\nSequence is Sorted! ");
	}
	else
	{
		printf("\nSequence is not Sorted! ");
		printf("\nSorting...");
		mergeSort(ar,0,n-1);
		printf("\n");
		sleep(1);
		for(i=0;i<n;i++)
		{
			printf("%d ",ar[i]);
		}	
	}
	int key;
	printf("\nEnter the Element to be Searched : ");
	scanf("%d",&key);
	ternerySearch(ar,0,n,key);
	return 0;
}
