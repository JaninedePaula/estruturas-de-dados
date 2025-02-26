#include "../include/doubly_linked_list.hpp"
#include <iostream>

int main() {
    DoublyLinkedList<int> list;
    
    list.push_back(10);
    list.push_back(20);
    list.push_front(5);
    list.print(); 
   
    list.pop_front();
    list.print(); 

    list.pop_back();
    list.print(); 

    list.push_back(30);
    list.push_back(40);
    list.push_front(1);
    list.print(); 

    std::cout << "O elemento 10 está na lista? " << (list.contains(10) ? "Sim" : "Não") << std::endl;
    
    return 0;
}
