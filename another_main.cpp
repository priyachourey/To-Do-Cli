#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

struct Task
{
    string description;
    bool completed;

    Task(const string &description) : description(description), completed(false) {}
};

void loadTask(vector<Task> &task)
{

    ifstream read("Task.txt");
    if (read.is_open())
    {
        string line;
        while (getline(read, line))
        {
            task.push_back({line});
        }
        read.close();
    }
}

void Save_Task(vector<Task> &task)
{
    ofstream write("Task.txt");
    for (const Task &task : task)
    {
        write << task.description << endl;
    }
    write.close();
}

void help()
{
    cout << "How to use the app" << endl;
    cout << "./another_main add \"your task\"________________# To Add Task use double quotes" << endl;
    cout << "./another_main list_____________________________# To get the list of your task" << endl;
    cout << "./another_main complete <task index>____________# To mark the task completed" << endl;
    cout << "./another_main remove <task index>______________# To remove the task" << endl;
}

void listing(vector<Task> &Task)
{
    for (size_t i = 0; i < Task.size(); ++i)
    {
        cout << i + 1 << "->";
        if (Task[i].completed == true)
        {
            cout << "[O] ";
        }
        else
        {
            cout << "[] ";
        }
        cout << Task[i].description << endl;
    }
}

void AddTask(string &desc, vector<Task> &task)
{
    task.push_back({desc});
}

void remove(int &TaskIndex, vector<Task> &task)
{
    if (TaskIndex >= 1 && TaskIndex <= task.size())
    {
        task.erase(task.begin() + TaskIndex);
        cout << "Task removed" << endl;
    }
    else
    {
        cout << "invalid index...." << endl;
    }
}

void completed_task(int &TaskIndex, vector<Task> &tasks)
{
    if (TaskIndex >= 0 && TaskIndex < tasks.size())
    {
        tasks[TaskIndex].completed = true;
        cout << "Task marked as completed" << endl;
        cout<< tasks[TaskIndex].completed;
    }
    else
    {
        cout << "invalid index....." << endl;
    }
}



int main(int argc, char *argv[])
{
    vector<Task> tasks;

    loadTask(tasks);
    string command = argv[1];
    if (command == "help")
    {
        help();
    }
    else if (command == "list")
    {
        if (tasks.empty())
        {
            cout << "no task present right now" << endl;
        }
        listing(tasks);
    }
    else if (command == "add")
    {
        if (argc < 3)
        {
            cout << "arguments are not sufficient...Task not provided" << endl;
            cout << "use 'help' command for more info " << endl;
        }
        else
        {
            string TaskDesc = argv[2];
            AddTask(TaskDesc, tasks);
            cout << "Task added" << endl;
        }
    }

    else if (command == "remove")
    {
        if (argc < 3)
        {
            cout << "arguments are not sufficient.....task index required" << endl;
            cout << "use 'help' command for more info " << endl;
        }
        else
        {
            int index = stoi(argv[2]);
            remove(index, tasks);
        }
    }

    else if (command == "complete")
    {
        if (argc < 3)
        {
            cout << "arguments are not sufficient......task index required" << endl;
            cout << "use 'help' command for more info " << endl;
        }
        else
        {
            int index = stoi(argv[2]) - 1;
            completed_task(index, tasks);
        }
    }

    else
    {
        cout << "invalid command...." << endl;
        cout << "use 'help' command for more info " << endl;
    }

    Save_Task(tasks);
    return 0;
}