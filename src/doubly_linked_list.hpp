#include <iostream>

#include "../include/doubly_linked_list.hpp"

template < class T>
DoublyLinkedList<T>::Node::Node(const T& value) : value{value}, next{nullptr}, prev{nullptr} {}

template <class T>
DoublyLinkedList<T>::Node::~Node(){
    if(next != nullptr){
        delete next;
    }
}

template <class T>
DoublyLinkedList<T>::DoublyLinkedList() : head{nullptr}, tail{nullptr}, _size(0) {}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList(){
    if(head != nullptr){
        delete head;
    }
}

template <class T>
size_t DoublyLinkedList<T>::size() const {
    return _size;
}

template <class T>
bool DoublyLinkedList<T>::empty() const {
    return size() == 0;
}

template <class T>
void DoublyLinkedList<T>::push_front(const T& value){
    auto new_node = new Node(value);
    if(empty()){
        tail = new_node;
    }else{
        new_node->next = head;
        head->prev = new_node;
    }
    head = new_node;

    _size++;
}

template <class T>
void DoublyLinkedList<T>::print() const {
    Node* current = head;
    while (current) {
        std::cout << current->value << " <-> ";
        current = current->next;
    }
    std::cout << "NULL (" << _size << ")\n";
}

template <class T>
void DoublyLinkedList<T>::push_back(const T& value){
    auto new_node = new Node(value);
    if(empty()){
        head = new_node;
    }else{
    new_node->prev = tail;
    tail->next = new_node;
}

tail = new_node;
_size++;
}

template <class T>
void DoublyLinkedList<T>::pop_front(){
    if(empty()){
        throw std::out_of_range("A lista está vazia");
    }
    auto tmp = head;
    head = head->next;
    if(head != nullptr){
        head->prev = nullptr;
    }else{
        tail = nullptr;
    }
    tmp->next = nullptr;
    delete tmp;

    _size--;
}

template <class T>
void DoublyLinkedList<T>::pop_back(){
    if(empty()){
        throw std::out_of_range("A lista está vazia");
    }else if (size() == 1){
        delete tail;
        head = nullptr;
        tail = nullptr;
    }else{
        auto temp = tail;
        tail = tail->prev;
        tail->next = nullptr;

        delete temp;
    }
    _size--;
}

 
template <class T>
template <class U>
DoublyLinkedList<T>::Iterator<U>::Iterator(U* ptr, bool end) : node(ptr), end{end}{}

template <class T>
template <class U>
auto& DoublyLinkedList<T>::Iterator<U>::operator*() const{
    return node->value;
}

template <class T>
template <class U>
DoublyLinkedList<T>::Iterator<U>&DoublyLinkedList<T>::Iterator<U>:: operator++() {
    if(node->next == nullptr){
        end = true;
    }else{
        node = node->next;
    }
    return *this;
}

template <class T>
template <class U>
DoublyLinkedList<T>::Iterator<U>&DoublyLinkedList<T>::Iterator<U>:: operator--() {
    if(end){
        end = false;
    }else{
        node = node->prev;
    }

    return *this;
}

template <class T>
template <class U>
bool DoublyLinkedList<T>::Iterator<U>::operator==(const Iterator<U>& other) const {
    return node == other.node and end == other.end;
}

template <class T>
template <class U>
bool DoublyLinkedList<T>::Iterator<U>::operator!= (const Iterator<U>& other) const {
    return not(*this == other);
}

template <class T>
auto DoublyLinkedList<T>::begin() const -> const_iterator {
    return const_iterator(head, empty());
} 

template <class T>
auto DoublyLinkedList<T>::begin() -> iterator {
    return iterator(head, empty());
} 

template <class T>
auto DoublyLinkedList<T>::end() const -> const_iterator {
    return const_iterator(tail, true);
} 

template <class T>
auto DoublyLinkedList<T>::end() -> iterator {
    return iterator(tail, true);
} 

template <class T>
template <class U>
 DoublyLinkedList<T>::Iterator<U> DoublyLinkedList<T>::Iterator<U>::operator+(size_t offset) const {
    auto it = *this;

    for (int i = 0; i < offset; i++) {
        ++it;
    }

    return it;
}

template <class T>
template <class U>
auto DoublyLinkedList<T>::Iterator<U>::operator-(size_t offset) const -> Iterator<U> {
    auto it = *this;

    for(int i = 0; i < offset; i++){
        --it;
    }

    return it;
}

template <class T>
template <class U>
size_t DoublyLinkedList<T>::Iterator<U>::operator-(const Iterator<U> other) const {
    auto pos = other;
    size_t count = 0;
    while (pos != *this) {
        ++count;
        ++pos;
    }
    return count;
}

template <class T>
void DoublyLinkedList<T>::insert(iterator pos, const T& value) {
    if(pos == begin()){
        return push_front(value);
    }else if(pos == end()){
        return push_back(value);
    }

    auto node_pos = pos.node;
    auto node_prev = (--pos).node;

    auto new_node = new Node(value);

    node_prev->next = new_node;
    new_node->next = node_pos;

    new_node->prev = node_prev;
    node_pos->prev = new_node;

    _size++;
}

template <class T>
void DoublyLinkedList<T>::erase(iterator first, iterator last) {
    if (first == last) {
        return; 
    
    }else if(first == begin() and last == end()){
        delete head;
        head = nullptr;
        tail = nullptr;
        _size = 0;
        return;
  
    }else if (first == begin()){
    auto num_elementos_removido = last - first;
    auto last_node = last.node;
    auto last_prev_node = (--last).node;

    head = last_node;
    last_node->prev = nullptr;
    _size -= num_elementos_removido;
} else {
    auto prev_first_node = (--first).node;
    auto next_last_node = last.node;
    
  
    prev_first_node->next = next_last_node;
    if (next_last_node != nullptr) {
        next_last_node->prev = prev_first_node;
    }

  
    auto num_elementos_removido = last - first;
    _size -= num_elementos_removido;
}
}

template <class T>
auto DoublyLinkedList<T>::find(const T& item) -> iterator {
    auto it = begin();
    while(it != end()){
        if(*it == item) break;
        ++it;
    }
    return it;
}

template <class T>
auto DoublyLinkedList<T>::find(const T& item) const -> const_iterator {
    auto it = begin();
    while(it != end()){
        if(*it == item) break;
        ++it;
    }
    return it;
}

template <class T>
bool DoublyLinkedList<T>::contains(const T& item) const{
    return find(item) != end();
}

template <class T>
T& DoublyLinkedList<T>::operator[](size_t index) {
    if(index >= size()){
        throw std::out_of_range("Índice inválido ");
    }
    return *(begin() + index);
}

template <class T>
const T& DoublyLinkedList<T>::operator[](size_t index) const {
    if(index >= size()){
        throw std::out_of_range("Índice inválido ");
    }
    return *(begin() + index);
}

template <class T>
void DoublyLinkedList<T>::clear(){
    erase(begin(), end());
}

template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& list) : head{nullptr}, tail{nullptr}, _size(0){
    for(auto& i : list){
        push_back(i);
    }
} 

template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& list){
    clear();
    for(auto& i : list){
        push_back(i);
    }
    return *this;

}