#include "rainbow.h"
using namespace std;
string $COLOR=BBGDGREEN;  //environment variable for changing board color

//node food for snake
struct food
{
    int x;
    int y;
    char value;
};
struct poison
{
    int x;
    int y;
    char value;
};
//FUNCTIONS
/*
 * cleans and add spaces to the board
 */
void intializeBoard(int n,int m,char board[][80])
{
    for(register int i=1;i<n-1;i++)
    {
        for(register int j=1;j<m-1;j++)
        {
            board[i][j]=' ';
        }
    }
}
/*
 *  set board boundary
 */
void setBoardBoundary(int n,int m,char board[][80])
{
    /*MAKIING BOARD BOUNDARY*/
    //horizontal
    for(register int i=0;i<m;i++)
    {
        board[0][i]='X';
        board[n-1][i]='X';
    }
    //left vertical
    for(register int i=1;i<n-1;i++)
    {
        board[i][0]='X';
        board[i][m-1]='X';
    }
}
//UI OF THE BOARD
// //function printing the board
void printarray(int n,int m,char board[][80])
{
    for(register int i=0;i<n;i++)
    {
        cout << $COLOR;
        for(register int j=0;j<m;j++)
        {
            if(board[i][j]=='F')
            {
                cout<<BYELLOW;
            }
            else if(board[i][j]=='P')
            {
                cout <<RED;
            }
            cout << board[i][j];
            // cout << WHITE;
            cout << RESET << $COLOR;
        }
        if(i==n-1)
        {
            cout << RESET;
        }
        cout <<RESET<< endl;
    }
    cout << RESET;
    cout << endl;
}
/*********************************************************/
/*********************************************************/
struct node
{
    int x;
    int y;
    char value;
    node* next;
};
class Snake
{
    node *head;
    node *tail;
    int score;
    public:
    Snake()
    {
        head = NULL;
        tail = NULL;
        score=0;
    }
    node* getHead()
    {
        return head;
    }
    node* getTail()
    {
        return tail;
    }
    int getScore()
    {
        return score;
    }
    //FUNCTIONS
    /*############################################################*/
    /*=======================> create node <======================*/
    node *create(int a,int b,char val)
    {
        node *newNode = new node;
        newNode->x = a;
        newNode->y = b;
        newNode->value=val;
        return newNode;
    }
    /*===========> delete the all the nodes of the linked list <==========*/
    void free()
    {   
        delete [] head;
        delete [] tail;
        delete head;
        delete tail;
    }
    /*############################################################*/
    /*===============> INSERT AT HEAD OF THE SNAKE <==============*/
    void insert_head(int x,int y,char value)
    {
        node *newNode = create(x,y,value);
        if(head==NULL)
        {
            //null linked list
            head = newNode;
            tail = newNode;
            head->value='H';
        }
        else
        {
            //no need to  change tail
            newNode->next = head;
            head->value='O';
            head = newNode;
            head->value='H';
        }
        score++;
    }

    /*############################################################*/
    /*===============> INSERT AT TAIL OF THE SNAKE <==============*/
    void insert_tail(int x,int y,int value)
    {
        node* newNode = create(x,y,value);
        if(head==NULL)
        {
            head=newNode;
            tail=newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->next=NULL;
            tail = newNode;
        }
        score++;
    }
    
    /*############################################################*/
    /*===============> DELETE FROM HEAD IN A SNAKE <==============*/
    void delete_head()
    {
        if(head==NULL)
        {
            return;
        }
        node *temp=head;
        temp->value='O';
        head=head->next;
        head->value='H';
        temp->next=NULL;
        delete(temp);
        score--;
    }

    /*############################################################*/
    /*===============> DELETE TAIL OF SNAKE <==============*/
    void delete_tail()
    {
        if(head==NULL)
        {
            // cout << "GAME OVER"<<endl;
            return;
        }
        else if(head->next==NULL)
        {
            head=NULL;
            tail=NULL;
        }
        else
        {
            node *current=head;
            node *prev=head;
            while(current->next!=NULL)
            {
                prev=current;
                current=current->next;
            }
            prev->next=NULL;
            delete(current);
        }
        score--;
    }

    /*############################################################*/
    /*===============> PRINTING THE SNAKE <==============*/
    void print()
    {
        node *current = head;
        while(current!=NULL)
        {
            cout << current->x;
            cout << current->y;
            cout << current->value;
            cout << " -> ";
            current=current->next;
        }
        cout<< "NULL" << endl; 
    }

    void save(food f,poison p)
    {
        FILE *ptr;
        ptr=fopen("file.txt","a");
        fprintf(ptr,"%d %d\n",f.x,f.y);
        fprintf(ptr,"%d %d\n",p.x,p.y);
        node* current=head;
        while(current!=NULL)
        {
            fprintf(ptr,"%d %d\n",current->x,current->y);
            current=current->next;
        }
        
        fclose(ptr);
    }
    /*############################################################*/
    /*===============> INSERT SNAKE ON BOARD <==============*/
    void insertSnakeOnBoard(int n,int m,char board[][80])
    {
        node *current=head;
        while(current!=NULL)
        {    
            board[current->x][current->y]=current->value;
            current=current->next;
        }
    }

    /*############################################*/
    /*===============> EAT FOOD <==============*/
    void eatfood(int a,int b,int n,int m)
    {
        int flag=0;
        int check=0;
        //traversing the list snake
        node *current=head;
        while(current!=NULL)
        {
            if(current->x == a && current->y == b)
            {
                flag=1;
                break;
            }
            current=current->next;
        }
        //FOR VALID BUT ENTERING AGAIN
        if(a > 0 && a < n-1 && b < m-1 && b>0 && flag==0)
        {
            check=1;
        }
        else
        {
            check=0;
        }
        cout << "CHECK" << check<<endl;
        if(check)
        {
            insert_head(a,b,'O');
            // delete_tail();
        }
    }

    /*############################################*/
    /*===============> MOVE RIGHT <==============*/
    void moveRight(int n,int m,char board[][80],food F,poison P,bool *fptr,bool *pptr)
    {
        int a = head->x;
        int b = head->y+1;
        if(a==F.x && b==F.y) //if food found
        {
            eatfood(a,b,n,m);
            //delete food
            *fptr = true;//set boolean of food to true means food eated
        }
        else if(a==P.x && b==P.y) //if poison found
        {
            printf("%d %d\n",P.x,P.y);
            //delte tail node
            delete_tail();
            checkandadd(a,b,n,m);
            *pptr=true; //poison eated set bool to true
        }
        else
        {
            //simple right no chnages
            checkandadd(a,b,n,m);
        }
    }

    /*############################################*/
    /*===============> MOVE LEFT <==============*/
    void moveLeft(int n,int m,char board[][80],food F,poison P,bool *fptr,bool *pptr)
    {
        int a = head->x;
        int b = head->y-1;
        if(a==F.x && b==F.y) //if food found
        {
            eatfood(a,b,n,m);
            //delete food
            *fptr=true; //food eated
        }
        else if(a==P.x && b==P.y) //if poison found
        {
            printf("%d %d\n",P.x,P.y);
            //delte tail node
            delete_tail();
            checkandadd(a,b,n,m);
            *pptr=true; //poison eated
        }
        else
        {
            //simple left no changes
            checkandadd(a,b,n,m);
            
        }
        
    }

    /*############################################*/
    /*===============> MOVE UP <==============*/
    void moveUp(int n,int m,char board[][80],food F,poison P,bool *fptr,bool *pptr)
    {
        int a = head->x - 1;
        int b = head->y;
        if(a==F.x && b==F.y) //if food found
        {
            eatfood(a,b,n,m);
            //delete food
            *fptr=true; //food eated
        }
        else if(a==P.x && b==P.y) //if poison found
        {
            printf("%d %d\n",P.x,P.y);
            //delte tail node
            delete_tail();
            checkandadd(a,b,n,m);
            *pptr = true; //poison eated
        }
        else
        {
            //simple up no changes
            checkandadd(a,b,n,m);
            
        }
        
    }

    /*############################################*/
    /*===============> MOVE DOWN <==============*/
    void moveDown(int n,int m,char board[][80],food F,poison P,bool *fptr,bool *pptr)
    {
        int a = head->x + 1;
        int b = head->y;
        if(a==F.x && b==F.y) //if food found
        {
            eatfood(a,b,n,m);
            //delete food
            *fptr=true; //food eated
        }
        else if(a==P.x && b==P.y) //if poison found
        {
            printf("%d %d\n",P.x,P.y);
            //delte tail node
            delete_tail();
            checkandadd(a,b,n,m);
            *pptr=true; //poison eated
        }
        else
        {
            //simple down no chnages
            checkandadd(a,b,n,m);   
        }
    }

    /*######################################################*/
    /*======> FUNCTION FOR CHECKING ITS VALID OR NOT <======*/
    void checkandadd(int a,int b,int n,int m)
    {
        int flag=0;
        int check=0;
        //traversing the list snake
        node *current=head;
        while(current!=NULL)
        {
            if(current->x == a && current->y == b)
            {
                flag=1;
                break;
            }
            current=current->next;
        }
        //FOR STOPPING GAME when on boundary or on snake
        if(a==0 || a==n-1 || b==m-1 || b==0 || flag==1)
        {
            cout << "GAME OVER" <<endl;
            cout << BOLD << "----------------------------" << endl;
            cout << "FINAL SCORE: " << score << endl;
            cout << "----------------------------" << RESET << endl;
            exit(0);
        }
        //FOR VALID BUT ENTERING AGAIN
        if(a > 0 && a < n-1 && b < m-1 && b>0 && flag==0)
        {
            check=1;
        }
        else
        {
            check=0;
        }
        cout << "CHECK" << check<<endl;
        if(check)
        {
            insert_head(a,b,'O');
            delete_tail();
        }
        else
        {
            cout << "ENTER VALID COORDINATES" << endl;
        }
    }
};

/****************************************************************/
/*=======================> generate valid value in between matrix <========================*/
int generateValue(int n,int m,int check)
{
    int val=-1;
    // srand(time(0));
    if(check==1) //for x
    {
        srand(time(0));
        while(1)
        {
            val = rand()%100;
            // val=val/10000000;
            // cout << val << endl;
            if(val>0 && val<n-1)
            {
                break;
            }
        }
    }
    else if(check==2) //for y
    {
        srand(time(0));
        while(1)
        {
            val = rand()%100;
            // val=val/10000000;
            // cout << val << endl;
            if(val>0 && val<m-1)
            {
                break;
            }
        }
    }
    else if(check==3) //for x poison
    {
        // srand(time(0));
        while(1)
        {
            val = rand()%100;
            // val=val/10000000;
            // cout << val << endl;
            if(val>0 && val<n-1)
            {
                break;
            }
        }
    }
    else if(check==4) //for x poison
    {
        // srand(time(0));
        while(1)
        {
            val = rand()%100;
            // val=val/10000000;
            // cout << val << endl;
            if(val>0 && val<n-1)
            {
                break;
            }
        }
    }
    return val;
}
/****************************************************************/
/*=======================> create food <========================*/
food createfood(int n,int m,Snake s,bool flagfood,food F)
{
    if(flagfood)
    {
        //food eated
        //then create new food
        int valx=0,valy=0;
        while(1)
        {
            valx=generateValue(n,m,1); //generating random value in array
            valy=generateValue(n,m,2); //generating random value in array
            int flag=0;
            node *current=s.getHead();
            while(current!=NULL)
            {
                if(current->x==valx && current->y==valy)
                {
                    flag=1;
                    break;
                }
                current=current->next;
            }
            if(flag==0)
            {
                break;
            }
        }
        cout <<"valx:"<< valx<<"valy:" << valy << endl;
        F.x = valx;
        F.y = valy;
        F.value='F';
    }
    // else
    // {
    //     //food not eated do nothing
    // }
    return F;
}
/****************************************************************/
/*=======================> createpoison <========================*/
poison createpoison(int n,int m,Snake s,bool flagpoison,poison P)
{
    if(flagpoison)
    {
        //poison eated
        //then create new poison
        int valx=0,valy=0;
        while(1)
        {
            valx=generateValue(n,m,3); //generating random value in array
            valy=generateValue(n,m,4); //generating random value in array
            int flag=0;
            node *current=s.getHead();
            while(current!=NULL)
            {
                if(current->x==valx && current->y==valy)
                {
                    flag=1;
                    break;
                }
                current=current->next;
            }
            if(flag==0)
            {
                break;
            }
        }
        cout <<"valx:"<< valx<<"valy:" << valy << endl;
        P.x = valx;
        P.y = valy;
        P.value='P';
    }
    return P;
}
/****************************************************************/
/*=======================> SNAKE UI <========================*/
void printSnakeGameLogo()
{
    cout << BLUE;
    for(int i=0;i<80;i++)
    {
        cout <<"=";
    }
    cout << RESET<<endl;
    cout << BGREEN;
    cout << "\t" << "@ @ * * *" <<"\t"<< "----- --   -      -     |  /   -----"<<endl;
    cout << "\t" << " ~      *" <<"\t"<< "|     | \\  |     / \\    | /    |    "<<endl;
    cout << "\t" << "  * * * *" <<"\t"<< "----- |  \\ |    /---\\   |/\\    -----"<<endl;
    cout << "\t" << "  *      " <<"\t"<< "    | |   \\|   /     \\  |  \\   |    "<<endl;
    cout << "\t" << "  * * * *" <<"\t"<< "----- |    |  /       \\ |   \\  -----"<<endl;   
    cout << RESET;
    cout << BOLD << "\t\t\t\t\t\t\t\t       version 2" << RESET << endl;
    cout << BLUE;
    for(int i=0;i<80;i++)
    {
        cout <<"=";
    }
    cout << RESET<<endl; 
}