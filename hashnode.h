#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <cctype>
#include <set>
#include <vector>


// шаблон для универсального типа

template<typename K, typename V>


// Hashnode class

class HashNode{

    public:
    V value;
    K key;
    int count = 0;
    // Конструктор hashnode

    HashNode(K key, V value){
        this->value = value;

        this->key = key;

    }

};


// шаблон для универсального типа

template<typename K, typename V>


// Наш собственный класс Hashmap

class HashMap{
public:

    HashMap(){
        // Начальная емкость хеш-массива
        capacity = 20;
        size=0;
        arr = new HashNode<K,V>*[capacity];
        // Инициализируем все элементы массива как NULL
        for(int i=0 ; i < capacity ; i++)
            arr[i] = NULL;
        // фиктивный узел со значением и ключом -1

        dummy = new HashNode<K,V>(-1, "-1");
    }

    HashMap(HashMap const &other){
        capacity = 20;
        size=0;
        arr = new HashNode<K,V>*[capacity];
        dummy = new HashNode<K,V>(-1, "-1");
        for(int i = 1; i <= other.size; ++i){
            this->insertNode(other.arr[hashCode(i)]->value);
        }
    }

    ~HashMap(){
        DelAll();
    }

    // Реализует хеш-функцию для поиска индекса

    // для ключа

    int hashCode(K key){
        return key % capacity;
    }

    void DelAll(){
        int s = size;
        for(int i = 1; i <= s; i++){
            this->deleteNode(i);
        }
        size = 0;
        key = 1;
    }

    // Функция для добавления пары ключ-значение

    void insertNode(V value){

        if(!Find(value)){

            HashNode<K,V> *temp = new HashNode<K,V>(key, value);

            // Применяем хеш-функцию для поиска индекса для данного ключа

            int hashIndex = hashCode(key);

            // найти следующее свободное место

            while(arr[hashIndex] != NULL && arr[hashIndex]->key != key

                  && arr[hashIndex]->key != -1){

                hashIndex++;

                hashIndex %= capacity;

            }

            // если новый узел для вставки увеличивает текущий размер

            if(arr[hashIndex] == NULL || arr[hashIndex]->key == -1){
                size++;
            }

            arr[hashIndex] = temp;
            arr[hashIndex]->count++;
            key++;
        }else{
            int k = get_key(value);
            int hashIndex = hashCode(k);
            arr[hashIndex]->count++;
        }

    }

    // Функция для удаления пары ключ-значение

    V deleteNode(int k){

        // Применяем хеш-функцию для поиска индекса для данного ключа

        int hashIndex = hashCode(k);

        // найти узел с заданным ключом

        while(arr[hashIndex] != NULL){
            // если узел найден

            if(arr[hashIndex]->key == k){
                HashNode<K,V> *temp = arr[hashIndex];
                // Вставляем здесь фиктивный узел для дальнейшего использования
                arr[hashIndex] = dummy;
                // Уменьшаем размер
                size--;
                return temp->value;
            }

            hashIndex++;

            hashIndex %= capacity;
        }
        // Если не найдено, вернем null

        return NULL;

    }

    void deleteNode(std::string value){
        if(this->Find(value)){
            // Применяем хеш-функцию для поиска индекса для данного ключа
            int hashIndex = hashCode(1);
            // найти узел с заданным ключом
            while(arr[hashIndex] != NULL){
                // если узел найден
                if(arr[hashIndex]->value == value){
                    HashNode<K,V> *temp = arr[hashIndex];
                    // Вставляем здесь фиктивный узел для дальнейшего использования
                    arr[hashIndex] = dummy;
                    // Уменьшаем размер
                    size--;
                    break;
                }
                hashIndex++;
                hashIndex %= capacity;
            }
        }
    }

    // Функция для поиска значения для данного ключа

    V get(int key){
        // Применяем хеш-функцию для поиска индекса для данного ключа

        int hashIndex = hashCode(key);
        int counter=0;

        // найти узел с заданным ключом

        while(arr[hashIndex] != NULL){
             int counter = 0;
             if(counter++>capacity)  // чтобы избежать бесконечного цикла
                return "";
            // если найденный узел возвращает его значение

             if(arr[hashIndex]->key == key){
                 return std::to_string(arr[hashIndex]->count) + " - " + arr[hashIndex]->value;
//                 return arr[hashIndex]->value + " " + std::to_string(arr[hashIndex]->count);
             }

            hashIndex++;
            hashIndex %= capacity;
        }
        // Если не найдено, вернем null

        return "";
    }

    int get_key(std::string value){
        // Применяем хеш-функцию для поиска индекса для данного ключа
        int hashIndex = hashCode(1);
        int counter=0;
        // найти узел с заданным ключом

        while(arr[hashIndex] != NULL){
             int counter = 0;
             if(counter++>capacity)  // чтобы избежать бесконечного цикла
                return 0;

            // если найденный узел возвращает его значение
            if(arr[hashIndex]->value == value)
                return arr[hashIndex]->key;

            hashIndex++;
            hashIndex %= capacity;
        }
        // Если не найдено, вернем null

        return 0;
    }

    int get_count(std::string value){
        // Применяем хеш-функцию для поиска индекса для данного ключа
        int hashIndex = hashCode(1);
        int counter=0;
        // найти узел с заданным ключом

        while(arr[hashIndex] != NULL){
             int counter = 0;
             if(counter++>capacity)  // чтобы избежать бесконечного цикла
                return 0;
            // если найденный узел возвращает его значение
            if(arr[hashIndex]->value == value)
                return arr[hashIndex]->count;

            hashIndex++;
            hashIndex %= capacity;
        }
        // Если не найдено, вернем null
        return 0;

    }

    // Возвращаем текущий размер

    int sizeofMap(){
        return size;
    }

    // Возвращаем true если размер равен 0

    bool isEmpty(){
        return size == 0;
    }

    // Функция для отображения сохраненных пар ключ-значение

    void display(){
        for(int i=0 ; i<capacity ; i++){
            if(arr[i] != NULL && arr[i]->key != -1)
                std::cout << "key = " << arr[i]->key
                     <<"  value = "<< arr[i]->value << "  count = " << arr[i]->count << std::endl;
        }
    }

    int toFile(std::string& file){
        QJsonArray array;
        for(int i=0 ; i<capacity ; i++) {
            if(arr[i] != NULL && arr[i]->key != -1){
                std::string v = arr[i]->value;
                QJsonObject obj{
                    {"value", v.c_str()},
                    {"count", arr[i]->count}
                };
                array.append(obj);
            }
        }

        QJsonDocument stack_doc(array);
        std::ofstream out(file);
        if (out.is_open()){
            out << stack_doc.toJson().toStdString() << std::endl;
        }
        out.close();
        return 0;
    }

    int intoFile(std::string& file){
        std::string line, stack = "";
        std::ifstream in(file);
        if (in.is_open()){
            while (getline(in, line)){
                stack += line;
            }
        }
        in.close();
        QJsonDocument doc = QJsonDocument::fromJson(QString::fromUtf8(stack.c_str()).toLocal8Bit());
        QJsonArray array = doc.array();
        for(int i = 0; i < array.size(); i++){
            int c;
            std::string v;
            v = array.at(i)["value"].toString().toStdString();
            c = array.at(i)["count"].toInt();
            this->insertNode(v);
            int j = this->get_key(v);
            int hashIndex = hashCode(j);
            this->arr[hashIndex]->count = c;
        }
        return 0;
    }

    bool Find(std::string value){
        // Применяем хеш-функцию для поиска индекса для данного ключа
        int hashIndex = hashCode(1);
        int counter=0;
        // найти узел с заданным ключом

        while(arr[hashIndex] != NULL){
             int counter = 0;
             if(counter++>capacity)  // чтобы избежать бесконечного цикла
                return false;

            // если найденный узел возвращает его значение
            if(arr[hashIndex]->value == value)
                return true;

            hashIndex++;
            hashIndex %= capacity;
        }
        // Если не найдено, вернем null

        return false;
    }
    int Find_counts(int count){
        int amount = 0;
        // Применяем хеш-функцию для поиска индекса для данного ключа
        int hashIndex = hashCode(1);
        int counter=0;
        // найти узел с заданным ключом

        while(arr[hashIndex] != NULL){
             int counter = 0;
             if(counter++>capacity)  // чтобы избежать бесконечного цикла
                return amount;

            // если найденный узел возвращает его значение
            if(arr[hashIndex]->count >= count)
                amount++;

            hashIndex++;
            hashIndex %= capacity;
        }
        // Если не найдено, вернем null
        return amount;
    }

    bool isEqualto(HashMap& other){
        if(this->size != other.size)
            return false;
        if (this->size == 0 && other.size == 0)
            return true;
        int hashIndex = hashCode(1);
        while(this->arr[hashIndex] != NULL){
            if(this->arr[hashIndex]->count != other.arr[hashIndex]->count){
                return false;
            }
            if(this->arr[hashIndex]->value != other.arr[hashIndex]->value){
                return false;
            }
            hashIndex++;

            hashIndex %= capacity;

        }
        return true;
    }    

    friend HashMap<int, std::string>& operator <<(HashMap<int, std::string>& s, std::string v){
        s.insertNode(v);
        return s;
    }

    int operator [] (std::string value){
        return get_count(value);
    }

    friend bool operator == (HashMap<int, std::string>& left, HashMap<int, std::string>& right){
        return left.isEqualto(right);
    }

    friend bool operator != (HashMap<int, std::string>& left, HashMap<int, std::string>& right){
        if(left.isEqualto(right)){
            return false;
        }
        return true;
    }

private:
    int key = 1;
    // массив хеш-элементов
    HashNode<K,V> **arr;
    int capacity;
    // текущий размер
    int size;
    // фиктивный узел
    HashNode<K,V> *dummy;
};

