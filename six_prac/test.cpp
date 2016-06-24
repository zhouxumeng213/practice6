#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<iostream>
using namespace std;

//��Ŀһ���������е������������ǰ��һ�����ִ��ں�������֣����������������һ������ԡ�����
//һ�����飬�����������е�����Ե�������

//˼·���Ȱ�������������飬��ͳ���������ڲ�������Ե���Ŀ��Ȼ����ͳ�Ƴ���������������֮��
//������Ե���Ŀ����ͳ������ԵĹ����У�����Ҫ���������������ͳ�������������������Ŀʱ��
//������ָ��ֱ�ָ�������������ĩβ��ÿ�αȽ�����ָ��ָ������֡������һ���������е�����
//���ڵڶ����������е����֣��򹹳�����ԣ���������Ե���Ŀ���ڵڶ�����������ʣ�����ֵĸ���
//�����һ���������е�����С�ڻ���ڵڶ����������е����֣��򲻹�������ԡ�

int Inverse(int arr[],int copy[],int begin,int end)
{
	if (begin == end)
	{
		copy[begin] = arr[begin];
		return 0;
	}
	int len = (end - begin) / 2;
	//���������ڲ�����Ե���Ŀ
	int left = Inverse(arr, copy, begin, begin + len);
	//���������ڲ�����Ե���Ŀ
	int right = Inverse(arr, copy, begin + len + 1, end);

	//i:��һ������������һ���±�
	int i = begin + len;
	//j:�ڶ�������������һ���±�
	int j = end;
	int index = end;
	//count:����Եĸ���
	int count = 0;
	while (i >= begin && j >= begin + len + 1)
	{
		//��һ���������е����ִ��ڵڶ����������е�����
		if (arr[i] > arr[j])
		{
			copy[index--] = arr[i--];
			count += j - begin - len;
		}
		else
		{
			copy[index--] = arr[j--];
		}
	}
	//��ʣ�µ���ȫ������copy��
	for (; i >= begin; i--)
		copy[index--] = arr[i];
	for (; j >= begin + len + 1; j--)
		copy[index--] = arr[j];

	return left + right + count;
}
int InversePairs(int arr[], int len)
{
	if (arr == NULL || len < 0)
		return 0;
	int* copy = new int[len];
	for (int i = 0; i < len; i++)
		copy[i] = arr[i];
	int count=Inverse(arr, copy, 0, len - 1);
	delete[] copy;
	return count;
}
int main()
{
	int arr[] = { 7, 6, 5, 4 };
	int ret = InversePairs(arr, 4);
	printf("%d\n", ret);
	return 0;
}



//��Ŀ�����������������ҳ����ǵĵ�һ��������㡣��㶨�����£�
struct ListNode
{
	int data;
	ListNode* next;
};

//˼·һ�����������й�����㣬���ĳһ�ڵ㿪ʼ���ý���nextָ��ͬһ����㡣�����ǵ�������
//��˴ӵ�һ��������㿪ʼ��֮������н�㶼���غϵģ����ٳ��ֲַ档���Կ��Խ���ջ��ʵ�֣�
//������������ջ���ֱ����������Ľ����븨��ջ�У�β�����ջ�����Ƚ���������ջ��ջ�������
//����ͬ�����������Ƚϣ�֪���ҵ���һ����ͬ�Ľ�㡣  ���ַ�����ʱ�临�Ӷ�ΪO(m+n),���пռ�
//���ӶȵĿ�����

//˼·�������������������ĳ��ȣ������������ĳ��Ȳ���������߳��Ȳ��Ȼ���ٱȽ�����
//�����ҵ���һ��������㡣���ַ�����ʱ�临�Ӷ�Ҳ��O(m+n),��û�пռ临�ӶȵĿ�����

//��ȡ������
int GetLenth(ListNode* head)
{
	int len = 0;
	ListNode* begin = head;
	while (begin)
	{
		len++;
		begin = begin->next;
	}
	return len;
}
//�ҵ�һ���������
ListNode* FindFirstCommNode(ListNode* head1, ListNode* head2)
{
	assert(head1);
	assert(head2);
	int len1 = GetLenth(head1);
	int len2 = GetLenth(head2);
	//LongList:������
	ListNode* LongList = NULL;
	//ShortList:������
	ListNode* ShortList = NULL;
	//lenDif����������ĳ��Ȳ�
	int lenDif = 0;
	if (len1 > len2)
	{
		LongList = head1;
		ShortList = head2;
		lenDif = len1 - len2;
	}
	else
	{
		LongList = head2;
		ShortList = head1;
		lenDif = len2 - len1;
	}
	//����������lenDif��
	for (int i = 0; i < lenDif; i++)
		LongList = LongList->next;
	//�Ƚ����������ҳ���һ���������
	while (LongList != NULL && ShortList != NULL && LongList != ShortList)
	{
		LongList = LongList->next;
		ShortList = ShortList->next;
	}
	//FirstCommNode:��һ���������
	ListNode* FirstCommNode = LongList;

	return FirstCommNode;
}



//��Ŀ����ͳ��һ�����������������г��ֵĴ���������������������{1��2��3��3��3��3��4��5}������
//3������3����������г�����4�Σ�������4

//˼·һ�������������飬ͳ�����������ֳ��ֵĴ��������ַ�����ʱ�临�Ӷ�ΪO(n).

//˼·�������ö��ֲ��ҵ�˼�룬�ֱ��ҳ���һ��3���ֵ�λ�ú����һ��3���ֵ�λ�á����ַ�����ʱ��
//���Ӷ�ΪO(log(n)).

//�ҵ�һ��k���ֵ�λ��
int FindFirstK(int arr[], int len, int k, int begin, int end)
{
	if (begin > end)
		return -1;
	while (begin<end)
	{
		int mid = (begin + end) / 2;
		if (arr[mid] == k)
		{
			if ((mid > 0 && arr[mid - 1] != k) || mid == 0)
				return mid;
			else
				end = mid - 1;
		}
		else if (arr[mid] > k)
			end = mid - 1;
		else
			begin = mid + 1;
	}
}
//�����һ��k���ֵ�λ��
int FindLastK(int arr[], int len, int k, int begin, int end)
{
	if (begin > end)
		return -1;
	while (begin < end)
	{
		int mid = (begin + end) / 2;
		if (arr[mid] == k)
		{
			if ((mid < len - 1 && arr[mid + 1] != k) || mid == len - 1)
				return mid;
			else
				begin = mid + 1;
		}
		else if (arr[mid] > k)
			end = mid - 1;
		else
			begin = mid + 1;
	}
}
//����k�������г��ֵĴ���
int NumofK(int arr[], int len, int k)
{
	assert(arr);
	assert(len > 0);
	int count = 0;
	int begin = 0;
	int end = len - 1;
	int left = FindFirstK(arr, len, k, begin, end);
	int right = FindLastK(arr, len, k, begin, end);
	if (left > -1 && right > -1)
		count = right - left + 1;
	return count;
}
int main()
{
	int arr[] = { 1, 2, 3, 3, 3, 3, 4, 5 };
	int ret = NumofK(arr, sizeof(arr) / sizeof(arr[0]), 3);
	printf("%d\n", ret);
	return 0;
}


//��Ŀ�ģ�����һ�Ŷ������ĸ���㣬���������ȡ��Ӹ���㵽Ҷ������ξ����Ľ�㣨������Ҷ��㣩
//�γ�����һ��·�����·���ĳ���Ϊ������ȡ�

struct BinaryTreeNode
{
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	int data;
};
//�ݹ鷽ʽ
int Depth(BinaryTreeNode* root)
{
	assert(root);
	int left = Depth(root->left);
	int right = Depth(root->right);
	return left > right ? (left + 1) : (right + 1);
}

//�����Ŀһ������һ�Ŷ������ĸ���㣬�жϸ����ǲ���ƽ������������ĳ���������������
//�������������������1����ô������һ��ƽ���������

//˼·һ���������������ȵķ�����ÿ����һ����㣬����Depth()�õ�����������������ȣ��ж�
//����������left��right����ǲ��ǲ�����1��  �������ַ������α���һ����㣬Ч�ʲ���

bool IsBalanceTree(BinaryTreeNode* root)
{
	assert(root);
	int left = Depth(root->left);
	int right = Depth(root->right);
	if (left - right > 1 || left - right < -1)
		return false;
	return IsBalanceTree(root->left) && IsBalanceTree(root->right);
}

//˼·�������ö������ĺ���������ڱ���һ������ʱ�������ҽڵ��Ѿ���������¼����ȼ��ɡ�
//�����Ϳ���һ�����һ���ж�ĳ���ڵ��ǲ���ƽ���

bool IsBalance(BinaryTreeNode* root, int* depth)
{
	if (root == NULL)
	{
		*depth = 0;
		return true;
	}
	int left, right;
	//�����������������¼���
	if (IsBalance(root->left,&left) && IsBalance(root->right,&right))
	{
		if (left - right <= 1 && left - right >= -1)
		{
			*depth = (left > right ? left : right) + 1;
			return true;
		}
	}
	return false;
}
bool IsBalanceTree(BinaryTreeNode* root)
{
	assert(root);
	int depth = 0;
	IsBalance(root, &depth);
}


//��Ŀ�壺һ�����������������������֮�⣬���������ֶ����������Ρ���д�����ҳ����ֻ����һ
//�ε����֡�Ҫ��ʱ�临�Ӷ���O(n),�ռ临�Ӷ���O(1).

//˼·�����һ������������ֻ��һ�����ֳ�����һ�Σ����������ֶ����������Σ������һ�ζ�����
//�����ֽ��������Ϊ������ͬ���������Ϊ0���������϶�Ϊ�Ǹ�ֻ����һ�ε����֡����һ��
//������������ֻ����һ�ε����֣�����Խ���������Ϊ�����֣������ֱַ����һ������һ�ε�
//����Ȼ����ݳ���һ�ε�һ�����������Ϳ����ҳ����ؼ�����������������Ϊ�����֣�������һ
//����һ�ζ������е����ֽ�����򣬽���϶���Ϊ0���ڽ�����ҳ���һ��Ϊ1��λ�ã�������������
//��λΪ1�Ͳ�Ϊ1������Ϊ�����֣��������ε����϶�����һ���������С�

//�ҳ�����Ĵ�������ĵ�һ��1��λ��
unsigned int FindIndexOf1(int result)
{
	int indexBit = 0;
	while (((result & 1) == 0) && indexBit<8 * sizeof(int))
	{
		result=result >> 1;
		indexBit++;
	}
	return indexBit;
}
//�ж����������д�������ĵ�indexBitλ�ǲ���1
bool IsBit(int num, unsigned int indexOf1)
{
	num=num >> indexOf1;
	return (num & 1);
}
void FindNum(int arr[], int len,int* num1,int* num2)
{
	assert(arr);
	assert(len > 0);
	//�������������������������򣬵õ����result.
	int result = 0;
	for (int i = 0; i < len; i++)
	{
		result ^= arr[i];
	}
	//indexOf1:��������ĵ�һ��1��λ��
	unsigned int indexOf1 = FindIndexOf1(result);
	//num1��num2�ֱ𱣴�����������
	*num1 = 0;
	*num2 = 0;
	//ͨ���ж������е�ÿ�����ĵ�indexOf1��λ�ǲ���1�������ֱַ����������������
	for (int j = 0; j < len; j++)
	{
		if (IsBit(arr[j], indexOf1))
		{
			*num1 ^= arr[j];
		}
		else
		{
			*num2 ^= arr[j];
		}
	}
	//��ӡ����ֻ����һ�ε���
	int result1 = 0;
	int result2 = 0;
	for (int i = 0; i < sizeof(num1) / sizeof(num1[0]); i++)
	{
		result1 ^= num1[i];
		printf("%d\n", result1);
	}
	for (int i = 0; i < sizeof(num2) / sizeof(num2[0]); i++)
	{
		result2 ^= num2[i];
		printf("%d\n", result2);
	}
}
int main()
{
	int arr[] = { 2, 4, 3, 6, 3, 2, 5, 5 };
	int num1[8] = {0};
	int num2[8] = {0};
	FindNum(arr, 8, num1, num2);
	return 0;
}


//��Ŀ��������һ����������������һ������s,�������в�����������ʹ�����ǵĺ�������s�������
//������ֵĺ͵���s���������һ�Լ��ɡ�

//˼·һ���ӵ�һ�����ֿ�ʼ���̶�����Ȼ�������Һ����������͵��������ĺ͡�������˼·ʱ�临��
//��ΪO(n2)

//˼·������������ָ�룬һ��ָ���һ�����֣�һ��ָ�����һ�����֣������ӵĺʹ��������ĺͣ�
//��Ϊ����������飬���Խ���һ��ָ����ǰ�ƣ������ӵĺ�С�������ĺͣ��򽫵�һ��ָ��������
//����˼·��ʱ�临�Ӷ�ΪO(n)

bool FindSum(int arr[],int len,int sum)
{
	assert(arr);
	assert(len > 0);
	int left = 0;
	int right = len - 1;
	while (left < right)
	{
		if (arr[left] + arr[right]>sum)
			right--;
		else if (arr[left]+arr[right]<sum)
			left++;
		else if (arr[left]+arr[right]==sum)
		{
			printf("%d %d", arr[left], arr[right]);
			return true;
		}
	}
	return false;
}
int main()
{
	int arr[] = { 1, 2, 4, 7, 11, 15 };
	FindSum(arr, 6, 15);
	return 0;
}

//�����Ŀһ������һ������s,��ӡ�����к�Ϊs�������������У����ٺ���������������������15������
//1+2+3+4+5=4+5+6=7+8=15�����Խ����ӡ��3����������1~5��4~6��7~8.

//˼·��������˼·һ����������������һ����1��һ����2�������ӵĺʹ���s��ȥ����һ���������
//��ӵĺ�С��s�������ټ�һ����

void Print(int begin, int end)
{
	for (int i = begin; i <= end; i++)
	{
		printf("%d ", i);
	}
	printf("\n");
}
void FindAllSum(int sum)
{
	//���ٰ�������������sum�ĺ�Ӧ����3
	assert(sum > 3);
	int begin = 1;
	int end = 2;
	//��һ�������ܳ����͵�һ�룬������û������Ҫ���
	int mid = (1 + sum) / 2;
	int currentSum = begin + end;
	while (begin < mid)
	{
		if (currentSum == sum)
		{
			Print(begin, end);
		}
		//�����ӵĺʹ��������ĺ�
		while (currentSum>sum && begin < mid)
		{
			currentSum -= begin;
			begin++;
			if (currentSum == sum)
			{
				Print(begin, end);
			}
		}
		//����������
		end++;
		currentSum += end;
	}
}
int main()
{
	FindAllSum(15);
	return 0;
}

//��Ŀ�ߣ�����һ��Ӣ�ľ��ӣ���ת�����е��ʵ�˳�򣬵��������ַ���˳�򲻱䡣Ϊ����������
//���ź���ͨ�ַ�һ���������������ַ���"I am a student."�������"student. a am I"

//˼·�����Ƚ������ַ�����ת����Ϊ".tneduts a ma I",Ȼ��ÿ�����ʷ�ת����Ϊ"student. a am I"
void Reverse(char* left,char* right)
{
	while (left < right)
	{
		swap(*left, *right);
		left++;
		right--;
	}
}
void reverse_string(char* str,int len)
{
	assert(str);
	int i = 0;
	char* left = str;
	char* right = str;
	//�ȷ�ת���е��ַ�
	Reverse(str, str + len - 1);
	//��������תÿ�����ʣ��Կո����
	while (str[i])
	{
		if (str[i] == ' ')
		{
			Reverse(left, right - 1);
			left = ++right;
		}
		else
		{
			right++;
		}
		i++;
	}
}
int main()
{
	char str[] = "I am a student.";
	reverse_string(str, strlen(str));
	printf("%s\n", str);
	return 0;
}

//������Ŀ���ַ���������ת�����ǰ��ַ���ǰ������ɸ��ַ�ת�Ƶ��ַ�����β�����붨��һ������
//ʵ���ַ�������ת�����Ĺ��ܡ����������ַ���"abcdefg"������2���ú�������������ת��λ�õ���
//���"cdefgab"

//˼·���������÷�ת�ַ����������ַ�����Ϊ�����֣�Ȼ��ֱ�ת�������֣���"bagfedc".Ȼ��
//���巭ת�õ�"cdefgab"
void reverse(char* str, int len,int k)
{
	assert(str);
	if (len > 0 && k > 0 && k < len)
	{
		//left1:��һ���ֵ���߽�
		char* left1 = str;
		//right1:��һ���ֱ����ұ߽�
		char* right1 = str + k - 1;
		//left2:�ڶ����ֵ���߽�
		char* left2 = str + k;
		//right2���ڶ����ֵ��ұ߽�
		char* right2 = str + len - 1;
		
		//��ת��һ����
		Reverse(left1, right1);
		//��ת�ڶ�����
		Reverse(left2, right2);
		//ȫ����ת
		Reverse(left1, right2);
	}
}
int main()
{
	char str[] = "abcdefg";
	reverse(str, strlen(str),2);
	printf("%s\n", str);
	return 0;
}