## 安装lvgl字体与图片工具
```bash
npm i lv_font_conv 
npm i lv_img_conv
```


有如下code
```c++
class X
{
public:
    X(int arg);
    X() = delete;
    ~X();
};
```

为什么`X x1();`可以编译?(`X x1;`是期望的不能编译)


```
class X
{ 
public:
    X(int) {}
    X() = delete; // will never be generated
    void foo(){printf("foo");}
};

int main()
{ 
    X x;        // will not compile， expected;
    X y(1);     // will compile, expected.
    X z();      // can compile, what is z?.
    y.foo();    
    return 0;
}
```