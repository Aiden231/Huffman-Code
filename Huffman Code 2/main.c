#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

typedef struct treeNode {
	int weight;
	char ch;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

typedef struct Elemet {
	TreeNode* ptree;
	char ch;
	int key;
}element;

typedef struct heapType {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;
// 생성 함수
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}
// 초기화
void init(HeapType* h)
{
	h->heap_size = 0;
}
// 삽입 함수
void insert_min_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;

	for (int i = 1; i <= h->heap_size; i++) {
		printf("%d ", h->heap[i].key);
	}
	printf("\n");
}
// 삭제 함수
element delete_min_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];

	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key) {
			child++;
		}
		if (temp.key < h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
// 이진 트리 생성 함수
TreeNode* make_tree(TreeNode* left, TreeNode* right)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->left = left;
	node->right = right;
	return node;
}
// 이진 트리 제거 함수
void destory_tree(TreeNode* root)
{
	if (root == NULL) return;

	destory_tree(root->left);
	destory_tree(root->right);
	free(root);
}
// 단말 노드 확인
int is_leaf(TreeNode* root)
{
	return !(root->left) && !(root->right);
}
// 배열 출력
void print_array(int codes[], int n)
{
	for (int i = 0; i < n; i++) {
		printf("%d ", codes[i]);
	}
	printf("\n");
}
// 코드 출력
void print_codes(TreeNode* root, int codes[], int top)
{
	// 1을 저장하고 순환호출한다.
	if (root->left) {
		codes[top] = 1;
		print_codes(root->left, codes, top + 1);
	}
	// 0을 저장하고 순환호출한다.
	if (root->right) {
		codes[top] = 0;
		print_codes(root->right, codes, top + 1);
	}
	// 단말 노드이면 코드를 출력한다.
	if (is_leaf(root)) {
		printf("%c : ", root->ch);
		print_array(codes, top);
	}
}

// 허프만 코드 생성 함수
void huffman_tree(int freq[], char ch_list[], int n)
{
	int i;
	TreeNode* node, * x;
	HeapType* heap;
	element e, e1, e2;
	int codes[100];
	int top = 0;

	heap = create();
	init(heap);

	for (int i = 0; i < n; i++) {
		node = make_tree(NULL, NULL);
		e.ch = node->ch = ch_list[i];
		e.key = node->weight = freq[i];
		e.ptree = node;
		insert_min_heap(heap, e);
	}

	for (i = 1; i < n; i++) {
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);
		// 두 개의 노드를 합친다
		x = make_tree(e1.ptree, e2.ptree);
		e.key = x->weight = e1.key + e2.key;
		e.ptree = x;
		printf("/// %d + %d -> %d\n", e1.key, e2.key, e.key);
		insert_min_heap(heap, e);
	}

	e = delete_min_heap(heap); // 최종 트리
	print_codes(e.ptree, codes, top);
	destory_tree(e.ptree);
	free(heap);
}

int main()
{
	char ch_list[] = { 'a','e','i','o','u','s','t' };
	int freq[] = { 10, 15, 12, 3, 4, 13, 1 };
	huffman_tree(freq, ch_list, 7); //허프만 정렬
	return 0;
}