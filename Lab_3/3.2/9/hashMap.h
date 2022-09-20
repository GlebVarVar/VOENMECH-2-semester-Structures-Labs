#include <cstddef>

template <typename K, typename V>
struct HashNode
{
    // пара ключ значение
    K _key;
    V _value;
    // следующий элемент(используется если произошла коллизия)
    HashNode *_next;

    HashNode(const K &key, const V &value) : _key(key), _value(value), _next(NULL) {}

    K getKey() const { return _key; }

    V getValue() const { return _value; }

    void setValue(V value) { _value = value; }

    HashNode *getNext() const { return _next; }

    void setNext(HashNode *next) { _next = next; }
};

template <typename K, typename V, size_t tableSize, typename F>
class HashMap
{
public:
    HashMap() : table(),
                hashFunc(), comparing(0), totalMemory(0)
    {
        totalMemory = tableSize * sizeof(HashNode<K, V>) + 8 + sizeof(hashFunc);
    }

    ~HashMap()
    {
        // удаляем все слоты один за другим
        for (size_t i = 0; i < tableSize; ++i)
        {
            HashNode<K, V> *entry = table[i];

            while (entry != NULL)
            {
                HashNode<K, V> *prev = entry;
                entry = entry->getNext();
                delete prev;
            }
            table[i] = NULL;
        }
    }

    // получение значения по ключу
    bool get(const K &key, V &value)
    {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *entry = table[hashValue];

        while (entry != NULL)
        {
            comparing++; // увеличиваем количество сравнений
            if (entry->getKey() == key)
            {
                value = entry->getValue();
                return true;
            }

            entry = entry->getNext();
        }

        return false;
    }

    // запись в хеш-таблицу
    void put(const K &key, const V &value)
    {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = NULL;
        HashNode<K, V> *entry = table[hashValue];

        while (entry != NULL && entry->getKey() != key)
        {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == NULL)
        {
            entry = new HashNode<K, V>(key, value);

            if (prev == NULL)
            {
                // если слот ещё не занят то записываем как первый
                table[hashValue] = entry;
            }
            else
            {
                // иначе записываем последовательно
                prev->setNext(entry);
            }
            totalMemory += sizeof(HashNode<K, V>);
        }
        else
        {
            // если элемент уже был то просто обновляем его значение
            entry->setValue(value);
        }
    }

    // удаление элемента из хеш-таблицы
    void remove(const K &key)
    {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = NULL;
        HashNode<K, V> *entry = table[hashValue];

        while (entry != NULL && entry->getKey() != key)
        {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == NULL)
        {
            // если ключ не найден то просто выходим
            return;
        }
        else
        {
            if (prev == NULL)
            {
                // удаляем элемент списка если перед ним ничего нет
                table[hashValue] = entry->getNext();
            }
            else
            {
                // удаляем элемент если он в середине
                prev->setNext(entry->getNext());
            }
            // из общей выделенной памяти вычитаем удаленный элемент
            totalMemory -= sizeof(HashNode<K, V>);
            delete entry;
        }
    }

    // получаем количество сравнений и обнуляем счетчик
    int getComparing()
    {
        int i = comparing;
        comparing = 0;
        return i;
    }

    // получаем количество выделенной памяти
    int getTotalMemory()
    {
        return totalMemory;
    }

private:
    HashMap(const HashMap &other);

    const HashMap &operator=(const HashMap &other);

    HashNode<K, V> *table[tableSize];
    F hashFunc;
    int comparing;
    int totalMemory;
};
