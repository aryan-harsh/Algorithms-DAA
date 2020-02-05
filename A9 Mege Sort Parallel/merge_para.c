#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

/*
Author G[-]0$T
*/

#define MAX 1000       // Maximum Size of Array

int ar[MAX];           // Globally Declaring Array

struct task{           // Parameters of Thread
	int task_no;
	int task_l;
	int task_r;
};

void generateRandom(int n)            // Function to Randomly Generate Random Matrix
{
	int i;
	srand(time(NULL));
	for(i=0;i<n;i++)
	{
		ar[i]=rand()%100+1;
	}
}


void merge(int l,int m,int r)            // Function to Perform Merge on Two SubArrays
{
	int n1=m-l+1;
	int n2=r-m;
	int L[n1],R[n2];
	int i,j,k;
	for(i=0;i<n1;i++)
	{
		L[i]=ar[l+i];
	}
	for(j=0;j<n2;j++)
	{
		R[j]=ar[m+1+j];
	}
	i=0;
	j=0;
	k=l;
	while(i<n1 && j<n2)
	{
		if(L[i]<=R[j])
		{
			ar[k]=L[i];
			i++;
		}
		else
		{
			ar[k]=R[j];
			j++;
		}
		k++;
	}

	while(i<n1)
	{
		ar[k]=L[i];
		i++;
		k++;
	}
	while(j<n2)
	{
		ar[k]=R[j];
		j++;
		k++;
	}
}
void mergeSort(int l,int r)           // Function to Perform MergeSort
{
	if(l<r)
	{
		int m=l+(r-l)/2;
		mergeSort(l,m);
		mergeSort(m+1,r);

		merge(l,m,r);
	}
}
void *merge_Sort(void *arg)               //Function which is passed when thread is created
{
	struct task *tsk=arg;
	int l;
	int r;

	l=tsk->task_l;
	r=tsk->task_r;

	int m=l+(r-l)/2;

	if(l<r)
	{
		mergeSort(l,m);
		mergeSort(m+1,r);

		merge(l,m,r);
	}
	return 0;
}
int main()
{
	clock_t start,end;            
	double cpu_time;
	start=clock();                  // Timer Starts
	int n;
	int flag1=0,flag2=0;            // Flags to Check if Array is Sorted
	int i,k;
	int thread_count;
	printf("\nEnter the Size of Array : ");
	scanf("%d",&n);
	int ch;
	printf("\nEnter 1 if you want to input the array 0 for Generating a Random Array : ");
	scanf("%d",&ch);
	if(ch==1)
	{
		printf("Enter the Array:");
		for(i=0;i<n;i++)
		{
			scanf("%d",&ar[i]);
		}
	}
	else
	{
		generateRandom(n);
		printf("\nRandomly Generated Array : ");            //Printing Randomly generated matrix
		for(i=0;i<n;i++)
		{
			printf("%d ",ar[i]);
		}
	}
	for(i=0;i<n-1;i++)
	{
		if(ar[i]<ar[i+1])
			flag1++;
	}
	for(i=0;i<n-1;i++)
	{
		if(ar[i]>ar[i+1])
			flag2++;
	}
	if(flag1==n-1 || flag2==n-1)
	{
		printf("\nSequence is Sorted !\n");
		exit(1);
	}
	else
	{
		printf("\nSequence is not Sorted !");
		printf("\nEnter Number of threads for multithreading(<=4): ");       // My Processor has 4 Cores
		scanf("%d",&thread_count);
		pthread_t threads[thread_count];                                     // Initializing threads
		struct task tasklist[thread_count];                                  // Making List of Structures
		struct task *tsk;                                                    // Temporary Pointer
		int l=0;															 // Lowest Value of Array
		int len=n/thread_count;												 // Length of Array in each thread
		for(i=0;i<thread_count;i++,l+=len)
		{
			//This Loop Assigns values to each element of Task List
			tsk=&tasklist[i];
			tsk->task_no=i;
			tsk->task_l=l;
			tsk->task_r=l+len-1;
			if(i==(thread_count-1))
				tsk->task_r=n-1;
		}
		for(i=0;i<thread_count;i++)
		{
			tsk=&tasklist[i];
			pthread_create(&threads[i],NULL,merge_Sort,tsk);       // Creating Thread and Passing Merge_Sort function with Argument
		}

		/*
		If You Want to See Arrays in each Thread Uncomment the Following Segment

		for (i=0; i<thread_count;i++) {
            tsk = &tasklist[i];
            printf("SUB %d:", tsk->task_no);
            for (j = tsk->task_l; j <= tsk->task_r; ++j)
                printf(" %d", ar[j]);
            printf("\n");
        }
		*/

		for(i=0;i<thread_count;i++)
		{
			pthread_join(threads[i],NULL);       // Joining Threads
		}


		// Performing Merge Sort on Arrays Computed by each thread
		struct task *tskm = &tasklist[0];
		for(i=1;i<thread_count;i++)
		{
			struct task *tsk=&tasklist[i];
			merge(tskm->task_l,tsk->task_l - 1,tsk->task_r);
		}
		printf("Sorting...\n");
		for(i=0;i<n;i++)
		{
			printf("%d ",ar[i]);
		}
	}
	end=clock();         // Timer Ends
	cpu_time=((double)(end-start))/CLOCKS_PER_SEC;   // Converting time Taken to Seconds
	printf("\nTime Taken by Multi-Threaded Version: %f\n",cpu_time);
	return 0;
}