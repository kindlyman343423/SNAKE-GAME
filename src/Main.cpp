#include <iostream>
#include <cstdlib>
#include <ctime>
#include "list.h"
#include "highscores.hpp"
#include "highscores.cpp"
using namespace std;
int main()
{
    // HighScores hs;
    // data D;
    // D.score=100;
    // D.name="GAITONDE";
    // hs.insert_tail(D);
    // D.score=50;
    // D.name="GAURAV";
    // hs.insert_tail(D);
    // D.score=10;
    // D.name="WALIA";
    // hs.insert_tail(D);

    // D.score=0;
    // D.name="sadfhjsak";
    // hs.insert_at_middle_using_value(D);
    
    // hs.print();
    // hs.free();
    // exit(0);
    //DATA STRUCTURE FOR STORING THE SCORES
    //ONE MORE LINK LIST
    /*DON'T CHANGE SIZE*/
    int n=20;//rows
    int m=80;//cols
    char board[20][80];
    
    food f; //sample food
    poison p; //sample poison
    bool flagfood = true; //eated food already
    bool flagpoison = true;//eated poison already
    Snake S;

    printSnakeGameLogo(); //printing game logo
    setBoardBoundary(n,m,board); //setting boundary
    intializeBoard(n,m,board); //function for cleaning garbage

    int option;
    cout <<BYELLOW;
    cout << "SELECT ONE CHOICE"<<endl;
    cout << "1. DO YOU WANT TO START A NEW GAME"<<endl;
    cout << "2. DO YOU WANT TO START A EXISTING GAME"<<endl;
    cout << "3. SETTINGS" << endl;
    cout << "0. EXIT SNAKE GAME" <<RESET<<endl;
    cin >> option;
    if(option==1)
    {
        //new game
        //INITALIZE SNAKE
        S.insert_head(2,5,'O');
        S.insert_tail(2,4,'O');
        S.insert_tail(2,3,'O');
        S.insert_tail(2,2,'O');
        S.print();
    }
    else if(option==2)
    {
        //take food,poison and snake from file
        //reading from a file
        FILE *ptr;
        ptr=fopen("file.txt","r");
        int a,b;
        
        //for food
        fscanf(ptr,"%d %d",&a,&b);
        flagfood=false; //it will don't create food again
        f.x=a;
        f.y=b;
        f.value='F';
        board[f.x][f.y]=f.value; //insert food on board
        flagfood=false;

        //for poison
        fscanf(ptr,"%d %d",&a,&b);
        flagpoison=false; //it will not create poison again
        p.x=a;
        p.y=b;
        p.value='P';
        board[p.x][p.y]=p.value; //insert poison on board
        flagpoison=false;
        fscanf(ptr,"%d %d",&a,&b);
        S.insert_head(a,b,'O');
        while(!feof(ptr))
        {
            fscanf(ptr,"%d %d",&a,&b);
            S.insert_tail(a,b,'O');
            // cout << a << b << endl;
        }
        
        // fscanf(ptr,"%d %d",&a,&b);
        // S.insert_tail(a,b,'O');
        // fscanf(ptr,"%d %d",&a,&b);
        // S.insert_tail(a,b,'O');
        // fscanf(ptr,"%d %d",&a,&b);
        // S.insert_tail(a,b,'O');
        fclose(ptr);
    } 
    else if(option==3)
    {
        cout <<BYELLOW;
        cout << "SELECT ONE CHOICE" << endl;
        cout << "1. HIGH SCORES" << endl;
        cout << "2. CHANGE BOARD COLOR" << endl;
        cout << "3. RETURN" << endl;
        cout << RESET;
        cin >> option;

        if(option==1)
        {
            S.free();
            main();
            exit(0);
        }
        else if(option==2)
        {
            cout << "SELECT BOARD COLORS" <<endl;
            cout << "0. NO COLOR" <<endl;
            cout << "1. BGGREENISH" <<endl;
            cout << "2. BGRED" <<endl;
            cout << "3. BGLGREEN" <<endl;
            cout << "4. BGORANGE" << endl;
            cout << "5. BGLBLUE" << endl;
            cout << "6. BGPINK" << endl;
            cout << "7. BGDGREEN" << endl;
            cout << "8. BGWHITE" << endl;
            cin >> option;
            switch(option)
            {
                case 0:
                $COLOR="";
                break;
                case 1:
                $COLOR=BGGREENISH;
                break;
                case 2:
                $COLOR=BGRED;
                break;
                case 3:
                $COLOR=BGLGREEN;
                break;
                case 4:
                $COLOR=BGORANGE;
                break;
                case 5:
                $COLOR=BGLBLUE;
                break;
                case 6:
                $COLOR=BGPINK;
                break;
                case 7:
                $COLOR=BGDGREEN;
                break;
                case 8:
                $COLOR=BGWHITE;
                break;
            }
            S.free();
            main();
            exit(0);
        }
        else
        {
            S.free();
            main();
            exit(0);
        }
    }
    else
    {
        S.free();
        cout <<BBLUE<< "GAME EXITED...." <<RESET<<endl;
        exit(0);
    }
    //PRINTING SNAKE ON BOARD
    S.insertSnakeOnBoard(n,m,board);
    
    //PRINTING THE BOARD
    printarray(n,m,board);
    
    char input; //for inputing the direction
    while(1)
    {
        intializeBoard(n,m,board); //function for cleaning garbage
        if(S.getHead()==NULL)
        {
            cout <<RED<< "GAME OVER SNAKE DIED!!!!!" <<RESET<<endl;
            S.free();
            break;
        }
        p = createpoison(n,m,S,flagpoison,p); //create,get poison
        board[p.x][p.y]=p.value; //insert poison on board
        flagpoison=false;
        
        f = createfood(n,m,S,flagfood,f); //create,get food
        board[f.x][f.y]=f.value; //inseert food on board
        flagfood=false;

        cout << "Enter the option" << endl;
        cout << "W / w ---- UP" << endl;
        cout << "S / s ---- DOWN" << endl;
        cout << "A / a ---- LEFT" << endl;
        cout << "D / d ---- RIGHT" <<endl;
        cout << "C / c / V / v ---- SAVE GAME" <<endl;
        cout << "X / x ---- EXIT THIS GAME" <<endl;
        cout << "R / r ---- SAVE AND EXIT"<<endl;
        cin >> input;
        if(input=='W' || input=='w') //UP
        {
            S.moveUp(n,m,board,f,p,&flagfood,&flagpoison);
            S.print();
        }
        else if(input=='S' || input=='s') //DOWN
        {
            S.moveDown(n,m,board,f,p,&flagfood,&flagpoison);
            S.print();
        }
        if(input=='D' || input=='d') //right
        {
            S.moveRight(n,m,board,f,p,&flagfood,&flagpoison);
            S.print();
        }
        else if(input=='A' || input=='a') //left
        {
            S.moveLeft(n,m,board,f,p,&flagfood,&flagpoison);    
            S.print();
        }
        else if(input=='C' || input=='c' || input=='V'||input=='v')
        {
            //for saving game
            FILE *ptr;
            ptr=fopen("file.txt","w");
            fclose(ptr);
            S.save(f,p);
            S.free();
            break;
        }
        else if(input=='X' || input=='x')
        {
            //for exiting game
            main();
            exit(0);
        }
        else if(input=='R'||input=='r')
        {
            //for save and exit
            break;
        }
        /*PRINTING SNAKE ON BOARD*/
        S.insertSnakeOnBoard(n,m,board);

        /*PRINTING THE BOARD*/
        printarray(n,m,board);
        cout <<"CURRENT SCORE:" << S.getScore() << endl;
    }
    
    cout << BOLD << "----------------------------" << endl;
    cout << "FINAL SCORE: " << S.getScore() << endl;
    cout << "----------------------------" << RESET << endl;
}