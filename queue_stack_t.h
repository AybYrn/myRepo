//
// Stack Implementation
//
#define _CRT_SECURE_NO_WARNINGS
#define QUEUE_SIZE  100

typedef  stack_t  QType;

//QType  QUEUE_EMPTY = { 0, 0 };

typedef struct
{	int	front, rear, count;
	QType data[QUEUE_SIZE];
} queue_t;

//Functions in this file...
void initializeQ (queue_t*q);
int isEmptyQ (queue_t*q);
int isFullQ (queue_t*q);
void insertQ (queue_t*q, QType item);
QType removeQ (queue_t*q);

//------------------------------------------------------------------------------

void initializeQ (queue_t*q)
{
	q->front = 0;
	q->rear = -1;
	q->count = 0;
}

//------------------------------------------------------------------------------

int isEmptyQ (queue_t*q)
{
	if (q->count == 0)
		return 1;
	return 0;
}

//------------------------------------------------------------------------------

int isFullQ (queue_t*q)
{
	if (q->count == QUEUE_SIZE)
		return 1;
	return 0;
}

//------------------------------------------------------------------------------

void insertQ (queue_t*q, QType item)
{
	if (isFullQ (q))
		printf("Error: Stack is full!\n");
	else
	{
		q->rear = (q->rear + 1) % QUEUE_SIZE;
		q->data[q->rear] = item;
		(q->count)++;
	}
}

//------------------------------------------------------------------------------

QType removeQ (queue_t*q)
{
	QType item;
	if (isEmptyQ(q))
	{	printf("Error: Stack is empty!\n");
		//item = QUEUE_EMPTY;	
	}
	else
	{	item = q->data[q->front];
		q->front = (q->front + 1) % QUEUE_SIZE;
		(q->count)--;
	}		    	
	return (item);
}
