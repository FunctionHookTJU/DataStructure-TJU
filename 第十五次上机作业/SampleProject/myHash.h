/*******************************************************************************
* FileName:         myHash.cpp
* Author:           于乘骁
* Student Number:   3024244054
* Date:             2025/12/29 09:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #15
*******************************************************************************/


class MyHash{
private:
    int* keys;
    int* values;
    int maxSize;
    int nowSize;
    
    int hash_Mod(int key){ 
        return key % maxSize;

    }
    int rehash(int hashed_key, int attempt){
        return (hashed_key + attempt * attempt) % maxSize;
    }

    bool isPrime(int num){
        if(num <=1 )return false;
        if(num <= 3)return true;
        if(num % 2 == 0||num % 3 == 0)return false;
        for(int i = 5;i*i<num;i+=6){
            if(num % i == 0 || num % (i+2) == 0 )return false;
        }
        return true;
    }
    int nextPrime(int num){
        int t=num;
        while(!isPrime(t)){
            t++;
        }
        return t;
    }

public:
    /**
     *  声明一个哈希表，哈希表中元素最多为max_element个。
        @name MyHash(int max_element)
        @param arg1  哈希表对最大元素个数
        @return 
    */
    MyHash(int max_element);


    /**
     *  析构函数
        @name 
        @param 
        @return 
    */
    ~MyHash();




    /**
     *  获取哈希表中键值为key的元素的值。 
        @name int getvalue(int);
        @param  arg1 需要获取值的主键
        @return int 对应key值储存的结果
    */
    int getvalue(int key);



    /**
     *  将哈希表中键值为key的值设定为value。 
        @name void setvalue(int, int);
        @param  arg1 需要设定的键值key
        @param  arg2 需要被设定的值value
        @return void
    */
    void setvalue(int key, int value);   

    int find(int key);
};