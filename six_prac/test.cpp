#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<iostream>
using namespace std;

//题目一：在数组中的两个数字如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入
//一个数组，求出这个数组中的逆序对的总数。

//思路：先把数组隔成子数组，先统计子数组内部的逆序对的数目，然后再统计出两个相邻子数组之间
//的逆序对的数目。在统计逆序对的过程中，还需要对数组进行排序。在统计相邻子数组逆序对数目时，
//用两个指针分别指向两个子数组的末尾，每次比较两个指针指向的数字。如果第一个子数组中的数字
//大于第二个子数组中的数字，则构成逆序对，并且逆序对的数目等于第二个子数组中剩余数字的个数
//如果第一个子数组中的数字小于或等于第二个子数组中的数字，则不构成逆序对。

int Inverse(int arr[],int copy[],int begin,int end)
{
	if (begin == end)
	{
		copy[begin] = arr[begin];
		return 0;
	}
	int len = (end - begin) / 2;
	//左子数组内部逆序对的数目
	int left = Inverse(arr, copy, begin, begin + len);
	//右子数组内部逆序对的数目
	int right = Inverse(arr, copy, begin + len + 1, end);

	//i:第一个子数组的最后一个下标
	int i = begin + len;
	//j:第二个子数组的最后一个下标
	int j = end;
	int index = end;
	//count:逆序对的个数
	int count = 0;
	while (i >= begin && j >= begin + len + 1)
	{
		//第一个子数组中的数字大于第二个子数组中的数字
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
	//将剩下的数全部拷回copy中
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



//题目二：输入两个链表，找出它们的第一个公共结点。结点定义如下：
struct ListNode
{
	int data;
	ListNode* next;
};

//思路一：两个链表有公共结点，则从某一节点开始，该结点的next指向同一个结点。由于是单项链表
//因此从第一个公共结点开始，之后的所有结点都是重合的，不再出现分叉。所以可以借助栈来实现，
//借助两个辅助栈，分别把两个链表的结点放入辅助栈中，尾结点在栈顶，比较两个辅助栈的栈顶，如果
//不相同，弹出继续比较，知道找到第一个相同的结点。  这种方法的时间复杂度为O(m+n),但有空间
//复杂度的开销。

//思路二：首先求出两个链表的长度，求出两个链表的长度差，则长链表先走长度差步，然后再比较两个
//链表，找到第一个公共结点。这种方法的时间复杂度也是O(m+n),但没有空间复杂度的开销。

//获取链表长度
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
//找第一个公共结点
ListNode* FindFirstCommNode(ListNode* head1, ListNode* head2)
{
	assert(head1);
	assert(head2);
	int len1 = GetLenth(head1);
	int len2 = GetLenth(head2);
	//LongList:长链表
	ListNode* LongList = NULL;
	//ShortList:短链表
	ListNode* ShortList = NULL;
	//lenDif：两个链表的长度差
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
	//长链表先走lenDif步
	for (int i = 0; i < lenDif; i++)
		LongList = LongList->next;
	//比较两个链表，找出第一个公共结点
	while (LongList != NULL && ShortList != NULL && LongList != ShortList)
	{
		LongList = LongList->next;
		ShortList = ShortList->next;
	}
	//FirstCommNode:第一个公共结点
	ListNode* FirstCommNode = LongList;

	return FirstCommNode;
}



//题目三：统计一个数字在排序数组中出现的次数。例如输入排序数组{1，2，3，3，3，3，4，5}和数字
//3，由于3在这个数组中出现了4次，因此输出4

//思路一：遍历整个数组，统计所给的数字出现的次数。这种方法的时间复杂度为O(n).

//思路二：利用二分查找的思想，分别找出第一个3出现的位置和最后一个3出现的位置。这种方法的时间
//复杂度为O(log(n)).

//找第一个k出现的位置
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
//找最后一个k出现的位置
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
//计算k在数组中出现的次数
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


//题目四：输入一颗二叉树的根结点，求该树的深度。从根结点到叶结点依次经过的结点（含根、叶结点）
//形成树的一条路径，最长路径的长度为树的深度。

struct BinaryTreeNode
{
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	int data;
};
//递归方式
int Depth(BinaryTreeNode* root)
{
	assert(root);
	int left = Depth(root->left);
	int right = Depth(root->right);
	return left > right ? (left + 1) : (right + 1);
}

//相关题目一：输入一颗二叉树的根结点，判断该树是不是平衡二叉树。如果某二叉树中任意结点的
//左右子树的深度相差不超过1，那么它就是一颗平衡二叉树。

//思路一：基于求二叉树深度的方法，每遍历一个结点，调用Depth()得到它的左右子树的深度，判断
//它的子树的left、right相差是不是不超过1。  但是这种方法会多次遍历一个结点，效率不高

bool IsBalanceTree(BinaryTreeNode* root)
{
	assert(root);
	int left = Depth(root->left);
	int right = Depth(root->right);
	if (left - right > 1 || left - right < -1)
		return false;
	return IsBalanceTree(root->left) && IsBalanceTree(root->right);
}

//思路二：利用二叉树的后序遍历，在遍历一个结点的时候，其左右节点已经遍历，记录其深度即可。
//这样就可以一遍遍历一遍判断某个节点是不是平衡的

bool IsBalance(BinaryTreeNode* root, int* depth)
{
	if (root == NULL)
	{
		*depth = 0;
		return true;
	}
	int left, right;
	//后序遍历二叉树，记录深度
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


//题目五：一个整形数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这个只出现一
//次的数字。要求时间复杂度是O(n),空间复杂度是O(1).

//思路：如果一个整形数组中只有一个数字出现了一次，其他的数字都出现了两次，则可以一次对所有
//的数字进行异或，因为两个相同的数字异或为0，故其结果肯定为那个只出现一次的数字。如果一个
//数组中有两个只出现一次的数字，则可以将这个数组分为两部分，两部分分别包含一个出现一次的
//数。然后根据出现一次的一个数进行异或就可以找出。关键是怎样把这个数组分为两部分，像上面一
//样，一次对数组中的数字进行异或，结果肯定不为0，在结果中找出第一个为1的位置，在数组中找这
//个位为1和不为1的数分为两部分，出现两次的数肯定分在一个子数组中。

//找出结果的从右向左的第一个1的位置
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
//判断整形数组中从右向左的第indexBit位是不是1
bool IsBit(int num, unsigned int indexOf1)
{
	num=num >> indexOf1;
	return (num & 1);
}
void FindNum(int arr[], int len,int* num1,int* num2)
{
	assert(arr);
	assert(len > 0);
	//将所有整形数组的数字依次异或，得到结果result.
	int result = 0;
	for (int i = 0; i < len; i++)
	{
		result ^= arr[i];
	}
	//indexOf1:从右向左的第一个1的位置
	unsigned int indexOf1 = FindIndexOf1(result);
	//num1和num2分别保存两个子数组
	*num1 = 0;
	*num2 = 0;
	//通过判断数组中的每个数的第indexOf1的位是不是1，将数字分别存在两个子数组中
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
	//打印两个只出现一次的数
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


//题目六：输入一个递增排序的数组和一个数字s,在数组中查找两个数，使得它们的和正好是s，如果有
//多对数字的和等于s，输出任意一对即可。

//思路一：从第一个数字开始，固定它，然后往后找和它加起来和等于所给的和。这样的思路时间复杂
//度为O(n2)

//思路二：定义两个指针，一个指向第一个数字，一个指向最后一个数字，如果相加的和大于所给的和，
//因为是排序的数组，所以将后一个指针往前移，如果相加的和小于所给的和，则将第一个指针往后移
//这种思路的时间复杂度为O(n)

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

//相关题目一：输入一个正数s,打印出所有和为s的连续正数序列（至少含有两个数）。例如输入15，由于
//1+2+3+4+5=4+5+6=7+8=15，所以结果打印出3个连续序列1~5、4~6、7~8.

//思路：跟上面思路一样，定义两个数，一个是1，一个是2，如果相加的和大于s，去掉第一个数，如果
//相加的和小于s，往后再加一个数

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
	//至少包含两个数，故sum的和应大于3
	assert(sum > 3);
	int begin = 1;
	int end = 2;
	//第一个数不能超过和的一半，超过就没有满足要求的
	int mid = (1 + sum) / 2;
	int currentSum = begin + end;
	while (begin < mid)
	{
		if (currentSum == sum)
		{
			Print(begin, end);
		}
		//如果相加的和大于所给的和
		while (currentSum>sum && begin < mid)
		{
			currentSum -= begin;
			begin++;
			if (currentSum == sum)
			{
				Print(begin, end);
			}
		}
		//依次往后找
		end++;
		currentSum += end;
	}
}
int main()
{
	FindAllSum(15);
	return 0;
}

//题目七：输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。为简单起见，标点
//符号和普通字符一样处理。例如输入字符串"I am a student."，则输出"student. a am I"

//思路：首先将所有字符串翻转，变为".tneduts a ma I",然后将每个单词翻转。变为"student. a am I"
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
	//先翻转所有的字符
	Reverse(str, str + len - 1);
	//接下来翻转每个单词，以空格隔开
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

//类似题目：字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。请定义一个函数
//实现字符串左旋转操作的功能。比如输入字符串"abcdefg"和数字2，该函数将返回左旋转两位得到的
//结果"cdefgab"

//思路：还是利用翻转字符串，将该字符串分为两部分，然后分别翻转这两部分，即"bagfedc".然后
//整体翻转得到"cdefgab"
void reverse(char* str, int len,int k)
{
	assert(str);
	if (len > 0 && k > 0 && k < len)
	{
		//left1:第一部分的左边界
		char* left1 = str;
		//right1:第一部分被的右边界
		char* right1 = str + k - 1;
		//left2:第二部分的左边界
		char* left2 = str + k;
		//right2：第二部分的右边界
		char* right2 = str + len - 1;
		
		//翻转第一部分
		Reverse(left1, right1);
		//翻转第二部分
		Reverse(left2, right2);
		//全部翻转
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