#ifndef STREAM_HPP
#define STREAM_HPP

#include <cstdio>
#include <string>
#include <cstring>

#ifdef WIN32
 #include <iostream>
 #define SIM_STREAM std::ostream&
#else
 #define SIM_STREAM std::FILE*
#endif

namespace sim
{
    void to_string(char*, int);
    void to_string(char*, unsigned);
    void to_string(char*, long);
    void to_string(char*, unsigned long);
    void to_string(char*, long long);
    void to_string(char*, unsigned long long);

    class ios_base
    {
    public:
        typedef unsigned fmtflags;
        static const fmtflags reset=1ul<<0;
        static const fmtflags internal=1ul<<1;
        static const fmtflags left=1ul<<2;
        static const fmtflags right=1ul<<3;
    protected:
        fmtflags _M_flags;
        unsigned _M_width, _M_precision;

        ios_base(): _M_flags(0), _M_width(0), _M_precision() {}

    public:
        virtual ~ios_base(){}

        fmtflags flags() const
        {return this->_M_flags;}

        fmtflags flags(fmtflags __fmtfl)
        {
            fmtflags __old=this->_M_flags;
            this->_M_flags=__fmtfl;
            return __old;
        }

        fmtflags setf(fmtflags __fmtfl)
        {
            fmtflags __old=this->_M_flags;
            this->_M_flags |= __fmtfl;
            return __old;
        }

        void unsetf(fmtflags __mask)
        {this->_M_flags &= ~__mask;}

        char fill(char fillch=' ');

        unsigned width() const
        {return this->_M_width;}

        unsigned width(unsigned __wide)
        {
            unsigned __old=this->_M_width;
            this->_M_width=__wide;
        return __old;
        }

        unsigned precision() const
        {return _M_precision;}

        unsigned precision(unsigned __precision)
        {
            unsigned __old=this->_M_precision;
            this->_M_precision=__precision;
            return __old;
        }
    };

    typedef ios_base ios;

    class basic_ostream : virtual public ios
    {
    public:
        typedef basic_ostream __ostream_type;
    protected:
        bool _M_ok;
        char _M_fill;

        class _M_flush
        {
        public:
            SIM_STREAM __stream;
            bool is_flush;
            unsigned size, max_size;
            char *buffer;

            _M_flush(SIM_STREAM stream, bool _b, unsigned _n=0): __stream(stream), is_flush(_b), size(0), max_size(_n), buffer(new char[_n+1]){}

            void resize(unsigned new_size)
            {
                this->flush();
                if(max_size==new_size) return;
                delete[] buffer;
                buffer=new char[this->max_size=new_size];
            }

            void add(char _c)
            {
                if(is_flush)
                {
                    if(this->size==this->max_size)
                    {
                    #ifdef WIN32
                        this->__stream.write(this->buffer, this->size);
                        this->__stream.flush();
                    #else
                        fwrite(this->buffer, sizeof(char), this->size, this->__stream);
                    #endif
                        this->size=1;
                        buffer[0]=_c;
                    }
                    else buffer[this->size++]=_c;
                }
                else
                {
                #ifdef WIN32
                    this->__stream.put(_c);
                    this->__stream.flush();
                #else
                    fputc(_c, this->__stream);
                #endif
                }
            }

            void add(const char* _str, unsigned _lenght)
            {
                if(is_flush)
                {
                    if(this->size+_lenght>this->max_size)
                    {
                        this->flush();
                        if(_lenght>this->max_size)
                        {
                            #ifdef WIN32
                                this->__stream.write(_str, _lenght);
                                this->__stream.flush();
                            #else
                                fwrite(_str, sizeof(char), _lenght, this->__stream);
                            #endif
                        }
                        else
                        {
                            memcpy(this->buffer, _str, _lenght);
                            this->size=_lenght;
                        }
                    }
                    else
                    {
                        memcpy(this->buffer+this->size, _str, _lenght);
                        this->size+=_lenght;
                    }
                }
                else
                {
                    #ifdef WIN32
                        this->__stream.write(_str, _lenght);
                        this->__stream.flush();
                    #else
                        fwrite(_str, sizeof(char), _lenght, this->__stream);
                    #endif
                }
            }

            void flush()
            {
                if(is_flush && this->size)
                {
                    #ifdef WIN32
                        this->__stream.write(this->buffer, this->size);
                        this->__stream.flush();
                    #else
                        fwrite(this->buffer, sizeof(char), this->size, this->__stream);
                    #endif
                }
                this->size=0;
            }

            ~_M_flush()
            {
                this->flush();
                delete[] buffer;
            }
        } _buffer;


        basic_ostream(SIM_STREAM stream, unsigned buffer_size): _M_ok(true), _M_fill(' '), _buffer(stream, true, buffer_size) {}

    public:
        basic_ostream(SIM_STREAM stream): _M_ok(true), _M_fill(' '), _buffer(stream, false) {}

        virtual ~basic_ostream(){}

        virtual bool good()
        {return _M_ok;}

        virtual bool fail()
        {return !_M_ok;}

        __ostream_type& flush()
        {
            _buffer.flush();
            return *this;
        }

        char fill() const
        {return this->_M_fill;}

        char fill(char fillch)
        {
            unsigned __old=this->_M_fill;
            this->_M_fill=fillch;
        return __old;
        }

        // Unformatted output:

        __ostream_type& put(char _c)
        {
            this->_buffer.add(_c);
//            fputc(_c, _buffer.__stream);
            return *this;
        }

        __ostream_type& write(const char* _str, unsigned _size)
        {
            this->_buffer.add(_str, _size);
//            fwrite(_str, sizeof(char), _size, _buffer.__stream);
            return *this;
        }

        // Formatted output:

        __ostream_type& operator<<(char _c)
        {
            // something
            if(this->_M_width)
            {
                int width=std::max(0u, this->_M_width-1);
                char buff[width+2];
                if(width) memset(buff, this->_M_fill, width);
                buff[width]=_c;
                this->_M_width=0;
                this->_M_fill=' ';
                this->_buffer.add(buff, width+1);//fwrite(buff, sizeof(char), width+1, _buffer.__stream);
            }
            else
                this->_buffer.add(_c);//fputc(_c, _buffer.__stream);
            return *this;
        }

        __ostream_type& operator<<(const char* _str)
        {
            // something
            if(this->_M_width)
            {
                int size=strlen(_str), width=std::max(0u, this->_M_width-size);
                char buff[width+size+1];
                if(width) memset(buff, this->_M_fill, width);
                if(size) memcpy(buff+width, _str, size);
                this->_M_width=0;
                this->_M_fill=' ';
                if(width+size) this->_buffer.add(buff, width+size);//fwrite(buff, sizeof(char), width+size, _buffer.__stream);
            }
            else
                this->_buffer.add(_str, strlen(_str));//fwrite(_str, sizeof(char), strlen(_str), _buffer.__stream);
            return *this;
        }

        __ostream_type& operator<<(const std::string& _str)
        {
            // something
            if(this->_M_width)
            {
                int size=_str.size(), width=std::max(0u, this->_M_width-size);
                char buff[width+size+1];
                if(width) memset(buff, this->_M_fill, width);
                if(size) memcpy(buff+width, _str.c_str(), size);
                this->_M_width=0;
                this->_M_fill=' ';
                if(width+size) this->_buffer.add(buff, width+size);
//                    fwrite(buff, sizeof(char), width+size, _buffer.__stream);
            }
            else
                this->_buffer.add(_str.c_str(), _str.size());
//                fwrite(_str.c_str(), sizeof(char), _str.size(), _buffer.__stream);
            return *this;
        }

        __ostream_type& operator<<(int short _n)
        {
            // something
            char buff[7];
            to_string(buff, _n);
            return this->operator<<(buff);
        }

        __ostream_type& operator<<(unsigned short _n)
        {
            // something
            char buff[6];
            to_string(buff, _n);
            return this->operator<<(buff);
        }

        __ostream_type& operator<<(int _n)
        {
            // something
            char buff[11];
            to_string(buff, _n);
            return this->operator<<(buff);
        }

        __ostream_type& operator<<(unsigned _n)
        {
            // something
            char buff[10];
            to_string(buff, _n);
            return this->operator<<(buff);
        }

        __ostream_type& operator<<(long int _n)
        {
            // something
            char buff[21];
            to_string(buff, _n);
            return this->operator<<(buff);
        }

        __ostream_type& operator<<(long unsigned _n)
        {
            // something
            char buff[21];
            to_string(buff, _n);
            return this->operator<<(buff);
        }

        __ostream_type& operator<<(long long int _n)
        {
            // something
            char buff[21];
            to_string(buff, _n);
            return this->operator<<(buff);
        }

        __ostream_type& operator<<(long long unsigned _n)
        {
            // something
            char buff[21];
            to_string(buff, _n);
            return this->operator<<(buff);
        }

        operator bool() const
        {return this->_M_ok;}
    };

    class ostream : virtual public basic_ostream
    {
    public:
        ostream(SIM_STREAM stream): basic_ostream(stream){}
        ~ostream(){}
        bool active_buffering(bool buffering=false)
        {
            this->_buffer.flush();
            if(buffering) this->_buffer.resize(10000);
            bool __old=this->_buffer.is_flush;
            this->_buffer.is_flush=buffering;
        return __old;
        }
    };

    inline basic_ostream& operator<<(basic_ostream& _os, basic_ostream& (*_p)(basic_ostream&))
    {return _p(_os);}

    inline basic_ostream& flush(basic_ostream& _os)
    {return _os.flush();}

    inline basic_ostream& endl(basic_ostream& _os)
    {return /*flush*/(_os.put('\n'));}

    inline basic_ostream& ends(basic_ostream& _os)
    {return _os.put(char());}

    extern ostream cout;
    extern ostream cerr;
} // namespace sim

#undef SIM_STREAM

#endif // STREAM_HPP
