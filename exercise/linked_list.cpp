#include <iostream>
#include "../include/linked_list.hpp"

int main() {
    LinkedList<int> list;

    std::cout << "Lista vazia? " << (list.empty() ? "Sim" : "Não") << std::endl;

    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    
    std::cout << "Lista após inserções:\n";
    list.print();

    list.insert(1, 25);
    std::cout << "Lista após inserção no índice 1:\n";
    list.print();

    list.pop_front();
    std::cout << "Lista após remover o primeiro elemento:\n";
    list.print();

    list.remove(1);
    std::cout << "Lista após remover o elemento do índice 1:\n";
    list.print();

    std::cout << "Elemento no índice 1: " << list[1] << std::endl;

    std::cout << "A lista contém o número 25? " << (list.contains(25) ? "Sim" : "Não") << std::endl;

    list.clear();
    std::cout << "Lista após limpar:\n";
    list.print();

    return 0;
}
