#include <iostream>
#include <random>
#include <stack>
#include <stdexcept>
#include <vector>
#include <thread>

#include <QDebug>

using namespace std;

// CheckRange fucntion
void checkRange(pair<unsigned, unsigned> index)
{
    if (index.first < 0 || index.first > 7 || index.second < 0 || index.second > 7)
        throw out_of_range("positon must between 0, 7");
}

// _______________________________________________________________________________________

long unsigned randomNum()
{
    static mt19937 generator{random_device{}()}; // random engine

    uniform_int_distribution<long> distribution{0, 1000000000}; // range

    return distribution(generator);
}

// _______________________________________________________________________________________

void printStack(const std::stack<std::string> &moves)
{
    std::stack<std::string> temp = moves;
    qDebug() << "====================================";
    while (!temp.empty())
    {
        qDebug() << QString::fromStdString(temp.top());
        temp.pop();
    }
    qDebug() << "====================================";
}

// _______________________________________________________________________________________

template <class ContainerT, class Val1T, class Val2T>
bool multiThreadingSearch(
    ContainerT &container,                    // search area
    Val1T &src_args,                          // arg needed in function body
    bool (*check)(Val1T src_args, Val2T item) // functoin we want to call for each item in search area
)
{
    vector<thread> threads;
    bool found = false;

    // add threads
    for (auto &item : container)
    {
        threads.push_back(
            thread(
                [&src_args, &found, &item, check]()
                {
                    if (check(src_args, item))
                    {
                        found = true;
                    }
                }));
    }

    // if still not found
    if (!found)
    {
        cout << "still not found" << endl;
        // search in threads
        for (size_t i = 0; i < threads.size(); i++)
        {
            // finish a thread
            // threads can be done by priority (SJF, Prediction, ...)
            threads[i].join();
            cout << "thread " << i << " joined" << endl;

            // if found one
            if (found)
            {
                cout << "found" << endl;
                // detach other threads and exit
                for (size_t j = i + 1; j < threads.size(); j++)
                {
                    threads[j].detach();
                    cout << "thread " << j << " detached" << endl;
                }
                // *important*
                break;
            }
            // else: finish others
        }
    }
    return found;
}
