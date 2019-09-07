#include<iostream>
#include<queue>
#pragma warning(disable:4996)
using namespace std;
struct node {
	char ch;
	node * left;
	node *right;
};
void BuildTree(node * &root )
{
	char ch;
	scanf("%c", &ch);
	getchar();
	if (ch == ' ')root = NULL;
	else
	{
		root = new node;
		root->ch = ch;
		cout << "����������" << endl;
		BuildTree(root->left);
		cout << "����������" << endl;
		BuildTree(root->right);
	}

}
//�������
void prishow(node *T)
{
	if (T)
	{
		cout << T->ch << " ";
		prishow(T->left);
		prishow(T->right);
	}
}
//��α���
void leavelorder(node * root)
{
	node *T=root;
	queue<node*> ans;
	ans.push(T);
	while (!ans.empty())
	{
		T = ans.front();
		ans.pop();
		cout << T->ch << " ";
		if (T->left)
			ans.push(T->left);
		if (T->right)
			ans.push(T->right);
	}
}
//���������
int Depth(node * root)
{
	int deep = 0;
	if (root)
	{
		int left_depth = Depth(root->left);
		int right_depth = Depth(root->right);
		deep = left_depth >= right_depth ? left_depth + 1 : right_depth + 1;
	}
	return deep;
}
//����Ҷ�ĸ���
int leaves(node * root)
{
	int num = 0;
	if (root)
	{
		if (root->left == NULL && root->right == NULL)
			num++;
		leaves(root->left);
		leaves(root->right);
	}
	return num;
}
int main() 
{	 
	node * root = NULL;
	BuildTree(root);
	prishow(root);
	cout << endl;
	leavelorder(root);
	cout << "���ĸ߶�" << endl;
	cout << Depth(root) << endl;
	cout << "��Ҷ�ĸ���" << endl;
	system("pause");
	return 0;
}