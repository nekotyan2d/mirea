#include <iostream>
#include <vector>

std::vector<int> heap;
std::vector<int> lens = {2, 7, 4, 1, 10, 12, 9, 5};
std::vector<int> res;
int sum = 0;

void heapifyDown(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;
        if (heap[index] < heap[parent])
        {
            std::swap(heap[index], heap[parent]);
            index = parent;
        }
        else
        {
            break;
        }
    }
}

void insert(int data)
{
    heap.push_back(data);
    heapifyDown(heap.size() - 1);
}

int main()
{
    for (auto i : lens)
    {
        insert(i);
    }

    for (auto i : heap)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    while (heap.size() > 0)
    {
        int a = heap[0];
        int b = heap[1];

        res.push_back(a);
        res.push_back(b);
        sum += a + b;

        heap.erase(heap.begin());
        heap.erase(heap.begin());

        insert(a + b);

        for (int i = 0; i < heap.size(); i++)
        {
            heapifyDown(heap.size() - 1);
        }

                for (auto i : heap)
        {
            std::cout << i << " ";
        }
        std::cout << "(" << heap.size() << ")" << std::endl;
    }

    std::cout << sum << std::endl;
    for (auto i : res)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}