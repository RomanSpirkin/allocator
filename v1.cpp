#include "my_allocator.hpp"
#include "my_vector.hpp"
using namespace std;

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