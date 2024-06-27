#include<iostream>
#include<fstream>
#include<string>
#include<forward_list>
#include<conio.h>
#include<stdlib.h>
using namespace std;
// Text Color Function
void red()      {   cout<<"\033[1;31m";   }
void yellow()   {   cout<<"\033[1;33m";   }
void Blue()     {   cout<<"\033[0;34m";   }
void Green()    {   cout<<"\033[0;32m";   }
void Purple()   {   cout<<"\033[0;35m";   }
void White()    {   cout<<"\033[0;37m";   }
void Cyan()     {   cout<<"\033[0;36m";   }
void reset()    {   cout<<"\033[0m";      }

struct Task_Node
{
    string Task_Title;
    string Task_Description;
    string Task_Due_Date;
    Task_Node()     {}
    Task_Node(string &T,string &D,string &DD){
        Task_Title = T;
        Task_Description = D;
        Task_Due_Date = DD;
    }
    void Print_Task()   {
        Green();
        cout<<"|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout<<"| Task Title       : "<<Task_Title<<endl;
        cout<<"| Task Description : "<<Task_Description<<endl;
        cout<<"| Task Due Date    : "<<Task_Due_Date<<endl;
        cout<<"|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        reset();
    }
};

class Task_Manager
{
    private:
        forward_list <Task_Node> Start;
    public:
        Task_Manager()  {   Load_Tasks();   }
        void Main_Menu();
        void Add_Task();
        void Delete_Task(string &);
        void View_All_Tasks();
        void Load_Tasks();
        void Unload_Tasks();
        ~Task_Manager(){    Unload_Tasks(); }
};

void Task_Manager::Main_Menu()
{
    char choice;
    string temp;
    do  {
        Cyan();
        cout<<"\n_________________________"<<endl;
        cout<<"Enter 1 For Add a Task"<<endl;
        cout<<"Enter 2 For Delete a Task"<<endl;
        cout<<"Enter 3 For View all Task"<<endl;
        cout<<"Enter 0 For Exit"<<endl;
        cout<<"Enter your choice : ";
        choice = getche();
        cout<<"\n_________________________"<<endl;
        reset();
        system("cls");
        switch(choice)  {
            case '1':
                Add_Task();
                break;
            case '2':
                cout<<"\n------------------------------\n";
                if(Start.empty())   {
                    red();
                    cout<<"Deletion not Possible\n";
                    cout<<"Task Manager is Empty\n";
                    Green();
                    cout<<"Fist add Task in Task Manager\n";
                    reset();
                    cout<<"------------------------------\n";
                }
                else {
                    cout<<"Enter Task Title : ";
                    getline(cin,temp);
                    Delete_Task(temp);
                }
                break;
            case '3':
                View_All_Tasks();
                break;
            case '0':
                cout<<"\nThank You\n";
                break;
            default:
                red();
                cout<<"\n|~~~~~~~~~~~~~~~~~~~~~~~~~~~~|";
                cout<<"\n| Your Choice is invalid : "<<choice<<" |";
                cout<<"\n|~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n";
                reset();
        }
    }while(choice != '0');
}

void Task_Manager::Add_Task()   {
    Task_Node Task_Data;
    Purple();
    cout<<"\n-------------------------------\n";
    cout<<"Enter Task Title         : ";
    getline(cin, Task_Data.Task_Title);
    cout<<"Enter Task Description   : ";
    getline(cin, Task_Data.Task_Description);
    cout<<"Enter Due Date (DD/MM/YY): ";
    getline(cin, Task_Data.Task_Due_Date);
    Start.push_front(Task_Data);
    cout<<"\nTask Add Successful";
    cout<<"\n-------------------------------\n";
    reset();
}

void Task_Manager::Delete_Task(string &Title)   {

    forward_list<Task_Node>::iterator it;
    forward_list<Task_Node>::iterator it1;

    bool flag = true;
    it = Start.begin();
    red();

    if((*it).Task_Title == Title)   {
        Start.erase_after(Start.before_begin());
        cout<<"\nDeletion Successful\n";
        it = Start.end();
        flag = false;
    }

    while(it != Start.end())   {
        if((*it).Task_Title == Title)  {
            Start.erase_after(it1);
            cout<<"\nDeletion Successful\n";
            flag = false;
            break;
        }
        it1 = it++; // Post Increment
    }

    reset();
    if(flag)
        cout<<"\nTitle Not Found in the Task Manager\n";
}

void Task_Manager::View_All_Tasks() {
    if(!Start.empty())
        for(Task_Node &temp : Start)
            temp.Print_Task();
    else
        cout<<"\n|-----------------------|\n| Task Manager is Empty |\n|-----------------------|\n";
}

void Task_Manager::Load_Tasks() {
    Start.clear();
    string title, date,description;
    ifstream fin;
    fin.open("Database_Tasks.txt");
    if(!fin)
        cout<<"\nTask Manager is Empty\n";
    else    {
        fin.ignore();
        while(!fin.eof())   {
            getline(fin, title);
            getline(fin, date);
            getline(fin, description);
            Start.push_front(Task_Node(title,description,date));
        }
        fin.close();
    }
}

void Task_Manager::Unload_Tasks()   {
    Task_Node temp;
    ofstream fout;
    if(!Start.empty())  {
        fout.open("Database_Tasks.txt");
            while(!Start.empty())   {
                temp = Start.front();
                fout<<'\n'<<temp.Task_Title;
                fout<<'\n'<<temp.Task_Due_Date;
                fout<<'\n'<<temp.Task_Description;
                Start.pop_front();
            }
        fout.close();
    }
    else
        remove("Database_Tasks.txt");
}

int main()
{
    Task_Manager t1;
    t1.Main_Menu();
    return 0;
}
