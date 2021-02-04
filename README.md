## KiwiBuffers的简单demo
### 目前只包含了C++语言，QT编译
  要使用kiwic命令，首先要安装kiwi环境 `npm install -g kiwi-schema`
  ***
  schema文件示例：
```
package testv1;

message Test {
  int x = 1;
}
```
将上述schema文件保存为`testv1.kiwi`，要生成cpp头文件，可以用`kiwic --schema testv1.kiwi --cpp testv1.h`命令。

Kiwi原仓库链接:
[Kiwi](https://github.com/evanw/kiwi)

C++下使用Kiwi教程：
[cpp usage](https://github.com/evanw/kiwi/blob/master/examples/cpp.md)
