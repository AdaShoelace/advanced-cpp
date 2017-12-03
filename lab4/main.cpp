#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <forward_list>


using std::vector;
using std::cout;

void random_fill_array(int* arr, int length);
void random_fill_vec(vector<int>& in);
void random_fill_forward_list(std::forward_list<int>& in);
void print_vec(const vector<int>& to_print);
void print_array(int* arr, int length);
void print_forward_list(std::forward_list<int>& in);

//Uses bubblesort O(n^2) BAD!!!
template<typename ForwardIterator>
void forward_sort(ForwardIterator begin, ForwardIterator end);


const int ARR_LENGTH = 15;

int main()
{
    srand((unsigned)time(NULL));

    //Vector
    vector<int> first_vec;
    first_vec.reserve(15);
    random_fill_vec(first_vec);

    //Unsorted
    cout << "(Vec) Pre sorting:\n";
    print_vec(first_vec);

    //Sorted
    std::sort(first_vec.begin(), first_vec.end());
    cout << "(Vec, Incline) Post sorting:\n";
    print_vec(first_vec);


    //Raw array
    int arr[ARR_LENGTH];
    random_fill_array(arr, ARR_LENGTH);

    //Unsorted
    cout << "(Raw array) Pre sorting:\n";
    print_array(arr, ARR_LENGTH);

    //Sorted
    std::sort(arr, arr + ARR_LENGTH);
    cout << "(Raw array, Incline) Post sorting:\n";
    print_array(arr, ARR_LENGTH);

    //Vec decline
    std::sort(first_vec.rbegin(), first_vec.rend());
    cout << "(Vec, Decline) Post sorting:\n";
    print_vec(first_vec);

    //Array decline
    std::sort(arr, arr + ARR_LENGTH, [](int a, int b) { return a > b;});
    cout << "(Raw array, Decline) Post sorting:\n";
    print_array(arr, ARR_LENGTH);

    //Remove even # from std::vec
    first_vec.erase(std::remove_if(first_vec.begin(), first_vec.end(), [](const int& a){return a % 2 == 0;}), first_vec.end());
    cout << "(Vec) Even numbers removed:\n";
    print_vec(first_vec);

    //Create and sort forward list
    std::forward_list<int> fw_list;
    random_fill_forward_list(fw_list);
    cout << "(forward_list) Pre sorting:\n";
    print_forward_list(fw_list);
    forward_sort(fw_list.begin(), fw_list.end());
    cout << "(forward_list) Post sorting:\n";
    print_forward_list(fw_list);
}

void random_fill_vec(vector<int>& in)
{
    for(int i = 0; i < in.capacity(); ++i)
    {
        in.push_back(rand() % 50 + 1);
    }
}

void print_vec(const vector<int>& to_print)
{
    int count = 0;
    for(auto i : to_print)
    {
        cout << "Index: " << count << ", Value: " << i << "\n";
        count++;
    }
    cout << "\n";
}

void random_fill_array(int* arr, int length)
{
    for(int i = 0; i < length; ++i)
    {
        arr[i] = rand() % 50 + 1;
    }
}

void print_array(int* arr, int length)
{
    for(int i = 0; i < length; ++i)
    {
        cout << "Index: " << i << ", Value: " << arr[i] << "\n";
    }
    cout << "\n";
}

void random_fill_forward_list(std::forward_list<int>& in)
{
    for(int i = 0; i < 15; ++i)
    {
        in.push_front(rand() % 50 + 1);
    }

}

void print_forward_list(std::forward_list<int>& in)
{
    int count = 0;
    for(auto i : in)
    {
        cout << "Index: " << count << ", Value: " << i << "\n";
        count++;
    }
    cout << "\n";
}

    template<typename ForwardIterator>
void forward_sort(ForwardIterator begin, ForwardIterator end)
{
    if(begin == end)
        return;

    ForwardIterator i, j;
    for (i = begin; i != end; i++)
        for (j = begin; j != i; j++)
            if (*i < *j)
                std::iter_swap(i, j);

}
