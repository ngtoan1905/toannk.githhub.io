#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct TuDien
{
	char word[20];
	char mean[20];
	struct TuDien *right;
	struct TuDien *left;
} TuDien;
TuDien *root = NULL;
TuDien *InsertNode(TuDien *root, char *word, char *mean)
{
	if (root == NULL)
	{
		TuDien *newnode = NULL;
		newnode = (TuDien *)calloc(1, sizeof(TuDien));
		strcpy(newnode->word, word);
		strcpy(newnode->mean, mean);
		newnode->left = NULL;
		newnode->right = NULL;
		return newnode;
	}
	else
	{
		if (strcmp(word, root->word) < 0)
			root->left = InsertNode(root->left, word, mean);
		else if (strcmp(word, root->word) > 0)
			root->right = InsertNode(root->right, word, mean);
		return root;
	}
}
void DocFile(FILE *f)
{
	char word[20];
	char mean[20];
	printf("Doc file va in ra man hinh du lieu trong file.\n");
	while (!feof(f))
	{
		fscanf(f, "%s %[^\n]", word, mean);
		fgetc(f);
		printf("%s %s\n", word, mean);
		root = InsertNode(root, word, mean);
	}
}
void printTree(TuDien *node)
{
	if (node != NULL)
	{
		printf("%s\n", node->word);
		printTree(node->left);
		printTree(node->right);
	}
}

TuDien *FindKey(TuDien *node, char *key)
{
	if (node == NULL)
	{
		return NULL;
	}
	else
	{
		if (strcmp(key, node->word) < 0)
		{
			printf("%s\n", node->word);
			return FindKey(node->left, key);
		}
		else if (strcmp(key, node->word) > 0)
		{
			printf("%s\n", node->word);
			return FindKey(node->right, key);
		}
		else
		{
			return node;
		}
	}
}
void menu(FILE *f)
{
	int choice;
	char word[20];
	char mean[20];
	char cau[50];
	char Tu[50];
	TuDien *tmp = NULL;
	memset(word, 0, sizeof(char) * 20);
	memset(mean, 0, sizeof(char) * 20);
	memset(cau, 0, sizeof(char) * 50);
	memset(Tu, 0, sizeof(char) * 50);
	while (1)
	{
		printf("-------------Menu--------------\n");
		printf("1. Duyet cay theo chieu sau va in ra cay.\n");
		printf("2. Them Tu.\n");
		printf("3. Dich.\n");
		printf("4. Thoat.\n");
		printf("-------------End----------------\n");
		printf("Nhap Lua chon: ");
		scanf("%d", &choice);
		if (choice == 1)
		{
			printf("1. In cay.\n");
			printTree(root);
		}
		else if (choice == 2)
		{
			printf("2. Them Tu.\n");
			printf("Word: ");
			fflush(stdin);
			gets(word);

			printf("Mean: ");
			fflush(stdin);
			gets(mean);
			root = InsertNode(root, word, mean);
		}
		else if (choice == 3)
		{
			memset(Tu, 0, sizeof(char) * 50);
			printf("Nhap mot Tu can tim kiem: ");
			fflush(stdin);
			gets(Tu);
			printf("Tu vua nhap la: %s\n", Tu);
			tmp = FindKey(root, Tu);
			if (tmp == NULL)
			{
				printf("Khong tim thay tu can tra.\n");
			}
			else
			{
				printf("Nghia cua tu do la: %s\n", tmp->mean);
			}
		}
		else if (choice == 4)
		{
			break;
		}
	}
}
int main(int argn,char** argv)
{	
	argn = 2;
	FILE *f = fopen(argv[1], "r");
	DocFile(f);
	menu(f);
}