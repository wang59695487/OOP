//enum bool{false,true};

struct node
{
	 int val;
	 node *next;
};
typedef struct node* PNODE;

class intlist{
private: 
	PNODE head;
	int size;
public:   
	intlist() : head(0),size(0)
	{	}

	~intlist();
	void insert(int); 		//插在链头
	void append(int);		//插在链尾
	int get();				//取出链头数据
	void print();			//遍历
};





