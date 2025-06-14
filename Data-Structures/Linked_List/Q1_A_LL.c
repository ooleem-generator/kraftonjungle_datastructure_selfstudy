//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

/* add your code here */
int insertSortedLL(LinkedList *ll, int item)
{
	ListNode *pre, *cur, *temp;
	int index;

	if (ll == NULL) // ll 자체가 유효하지 않은 경우
		return -1;
	
	cur = ll->head; // 일단 cur를 head가 가리키는 원소 주소(ll의 첫번째 원소 주소)로 초기화
	index = 0;

	if (cur == NULL) { // 연결리스트가 비어있는 경우 (ll->head가 NULL인 경우),
		cur = malloc(sizeof(ListNode)); // 새로운 원소를 생성하여 cur가 새로운 원소의 주소를 가리키도록 함
		cur->item = item; // item 넣고
		cur->next = NULL; // next는 NULL을 가리키면 되고
		ll->head = cur; // head가 새 원소 주소 가리키도록 하고
		ll->size++; // ll size 원소 하나만큼 늘려주고
		return index; // index = 0 반환
	}

	while (cur != NULL) { // 정상적으로 cur이 어떠한 원소를 가리킬 경우, cur가 가리키는 원소가 현재 원소
		if (cur->item == item) { // 만약 새로 들어올 item이 현재 원소의 값과 같다면
			return -1; // 이미 ll에 있는 값을 추가할 수 없으므로 -1을 반환하고 함수 종료
		}
		else if (cur->item > item) { // 만약 새로 들어올 item이 현재 원소의 값보다 작다면, 현재 원소의 앞에다가 item을 추가해야 함

			temp = cur; // 미리 현재 원소의 주소를 temp에 복사해 두고,
			cur = malloc(sizeof(ListNode)); // 새로운 원소를 생성하여 cur가 새로운 원소의 주소를 가리키도록 함 (현재 원소 변경)
			cur->item = item; // 새로운 원소에 item 값을 넣어 주고,
			cur->next = temp; // 새로운 원소의 next를 이전 원소의 주소로 연결해줌

			if (temp == ll->head) { // 만약 새로운 원소가 첫 번째 원소라면,
				ll->head = cur; // head를 새로운 원소의 주소로 연결해줌
			}
			else { // 만약 새로운 원소가 첫 번째 원소가 아니라면,
				pre->next = cur; // 이전 원소의 전에 있었던 원소(pre)의 next를 새로운 원소의 주소로 연결해줌
			}
			ll->size++; // ll의 size를 원소 하나만큼 증가시키고,
			return index; // 인덱스를 반환하고 함수 종료 (새로운 원소가 왼쪽에 추가되었으므로 인덱스에는 변화가 없음)

		}
		else { // 만약 새로 들어올 item이 현재 원소의 값보다 크다면,
			pre = cur; // 현재 원소의 주소를 이전 원소의 주소(pre)에 복사하고,
			cur = cur->next; // cur는 이제 다음 원소의 주소를 가리킨다 (현재 원소 변경)
			index++; // 그러면서 index가 1 증가한다
		}
	}

	
	// 연결리스트의 마지막에 도달한 경우, cur == NULL이 되어 while문 탈출
	cur = malloc(sizeof(ListNode)); // 새로운 원소 추가 
	cur->item = item; // 원소에 item 넣어주고
	cur->next = NULL; // next는 NULL
	pre->next = cur;
	ll->size++; // ll 사이즈를 원소 하나만큼 늘리고
	return index; // 인덱스 반환 후 함수 종료

}







///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
