#include "../include/vector_list.hpp"

int main() {
  VectorList<int> list(10);

  list.push_back(5);
  list.push_back(10);
  list.push_back(15);
  
  std::cout << "Lista após push_back: ";
  list.print(); 

  list.insert(1, 7);
  std::cout << "Lista após insert(1, 7): ";
  list.print(); 

  list.remove(2);
  std::cout << "Lista após remove(2): ";
  list.print(); 

  std::cout << "O elemento 7 está na lista? " << (list.contains(7) ? "Sim" : "Não") << std::endl;

  try {
      std::cout << "Buscando elemento 10: " << list.find(10) << std::endl;
  } catch (const std::out_of_range& e) {
      std::cout << e.what() << std::endl;
  }

  list.clear();
  std::cout << "Lista após clear(): ";
  list.print(); // Esperado: (vazia)

  return 0;
}
