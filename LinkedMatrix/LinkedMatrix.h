#ifndef LinkedMatrix_H
#define LinkedMatrix_H
#include <Arduino.h>


// Quartz

template <typename T> 
class ListNode
{
    private:
        T m_value;
        ListNode *m_nextNode;

    public:
        ListNode( T value );

        ListNode( const ListNode &other ) = delete;

        ListNode operator = ( const ListNode &other) = delete;

        ~ListNode();

        T value() const;

        ListNode *nextNode() const;

        void setNextNode( ListNode *nextNode );

};

template <typename T> 
ListNode<T>::ListNode( T value )
{
    this->m_value = value;
    this->m_nextNode = nullptr;

}

template <typename T> 
ListNode<T>::ListNode::~ListNode()
{
    if( m_nextNode != nullptr )
    {
        delete m_nextNode;
        m_nextNode = nullptr;
    }
}

template <typename T> 
T ListNode<T>::ListNode::value() const
{
    return m_value;
}

template <typename T> 
ListNode<T> *ListNode<T>::nextNode() const
{
    return m_nextNode;
}

template <typename T> 
void ListNode<T>::setNextNode( ListNode *nextNode )
{
    m_nextNode = nextNode;
}


// Atom

template <typename T>
class LinkedList
{
    private:
        ListNode<T> *m_head;
        ListNode<T> *m_current;//Aunque sea el nodo actual. Siempre apuntara al ultimo nodo.
        LinkedList *m_nextList;
        int m_size;

    public:
        LinkedList();

        LinkedList( const LinkedList &other ) = delete;

        LinkedList operator = ( const LinkedList &other ) = delete;

        ~LinkedList();

        T at( int index) const;

        void append(T newElement );

        void insert( int index, T newElement);

        void write( int index, T newElement );

        void remove( T element );

        T pop( int index = -1 );

        int count( T element ) const;

        int length() const;

        void print( char _endl = '\t') const;

        void setNextList( LinkedList *nextList );

        LinkedList<T> *nextList() const;

        void destroid();

};


template <typename T> 
void LinkedList<T>::destroid()
{
    
    if( m_nextList != nullptr )
    {
        delete m_nextList;
        m_nextList = nullptr;
    }
    if( m_head != nullptr )
    {
        delete m_head;
        // delete m_current;
        m_head = nullptr;
    }
}

template <typename T>
LinkedList<T>::LinkedList()
{
    //placeholder de donde inicia nuestra cabecera de la lista
    this->m_head = new ListNode<T>(0);
    this->m_size = 0;
    m_current = m_head;

    this->m_nextList = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    if( m_nextList != nullptr )
    {
        delete m_nextList;
        m_nextList = nullptr;
    }
    // if( m_head != nullptr )
    // {
    //     delete m_head;
    //     m_head = nullptr;
    // }
}

//LinkedList.at( index )
//Return list element by position.
//a.at( -1 ) return last element of list
template <typename T>
T LinkedList<T>::at( int index) const
{
    if ( index >= m_size || index < -1 )
    {
        Serial.println("index out of range");
        abort();
    }
    else if ( index == -1)
    {
        return m_current->value();
    }

    int i = 0;
    ListNode<T> *node = m_head->nextNode();
    while( node != nullptr && i < index)
    {
        node = node->nextNode();
        ++i;
    }
    if ( node != nullptr )
    {
        return node->value();
    }
    Serial.println("Contact me if this error occurs");
    abort();
    // return -1;

}

//LinkedList.append( x )
//Add an item to the end of the list.
template <typename T>
void LinkedList<T>::append(T newElement )
{
    ListNode<T> *newNode = new ListNode<T>(newElement);
    m_current->setNextNode(newNode);
    m_current = newNode;
    ++m_size;
}

//LinkedList.insert( index, x )
//Insert an item at a given position.
//The first argument is the index of the element before which to insert, so a.insert(0, x) inserts at the front of the list.
//a.insert(len(a), x) or a.insert(len(a) + n, x) or a.insert( -1, x) is equivalent to a.append(x).
template <typename T>
void LinkedList<T>::insert( int index, T newElement)
{
    if( index < -1 )
    {
        Serial.println("index out of range");
        abort();
    } 
    else if( index == -1 )
    {
        index = m_size;
    }

    ListNode<T> *newNode = new ListNode<T>(newElement);
    int i = 0;
    ListNode<T> *node = m_head->nextNode();
    ListNode<T> *prev = m_head;
    
    while( node != nullptr && i < index && i < m_size)
    {
        ++i;
        prev = node;
        node = node->nextNode();
    }

    if( prev != nullptr )
    {
        prev->setNextNode( newNode );

        if( node != nullptr )
        {
            newNode->setNextNode( node );
        }
        else 
        {
            m_current = newNode;
        }
        ++m_size;
    }
}

template <typename T>
void LinkedList<T>::write( int index, T newElement)
{
    this->insert( index, newElement );
    if ( index + 1 < m_size )
    {
        this->pop( index + 1);
    }
}

//LinkedList.remove( x )
//Remove the first item from the list whose value is equal to x.
template <typename T>
void LinkedList<T>::remove( T element )
{
    ListNode<T> *node = m_head->nextNode();
    ListNode<T> *prev = m_head;
    while (node != nullptr && node->value() != element)
    {
        prev = node;//Guardamos el nodo previo al encontrado.
        node = node->nextNode();//Si existe aca se guardara el elemento pra una posterior eliminacion.
    }

    if( node != nullptr)
    {
        prev->setNextNode(node->nextNode());
        if( prev->nextNode() == nullptr )
        {
            m_current = prev;
        }

        //Es necesario indicar que su siguiente nodo es nulo. de lo contrario al eliminarlo comienza una reaccion en cadena eliminando todo.
        node->setNextNode(nullptr);
        delete node;

        --m_size;
    }
}

//LinkedList.pop()
//Remove the item at the given position in the list, and return it. 
//If no index is specified, a.pop() or a.pop(-1) removes and returns the last item in the list.
template <typename T>
T LinkedList<T>::pop( int index)
{

    if( index >= m_size || index < -1 )
    {
        Serial.println("index out of range");
        abort();
        // return -1;
    } 
    else if ( index == -1 ) 
    {
        index = m_size - 1;
    } 

    int i = 0;
    ListNode<T> *node = m_head->nextNode();
    ListNode<T> *prev = m_head;
    while( node != nullptr && i < index )
    {
        ++i;
        prev = node;
        node = node->nextNode();
    }
    if ( node != nullptr )
    {
        T item = node->value();

        //Aca se borra el nodo de nuestra lista
        prev->setNextNode( node->nextNode() );
        if( prev->nextNode() == nullptr )
        {
            m_current = prev;
        }

        //Tambien cabe destacar que las suiguientes dos lineas son solo para limpiar memoria
        node->setNextNode( nullptr );
        delete node;
        --m_size;

        return item;
    }
    else
    {
        Serial.println("Contact me if this error occurs");
        abort();
        // return -1;
    }
}



//LinkedList.count( x )
//Return the number of times x appears in the list.
template <typename T>
int LinkedList<T>::count( T element ) const
{
    ListNode<T> *node = m_head->nextNode();
    int counter = 0;

    while( node != nullptr )
    {
       if( node->value() == element )
       {
            ++counter;
       }
       node = node->nextNode();
    }
    return counter;
}

//LinkedList.length()
//Return the length list
template <typename T>
int LinkedList<T>::length() const
{
    return m_size;
}

//LinkedList.print()
//Print the list
template <typename T>
void LinkedList<T>::print( char _endl ) const 
{
    for( int i = 0; i < m_size; i++)
    {
        Serial.print( this->at(i) );
        Serial.print( " " );
    }
    Serial.print( _endl );
}

template <typename T>
void LinkedList<T>::setNextList( LinkedList *nextList )
{
    m_nextList = nextList;
}

template <typename T>
LinkedList<T> *LinkedList<T>::nextList() const
{
    return m_nextList;
}


// Structure


template <typename T>
class LinkedMatrix
{
    private:
        LinkedList<T> *m_head;
        LinkedList<T> *m_current;
        int m_size;

        void append();

    public:

        LinkedMatrix();

        LinkedMatrix( const LinkedMatrix &other ) = delete;

        LinkedMatrix operator = ( const LinkedMatrix &other ) = delete;

        ~LinkedMatrix();

        T at( int row, int col ) const;

        T maxElement() const;

        void write( int row, int col, T newElemet );

        int length() const;

        void print( char _endl = '\t') const;

        LinkedList<int>* shape() const;

        LinkedList<T>* getColumn( int colIndex) const;

        LinkedList<T>* getRow( int rowIndex) const;

        void initFill( int rows, int cols, T element );

        void destroid();

        
};


template <typename T> 
void LinkedMatrix<T>::destroid()
{
    
    if( m_head != nullptr )
    {
        delete m_head;
        m_head = nullptr;
    }
}

template<class T> 
T LinkedMatrix<T>::maxElement() const
{

    T max = 0;
    for ( int i = 0; i < this->shape()->at(0); i ++)
    {
        for( int j = 0; j < this->shape()->at(1); j++ )
        {
            T element = this->at( i, j);
            max = max < element ? element : max;
        }
    }
    return max;

}


template <typename T>
void LinkedMatrix<T>::initFill( int rows, int cols, T element )
{
    for ( int i = 0; i < rows; i ++)
    {
        for( int j = 0; j < cols; j++ )
        {
            this->write( i, j, element );
        }
    }
}

template <typename T>
LinkedMatrix<T>::LinkedMatrix()
{
    this->m_head = new LinkedList<T>();
    this->m_size = 0;
    m_current = m_head;

}

template <typename T>
LinkedMatrix<T>::~LinkedMatrix()
{
    if( m_head != nullptr )
    {
        delete m_head;
        m_head = nullptr;
    }
}

template <typename T>
LinkedList<T> *LinkedMatrix<T>::getRow( int rowIndex ) const
{

    LinkedList<T> *node = m_head->nextList();

    int i = 0;
    while( i < rowIndex )
    {
        ++i;
        node = node->nextList();
    }

    LinkedList<T> *row = new LinkedList<T>();

    //copy
    for ( int i = 0; i < node->length(); i++ )
    {
        row->append( node->at(i) );
    }

    //Reference selft
    // row = node;


    return row;
}

template <typename T>
LinkedList<T> *LinkedMatrix<T>::getColumn( int colIndex) const
{
    LinkedList<T> *col = new LinkedList<T>;

    LinkedList<T> *node = m_head->nextList();

    int i = 0;
    while( node != nullptr )
    {
        ++i;
        col->append( node->at(colIndex) );
        node = node->nextList();
    }

    return col;
}

template <typename T>
T LinkedMatrix<T>::at( int row, int col ) const
{
    LinkedList<T> *node = m_head->nextList();
    LinkedList<T> *prev = m_head;

    int i = 0;
    while( node != nullptr && i < row )
    {
        ++i;
        prev = node;
        node = node->nextList();
    }
    return node->at(col);
}

template <typename T>
void LinkedMatrix<T>::append()
{
    LinkedList<T> *newNode = new LinkedList<T>();
    m_current->setNextList(newNode);
    m_current = newNode;
    ++m_size;
}

template <typename T>
void LinkedMatrix<T>::write( int row, int col, T newElement )
{
    ListNode<T> *newNode = new ListNode<T>(newElement);
    LinkedList<T> *node = m_head->nextList();

    int i = 0;
    while( node != nullptr && i < row )
    {
        ++i;
        node = node->nextList();
    }

    if( node == nullptr )
    {
        this->append();
        node = m_current;
    }

    node->write( col, newElement );

}


template <typename T>
int LinkedMatrix<T>::length() const
{
    return m_size;
}

template <typename T>
LinkedList<int> *LinkedMatrix<T>::shape() const
{
    LinkedList<int> *shape = new LinkedList<int>();
    shape->append( this->length() ); 
    shape->append( m_current->length() );
    return shape;
}

template <typename T>
void LinkedMatrix<T>::print( char _endl ) const
{
    
    for ( int i = 0; i < this->shape()->at(0); i ++)
    {
        for( int j = 0; j < this->shape()->at(1); j++ )
        {
            Serial.print( this->at(i, j) );
            Serial.print( "\t");
        }
        Serial.print("\n");
    }
}


#endif