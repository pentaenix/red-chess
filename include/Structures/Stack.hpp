#pragma once
#include <iostream>

using std::cout; 
using std::endl;
using std::length_error;
using std::out_of_range;

/**
 * @author Mateo Saldivar
 * @class stack
 * @brief estructura de datos de tipo ligadura/stack
 * @template Type es el tipo de dato a almacenar en el stack
 */
template <class Type>
class stack { // DoubleLinkedListcyclicDL
  private:
  
    class Node {
      private:
        Type m_data; // m_data
        Node* m_next; // m_pNext
      friend class stack;
    };

    Node* head;
    Node* tail = nullptr;
    size_t m_size;

    Node* generateNode(Type p_data) {
      Node* newNode = new Node;
      newNode->m_data = p_data;
      newNode->m_next = nullptr;
      return newNode;
    }
  
    
  public:
    //constructores
    stack<Type>() noexcept {
      head = tail = nullptr;
    }
    stack<Type>(Type p_data);
    stack<Type>(stack<Type>& p_data);
    stack<Type>(const Type p_array[], const size_t& p_arrSize);

    //modificadores
    void push(Type p_data);
    void pop();
    void clear();

    //accesores
    Type peek();
    void traverse();
};

/**
 * @Brief Constructor con un dato
 * @Param p_data dato a insertar
 */
template<class Type>
stack<Type>::stack(Type p_data){
  head = tail = generateNode(p_data);
  m_size=1;
}

/**
 * @Brief Constructor por copia de otra lista
 * @param p_data lista a copiar
 */
template<class Type>
stack<Type>::stack(stack<Type>& p_data){
  m_size = p_data.m_size;
  if (!p_data.head){
        head = tail = nullptr; 
  }else { 
    Node* tempOther = p_data.head->m_next;
    head = generateNode(p_data.head->m_data); 
    Node* temp = head;
    for(int i = 0 ; i < m_size-1; ++i){
      temp->m_next = generateNode(tempOther->m_data); 
      temp = temp->m_next;                                      
      tempOther = tempOther->m_next;                            
    }
    tail = temp;
  } 
}

/**
 * @Brief Constructor por copia de un array
 * @param p_array[] array base p_arrsize tamaño del array
 */
template<class Type>
stack<Type>::stack(const Type p_array[], const size_t& p_arrSize){
  m_size = p_arrSize;
  if(p_arrSize==0){
    head=tail=nullptr;
  }else{
    head = generateNode(p_array[0]); 
    Node* temp = head;
    for(int i = 1; i < p_arrSize; ++i){
      temp->m_next = generateNode(p_array[i]); 
      temp = temp->m_next;
      tail = temp;
    }
  }
}

/**
 * @Brief agrega un nodo al inicio de la lista
 * @param p_data dato a insertar
 */
template<class Type>
void stack<Type>::push(Type p_data){
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
 * @Brief elimina el primer elemento de la lista
 * 
 */
template<class Type>
void stack<Type>::pop(){
  if (head){
    Node* tempNodePointer = head; 
    if(head->m_next){
      head = head->m_next;
    } else {
      head = tail = nullptr;
    }
    delete tempNodePointer;
    m_size--;
  }else{
    std::cout<<"\nNothing to delete\n";
  }
}

/**
 * @Brief elimina todos los nodos 
 */
template<class Type>
void stack<Type>::clear(){
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
  }else{
    throw length_error("ERROR: EMPTY STACK\n"); 
  }
}

/**
 * @Brief regresa datos contenidos en head
 * @ret datos en head 
 */
template<class Type>
Type stack<Type>::peek(){
  if(head){
    return head->m_data;
  }else{
    return nullptr; 
  }
}

/**
 * @Brief imprime el stack en terminal
 * 
 */
template<class Type>
void stack<Type>::traverse(){
  if(head){
    Node* itNode = head;
     while(itNode) {
      cout << itNode->m_data <<" ";
      itNode=itNode->m_next;
    }
    cout<<endl;
  }else{
    throw length_error("ERROR: EMPTY STACK\n"); 
  }
}