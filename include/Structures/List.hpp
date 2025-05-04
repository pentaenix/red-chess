#pragma once
#include <iostream>

using std::cout; 
using std::endl;
using std::length_error;
using std::out_of_range;

/**
 * @author Mateo Saldivar
 * @class List
 * @brief estructura de datos de tipo ligadura
 * @template Type es el tipo de dato a almacenar en la lista
 */
template <class Type>
class List { // DoubleList
  private:
  
    class Node {
      private:
        Type data; // m_data
        Node* next; // m_pNext
        Node* prev; // m_pPrev
      friend class List;
    };

    static Node* head;
    Node* tail = nullptr;
    size_t size;

    Node* generateNode(Type p_data) {
      Node* newNode = new Node;
      newNode->data = p_data;
      newNode->next = nullptr;
      newNode->prev = nullptr;
      return newNode;
    }

    Node* getNodeAt(const int& at){
      Node* tempNodePointer = head;
        int index = 0;
        while (tempNodePointer) {
          if (index == at)
            return tempNodePointer;
        index++;
        tempNodePointer = tempNodePointer->next;
      }
    }

    
  public:
    //constructores
    List<Type>() noexcept {
      head = nullptr;
      tail = nullptr;
    }
    List<Type>(Type p_data);
    List<Type>(List<Type>& p_data);
    List<Type>(const Type p_array[], const size_t& p_arrSize);

    //modificadores
    void push_back(Type p_data);
    void push_front(Type p_data);
    void insert(const size_t& p_place, Type p_data);


    void pop_front();
    void pop_back();

    void erase(Type p_data);
    void eraseAt(const size_t& p_at);
    void eraseAll(Type data);
    void eraseFromItoJ(const size_t p_i, const size_t p_j);

    void swap(size_t p_i, size_t p_j);
    void replace(Type orgnlDat, Type newDat);
    void replaceAll(Type orgnlDat, Type newDat);

    //accesores
    Type getHead(){
      return head->data;
    }
    size_t length(){
      return size;
    }
    Type at(int i){
      return getNodeAt(i)->data;
    }
    bool find(Type p_data);
    std::string print();
    void reverseprint();
};


template<class Type>
typename List<Type>::Node* List<Type>::head = nullptr;

/**
 * @Brief Constructor con un dato
 * @Param dato a insertar
 */
template<class Type>
List<Type>::List(Type p_data){
  head = tail = generateNode(p_data);
  size=1;
}

/**
 * @Brief Constructor por copia de otra lista
 * @param lista a copiar
 */
template<class Type>
List<Type>::List(List<Type>& p_data){
  size = p_data.size;
  if ( p_data.head == nullptr)
        head = tail = nullptr; 
  else { 
    Node* tempOther = p_data.head->next;
    head = generateNode(p_data.head->data); 
    Node* temp = head;
    while (tempOther != nullptr ) {
      temp->next = generateNode(tempOther->data); 
      temp->next->prev = temp;
      temp = temp->next;                                      
      tempOther = tempOther->next;                            
    }
    tail = temp;
  } 
}

/**
 * @Brief Constructor por copia de un array
 * @param array base p_arrsize size del array
 */
template<class Type>
List<Type>::List(const Type p_array[], const size_t& p_arrSize){
  size = p_arrSize;
  if(p_arrSize==0)
    head=tail=nullptr;
  else{
    head = generateNode(p_array[0]); 
    Node* temp = head;
    for(int i = 1; i < p_arrSize; ++i){
      temp->next = generateNode(p_array[i]); 
      temp->next->prev = temp;
      temp = temp->next;                                      
    }
  }
}

/**
 * @Brief agrega un nodo al final de la lista
 * @param dato a insertar
 */
template<class Type>
void List<Type>::push_back(Type p_data){
  Node* tempNodePointer = generateNode(p_data);
  if (!head){
    head = tail = tempNodePointer;
    size=1;
  }
  else{
    tail->next=tempNodePointer;
    tempNodePointer->prev = tail;
    tail=tempNodePointer;
    size++;
  }
}

/**
 * @Brief agrega un nodo al inicio de la lista
 * @param dato a insertar
 */
template<class Type>
void List<Type>::push_front(Type p_data){
  Node* tempNodePointer = generateNode(p_data);
  if (!head){
    head = tail = tempNodePointer;
    size=1;
  }
  else{
    tempNodePointer->next=head;
    head->prev = tempNodePointer;
    head=tempNodePointer;
    size++;
  }
}

/**
 * @Brief agrega un nodo en una posicion especificada
 * @param pdata dato a insertar place el lugar 
 */
template<class Type>
void List<Type>::insert(const size_t& place,Type p_data){
  if (place <= 0 || place >= size){
    if (place==0){
      push_front(p_data); 
    } else if(place==size) {
      push_back(p_data);       
    } else {
      throw out_of_range("ERROR: OUTSIDE OF List LIMITS\n");
    }
  } else {
      Node* nodeToInsert = generateNode(p_data);
      Node* nodeAtPlace = getNodeAt(place);
      nodeToInsert->next = nodeAtPlace;
      nodeToInsert->prev = nodeAtPlace->prev; 
      nodeAtPlace->prev = nodeToInsert;
      nodeToInsert->prev->next = nodeToInsert;
      size++;
    }
}

/**
 * @Brief elimina el primer elemento de la lista
 * 
 */
template<class Type>
void List<Type>::pop_front(){
    if (head){
      Node* tempNodePointer = head;
      
      if(head->next){
        head = head->next;
        head->prev = nullptr;
      } else {
        head = tail = nullptr;
      }
      delete tempNodePointer;
      size--;
    }else{
      throw length_error("ERROR: EMPTY List\n");
  }
}

/**
 * @Brief elimina el ultimo elemento de la lista
 * 
 */
template<class Type>
void List<Type>::pop_back(){
  if (head){
    Node* toDelete = tail;
    if(tail->prev){
      tail = tail->prev;
      tail->next= nullptr;
      
    } else { // Comantarios
      head = tail = nullptr;
    }
    delete toDelete;
    
    size--;
  }else{
    throw length_error("ERROR: EMPTY List\n");
  }
}

/**
 * @Brief elimina un nodo en una posicion especificada
 * @param at lugar de la lista a eliminar
 */
template<class Type>
void List<Type>::eraseAt(const size_t& at){
  if(!head)
    throw length_error("ERROR: EMPTY List\n");
  
  if (at <= 0 || at > size){
    if (at==0)
      pop_front(); 
    else if(at==size)
      pop_back();       
    else 
      throw out_of_range("ERROR: OUTSIDE OF List LIMITS\n");
  } else {
      Node* tempNodePointer = getNodeAt(at);
      tempNodePointer->prev->next = tempNodePointer->next;
      tempNodePointer->next->prev = tempNodePointer->prev;
      delete tempNodePointer;
      size--;
  }
}

/**
 * @Brief elimina el primer nodo que contenga el dato p_data
 * @param p_data dato  eliminar
 */
template<class Type>
void List<Type>::erase(Type p_data){

  if(!head) {
    throw length_error("ERROR: EMPTY List\n");
  }
  if(head->data == p_data){
    pop_front();
    return; // skip -> return;
  }
  if(tail->data == p_data){
    pop_back();
    return;
  }
  Node* itNode = head;
  while(itNode){
    if(itNode->data==p_data){
      Node* tempNodePointer = itNode;
      itNode->prev->next = tempNodePointer->next;
      tempNodePointer->next->prev = itNode->prev;
      delete tempNodePointer;
      size--;
      break;
    }
    itNode = itNode->next;
  }
}

/**
 * @Brief elimina todos los nodos que contengan el dato p_data
 * @param p_data dato eliminar
 */
template<class Type>
void List<Type>::eraseAll(Type p_data){
  if(!head) {
    throw length_error("ERROR: EMPTY List\n");
  }
  
  while(head->data == p_data)
      pop_front();
  while(tail->data == p_data)
      pop_back();

  Node* itNode = head;
  while(itNode){
    if(itNode->data==p_data){
      Node* tempNodePointer = itNode;
      
      itNode=itNode->next;
      tempNodePointer->next->prev = tempNodePointer->prev;
      tempNodePointer->prev->next = tempNodePointer->next;
      
      delete tempNodePointer;
      
      size--;
    }else
      itNode=itNode->next;
  }
}

/**
 * @Brief elimina todos los nodos en un area determinada
 * @param p_i,p_j indices limites
 */
template<class Type>
void List<Type>::eraseFromItoJ(size_t p_i, size_t p_j){
  if(!head) {
    throw length_error("ERROR: EMPTY List\n");
  }
  if(p_j < p_i)
    throw std::logic_error("ERROR: INDEX MUST GO IN GROWING ORDER\n");
  if(p_i == p_j)
    throw std::logic_error("ERROR: USE eraseAt(p_i) WHEN DEALING WITH A SINGLE INDEX\n");
  if(p_i > size || p_j >= size){
    throw out_of_range("ERROR: OUTSIDE OF List LIMITS\n");
  }else{
    int index = 0,
    startIndex = p_i,
    endIndex = p_j;
    Node* itNode = head;
    Node* firstConnectNode = nullptr;
    bool beHead = false,
    deTail = false;

    if(startIndex==0){
      startIndex = 1;
      beHead = true;
    }

    if(endIndex==size-1){
      endIndex = size-2;
      deTail = true;
    }
    
    while(itNode){
      if(index==startIndex){
          firstConnectNode = itNode->prev;
        for(int i = index; i <= endIndex; i++){
          Node* tempNodePointer = itNode;
          itNode=itNode->next;
          delete tempNodePointer;
          size--;
        }
        firstConnectNode->next=itNode;
        itNode->prev=firstConnectNode;
        
        if(beHead && head){
          itNode = head;
          if( head->next){
            head = head->next;
            head->prev = nullptr;
          }else{
            head=tail=nullptr;
          }
          delete itNode;
          size--;
        }
        
        if(deTail && tail){
          itNode = tail;
          if(tail->prev){
            tail = tail->prev;
            tail->next= nullptr;
          }else {
            head=tail=nullptr;
          }
          delete itNode;
          size--;
        }
        
        break;
      }
      index++;
      itNode=itNode->next;
    }
  }
}

/**
 * @Brief busca la primer instancia de un dato y la cambia por nw_data
 * @param og_data dato original
 * @param nw_data dato a cambiar
 */
template<class Type>
void List<Type>::replace(Type og_data, Type nw_data){  
  if(!head) {
    throw length_error("ERROR: EMPTY List\n");
  }
  Node* itNode = head;
  while(itNode){
    if(itNode->data==og_data){
      itNode->data=nw_data;
      break;
    }
    itNode=itNode->next;
  }
}

/**
 * @Brief busca todas las instancias de un dato y las cambia por nw_data
 * @param og_data dato original
 * @param nw_data dato a cambiar
 */
template<class Type>
void List<Type>::replaceAll(Type og_data, Type nw_data){  
  if(!head) {
    throw length_error("ERROR: EMPTY List\n");
  }
  Node* itNode = head;
  while(itNode){
    if(itNode->data==og_data){
      itNode->data=nw_data;
    }
    itNode=itNode->next;
  }
}

/**
 * @Brief cambia los datos contenidos en dos nodos 
 * @param p_i,p_j indices a cambiar
 */
template<class Type>
void List<Type>::swap(size_t p_i, size_t p_j){
  if(!head) {
    throw length_error("ERROR: EMPTY List\n");
  }
  if(p_i > size || p_j > size){
    throw out_of_range("ERROR: OUTSIDE OF List LIMITS\n");
  }else{
    Node* i = getNodeAt(p_i);
    Node* j = getNodeAt(p_j);

    Type tempData = i->data;
    i->data = j->data;
    j->data = tempData;

  }
}

/**
 * @Brief busca que exista un dato en la lista
 * @param p_data dato a encontrar
 * @ret true si encuentra el dato en la lista
 */
template<class Type>
bool List<Type>::find(Type p_data){
  if(!head) {
    throw length_error("ERROR: EMPTY List\n");
  }
  bool ret = false; // se puede omitir
  Node* itNode = head;
  while(itNode){
    if(itNode->data == p_data){
      ret = true;
      break;
    }
    itNode = itNode->next;
  }
  return ret;
}

/**
 * @Brief imprime la lista en terminal
 * 
 */
template<class Type>
std::string List<Type>::print(){
  if(head){
    std::string tmp = "";
    Node* itNode = head;
    while(itNode){
      if(itNode==head){
        tmp+="["+std::to_string(itNode->data)+"]-> ";
      }else
        tmp+= std::to_string(itNode->data) +" ";
      itNode=itNode->next;
    }
    return tmp;
  }
}

template<class Type>
void List<Type>::reverseprint(){
  if(tail){
    Node* itNode = tail;
    while(itNode){
      cout << itNode->data <<" ";
      itNode=itNode->prev;
    }
    cout<<endl;
  }else{}
    //throw length_error("ERROR: EMPTY List\n"); 
}