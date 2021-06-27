//
// Stack Implementation, CTIS 152
//
#define _CRT_SECURE_NO_WARNINGS

typedef vegAndFruit_t  LType;

typedef struct node_s
{	
	LType data;
	struct node_s* next;
} node_t;

//Functions in this file...

node_t* getNode();
void addAfter(node_t* p, LType item);
node_t* addBegining(node_t* headp, LType item);
void deleteAfter(node_t *p, LType item);
node_t* deleteFirst(node_t* headp, LType item);

//------------------------------------------------------------------------------

node_t* getNode() {
	node_t* node;
	node = (node_t*)malloc(sizeof(node_t));
	node->next = NULL;
	return node;
}

//------------------------------------------------------------------------------

void addAfter(node_t* p, LType item) {
	node_t* newp = getNode();
	newp->data = item;
	newp->next = p->next;
	p->next = newp;
}

//------------------------------------------------------------------------------

node_t* addBegining(node_t* headp, LType item) {
	node_t* newp = getNode();
	newp->data = item;
	newp->next = headp;
	return(newp);
}

//------------------------------------------------------------------------------

void deleteAfter(node_t* p, LType item) {
	node_t* del = p->next;
	item = del->data;
	p->next = del->next;
	free(del);
}

//------------------------------------------------------------------------------

node_t* deleteFirst(node_t* headp, LType item) {
	node_t* del = headp;
	item = del->data;
	headp = del->next;
	free(del);
	return headp;
}

//------------------------------------------------------------------------------

node_t* destroyList(node_t* headp) {
	node_t* p;
	while (headp != NULL)
	{
		p = headp;
		headp = headp->next;
		free(p);
	}
	return (headp);
}

