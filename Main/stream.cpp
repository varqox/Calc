#include "stream.hpp"

namespace sim
{
#define TO_STRING_MACRO             \
    while(a>0)                      \
    {                               \
        tmp=a/10;                   \
        buff[j++]=a-tmp*10+'0';     \
        a=tmp;                      \
    }                               \
    buff[j]='\0';                   \
    while(--j>++i)                  \
        std::swap(buff[i], buff[j]);\

    void to_string(char* buff, int a)
    {
        int i=-1, j=0;
        int tmp;
        if(a<0)
        {
            buff[j++]='-';
            ++i;
            a=-a;
        }
        else if(a==0) buff[j++]='0';
        TO_STRING_MACRO
    }

    void to_string(char* buff, unsigned a)
    {
        int i=-1, j=0;
        unsigned tmp;
        if(a==0) buff[++j]='0';
        TO_STRING_MACRO
    }

    void to_string(char* buff, long a)
    {
        int i=-1, j=0;
        long tmp;
        if(a<0)
        {
            buff[j++]='-';
            ++i;
            a=-a;
        }
        else if(a==0) buff[j++]='0';
        TO_STRING_MACRO
    }

    void to_string(char* buff, unsigned long a)
    {
        int i=-1, j=0;
        unsigned long tmp;
        if(a==0) buff[j++]='0';
        TO_STRING_MACRO
    }

    void to_string(char* buff, long long a)
    {
        int i=-1, j=0;
        long long tmp;
        if(a<0)
        {
            buff[j++]='-';
            ++i;
            a=-a;
        }
        else if(a==0) buff[j++]='0';
        TO_STRING_MACRO
    }

    void to_string(char* buff, unsigned long long a)
    {
        int i=-1, j=0;
        unsigned long long tmp;
        if(a==0) buff[j++]='0';
        TO_STRING_MACRO
    }
#undef TO_STRING_MACRO

#ifdef WIN32
    ostream cout(std::cout);
    ostream cerr(std::cerr);
#else
    ostream cout(stdout);
    ostream cerr(stderr);
#endif
}
