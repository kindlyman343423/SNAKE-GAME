//DOUBLE LINKED LIST
//DATA
struct data
{
    int score;
    string name;
};
//node for highscores
struct hnode
{
    struct data D;
    struct hnode *next;
    struct hnode *prev;
};

//HighScores class for storing high scores
class HighScores
{
    struct hnode* head;
    struct hnode* tail;
    public:
    HighScores()
    {
        head=NULL;
        tail=NULL;
    }
    struct hnode* create(struct data D)
    {
        struct hnode* newNode = new hnode;
        newNode->D = D;
        newNode->next=NULL;
        newNode->prev=NULL;
    }
    void insert_head(struct data D)
    {
        struct hnode* newNode = create(D);
        if(head==NULL)
        {
            head=newNode;
            tail=newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    void insert_tail(struct data D)
    {
        struct hnode* newNode = create(D);
        if(head==NULL)
        {
            head=newNode;
            tail=newNode;
        }
        else
        {
            tail->next=newNode;
            newNode->prev=tail;
            tail=newNode;   
        }
    }
    void insert_at_middle_using_value(struct data D)
    {
        struct hnode* newNode = create(D);
        if(head=NULL)
        {

        }
        else
        {
            struct hnode* current=head;
            struct hnode* prev=head;
            while(current!=NULL)
            {
                if(D.score < current->D.score)
                {
                    prev=current;
                    current=current->next;
                }
                else
                {   
                    //insert
                    cout << current->D.name << endl;
                    cout << prev -> D.name << endl;
                }
            }
        }

    }
    void free()
    {
        head=NULL;
        tail=NULL;
        delete head;
        delete tail;
    }
    void print()
    {
        if(head==NULL && tail==NULL)
        {
            cout << "NULL" << endl;
        }
        else
        {
            hnode* current=head;
            while(current!=NULL)
            {
                cout << current->D.name << "\t" << current->D.score << endl;
                current=current->next;
            }
        }
    }
};