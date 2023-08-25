#include<bits/stdc++.h>
template <typename T, class Allocator = std::allocator<T>>
class my_vector {
    public:
    T& operator[](size_t index)
    {
        return data[index];
    }

    void push_back(T value)
    {
        if(size == capacity) ExpandIfNeeded();

        data[size++] = value;
    }
    ~my_vector(){
        T* p=data;
        for(size_t i = 0; i < size; ++i){
                        allocator.destroy(p);
                        ++p;
        }
        allocator.deallocate(data, capacity);
    }
    
    private:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
    Allocator allocator;
    void ExpandIfNeeded()
    {
        T* olddata = data;
        std::size_t oldcap = capacity;
        auto new_cap = (capacity == 0 ? 1 : 2 * capacity);
        capacity = new_cap;
        data = allocator.allocate(capacity);
        {
                T* p = olddata;
                T* np = data;
                for(size_t i = 0; i < size; ++i){
                        allocator.construct(np, *p);
                        ++np;
                        ++p;
                }

        }
        {
                T* p = olddata;
                for(size_t i = 0; i < size; ++i){
                        allocator.destroy(p);
                        ++p;
                }
        }
        if(olddata != nullptr)
        allocator.deallocate(olddata, oldcap);

    }
};