#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

/*
Author G[-]0$T
*/

//Function to Randomly Generate Array
void generateRandom(int ar[],int n)
{
	int i;
	srand(time(NULL));
	for(i=0;i<n;i++)
	{
		ar[i]=rand()%100+1;
	}
}

//Function to Merge two Subarrays
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


//Function to Perform MergeSort
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

//Main

int main()
{
	clock_t start,end;   
	double cpu_time;

	start=clock();          //Timer Starts
	int n;
	//Flags to check Array Sorted or not
	int flag1=0;
	int flag2=0;
	printf("Enter the size of array : ");
	scanf("%d",&n);
	int ar[n];
	int i=0;
	int ch;
	printf("\nEnter 1 if you want to input the array 0 for Generating a Random Array : ");
	scanf("%d",&ch);
	if(ch==1)
	{
		printf("\nEnter The Array : ");
		for(i=0;i<n;i++)
		{
			scanf("%d",&ar[i]);
		}
	}
	else
	{
		generateRandom(ar,n);
		printf("\nRandomly Generated Array : ");
		for(i=0;i<n;i++)
		{
			printf("%d ",ar[i]);            // Prints Randomly Generated Array
		}
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
		exit(1);
	}
	else
	{
		printf("\nSequence is not Sorted! ");
		printf("\nSorting...");
		mergeSort(ar,0,n-1);            // Performs Merge Sort 
		printf("\n");
		for(i=0;i<n;i++)
		{
			printf("%d ",ar[i]);
		}	
	}
	end=clock();                    // Timer Ends
	cpu_time=((double)(end-start))/CLOCKS_PER_SEC;       //Calculating Time in Seconds
	printf("\nTime Taken by Sequential Version: %f\n",cpu_time);
}
