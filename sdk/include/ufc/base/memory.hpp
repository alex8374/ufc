/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/base/memory.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-17
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_BASE_MEMORY_HPP
#define UFC_BASE_MEMORY_HPP

#include <ufc/base/config.hpp>

namespace ufc {

    class memory
    {
    public:
        template <class C>
        static void delete_ptr(C*& __ptr, bool __delete_flag = true)
        {
            if (__ptr && __delete_flag) 
            {
                try 
                {
                    delete __ptr;
                }
                catch (...)
                {
                }
                __ptr = 0;
            }
        }

        template <class T, class C>
        static void delete_ptr_cast(C*& __ptr, bool __delete_flag = true)
        {
            if (__ptr && __delete_flag)
            {
                try 
                {
                    delete (T*)__ptr;
                }
                catch (...) 
                {
                }
                __ptr = 0;
            }
        }

        template <class C>
        static void new_ptr(C*& __ptr)
        {
            delete_ptr(__ptr);
            try 
            {
                __ptr = new C;
            } 
            catch (...) 
            {
                delete_ptr(__ptr);
            }
        }

        template <class C, class A1>
        static void new_ptr(C*& __ptr, A1 __a1)
        {
            delete_ptr(__ptr);
            try 
            {
                __ptr = new C(__a1);
            } 
            catch (...) 
            {
                delete_ptr(__ptr);
            }
        }

        template <class C, class A1, class A2>
        static void new_ptr(C*& __ptr, A1 __a1, A2 __a2)
        {
            delete_ptr(__ptr);
            try 
            {
                __ptr = new C(__a1, __a2);
            } 
            catch (...) 
            {
                delete_ptr(__ptr);
            }
        }

        template <class C, class A1, class A2, class A3>
        static void new_ptr(C*& __ptr, A1 __a1, A2 __a2, A3 __a3)
        {
            delete_ptr(__ptr);
            try 
            {
                __ptr = new C(__a1, __a2, __a3);
            } 
            catch (...) 
            {
                delete_ptr(__ptr);
            }
        }

        template <class C, class A1, class A2, class A3, class A4>
        static void new_ptr(C*& __ptr, A1 __a1, A2 __a2, A3 __a3, A4 __a4)
        {
            delete_ptr(__ptr);
            try 
            {
                __ptr = new C(__a1, __a2, __a3, __a4);
            } 
            catch (...) 
            {
                delete_ptr(__ptr);
            }
        }

        template <class C, class A1, class A2, class A3, class A4, class A5>
        static void new_ptr(C*& __ptr, A1 __a1, A2 __a2, A3 __a3, A4 __a4, A5 __a5)
        {
            delete_ptr(__ptr);
            try 
            {
                __ptr = new C(__a1, __a2, __a3, __a4, __a5);
            } 
            catch (...) 
            {
                delete_ptr(__ptr);
            }
        }

        template <class C, class A1, class A2, class A3, class A4, class A5, class A6>
        static void new_ptr(C*& __ptr, A1 __a1, A2 __a2, A3 __a3, A4 __a4, A5 __a5, A6 __a6)
        {
            delete_ptr(__ptr);
            try 
            {
                __ptr = new C(__a1, __a2, __a3, __a4, __a5, __a6);
            } 
            catch (...) 
            {
                delete_ptr(__ptr);
            }
        }

        template <class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
        static void new_ptr(C*& __ptr, A1 __a1, A2 __a2, A3 __a3, A4 __a4, A5 __a5, A6 __a6, A7 __a7)
        {
            delete_ptr(__ptr);
            try 
            {
                __ptr = new C(__a1, __a2, __a3, __a4, __a5, __a6, __a7);
            } 
            catch (...) 
            {
                delete_ptr(__ptr);
            }
        }

        template <class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
        static void new_ptr(C*& __ptr, A1 __a1, A2 __a2, A3 __a3, A4 __a4, A5 __a5, A6 __a6, A7 __a7, A8 __a8)
        {
            delete_ptr(__ptr);
            try 
            {
                __ptr = new C(__a1, __a2, __a3, __a4, __a5, __a6, __a7, __a8);
            } 
            catch (...) 
            {
                delete_ptr(__ptr);
            }
        }

        template <class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
        static void new_ptr(C*& __ptr, A1 __a1, A2 __a2, A3 __a3, A4 __a4, A5 __a5, A6 __a6, A7 __a7, A8 __a8, A9 __a9)
        {
            delete_ptr(__ptr);
            try 
            {
                __ptr = new C(__a1, __a2, __a3, __a4, __a5, __a6, __a7, __a8, __a9);
            } 
            catch (...) 
            {
                delete_ptr(__ptr);
            }
        }

        template <class T, class C>
        static void new_ptr_cast(C*& __ptr)
        {
            delete_ptr_cast<T>(__ptr);
            try 
            {
                __ptr = new T;
            } 
            catch (...) 
            {
                delete_ptr_cast<T>(__ptr);
            }
        }

        template <class T, class C, class A1>
        static void new_ptr_cast(C*& __ptr, A1 __a1)
        {
            delete_ptr_cast<T>(__ptr);
            try 
            {
                __ptr = new T(__a1);
            } 
            catch (...) 
            {
                delete_ptr_cast<T>(__ptr);
            }
        }

        template <class T, class C, class A1, class A2>
        static void new_ptr_cast(C*& __ptr, A1 __a1, A2 __a2)
        {
            delete_ptr_cast<T>(__ptr);
            try 
            {
                __ptr = new T(__a1, __a2);
            } 
            catch (...) 
            {
                delete_ptr_cast<T>(__ptr);
            }
        }

        template <class T, class C, class A1, class A2, class A3>
        static void new_ptr_cast(C*& __ptr, A1 __a1, A2 __a2, A3 __a3)
        {
            delete_ptr_cast<T>(__ptr);
            try 
            {
                __ptr = new T(__a1, __a2, __a3);
            } 
            catch (...) 
            {
                delete_ptr_cast<T>(__ptr);
            }
        }

        template <class T, class C, class A1, class A2, class A3, class A4>
        static void new_ptr_cast(C*& __ptr, A1 __a1, A2 __a2, A3 __a3, A4 __a4)
        {
            delete_ptr_cast<T>(__ptr);
            try 
            {
                __ptr = new T(__a1, __a2, __a3, __a4);
            } 
            catch (...) 
            {
                delete_ptr_cast<T>(__ptr);
            }
        }

        template <class T, class C, class A1, class A2, class A3, class A4, class A5>
        static void new_ptr_cast(C*& __ptr, A1 __a1, A2 __a2, A3 __a3, A4 __a4, A5 __a5)
        {
            delete_ptr_cast<T>(__ptr);
            try 
            {
                __ptr = new T(__a1, __a2, __a3, __a4, __a5);
            } 
            catch (...) 
            {
                delete_ptr_cast<T>(__ptr);
            }
        }

        template <class T, class C, class A1, class A2, class A3, class A4, class A5, class A6>
        static void new_ptr_cast(C*& __ptr, A1 __a1, A2 __a2, A3 __a3, A4 __a4, A5 __a5, A6 __a6)
        {
            delete_ptr_cast<T>(__ptr);
            try 
            {
                __ptr = new T(__a1, __a2, __a3, __a4, __a5, __a6);
            } 
            catch (...) 
            {
                delete_ptr_cast<T>(__ptr);
            }
        }

        template <class T, class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
        static void new_ptr_cast(C*& __ptr, A1 __a1, A2 __a2, A3 __a3, A4 __a4, A5 __a5, A6 __a6, A7 __a7)
        {
            delete_ptr_cast<T>(__ptr);
            try 
            {
                __ptr = new T(__a1, __a2, __a3, __a4, __a5, __a6, __a7);
            } 
            catch (...) 
            {
                delete_ptr_cast<T>(__ptr);
            }
        }

        template <class T, class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
        static void new_ptr_cast(C*& __ptr, A1 __a1, A2 __a2, A3 __a3, A4 __a4, A5 __a5, A6 __a6, A7 __a7, A8 __a8)
        {
            delete_ptr_cast<T>(__ptr);
            try 
            {
                __ptr = new T(__a1, __a2, __a3, __a4, __a5, __a6, __a7, __a8);
            } 
            catch (...) 
            {
                delete_ptr_cast<T>(__ptr);
            }
        }

        template <class T, class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
        static void new_ptr_cast(C*& __ptr, A1 __a1, A2 __a2, A3 __a3, A4 __a4, A5 __a5, A6 __a6, A7 __a7, A8 __a8, A9 __a9)
        {
            delete_ptr_cast<T>(__ptr);
            try 
            {
                __ptr = new T(__a1, __a2, __a3, __a4, __a5, __a6, __a7, __a8, __a9);
            } 
            catch (...) 
            {
                delete_ptr_cast<T>(__ptr);
            }
        }

        template <class C>
        static void delete_array(C*& __parray, bool __delete_flag = true)
        {
            if (__parray && __delete_flag) 
            {
                try 
                {
                    delete []__parray;
                } 
                catch (...) 
                {
                }
                __parray = 0;
            }
        }

        template <class C> 
        static void new_array(C*& __parray, uint32_t __num)
        {
            delete_array(__parray);
            try 
            {
                __parray = new C[__num];
            } 
            catch (...) 
            {
                delete_array(__parray);
            }
        }
    };

}//namespace ufc

#endif//UFC_BASE_MEMORY_HPP
