#include<bits/stdc++.h>

template <class T>
struct my_allocator {
    using value_type = T;
    size_t current_size = 0;
    T* init_pool = nullptr;
    static constexpr std::size_t PoolSize = 1000;

    my_allocator () noexcept { init_pool= static_cast<T*>(::operator new(PoolSize * sizeof(T)));}
    my_allocator  (const my_allocator<T>&) = delete ;
    my_allocator<T> &operator=(const my_allocator<T>&) = delete ;
    my_allocator(my_allocator<T> &&other) : init_pool{other.init_pool},current_size{other.current_size} { other.ptr = nullptr;other.current_size = 0; }
    my_allocator<T> &operator=(my_allocator<T> &&other) {
        init_pool = other.init_pool;
        current_size = other.current_size;
        other.ptr = nullptr;
        other.current_size = 0;
        return *this;
    };

    T* allocate (std::size_t n)
    {   
        if (current_size + n< PoolSize){
            auto ans = init_pool + (current_size)*sizeof(T);
            current_size+=n;
            return ans;
        }
        throw std::bad_alloc();
    }
    void deallocate (T* p, std::size_t n)
    {
        current_size-=n;
        if (!current_size && init_pool){
            ::operator delete(init_pool);
            init_pool=nullptr;
        }
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