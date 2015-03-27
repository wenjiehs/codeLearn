#include <stdio.h>
#include <stdlib.h>
void insertSort(int data[], int n);
void shellSort(int data[], int n);
void heapSort(int data[], int lenght);
void mergerSort(int data[], int length);
void quitSort(int data[], int length);
void selectSort(int data[], int length);
void bubbleSort(int data[], int length);
int main()
{
	int Array[20];
	printf("≈≈–Ú«∞£∫\n");
	for(int i = 0; i < 20; i++)
	{
		Array[i] = rand()%100;
		printf("%d ",Array[i]);
	}
	bubbleSort(Array, 20);
	printf("\n≈≈–Ú∫Û£∫\n");
	for(int i = 0; i < 20; i++)
	{
		printf("%d ",Array[i]);
	}

	printf("\n");

}

void bubbleSort(int data[], int length)
{
	int temp;
	for(int i = 0; i < length -1; i++)
		for(int j = 0; j < length -1 - i; j++)
			if(data[j] > data[j + 1])
			{
				temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
			}
}


int selectMin(int data[], int start, int end);
void selectSort(int data[], int length)
{
	int i, j, temp;
	for(i = 0; i < length - 1; i++)
	{
		j = selectMin(data, i, length - 1);
		if(j != i)
		{
			temp = data[j];
			data[j] = data[i];
			data[i] = temp;
		}
	}
}
int selectMin(int data[], int start, int end)
{
	int min = start;
	for(; start <= end; start++)
	{
		if(data[start] < data[min])
			min = start;
	}
	return min;
}
void QSort(int data[], int left, int right);
void quitSort(int data[], int length)
{
	QSort(data, 0, length-1);
}
int patition(int data[], int low, int high);
void QSort(int data[], int left, int right)
{
	if(left < right)
	{
		int pivotloc = patition(data, left, right);
		QSort(data, left, pivotloc);
		QSort(data, pivotloc + 1, right);
	}
}
int patition(int data[], int low, int high)
{
	data[0] = data[low];
	int pivotloc = data[low];
	while(low < high)
	{
		while(low < high && data[high] >= pivotloc)
			high--;
		data[low] = data[high];
		while(low < high && data[low] <= pivotloc)
			low++;
		data[high] = data[low];
	}
	data[low] = data[0];
	return low;
}

void mSort(int data[], int tempData[], int left, int right);
void mergerSort(int data[], int length)
{
	int *tempArray;
	tempArray =(int*)malloc(length * sizeof(int));
	if(tempArray != NULL)
	{
		mSort(data, tempArray, 0, length - 1);
		free(tempArray);
	}
}
void Merge(int data[], int tempData[], int left, int center, int right);
void mSort(int data[], int tempData[], int left, int right)
{
	int center;
	if(left < right)
	{
		center = (left + right)/2;
		mSort(data, tempData, left, center);
		mSort(data, tempData, center + 1, right);
		Merge(data, tempData, left, center + 1, right);
	}
}
void Merge(int data[], int tempData[], int leftPos, int rightPos, int rightEnd)
{
	int leftEnd = rightPos - 1;
	int TempPos = leftPos;
	int num = rightEnd - leftPos + 1;
	while(leftPos <= leftEnd && rightPos <= rightEnd)
	{
		if(data[leftPos] <= data[rightPos])
			tempData[TempPos++] = data[leftPos++];
		else
			tempData[TempPos++] = data[rightPos++];
	}
	while(leftPos <= leftEnd)
		tempData[TempPos++] = data[leftPos++];
	while(rightPos <= rightEnd)
		tempData[TempPos++] = data[rightPos++];
	for(int i = 0; i < num; i++, rightEnd --)
	{
		data[rightEnd] = tempData[rightEnd];
	}
}



void heapAdjust(int data[], int i, int length);
void heapSort(int data[], int length)
{
	int temp;
	for(int i = length/2 -1; i >= 0; i--)
		heapAdjust(data, i, length);
	for(int i = length - 1; i > 0; i--)
	{
		temp = data[0];
		data[0] = data[i];
		data[i] = temp;
		heapAdjust(data, 0, i);
	}
}

void heapAdjust(int data[], int i, int length)
{
	int child, temp;
	for( ; 2 * i + 1 < length; i = child)
	{
		child = 2 * i + 1;
		if( child < length - 1 && data[child + 1] > data[child])
			child++;
		if(data[i] < data[child])
		{
			temp = data[i];
			data[i] = data[child];
			data[child] = temp;
		}
		else
			break;
	}
}

void shellSort(int data[], int n)
{
	int i, j , increment;
	int tmp;
	for(increment = n/2; increment > 0; increment /= 2)
	{
		for(i = increment; i < n; i++)
		{
			tmp = data[i];
			for(j = i; j >= increment; j -= increment)
			{
				if(tmp < data[j - increment])
					data[j] = data[j - increment];
				else
					break;
			}
			data[j] = tmp;
		}
	}
}

void insertSort(int data[], int n)
{
	int tmp, j;
	for(int i = 1; i < n; i++)
	{
		tmp = data[i];
		for(j = i; j > 0; j--)
		{
			if(tmp < data[j - 1])
				data[j] = data[j - 1];	
			else 
				break;
		}
		data[j] = tmp;
	}
}