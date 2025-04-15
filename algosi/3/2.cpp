#include <iostream>
#include <vector>

class BinaryHeap
{
private:
    std::vector<int> heap;

    void heapifyDown(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (heap[index] > heap[parent])
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

public:
    BinaryHeap(std::vector<int> arr)
    {
        for (auto it : arr)
        {
            insert(it);
        }
    }

    BinaryHeap() {}

    int max()
    {
        return heap[0];
    }

    void delMax()
    {
        heap[0] = heap.back();
        heap.pop_back();

        for (int i = 0; i < heap.size(); i++)
        {
            heapifyDown(i);
        }
    }

    void insert(int data)
    {
        heap.push_back(data);
        heapifyDown(heap.size() - 1);
    }

    void print()
    {
        for (auto h : heap)
        {
            std::cout << h << " ";
        }
        std::cout << std::endl;
    }
};

int main()
{
    BinaryHeap heap = BinaryHeap({13, 2, 3, 43, 54, 65, 23, 44});
    heap.print();

    heap.delMax();
    heap.print();

    std::cout << "max: " << heap.max() << std::endl;
}