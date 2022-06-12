#ifndef UNITY_H
#define UNITY_H

typedef struct _monoString
{
    void* klass;
    void* monitor;
    int length;    
    char chars[1];   
    int getLength()
    {
      return length;
    }
    char* getChars()
    {
        return chars;
    }
} monoString;


#endif