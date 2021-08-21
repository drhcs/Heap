#ifndef HEAP
#define HEAP

#include <functional>
#include <vector>

template<class T>
class Heap {

    std::vector<T> tree_;
    std::function<bool(T, T)> OutOfOrder_;

    bool WithinHeap(int index) {
        return index < tree_.size();
    }

    int LeftChild(int parent) {
        return (parent * 2) + 1;
    }

    int RightChild(int parent) {
        return (parent * 2) + 2;
    }

    int Parent(int child) {
        return (child - 1) / 2;
    }

    int CountChildren(int parent) {
        int count = 0;
        if (WithinHeap(LeftChild(parent))) count++;
        if (WithinHeap(RightChild(parent))) count++;
        return count;
    }

    int SwapDown(int parent, int child) {
        std::swap(tree_[parent], tree_[child]);
        return child;
    }

    void BubbleUp(int child) {
        int parent = Parent(child);
        while (OutOfOrder_(tree_[parent], tree_[child]))
        {
            std::swap(tree_[child], tree_[parent]);
            child = parent;
            parent = Parent(child);
        }
    }

    void BubbleDown(int parent) {
        int left_child = LeftChild(parent);
        int right_child = RightChild(parent);
        while (WithinHeap(left_child) && OutOfOrder_(tree_[parent], tree_[left_child]) || WithinHeap(right_child) && OutOfOrder_(tree_[parent], tree_[right_child]))
        {
            if (!WithinHeap(right_child) || (WithinHeap(left_child) && OutOfOrder_(tree_[right_child], tree_[left_child])))
            {
                parent = SwapDown(parent, left_child);
            }
            else
            {
                parent = SwapDown(parent, right_child);
            }

            left_child = LeftChild(parent);
            right_child = RightChild(parent);
        }
    }

public:

    Heap() {
        OutOfOrder_ = [&](const T & parent, const T & child) {
            return parent < child;
        };
    }

    Heap(std::function<bool(T, T)> OutOfOrder) {
        OutOfOrder_ = OutOfOrder;
    }

    ~Heap() = default;

    void Push(T new_node) {
        tree_.push_back(new_node);
        BubbleUp(Size() - 1);
    }

    T Pop() {
        T popped = Peek();
        std::swap(tree_.front(), tree_.back());
        tree_.pop_back();
        if (!Empty())
        {
            BubbleDown(0);
        }
        return popped;
    }

    T Peek() {
        return tree_.front();
    }

    int Size() {
        return tree_.size();
    }

    void Clear() {
        tree_.clear();
    }

    bool Empty() {
        return tree_.empty();
    }

};

#endif
