#ifndef COMMON_H
#define COMMON_H
#define ToStr(v) #v
#define TOSTR(v) ToStr(v)
#define __LOC__ __FILE__" : ("TOSTR(__LINE__)")"

inline void MARK(int i)
{std::cout << "(" << i << ")" << std::endl;}
inline void NEWL()
{std::cout<<std::endl;}

#define RUNCOMMAND(c)\
std::cout << "執行「" << #c << "」之後:" << std::endl;(c)

#define SHOWVALUE(v)\
std::cout << #v << " = " << (v) << std::endl

#define OUTPUTVALUE(outstream, v)\
outstream << #v << " = " << (v) << std::endl

#endif //COMMON_H
