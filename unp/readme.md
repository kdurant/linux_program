# 下载
`git clone https://github.com/unpbook/unpv13e.git`

# 编译
参考`README`里步骤，产生`libunp.a`文件
```
cd lib         # build the basic library that all programs need
make           # use "gmake" everywhere on BSD/OS systems

cd ../libfree  # continue building the basic library
make
```

# 复制
```bash
sudo cp libunp.a /usr/lib/
# unp.h里  #include "../config.h" 修改为 #include "config.h"
sudo cp ./lib/unp.h /usr/include/
sudo cp config.h /usr/include/
```

# 备注
1. 不能使用`-std=c99`编译，可以使用`-std=gnu99`