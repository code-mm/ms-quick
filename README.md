# IM 客户端

桌面上使用的IM客户端，使用QT QML 开发


## 参考或使用项目

https://github.com/m-maohuawei/ms-quick/blob/master/docs/%E4%BD%BF%E7%94%A8%E7%9A%84%E5%BA%93%E5%92%8C%E4%BE%9D%E8%B5%96.md

## 库管理工具 
    
    vcpkg
    https://github.com/microsoft/vcpkg

## macos 编译

    #DCMAKE_PREFIX_PATH=qt库路径 
    mkdir out 
    cd out
    cmake . -Bbuild -DCMAKE_PREFIX_PATH=/Users/maohuawei/dev/Qt/5.14.0/clang_64/lib/cmake
    cmake --build build
    