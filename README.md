# hdfreader
**<font color=#0099ff size= 72>阅读hdf5文件的类</font>**   
*qt版本*  
*vs版本*  
*vs封装的dll版本*   
1. 在配置完hdf5之后把hdf5的dll文件拷贝到sysytem32和syswow64中
该[博客](https://blog.csdn.net/hou09tian/article/details/72777922?utm_source=blogxgwz0)处理动态链接库的问题
2. hdf5类开发过程中，发现当vs初始定义矩阵过大时会造成栈溢出
比如float[512][512]  
解决办法：  
* a、把vs的保留栈空间设的大一点，但是一般不建议这么做  
* b、用全局变量去声明  
*  c、用指针去存储，另外划分空间，但是使用完毕不要忘了释放  
3. hdf5在vs中和qt中的读取文件内容的方法不一样，具体在桌面coding文件夹，写的三个hdf类中有所体现。
4. 写类的过程中记住c++的命名规范

