#pragma once
#include <iostream>

using std::cout; 
using std::endl;
using std::length_error;
using std::out_of_range;

/**
 * @author Mateo Saldivar
 * @class queue
 * @brief estructura de datos de tipo ligadura queue
 * @template Type es el tipo de dato a almacenar en la lista queue
 */
template <class Type>
class queue { // DoubleLinkedListcyclicDL
  private:
  
    class Node {
      private:
        Type q_data; // q_data
        Node* m_next; // m_pNext
      friend class queue;
    };

    Node* head;
    Node* tail = nullptr;
    size_t m_size;

    Node* generateNode(Type p_data) {
      Node* newNode = new Node;
      newNode->q_data = p_data;
      newNode->m_next = nullptr;
      return newNode;
    }
    
  public:
    //constructores
    queue<Type>() noexcept {
      head = tail = nullptr;
    }
    queue<Type>(Type p_data);
    queue<Type>(queue<Type>& p_data);
    queue<Type>(const Type p_array[], const size_t& p_arrSize);

    //modificadores
    void enqueue(Type p_data);
    void dequeue();
    void clear();

    //accesores
    Type peek();
    void traverse();
};



/**
 * @Brief Constructor con un dato
 * @Param dato a insertar
 */
template<class Type>
queue<Type>::queue(Type p_data){
  head = tail = generateNode(p_data);
  m_size=1;
}

/**
 * @Brief Constructor por copia de otra lista
 * @param lista a copiar
 */
template<class Type>
queue<Type>::queue(queue<Type>& p_data){
  m_size = p_data.m_size;
  if(!p_data.head){
    head = tail = nullptr; 
  }else { 
    Node* tempOther = p_data.head->m_next;
    head = generateNode(p_data.head->q_data); 
    Node* temp = head;
    for(int i = 0 ; i < m_size-1; ++i){
      temp->m_next = generateNode(tempOther->q_data); 
      temp = temp->m_next;                                      
      tempOther = tempOther->m_next;                            
    }
    tail = temp;
  } 
}

/**
 * @Brief Constructor por copia de un array
 * @param p_array[] array base p_arrsize size del array
 */
template<class Type>
queue<Type>::queue(const Type p_array[], const size_t& p_arrSize){
  m_size = p_arrSize;
  if(p_arrSize==0){
    head=tail=nullptr;
  }else{
    head = generateNode(p_array[0]); 
    Node* tempNodePointer = head;
    for(int i = 1; i < p_arrSize; ++i){
      tempNodePointer->m_next = generateNode(p_array[i]); 
      tempNodePointer = tempNodePointer->m_next;
      tail = tempNodePointer;
    }
  }
}

/**
 * @Brief agrega un nodo al inicio de la lista
 * @param p_data dato a insertar
 */
template<class Type>
void queue<Type>::enqueue(Type p_data){
  Node* tempNodePointer = generateNode(p_data);
  if (!head){
    head = tail = tempNodePointer;
    m_size=1;
  }else{
    tempNodePointer->m_next=head;
    head=tempNodePointer;
    m_size++;
  }
}

/**
 * @Brief elimina el ultimo elemento del queue
 * 
 */
template<class Type>
void queue<Type>::dequeue(){
  if (head){
    Node* toDelete = tail;
    Node* prevNode = head;
    if(m_size > 1){
      while (prevNode->m_next!=tail) {
        prevNode = prevNode->m_next;
      }
      tail = prevNode;
      tail->m_next = nullptr;
    }else{ 
      head = tail = nullptr;
    }
    delete toDelete;
    m_size--;
    
  }else{
    return;
  }
}

/**
 * @Brief elimina todos los nodos 
 */
template<class Type>
void queue<Type>::clear(){
  if(head){
    Node* itNode = head;
    while(m_size > 0){
      Node* tempNodePointer = itNode;
      if(itNode->m_next){
        itNode=itNode->m_next;
      }
      
      delete tempNodePointer;
      --m_size;
    }
    head = tail = nullptr;
  }
}

/**
 * @Brief regresa head
 * @ret datos en head
 */
template<class Type>
Type queue<Type>::peek(){
  if (!head) {
    return nullptr;
  }
  return tail->q_data;
}

/**
 * @Brief imprime el queue en terminal
 */
template<class Type>
void queue<Type>::traverse(){
  if(head){
    Node* itNode = head;
    while(itNode) {
      cout << itNode->q_data <<" ";
      itNode=itNode->m_next;
    }
    cout<<endl;
  }else{
    throw length_error("ERROR: EMPTY QUEUE\n"); 
  }
}

