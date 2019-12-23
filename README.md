# IM 客户端

桌面上使用的IM客户端，使用QT QML 开发


## 参考或使用项目



## 库管理工具 
    
    vcpkg
    https://github.com/microsoft/vcpkg


## macos 编译

    #DCMAKE_PREFIX_PATH=qt库路径 
    mkdir out 
    cd out
    
    cmake . -Bbuild -DCMAKE_PREFIX_PATH=/Users/maohuawei/dev/Qt/5.14.0/clang_64/lib/cmake     

    cmake --build build