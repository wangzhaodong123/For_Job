/****************************实现七种内部排序算法******************************/
//直接插入排序
//基本思想是将第一个数据元素看成是一个有序子序列，再依次从第二个记录起逐个插入到
//这个有序的子序列中
//直接插入排序算法的时间效率是在O(n)到O(n^2）之间，数据序列的初始排列越接近有序，
//直接插入排序的时间效率越高。
//直接插入排序算法中的temp占用一个存储单元，空间复杂度为O(1)
//稳定
void InsertSort()
{
	cout << "InsertSort：" << endl;
	//目标数组
	int array_i[20] = { 3, 29, 10, 29, 34, 2, 8, 4, 19, 7, 31, 2, 54, 62, 12, 23,
						43, 60, 26, 13 };
	int size = sizeof(array_i) / sizeof(int);
	//排序
	int cur = 1;
	//从第二个开始向第一个序列中添加元素
	for (; cur < size; cur++)
	{
		if ( array_i[cur] < array_i[cur - 1] )
		{
			int tem_cur = array_i[cur];
			int j = cur - 1;
			//找到比当前元素小的元素下标，并将前面的进行后移
			for (; j >= 0 && tem_cur<array_i[j]; j--)
			{
				array_i[j+1] = array_i[j];
			}
			array_i[j+1] = tem_cur;
		}
	}
	OutputArray(array_i, size);
};
//Shell排序
//将原数组按照一定增量分割成若干个子序列，进行插入排序；不断缩小增量，同时对子序
//列进行插入排序，直到增量为1
//在最优的情况下，时间复杂度为：O（n^(1.3)）（元素已经排序好顺序）
//在最差的情况下，时间复杂度为：O（n^2）
//空间复杂度O(1)
//不稳定
void ShellSort()
{
	cout << "ShellSort：" << endl;
	//目标数组
	int array_i[20] = { 3, 29, 10, 29, 34, 2, 8, 4, 19, 7, 31, 2, 54, 62, 12, 23,
						43, 60, 26, 13 };
	int size = sizeof(array_i) / sizeof(int);
	//增量初值为数组的1/2，然后不断减半减半
	for (int gap = size / 2; gap > 0; gap = gap / 2)
	{
		//对于当前增量下分割出的每一个数组进行插入排序
		for (int m = 0; m < gap; m++)
		{
			//排序
			int cur = m+gap;
			//从第二个开始向第一个序列中添加元素
			for (; cur < size; cur+=gap)
			{
				if (array_i[cur] < array_i[cur - gap])
				{
					int tem_cur = array_i[cur];
					int j = cur - gap;
					//找到比当前元素小的元素下标，并将前面的进行后移
					for (; j >= 0 && tem_cur<array_i[j]; j-=gap)
						array_i[j + gap] = array_i[j];
					array_i[j + gap] = tem_cur;
				}
			}
		}
	}
	OutputArray(array_i,size);
};

//冒泡排序
//每次比较相邻两个元素的大小，如果不符合排序要求，则交换两个数据，每一轮比较会冒
//泡出一个最值，用于比较的数组就少一个，直到比较数列只剩一个为止
//时间复杂度O（n^2）
//空间复杂度O(1)
//稳定
void BubbleSort()
{
	cout << "BubbleSort：" << endl;
	//目标数组
	int array_i[20] = { 3, 29, 10, 29, 34, 2, 8, 4, 19, 7, 31, 2, 54, 62, 12, 23,
						43, 60, 26, 13 };
	int size = sizeof(array_i) / sizeof(int);

	//排序
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i-1; j++)
		{
			if (array_i[j]>array_i[j + 1])
			{
				int tem = array_i[j];
				array_i[j] = array_i[j + 1];
				array_i[j + 1] = tem;
			}
		}
	}
	OutputArray(array_i,size);
}
//快速排序
//选择一个元素（首元素）作为枢轴，经过一轮排序，比它大的元素放到它的后面，比它小
//的元素放到它的前面，以此将数组分为两段，重新对得到的两个数组进行上述操作，直到
//得到的数组只剩一个。
//时间复杂度O(n^2)
//空间复杂度O(n)
//不稳定
int QuickPartition(int arr[],int low ,int high)
{
	//分段排序，并返回枢轴位置
	//保存轴枢元素
	int arr_low = arr[low];
	//循环两头的指针
	while (low < high)
	{
		//首先从右往左查找，找到小于枢轴的数，并将其放到low地址位，原low地址位的数据已经保存，不会被覆盖
		while (low < high&&arr_low <= arr[high])
			high--;
		if (low < high)
			arr[low]=arr[high];
		//然后从左往右查找，找到大于枢轴的数，并将其放到high地址位，high地址位的数据曾放到过前low地址位，所以不会被覆盖
		while (low<high&&arr_low >= arr[low])
			low++;
		if (low < high)
		arr[high] = arr[low];
	}
	arr[low] = arr_low;
	return low;
}
void QuickMain(int array_int[],int low,int high)
{
	//递归调用，直到数组只有一个元素
	if (low < high)
	{
		int half = QuickPartition(array_int,low,high);
		QuickMain(array_int,low,half-1);
		QuickMain(array_int,half+1,high);
	}
};
void QuickSort()
{
	cout << "QuickSort：" << endl;
	//目标数组
	int array_i[20] = { 3, 29, 10, 29, 34, 2, 8, 4, 19, 7, 31, 2, 54, 62, 12, 23,
						43, 60, 26, 13 };
	int size = sizeof(array_i) / sizeof(int);

	QuickMain(array_i,0,size-1);
	OutputArray(array_i,size);
};

//简单选择排序
//在（i，n-1）个元素中，寻找出最小的元素，与i元素交换，直到i==n-1
//时间复杂度O(n^2)
//空间复杂度O(1)
void SelectSort()
{
	cout << "SelectSort：" << endl;
	//目标数组
	int array_i[20] = { 3, 29, 10, 29, 34, 2, 8, 4, 19, 7, 31, 2, 54, 62, 12, 23,
						43, 60, 26, 13 };
	int size = sizeof(array_i) / sizeof(int);

	for (int i = 0; i < size ; i++)
	{
		int tem = i;
		for (int j = i + 1; j < size ; j++)
		{
			if (array_i[j] < array_i[tem])
				tem = j;
		}
		if (tem != i)
		{
			int tem_arry = array_i[tem];
			array_i[tem] = array_i[i];
			array_i[i] = tem_arry;
		}
	}

	OutputArray(array_i,size);
}

//堆排序
//将数组的所有n个元素构建成一个小顶堆，输出堆顶元素，将剩下的n-1个元素重新构成小
//顶堆，直到只剩一个元素重建堆的时间复杂度O(n)
//新建堆O(nlogn)
//时间复杂度O(nlogn)
//空间复杂度O(1)
void BuildHeap(int arr[],int start,int size)
{
	for (int pnode = start, i = 2 * start + 1; i <= size - 1;)
	{
		//找到两个子节点中最大的一个
		if (i < size - 1 && arr[i] < arr[i + 1])
			i++;
		//如果当前节点大于最大的子节点，那么无需调整
		if (arr[pnode] >= arr[i])
			break;
		//否则，交换当前节点和最大子节点
		int tem = arr[i];
		arr[i] = arr[pnode];
		arr[pnode] = tem;
		//由于与子节点发生交换，可能破坏原先的子节点的大小关系，所以需要重新调整子节点
		pnode = i;
		i = 2 * i + 1;
	}
}





void HeapSort()
{
	cout << "HeapSort：" << endl;
	//目标数组
	int array_i[20] = { 3, 29, 10, 29, 34, 2, 8, 4, 19, 7, 31, 2, 54, 62, 12, 23,
						43, 60, 26, 13 };
	int size = sizeof(array_i) / sizeof(int);
	//初始化顶堆
	//从编号最大的节点开始构建，直到根节点
	for (int i = size / 2; i >= 0; i--)
		BuildHeap(array_i,i,size);
	//将数组第一个元素（最大值）与末尾元素交换，重新构建除末尾元素的大顶堆
	for (int i = size-1; i >=0; i--)
	{
		int tem = array_i[0];
		array_i[0] = array_i[i];
		array_i[i] = tem;
		BuildHeap(array_i,0,i);
	}
	OutputArray(array_i,size);
}

//归并排序
//分治思想，首先把数组n分成长度为1的n个数组，接着两两合并并排好顺序，再两两合并,
//重复上述操作，直到合并成原数组
void Merge(int arr[], int left,int mid, int right)
{
	//将分开后的两个数组进行合并
	int t_left = left;
	int t_mid = mid+1;
	int t = 0;
	int *temp = new int[right - left+1];
	//按顺序将元素放到临时数组中
	while (t_left <= mid&& t_mid <= right)
	{
		if (arr[t_left] <= arr[t_mid])
			temp[t++] = arr[t_left++];
		else
			temp[t++] = arr[t_mid++];
	}
	while (t_left <= mid)
		temp[t++] = arr[t_left++];
	while (t_mid <= right)
		temp[t++] = arr[t_mid++];
	t = 0;
	while (left<=right)
		arr[left++] = temp[t++] ;
	delete []temp;

}
void MergeMain(int arr[],int left ,int right)
{
	//主函数
	if (left < right)
	{
		int mid = (left + right) / 2;
		MergeMain(arr, left, mid);
		MergeMain(arr,mid+1,right);
		Merge(arr,left,mid,right);
	}

}
void MergeSort()
{
	cout << "MergeSort：" << endl;
	//目标数组
	int array_i[20] = { 3, 29, 10, 29, 34, 2, 8, 4, 19, 7, 31, 2, 54, 62, 12, 23,
						43, 60, 26, 13 };
	int size = sizeof(array_i) / sizeof(int);

	MergeMain(array_i,0,size-1);
	OutputArray(array_i,size);
}