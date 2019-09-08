#include<iostream>
#include<vector>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) :val(x), left(NULL), right(NULL) {};
};
TreeNode * reConstruct(vector<int> pre, vector<int> vin )
{
	int lenth = vin.size();
	if (lenth == 0)
		return NULL;
	int gen = 0;
	TreeNode * head = new TreeNode(pre[0]);
	for (int i = 0; i < lenth; i++)
	{
		if (vin[i] == pre[0])
		{
			gen = i;
			break;
		}
	}

	vector<int>pre_left, pre_right, vin_left, vin_right;
	for (int j = 0; j < gen; j++)
	{
		pre_left.push_back(pre[j + 1]);
		vin_left.push_back(vin[j]);
	}

	for (int k = gen + 1; k <lenth; k++)
	{
		pre_right.push_back(pre[k]);
		vin_right.push_back(vin[k]);
	}

	head->left = reConstruct(pre_left, vin_left);
	head->right = reConstruct(pre_right, vin_right);
	return head;
}
void show(TreeNode * head)
{
	if (head)
	{
		cout << head->val << " ";
		show(head->left);
		show(head->right);
	}
}
int main()
{
	vector<int>pre = { 1,2,4,7,3,5,6,8 };
	vector<int>vin = { 4,7,2,1,5,3,6,8 };
	TreeNode *root = NULL;
	root = reConstruct(pre, vin);
	cout << endl;
	show(root);
	system("pause");
	return 0;
}