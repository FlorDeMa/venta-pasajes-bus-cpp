#pragma once
template<typename T1, typename T2>
class HashEntidad {
private:
    T1 key;
    T2 value;
public:
    HashEntidad(T1 key, T2 value) {
        this->key = key;
        this->value = value;
    }
    T1 getKey() { return key; }
    T2 getValue() { return value; }
};
