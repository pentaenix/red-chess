#include <iostream>
#include "Queue.hpp"
#include "Stack.hpp"
#include "Vector.hpp"


using std::cout;
using std::invalid_argument;
/**
 * @author Mateo Saldivar
 * @class vector tree
 * @brief data structure that stores interconnected nodes 
 * @template T data type to store
 */
template <class T>
class Graph {
  private:
    class NodeT {
      private:
        T m_data;
        Vector<NodeT*> m_children;
        int maxChildren = 5;

        void enqueueChildren(queue<NodeT*>& p_queue, Vector<NodeT*>& p_visited){
          p_visited.push_back(this);
          for(int i = 0; i < m_children.size();i++){
            if(!p_visited.inVector(m_children[i])){
              p_queue.enqueue(m_children[i]);
            }
          }
          p_queue.dequeue();
        }

        void pushChildren(stack<NodeT*>& p_stack, Vector<NodeT*>& p_visited){
          p_visited.push_back(this);
          p_stack.pop();
          for(int i = 0; i < m_children.size();i++){
            if(!p_visited.inVector(m_children[i])){
              p_stack.push(m_children[i]);
            }
          }
        }

      friend class Graph;
    };

    NodeT  * m_pRoot;
    /**
     * @brief creates a new node
     * @param p_data value to insert
     * @return a pointer to the new node
     */
    NodeT* generateNode(T p_data) {
      NodeT* newNodeT = new NodeT;
      newNodeT->m_data = p_data;
      return newNodeT;
    }

    /**
     * @brief 
     * @return
     */
    NodeT*& getRootNodeT() { 
      return m_pRoot;
    }
    NodeT* BFS(T p_data);
    NodeT* DFS(T p_data);

    void checkIfEmpty();
    bool nodeFull(NodeT* node);
    void addChild(NodeT* p_parent, NodeT* p_child);
    void addDoubleChild(NodeT* p_parent, NodeT* p_child);

  public:
    Graph<T>(T p_data) noexcept {
      NodeT* newNodeT = generateNode(p_data);
      m_pRoot = newNodeT;
    }

    void insertBFS(T p_data);
    void insertDFS(T p_data);
    void insert(T p_dataParent, T p_dataChild);
    bool boolBFS(T p_data);
    bool boolDFS(T p_data);  
    bool alreadyConnected(NodeT* start, NodeT* finish);
    void addEdge(T start, T finish);
    void addDoubleEdge(T start, T finish);
    void deleteBFS(T p_data);
    void traverse();
    Vector<T> getChildren(T p_data);

};

/**
 * @brief looks for every node in the tree for a node with data p_data via BFS
 * @param p_data value to find
 * @return the Node specified or nullptr if the node doesnt exists
*/
template <class T>
typename Graph<T>::NodeT* Graph<T>::BFS(T p_data) {
  queue<NodeT*> q;
  q.enqueue(getRootNodeT());
  NodeT* pCurrent = q.peek();
  Vector<NodeT*> visited;
  while(pCurrent) {
    if (pCurrent->m_data == p_data) {
      break;
    }
    pCurrent->enqueueChildren(q, visited);
    pCurrent = q.peek();
  }
  return pCurrent;
}

/**
 * @brief looks for every node in the tree for a node with data p_data via DFS
 * @param p_data value to find
 * @return the Node specified or nullptr if the node doesnt exists
*/
template <class T>
typename Graph<T>::NodeT* Graph<T>::DFS(T p_data) {
  checkIfEmpty();
  stack<NodeT*> s;
  s.push(getRootNodeT());
  NodeT* pCurrent = s.peek();
  Vector<NodeT*> visited;
  while(pCurrent) {
    if (pCurrent->m_data == p_data) {
      break;
    }
    pCurrent->pushChildren(s, visited);
    pCurrent = s.peek();
  }
  return pCurrent;
}

/**
 * @brief looks for every node in the tree for a node with data p_data via BFS
 * @param p_data value to find
 * @return true if data is in the tree false if its not
*/
template <class T>
bool Graph<T>::boolBFS(T p_data) {
  checkIfEmpty();
  queue<NodeT*> q;
  q.enqueue(getRootNodeT());
  NodeT* pCurrent = q.peek();
  Vector<NodeT*> visited;
  
  while(pCurrent) {
    if (pCurrent->m_data == p_data) {
      return true;
    }
    pCurrent->enqueueChildren(q, visited);
    pCurrent = q.peek();
  }
  return false;
}

/**
 * @brief looks for every node in the tree for a node with data p_data via DFS
 * @param p_data value to find
 * @return true if data is in the tree false if its not
*/
template <class T>
bool Graph<T>::boolDFS(T p_data) {
  checkIfEmpty();
  stack<NodeT*> s;
  s.push(getRootNodeT());
  NodeT* pCurrent = s.peek();
  Vector<NodeT*> visited;
  
  while(pCurrent) {
    if (pCurrent->m_data == p_data) {
      return true;
    }
    pCurrent->pushChildren(s, visited);
    pCurrent = s.peek();
  }
  return false;
}

/**
 * @brief inserts a node via BFS 
 * @param p_data value to insert
 * @throw value in tree
*/
template <class T>
void Graph<T>::insertBFS(T p_data) {
  checkIfEmpty();
  if(!boolBFS(p_data)){
    NodeT* nodeToInsert = generateNode(p_data);
    queue<NodeT*> q;
    q.enqueue(getRootNodeT());
    NodeT* pCurrent = q.peek();
    Vector<NodeT*> visited;
    
    while(pCurrent){
      if (nodeFull(pCurrent)) {
        pCurrent->enqueueChildren(q, visited);
      } else {
        addChild(pCurrent,nodeToInsert);
        break;
      }
      pCurrent = q.peek();
    }
  }else{
    throw invalid_argument("ERROR: VALUE ALREADY IN TREE\n");
  }
}

/**
 * @brief inserts a node via DFS 
 * @param p_data value to insert
 * @throw value in tree
*/
template <class T>
void Graph<T>::insertDFS(T p_data) {
  if(!boolDFS(p_data)){
    NodeT* nodeToInsert = generateNode(p_data);
    stack<NodeT*> s;
    s.push(getRootNodeT());
    NodeT* pCurrent = s.peek();
    Vector<NodeT*> visited;
    
    while(pCurrent) {
      if (nodeFull(pCurrent)) {
       pCurrent->pushChildren(s, visited);
      }else {
        addChild(pCurrent,nodeToInsert);
        break;
      }
      pCurrent = s.peek();
    }
  }else{
    throw invalid_argument("ERROR: VALUE ALREADY IN TREE\n");
  }
}

/**
 * @brief inerts a node into a specified node
 * @param  p_dataParent parent node 
 * @param  p_dataChild child node
 * @throw full node, parent not in tree and child already in tree
*/
template <class T>
void Graph<T>::insert(T p_dataParent, T p_dataChild) {
  checkIfEmpty();
  if(!boolBFS(p_dataChild)){
    NodeT* parent = BFS(p_dataParent);
    Vector<NodeT*> visited;
    if(parent){
      NodeT* child = generateNode(p_dataChild);
      addChild(parent,child);    
    }else{
      throw invalid_argument("ERROR: VALUE NOT IN TREE\n");
    }
  }else{
    throw invalid_argument("ERROR: VALUE CHILD ALREADY IN TREE\n");
  }
}

/**
 * @brief prints the entire tree "node data[c,c,c...]"
 * 
*/
template <class T>
void Graph<T>::traverse() {
  checkIfEmpty();
  queue<NodeT*> q;
  q.enqueue(getRootNodeT());
  NodeT* pCurrent = q.peek();
  Vector<NodeT*> visited;
  
  while(pCurrent) {
    cout<<q.peek()->m_data<< "[";
    for(int i = 0; i < q.peek()->m_children.size();i++){
      cout<<q.peek()->m_children[i]->m_data;
      if(i!=q.peek()->m_children.size()-1){
        cout<<", ";
      }
    }
    cout<<"]\n";
    pCurrent->enqueueChildren(q, visited);
    pCurrent = q.peek();
    }
}

/**
 * @brief checks if the tree has any values
 * @throw empty tree if there are no values
*/
template <class T>
void Graph<T>::checkIfEmpty() {
  if(!m_pRoot){
    throw std::length_error("ERROR: EMPTY Graph\n");
  }
}

/**
 * @brief checks if the node has reached the maximun number of children
 * @return true if its full false if its not
 * @param node, the node to check
*/
template <class T>
bool Graph<T>::nodeFull(NodeT* node) {
  if(node->m_children.size() >= node->maxChildren){
    return true;
  }else{
    return false; 
  }
}

/**
 * @brief checks if the nodes are already connected if not, they are linked
 * @throw when the nodes are already connected
 * @throw if the node is already full
 * @param node, the nodes to check and add
*/
template <class T>
void Graph<T>::addChild(NodeT* p_parent, NodeT* p_child) {
  if(!nodeFull(p_parent)){
    for(int i = 0; i < p_parent->m_children.size();i++){
      if(p_parent->m_children[i]==p_child){
        throw invalid_argument("this node is already a child of p_parent");
        return;
      }
    }
    p_parent->m_children.push_back(p_child);
  }else{
    throw invalid_argument("this node is already full");
  }
}

/**
 * @brief checks if the nodes are already connected if not, they are linked
 * @throw when the nodes are already connected
 * @throw if the node is already full
 * @param node, the nodes to check and add
*/
template <class T>
void Graph<T>::addDoubleChild(NodeT* p_parent, NodeT* p_child) {
    for(int i = 0; i < p_parent->m_children.size();i++){
      if(p_parent->m_children[i]==p_child){
        return;
      }
    }
    for(int i = 0; i < p_child->m_children.size();i++){
      if(p_child->m_children[i]==p_parent){
        return;
      }
    }
  p_parent->m_children.push_back(p_child);
  p_child->m_children.push_back(p_parent);
  
}


/**
 * @brief deletes a node with a given value and reinserts the children data in the next nodes
 * 
*/
template <class T>
void Graph<T>::deleteBFS(T p_data) {
  if(getRootNodeT()->m_data==p_data){
    throw invalid_argument("Cant delete the root node");
  }
  checkIfEmpty();
  queue<NodeT*> q;
  Vector<NodeT*> visited;
  NodeT* toDelete = nullptr;
  q.enqueue(getRootNodeT());
  NodeT* pCurrent = q.peek();
  
  while(pCurrent) {
    visited.push_back(pCurrent);
    for(int i = 0; i < pCurrent->m_children.size();i++){
      NodeT* curChild = pCurrent->m_children[i];
      if(curChild->m_data==p_data){
        toDelete = curChild;
        q.clear();
        break;
      }
      if(!visited.inVector(curChild)){
        q.enqueue(curChild);
      }
    }if(toDelete){
      break;
    }
    q.dequeue();
    pCurrent = q.peek();
  }

  if(toDelete){
    pCurrent->m_children.erase(toDelete);
    for(int i = 0; i < toDelete->m_children.size(); i++){
      q.enqueue(pCurrent);
      NodeT* sCurrent = q.peek();
    
      while(sCurrent){
        if (nodeFull(sCurrent)) {
          sCurrent->enqueueChildren(q, visited);
        } else {
          addChild(sCurrent,toDelete->m_children[i]);
          break;
        }
      sCurrent = q.peek();
      }
    }
    delete[] toDelete;
  }
}

/**
 * @brief Adds an edge to the Graph, if the staring node doesnt exist, the two datas or the nodes are already connected, this will throw an error
*/
template <class T>
void Graph<T>::addEdge(T start, T finish){
  if(start!=finish && BFS(start) && !nodeFull(BFS(start))){
    queue<NodeT*> q;
    Vector<NodeT*> visited;
    q.enqueue(getRootNodeT());
    NodeT* str = nullptr;
    NodeT* end = nullptr;
    NodeT* pCurrent = q.peek();

    
    while(pCurrent) {
      if(pCurrent->m_data==start && !str)
        str=pCurrent;
      if(pCurrent->m_data==finish && !end)
        end=pCurrent;
      if(!str&&!end){
        pCurrent->enqueueChildren(q, visited);
        pCurrent = q.peek();
      }else{
        q.clear();
        break;
      }
    }
    if(str){
       if(end){
          str->m_children.push_back(end);
       }else{
         NodeT* tmp = generateNode(finish);
         str->m_children.push_back(tmp);
       }
    }
  }else
   throw std::invalid_argument("ERROR: Can't link elements\n");
}


/**
 * @brief Adds an edge to the Graph, if the staring node doesnt exist, the two datas or the nodes are already connected, this will throw an error
*/
template <class T>
void Graph<T>::addDoubleEdge(T start, T finish){
  if(start!=finish && BFS(start) && 
    !alreadyConnected(BFS(start),BFS(finish)) && 
    !nodeFull(BFS(start))) {

    if(BFS(finish)){
      if(alreadyConnected(BFS(finish),BFS(start))) return;
    }
    queue<NodeT*> q;
    Vector<NodeT*> visited;
    q.enqueue(getRootNodeT());
    //NodeT* str = BFS(start);
    //NodeT* end = BFS(finish);

    NodeT* str = nullptr;
    NodeT* end =nullptr;
    NodeT* pCurrent = q.peek();

    
    while(pCurrent) {
      if(pCurrent->m_data==start && !str)
        str=pCurrent;
      if(pCurrent->m_data==finish && !end)
        end=pCurrent;
      if(!str&&!end){
        pCurrent->enqueueChildren(q, visited);
        pCurrent = q.peek();
      }else{
        q.clear();
        break;
      }
    }
    if(!end) end = DFS(finish);
    if(!str) str = DFS(start);
    
    if(str){
       if(!end){
         end = generateNode(finish);
       }
      addDoubleChild(str,end);
    }
  }
}

/**
 * @brief checks the connection between two nodes
 * @return true if the finish is already a child of start
*/
template <class T>
bool Graph<T>::alreadyConnected(NodeT* start, NodeT* finish) { 
    for(int i = 0; i < start->m_children.size();i++){
      if(start->m_children[i]==finish){
        return true;
      }
    }
  
  return false;
}

/**
 * @brief returns allthe childern in a vector
 * @return a vector with the data of each children
*/
template <class T>
Vector<T> Graph<T>::getChildren(T p_data) { 
  NodeT* node = BFS(p_data);
  Vector<T> ret;
    for(int i = 0; i < node->m_children.size();i++){
      ret.push_back(node->m_children[i]->m_data);
    }
  return ret;
}


 