#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <qobject.h>

template <class T>
class MyVector
{


    T* vector;
    int _length;
public:
//    explicit MyVector(QObject* parrent = nullptr){
//        vector = nullptr;
//    }

//    MyVector(MyVector& user): vector(user.vector), _length(user._length) {};

//    const MyVector operator =(MyVector user) const{
//        MyVector user2(user);
//        return user2;
//    }

    void append(T el){
        vector[_length++] = el;
    }
    int length(){
        return _length;
    }

    bool contains(T element){
        for(int i = 0; i < _length; i++)
            if (vector[i] == element)
                return true;
        return false;
    }

    T operator[](int i){
        return vector[i];
    }

//    friend bool operator==(const MyVector& user1, const MyVector& user2) { return user1._length == user2._length; }
};

#endif // MYVECTOR_H
