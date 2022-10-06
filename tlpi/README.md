# [getopt()使用](https://blog.csdn.net/huangxiaohu_coder/article/details/7475156)
```c
int getopt(int argc, char * const argv[], const char *optstring);
```

## 选项字符串(char *optstring)
"a:b:cd::e"，这就是一个选项字符串。对应到命令行就是-a ,-b ,-c ,-d, -e 。

 冒号表示参数，一个冒号就表示这个选项后面必须带有参数（没有带参数会报错哦）
 但是这个参数可以和选项连在一起写，也可以用空格隔开，比如-a123 和-a   123（中间有空格） 都表示123是-a的参数
 
 两个冒号的就表示这个选项的参数是可选的，即可以有参数，也可以没有参数，
 但要注意有参数时，参数与选项之间不能有空格（有空格会报错的哦）

 如果optstring参数的第一个字符是冒号，那么getopt()函数就会保持沉默，并根据错误情况返回不同字
