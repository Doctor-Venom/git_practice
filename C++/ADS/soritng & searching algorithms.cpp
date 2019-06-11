int linear_search(int arr[], int size, int item)
{
	for (int i = 0; i < size; ++i)
	{
		if (arr[i] == item)
		{
			cout << "Item (" << item << ") found at index : " << i << endl;
			return i;
		}

	}
	return 0;
}

int binary_search(int arr[], int size, int item)
{
	static int low = 0;
	static int high = size - 1;
	int mid = low + (high - low) / 2;
	if (arr[mid] == item)
	{
		cout << "Item (" << item << ") found at index : " << mid << endl;
		return mid;
	}
	else if (arr[mid] < item)
	{
		low = mid + 1;
		binary_search(arr, size, item);
	}
	else if (arr[mid] > item)
	{
		high = mid;
		binary_search(arr, high, item);
	}
}


void bubble_sort(int arr[], int size)
{
	int last = size;
	bool sorted = false, swapped;
	while (sorted == false)
	{
		swapped = false;
		for (int i = 0; i < last-1; ++i)
		{
			if (arr[i] > arr[i + 1])
			{
				int temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				swapped = true;
			}
		}
		--last;
		if (swapped == false)
			break;
	}
}

void insertion_sort(int arr[], int size)
{
	int sorted_end = 0;
	for (int i = 1; i < size; i++)
	{
		if (arr[i] < arr[sorted_end])
		{
			int temp = arr[sorted_end];
			arr[sorted_end] = arr[i];
			arr[i] = temp;

			for (int j = sorted_end; j > 0; --j)
			{
				if (arr[j] < arr[j - 1])
				{
					int temp = arr[j - 1];
					arr[j - 1] = arr[j];
					arr[j] = temp;
				}
				else
					break;
			}
		}
		++sorted_end;
	}
}

void selection_sort(int arr[], int size)
{
	int unsorted_start = 0;
	int unsorted_end = size - 1;
	while (unsorted_start < unsorted_end)
	{
		int min = arr[unsorted_start], min_index = unsorted_start;
		int max = arr[unsorted_end], max_index = unsorted_end;
		for (int i = unsorted_start; i < unsorted_end; ++i)
		{
			if (arr[i] < min)
			{
				min = arr[i];
				min_index = i;
			}
			if (arr[i] > max)
			{
				max = arr[i];
				max_index = i;
			}
		}
		int temp = arr[unsorted_start];
		arr[unsorted_start] = min;
		arr[min_index] = temp;
		temp = arr[unsorted_end];
		arr[unsorted_end] = max;
		arr[max_index] = temp;
		++unsorted_start;
		--unsorted_end;
	}
}

void MERGE(int arr[], int left, int mid, int right)
{
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;
	int *arr1 = new int[n1], *arr2 = new int[n2];
	for (i = 0; i < n1; ++i)
		arr1[i] = arr[left + i];
	for (j = 0; j < n2; ++j)
		arr2[j] = arr[mid + 1 + j];
	i = j = 0;
	k = left;
	while (i < n1 && j < n2)
	{
		if (arr1[i] <= arr2[j])
		{
			arr[k] = arr1[i];
			++i;
		}
		else
		{
			arr[k] = arr2[j];
			++j;
		}
		++k;
	}
	while (i < n1)
	{
		arr[k] = arr1[i];
		++i;
		++k;
	}
	while (j < n2)
	{
		arr[k] = arr2[j];
		++j;
		++k;
	}
}void merge_sort(int arr[], int left, int right)
{
	if (left < right)
	{
		int mid = left + (right - left) / 2;
		merge_sort(arr, left, mid);
		merge_sort(arr, mid+1, right);

		MERGE(arr, left, mid, right);
	}
}

void quick_sort(int arr[], int lo, int hi) 
{
	int i = lo, j = hi;
	int temp;
	int pivot = arr[(lo + hi) / 2];

	while (i <= j) 
	{
		while (arr[i] < pivot) { ++i; }
		while (arr[j] > pivot) { --j; }
		if (i <= j) {
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
	}
	if (lo < j)
		quick_sort(arr, lo, j);
	if (i < hi)
		quick_sort(arr, i, hi);
}

int main()
{
	srand(time(0));
	int arr[200000];
	int x = 0;
	for (int i = 0; i < 200000; ++i)
	{
		x = (rand() % 100000);
		arr[i] = x;
	}

	//bubble_sort(arr, 200000);//125000ms 2mb
	//insertion_sort(arr, 200000);//42000ms 2mb
	//selection_sort(arr, 200000);//25000ms 2mb
	//merge_sort(arr, 0, 199999);//1700ms 46mb
	//quick_sort(arr, 0, 199999);//30ms 2mb !!

	system("pause");
	//linear_search(arr, 200000, 17531);//2ms
	//binary_search(arr, 200000, 17531);//1ms

	return 0;
}