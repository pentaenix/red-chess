#pragma once

/**
*@autor Mateo Saldivar
*@brief Clase de un vector custom
*
*/

/**
*@class Estructura de datos basada en un arreglo que se auto dimensiona
*@template Type es el tipo de dato a almacenar
*
*/
#include <stdexcept>
#include <iostream>

template<class Type>
class Vector {
  private:
    Type* m_data;
    size_t m_capacity;
    size_t m_size;
  public:

    //constructores
    Vector();
    Vector(const size_t& p_capacity);
    Vector(Vector& p_v1);
    Vector(Vector* p_v1);
    Vector(const Type p_array[], const size_t& p_arrSize);

    //accesores
    size_t capacity();
    size_t size();
    Type at(const size_t& p_index);
    void print();
    Type front();
    Type back();
    bool inVector(Type p_data);

    //modificadores
    void push_back(Type p_elem);
    void push_front(Type p_elem);
    void resize();
    void shrink_to_fit();
    void pop_back();
    void assign(size_t p_times, Type p_elem);
    void erase_at(size_t p_index);
    void erase(Type p_data);
    void clear();
    void swap(size_t i,size_t j);
    void join(Vector& p_v);

    //operadores
    Type& operator[](const size_t& p_index);
    bool operator==(Vector& p_v);
    bool operator!=(Vector& p_v);
    Vector<Type>& operator=(Vector& p_v);
    Vector<Type>& operator+(Vector& p_v);
};

/**
*@brief constructor default
*/
template<class Type>
Vector<Type>::Vector(){
  m_data = new Type[1];
  m_capacity = 1;
  m_size = 0;
}


/**
*@brief constructor tamano definido
@param p_capacity es el tamano
*/
template<class Type>
  Vector<Type>::Vector(const size_t& p_capacity){
  m_data = new Type[p_capacity];
  m_capacity = p_capacity;
  m_size = 0;
}

/**
*@brief constuctor por referencia
*/
template<class Type>
Vector<Type>::Vector(Vector<Type>& p_v1){  
  m_data = new Type[p_v1.capacity()];
  m_capacity = p_v1.capacity();
  m_size = p_v1.size();

  for (size_t i = 0; i <m_size;i++){
    m_data[i]=p_v1.at(i);
  }
}

/**
*@brief constuctor por copia de un arreglo
*/
template<class Type>
Vector<Type>::Vector(const Type p_array[], const size_t& p_arrSize){
  m_data = new Type[p_arrSize];
  m_capacity = p_arrSize;
  m_size = p_arrSize;

  for (size_t i = 0; i <m_size;i++){
    m_data[i]=p_array[i];
  }
}

/**
*@brief constuctor por apuntador
*/
template<class Type>
Vector<Type>::Vector(Vector<Type>* p_v1){
}

/**
*@brief devuelve el tamano total
*@return el tamano del vector
*/
template <class Type>
size_t Vector<Type>::capacity(){
  return m_capacity;
}

/**
*@brief devuelve el numero de elementos
*@return el elementos en el vector
*/
template <class Type>
size_t Vector<Type>::size(){
  return m_size;
}

/**
*@brief devuelve el tamano total
*@return el tamano del vector
*/
template<class Type> 
Type Vector<Type>::at(const size_t& p_index){
  if(p_index>=m_size){
   throw std::out_of_range("INDEX OUT OF RANGE");
  }
  return m_data[p_index];
}

/**
*@brief imprime todos los valores en el vector en la consola
*
*/
template<class Type> 
void Vector<Type>::print(){
  std::cout<<"{ ";
  for (size_t i = 0; i < m_size; i++){
   std::cout << m_data[i];
   if(i!=m_size-1) {
     std::cout<<", ";
   }
  }
  std::cout<<" }\n";
}

/**
*@brief devuelve el primer valor en el vector
*@return el primer valor en el vector
*/
template<class Type> 
Type Vector<Type>::front(){
  return m_data[0];
}

/**
*@brief devuelve el ultimo valor en el vector
*@return el ultimo valor en el vector
*/
template<class Type> 
Type Vector<Type>::back(){
  return m_data[m_size-1];
}

/**
*@brief devuelve el numero de elementos
*@return el elementos en el vector
*/
template <class Type>
bool Vector<Type>::inVector(Type p_data){
  for (size_t i = 0; i < m_size; i++){
   if(m_data[i]==p_data) {
     return true;
   }
  }
  return false;
}

/**
*@brief inserta un elemento al vector
*@param elemento a insertar
*/
template <class Type>
void Vector<Type>::push_back(Type p_elem){
  if(m_size==m_capacity){
    resize();
  }
  m_data[m_size] = p_elem;
  m_size++;
}

/**
*@brief inserta un elemento al vector
*@param elemento a insertar
*/
template <class Type>
void Vector<Type>::push_front(Type p_elem){
  if(m_size==m_capacity||m_capacity==0){
    resize();
  }

  for (size_t i = m_size; i > 0; i--){
    m_data[i]=m_data[i-1];
  }
  m_data[0]=p_elem;
  m_size++;
  
}


/**
*@brief actualiza el tamano del vector (lo duplica) esto se puede cambiar a ++ si no se hacen cambios muy seguidos, o si nada mas se agregara uno o dos datos
*/
template <class Type>
void Vector<Type>::resize(){
  Type* pointerTempArray = new Type[m_capacity];

  for (size_t i = 0; i < m_capacity; i++){
    pointerTempArray[i]=m_data[i];
  }

  delete[] m_data;
  m_capacity*=2;
  m_data = new Type[m_capacity];

  for (size_t i = 0; i < m_size; i++){
    m_data[i]=pointerTempArray[i];
  }

  delete[] pointerTempArray;
}


/**
*@brief actualiza el tamano del vector  al tamaño de los datos 
*/
template <class Type>
void Vector<Type>::shrink_to_fit(){
  if(m_capacity!=m_size && m_capacity>0){
    Type* pointerTempArray = new Type[m_size];

    for (size_t i = 0; i < m_size; i++){
      pointerTempArray[i]=m_data[i];
    }

    delete[] m_data;
    m_capacity=m_size;
    m_data = new Type[m_capacity];

    for (size_t i = 0; i < m_size; i++){
      m_data[i]=pointerTempArray[i];
    }
      
    delete[] pointerTempArray;
  }
}

/**
*@brief elimina el ultimo elemento
*
*/
template <class Type>
void Vector<Type>::pop_back(){
  //m_data[m_size-1] = 0; // No es necesario
  m_size--;
}

/**
*@brief elimina todos los elementos
*
*/
template <class Type>
void Vector<Type>::clear(){
  //m_data[m_size-1] = 0; // No es necesario
  m_size=0;
}

/**
*@brief assigna un elemento p_times veces
*
*/
template <class Type>
void Vector<Type>::assign(size_t p_times, Type p_elem){
  size_t sizeAtStartOfLoop = m_size;
  
  for(size_t i = 0; i < p_times; i++){
    if(i < sizeAtStartOfLoop){
      m_data[i]=p_elem;
    }else {
      push_back(p_elem);
    }
  }
}

/**
*@brief elimina el elemento en el índice indicado, sin dejar huecos en el vector.
*
*/
template <class Type>
void Vector<Type>::erase_at(size_t p_index){
  if(p_index < m_size){
    for (size_t i = p_index; i < m_size; i++){
      m_data[i]=m_data[i+1];
    }
    m_size--;
  } else
    throw std::out_of_range("INDEX OUT OF RANGE");
}

/**
*@brief elimina todas las instancias de un elemento
*
*/
template <class Type>
void Vector<Type>::erase(Type p_data){
  for(int i = m_size; i >= 0; i--){
    if(m_data[i] == p_data){
      erase_at(i);
    }
  }
}

/**
*@brief  intercambia el elemento del vector en la posición i, por el elemento en la posición j.
*
*/
template <class Type>
void Vector<Type>::swap(size_t i,size_t j){
  // Hace falta verificar que i y j son menores que m_size
  Type tempStorage = m_data[i];
  m_data[i] = m_data[j];
  m_data[j] = tempStorage;
}

/**
*@brief junta dos vectores
*
*/
template <class Type>
void Vector<Type>::join(Vector& p_v){
  for (size_t i = 0; i <p_v.size();i++){
    push_back(p_v.at(i));
  }
}


/**
*@brief sobrecarga de [] que permite obtener la referencia de un dato en el indice dado
*/
template <class Type>
Type& Vector<Type>::operator[](const size_t& p_index){
  if(p_index >=m_size){
    throw std::out_of_range("INDEX OUT OF RANGE");
  }
  return m_data[p_index];
}

/**
*@brief sobrecarga de = que permite copiar un vector
*/
template <class Type>
Vector<Type>& Vector<Type>::operator=(Vector& p_v){
  delete[] m_data;
  m_data = new Type[p_v.capacity()];
  m_capacity = p_v.capacity();
  m_size = p_v.size();

  for (size_t i = 0; i <m_size;i++){
    m_data[i]=p_v.at(i);
  }
  return *this;
}

/**
*@brief sobrecarga de == que permite comparar vectores
*/
template <class Type>
bool Vector<Type>::operator==(Vector& p_v){
  bool equal = true;
  if(m_size!=p_v.m_size){
    equal = false;
  }
  else
    for(int i = 0; i < m_size; i++){
      if(m_data[i]!=p_v.at(i)){
        equal=false;
        break;
      }
    }
  
  return equal;
}

/**
*@brief sobrecarga de != que permite comparar vectores
*/
template <class Type>
bool Vector<Type>::operator!=(Vector& p_v){
  bool equal = true;
  if(m_size!=p_v.m_size){
    equal = false;
  }
  else
    for(int i = 0; i < m_size; i++){
      if(m_data[i]!=p_v.at(i)){
        equal=false;
        break;
      }
    }
  
  return !equal;
}

/**
*@brief sobrecarga de = que permite copiar un vector
*/
template <class Type>
Vector<Type>& Vector<Type>::operator+(Vector& p_v){

  for (size_t i = 0; i <p_v.size();i++){
    push_back(p_v.at(i));
  }
  return *this;
}
