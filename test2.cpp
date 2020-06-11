#include <iostream>
#include <random>
#include <ctime>
#include <queue>

/// "Factory" function to generate  sequential integers (beginning with 1)
/// * Creates 1-5 values and passes them one at a time to 4 separate priority queues
/// * On subsequent iterations, the factory will pick up where it left off (if it dealt numbers to queues 0 and 1, then next time it would deal to 2)
/// Separate "receiver" function that randomly chooses one of the queues, pops one value from the queue, and loads that into a stack
/// Runs for five steps and then displays the contents of each queue and the stack
/// Prompts to see if user wants to run for another five steps
/// Output is like such:
/// Factory generates: 1, 2, 3
/// Q0: 1   Q1: 2   Q2: 3   Q3: empty
/// Stack: empty
/// Receiver choice: 1
/// Q0: 1   Q1: empty   Q2: 3   Q3: empty
/// Stack: 2

using namespace std;

/// ================================================================================
/// MAIN
/// ================================================================================

void display(priority_queue<int> q[], vector<int>& v);
void factory(int& lastInt, int& lastQ, priority_queue<int> q[], vector<int>& v);
void receiver(priority_queue<int> q[], vector<int>& v);
void step(int& lastInt, int& lastQ, priority_queue<int> q[], vector<int>& v);
int prompt(int& lastInt, int& lastQ, priority_queue<int> q[], vector<int>& v);

int main(int argc, char* argv[])
{
    int lastInt = 1;
    int lastQ = 0;
    vector<int> v;

    cout << "*******************************************************" << endl;
    cout << "\t\tDANIELLE D. BERTULFO" << endl;
    cout << "\t\tFINAL EXAM - PART B - PROBLEM 5" << endl;
    cout << "\t\tFACTORY" << endl;
    cout << "*******************************************************" << endl;

    priority_queue<int> q[4];
    int ui = -1;

    while(ui != 2)
    {
        ui = prompt(lastInt, lastQ, q, v);
    }

    return 0;
}

void display(priority_queue<int> q[], vector<int>& v)
{
    vector<int> iTemp;
    int temp;
    for(int i=0; i<4; i++)  /// Displaying queues
    {
        cout << "q" << i << ": ";
        //cerr << "* display()" << endl;
        while(!q[i].empty())    /// Put into temporary vector when poppin'
        {
            temp = q[i].top();
            cout << temp << " ";
            iTemp.push_back(temp);
            q[i].pop();
        }
        for(unsigned int j=0; j<iTemp.size(); j++)   /// Put back into queue
        {
            q[i].push(iTemp[j]);
        }
        while(!iTemp.empty())   /// Empty iTemp
        {
            iTemp.pop_back();
        }
        cout << "\t";
    }

    cout << endl;

    cout << "Stack: ";  /// Displaying stack
    if(v.empty())
    {
        cout << "empty";
    }
    else
    {
        for(unsigned int i=0; i<v.size(); i++)
        {
            cout << v[i];
            if(i != v.size()-1)
            {
                cout << ", ";
            }
        }
    }
    cout << endl;
}

void factory(int& lastInt, int& lastQ, priority_queue<int> q[], vector<int>& v)
{
    int numToGen = 1 + rand()%5;
    //cerr << "* numToGen = " << numToGen << endl;
    cout << "Factory generates: ";
    for(int i=0; i<numToGen; i++)
    {
        q[lastQ].push(lastInt);
        cout << lastInt;
        if(i < numToGen-1)
        {
            cout << ", ";
        }
        lastInt++;

        lastQ++;
        if(lastQ == 4)
        {
            lastQ = 0;
        }
        //cerr << "* lastQ = " << lastQ << endl;
    }
    cout << endl;

    display(q,v);
}

void receiver(priority_queue<int> q[], vector<int>& v)
{
    int qToPop = rand()%4;
    cout << "Receiver choice: " << qToPop << endl;
    int valuePopped = -1;

    if(!q[qToPop].empty())
    {
        //cerr << "* Poppin' from " << qToPop << ". ";
        valuePopped = q[qToPop].top();
        //cerr << "Value popped is " << valuePopped << "." << endl;
        v.push_back(valuePopped);
        //cerr << "* Size of v is now " << v.size() << ", ";
        q[qToPop].pop();
        //cerr << "size of q[qToPop] is now " << q[qToPop].size() << endl;
    }

    display(q,v);
}

void step(int& lastInt, int& lastQ, priority_queue<int> q[], vector<int>& v)
{
    cout << "-------------------------------------------------------" << endl;
    factory(lastInt, lastQ, q, v);
    receiver(q, v);
    cout << endl;
}

int prompt(int& lastInt, int& lastQ, priority_queue<int> q[], vector<int>& v)
{
    int ui;

    cout << "=======================================================" << endl;
    cout << "\tDisplay next five steps? (1) Yes, (2) No" << endl;
    cout << "\t";
    cin >> ui;

    for(int i=0; i<5; i++)
    {
        cout << "STEP " << i+1 << endl;
        step(lastInt, lastQ, q, v);
        cout << endl;
    }

    return ui;
}
