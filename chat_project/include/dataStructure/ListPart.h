

#define HEAD_NEXT(L) ((L) -> m_head.m_next)
#define TAIL_NEXT(L) ((L) -> m_tail.m_next)
#define TAIL_PREV(L) ((L) -> m_tail.m_prev)
#define HEAD(L) (&((L) -> m_head))
#define TAIL(L) (&((L) -> m_tail))

typedef struct Node Node;

struct Node{
	const void* m_data;
	Node *m_next;
	Node *m_prev;
};

struct List{
	Node m_head;
	Node m_tail;	
};

void DestroyNode(Node *_prevNode,Node *_toDestroyNode);
void InsertNode(Node *_prevNode,Node *_newNode);
Node* CreateNode(const void* _data);

