#include<bits/stdc++.h>
using namespace std;

template <class T>
struct my_allocator {
    using value_type = T;
    T* pool = nullptr;
    T* init_pool = nullptr;
    static constexpr std::size_t PoolSize = 1000;

    my_allocator () noexcept { pool = static_cast<T*>(std::malloc(PoolSize * sizeof(T)));init_pool = pool;}
    template <class U> my_allocator  (const my_allocator<U>&) noexcept {}

    T* allocate (std::size_t n)
    {   
        T* prev_head = pool;
        pool = prev_head + (n * sizeof(T));
        return prev_head;
    }
    void deallocate (T* p, std::size_t n)
    {
        delete init_pool;
        init_pool = nullptr;
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args)
    {
        new(p) U(std::forward<Args>(args)...);
    }

    template<typename U>
    void destroy(U* p)
    {
        p->~U();
    }

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type; //UB if std::false_type and a1 != a2;
};

template <class T, class U>
constexpr bool operator== (const my_allocator<T>& a1, const my_allocator<U>& a2) noexcept
{
    return true;
}

template <class T, class U>
constexpr bool operator!= (const my_allocator<T>& a1, const my_allocator<U>& a2) noexcept
{
    return false;
}


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

int main(){
    std::map<int,int> map_std_alloc;
    for(int i=0;i<10;i++){
        if (i==0) {
            map_std_alloc[0]=1;
            continue;
        }
        map_std_alloc[i]=map_std_alloc[i-1]*i;
    }
    for(int i=0;i<10;i++){
        std::cout<<map_std_alloc[i]<<" ";
    }
    std::cout<<std::endl;

    std::map<int, int, std::less<int>, my_allocator<std::pair<const int, int> > > map_my_alloc;
    for(int i=0;i<10;i++){
        if (i==0) {
            map_my_alloc[0]=1;
            continue;
        }
        map_my_alloc[i]=map_my_alloc[i-1]*i;
    }
    for(int i=0;i<10;i++){
        std::cout<<map_my_alloc[i]<<" ";
    }
    std::cout<<std::endl;

    my_vector<int> my_vector_std_alloc;
    my_vector_std_alloc.push_back(1);
    my_vector_std_alloc.push_back(1);
    my_vector_std_alloc.push_back(2);
    my_vector_std_alloc.push_back(6);
    my_vector_std_alloc.push_back(24);
    my_vector_std_alloc.push_back(120);
    my_vector_std_alloc.push_back(720);
    my_vector_std_alloc.push_back(5040);
    my_vector_std_alloc.push_back(40320);
    my_vector_std_alloc.push_back(362880);

    for(int i=0;i<10;i++){
        std::cout<<my_vector_std_alloc[i]<<" ";
    }
    std::cout<<std::endl;


    my_vector<int, my_allocator<int>> my_vector_my_alloc;
    my_vector_my_alloc.push_back(1);
    my_vector_my_alloc.push_back(1);
    my_vector_my_alloc.push_back(2);
    my_vector_my_alloc.push_back(6);
    my_vector_my_alloc.push_back(24);
    my_vector_my_alloc.push_back(120);
    my_vector_my_alloc.push_back(720);
    my_vector_my_alloc.push_back(5040);
    my_vector_my_alloc.push_back(40320);
    my_vector_my_alloc.push_back(362880);

    for(int i=0;i<10;i++){
        std::cout<<my_vector_my_alloc[i]<<" ";
    }
    std::cout<<std::endl;
}