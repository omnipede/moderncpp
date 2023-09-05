# C++20 module

# Requirements
* **clang** >= `16` (**important**) (`brew install llvm`)
* **ninja** >= `1.11` (**important**)

# Build

```shell
$ cd <project-root>
$ mkdir build && cd build
$ export CXX=<your-clang++16-path>
$ cmake -G Ninja ..
$ ninja
```

# References
* https://github.com/gaelanmcmillan/clang-modules-example/tree/main

# 사용 소감
* module 기능을 사용하기 위해서는 이것 저것 조건이 많이 붙고, 아직은 experimental 단계인 것 같다.
* 헤더 파일을 안 써도 되는 점은 정말 매력적이지만 ... 아직 사용하기에는 시기상조인듯.
