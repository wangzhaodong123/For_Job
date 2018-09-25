/****************************ʵ�������ڲ������㷨******************************/
#include <iostream>
using namespace std;
//�������
void OutputArray(int arr[],int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
};
//ֱ�Ӳ�������
//����˼���ǽ���һ������Ԫ�ؿ�����һ�����������У������δӵڶ�����¼��������뵽
//����������������
//ֱ�Ӳ��������㷨��ʱ��Ч������O(n)��O(n^2��֮�䣬�������еĳ�ʼ����Խ�ӽ�����
//ֱ�Ӳ��������ʱ��Ч��Խ�ߡ�
//ֱ�Ӳ��������㷨�е�tempռ��һ���洢��Ԫ���ռ临�Ӷ�ΪO(1)
//�ȶ�
void InsertSort()
{
	cout << "InsertSort��" << endl;
	//Ŀ������
	int array_i[20] = { 3, 29, 10, 29, 34, 2, 8, 4, 19, 7, 31, 2, 54, 62, 12, 23,
						43, 60, 26, 13 };
	int size = sizeof(array_i) / sizeof(int);
	
	//����
	int cur = 1;
	//�ӵڶ�����ʼ���һ�����������Ԫ��
	for (; cur < size; cur++)
	{
		if ( array_i[cur] < array_i[cur - 1] )
		{
			int tem_cur = array_i[cur];
			int j = cur - 1;
			//�ҵ��ȵ�ǰԪ��С��Ԫ���±꣬����ǰ��Ľ��к���
			for (; j >= 0 && tem_cur<array_i[j]; j--)
			{
				array_i[j+1] = array_i[j];
			}
			array_i[j+1] = tem_cur;
		}
	}
	OutputArray(array_i, size);
};

//Shell����
//��ԭ���鰴��һ�������ָ�����ɸ������У����в������򣻲�����С������ͬʱ������
//�н��в�������ֱ������Ϊ1
//�����ŵ�����£�ʱ�临�Ӷ�Ϊ��O��n^(1.3)����Ԫ���Ѿ������˳��
//����������£�ʱ�临�Ӷ�Ϊ��O��n^2��
//�ռ临�Ӷ�O(1)
//���ȶ�
void ShellSort()
{
	cout << "ShellSort��" << endl;
	//Ŀ������
	int array_i[20] = { 3, 29, 10, 29, 34, 2, 8, 4, 19, 7, 31, 2, 54, 62, 12, 23,
						43, 60, 26, 13 };
	int size = sizeof(array_i) / sizeof(int);
	//������ֵΪ�����1/2��Ȼ�󲻶ϼ������
	for (int gap = size / 2; gap > 0; gap = gap / 2)
	{
		//���ڵ�ǰ�����·ָ����ÿһ��������в�������
		for (int m = 0; m < gap; m++)
		{
			//����
			int cur = 1;
			//�ӵڶ�����ʼ���һ�����������Ԫ��
			for (; cur < size; cur+=gap)
			{
				if (array_i[cur] < array_i[cur - gap])
				{
					int tem_cur = array_i[cur];
					int j = cur - gap;
					//�ҵ��ȵ�ǰԪ��С��Ԫ���±꣬����ǰ��Ľ��к���
					for (; j >= 0 && tem_cur<array_i[j]; j-=gap)
					{
						array_i[j + gap] = array_i[j];
					}
					array_i[j + gap] = tem_cur;
				}
			}
		}
	}

	OutputArray(array_i,size);
};

//ð������
//ÿ�αȽ���������Ԫ�صĴ�С���������������Ҫ���򽻻��������ݣ�ÿһ�ֱȽϻ�ð
//�ݳ�һ����ֵ�����ڱȽϵ��������һ����ֱ���Ƚ�����ֻʣһ��Ϊֹ
//ʱ�临�Ӷ�O��n^2��
//�ռ临�Ӷ�O(1)
//�ȶ�
void BubbleSort()
{
	cout << "BubbleSort��" << endl;
	//Ŀ������
	int array_i[20] = { 3, 29, 10, 29, 34, 2, 8, 4, 19, 7, 31, 2, 54, 62, 12, 23,
						43, 60, 26, 13 };
	int size = sizeof(array_i) / sizeof(int);

	//����
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

//��������
//ѡ��һ��Ԫ�أ���Ԫ�أ���Ϊ���ᣬ����һ�����򣬱������Ԫ�طŵ����ĺ��棬����С
//��Ԫ�طŵ�����ǰ�棬�Դ˽������Ϊ���Σ����¶Եõ������������������������ֱ��
//�õ�������ֻʣһ����
//ʱ�临�Ӷ�O(n^2)
//�ռ临�Ӷ�O(n)
//���ȶ�
int QuickPartition(int arr[],int low ,int high)
{
	//�ֶ����򣬲���������λ��
	//��������Ԫ��
	int arr_low = arr[low];
	//ѭ����ͷ��ָ��
	while (low < high)
	{
		//���ȴ���������ң��ҵ�С�����������������ŵ�low��ַλ��ԭlow��ַλ�������Ѿ����棬���ᱻ����
		while (low < high&&arr_low <= arr[high])
			high--;
		if (low < high)
			arr[low]=arr[high];
		//Ȼ��������Ҳ��ң��ҵ��������������������ŵ�high��ַλ��high��ַλ���������ŵ���ǰlow��ַλ�����Բ��ᱻ����
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
	//�ݹ���ã�ֱ������ֻ��һ��Ԫ��
	if (low < high)
	{
		int half = QuickPartition(array_int,low,high);
		QuickMain(array_int,low,half-1);
		QuickMain(array_int,half+1,high);
	}
};
void QuickSort()
{
	cout << "QuickSort��" << endl;
	//Ŀ������
	int array_i[20] = { 3, 29, 10, 29, 34, 2, 8, 4, 19, 7, 31, 2, 54, 62, 12, 23,
						43, 60, 26, 13 };
	int size = sizeof(array_i) / sizeof(int);

	QuickMain(array_i,0,size-1);
	OutputArray(array_i,size);
};

//��ѡ������
//�ڣ�i��n-1����Ԫ���У�Ѱ�ҳ���С��Ԫ�أ���iԪ�ؽ�����ֱ��i==n-1
//ʱ�临�Ӷ�O(n^2)
//�ռ临�Ӷ�O(1)
void SelectSort()
{
	cout << "SelectSort��" << endl;
	//Ŀ������
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

//������
//�����������n��Ԫ�ع�����һ��С���ѣ�����Ѷ�Ԫ�أ���ʣ�µ�n-1��Ԫ�����¹���С
//���ѣ�ֱ��ֻʣһ��Ԫ���ؽ��ѵ�ʱ�临�Ӷ�O(n)
//�½���O(nlogn)
//ʱ�临�Ӷ�O(nlogn)
//�ռ临�Ӷ�O(1)
void BuildHeap(int arr[],int start,int size)
{
	for (int pnode = start, i = 2 * start + 1; i <= size - 1;)
	{
		//�ҵ������ӽڵ�������һ��
		if (i < size - 1 && arr[i] < arr[i + 1])
			i++;
		//�����ǰ�ڵ���������ӽڵ㣬��ô�������
		if (arr[pnode] >= arr[i])
			break;
		//���򣬽�����ǰ�ڵ������ӽڵ�
		int tem = arr[i];
		arr[i] = arr[pnode];
		arr[pnode] = tem;
		//�������ӽڵ㷢�������������ƻ�ԭ�ȵ��ӽڵ�Ĵ�С��ϵ��������Ҫ���µ����ӽڵ�
		pnode = i;
		i = 2 * i + 1;
	}
}
void HeapSort()
{
	cout << "HeapSort��" << endl;
	//Ŀ������
	int array_i[20] = { 3, 29, 10, 29, 34, 2, 8, 4, 19, 7, 31, 2, 54, 62, 12, 23,
						43, 60, 26, 13 };
	int size = sizeof(array_i) / sizeof(int);
	
	//��ʼ������
	//�ӱ�����Ľڵ㿪ʼ������ֱ�����ڵ�
	for (int i = size / 2; i >= 0; i--)
	{
		BuildHeap(array_i,i,size);
	}

	//�������һ��Ԫ�أ����ֵ����ĩβԪ�ؽ��������¹�����ĩβԪ�صĴ󶥶�
	for (int i = size-1; i >=0; i--)
	{
		int tem = array_i[0];
		array_i[0] = array_i[i];
		array_i[i] = tem;
		BuildHeap(array_i,0,i);
	}

	OutputArray(array_i,size);
}

//�鲢����
//����˼�룬���Ȱ�����n�ֳɳ���Ϊ1��n�����飬���������ϲ����ź�˳���������ϲ�,
//�ظ�����������ֱ���ϲ���ԭ����
void Merge(int arr[], int left,int mid, int right)
{
	//���ֿ��������������кϲ�
	int t_left = left;
	int t_mid = mid+1;
	int t = 0;
	int *temp = new int[right - left+1];
	//��˳��Ԫ�طŵ���ʱ������
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
	//������
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
	cout << "MergeSort��" << endl;
	//Ŀ������
	int array_i[20] = { 3, 29, 10, 29, 34, 2, 8, 4, 19, 7, 31, 2, 54, 62, 12, 23,
						43, 60, 26, 13 };
	int size = sizeof(array_i) / sizeof(int);

	MergeMain(array_i,0,size-1);
	OutputArray(array_i,size);
}

//������
int main(int argc,char** argv)
{	
	InsertSort();
	ShellSort();
	BubbleSort();
	QuickSort();
	SelectSort();
	HeapSort();
	MergeSort();
	while (1);
	return 0;
}