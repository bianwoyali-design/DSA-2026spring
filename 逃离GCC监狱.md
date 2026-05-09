# 逃离GCC监狱

在使用 gcc 配合 C/C++ extension 写了一个学期的程序以后，小A终于被 gcc 蜗牛一般的支持速度和极其弱智的 bug 激怒了！再加上 C/C++ extension 感人的速度，小A决定退出 gcc ，加入 clang 这个更权威（吗）的圈子。

## Clang是什么

目前主流的 C++ 编译器（大概？）就是 gcc, clang 和 msvc。

GCC 最初全称为GNU C Compiler，由GNU计划开发，旨在为GNU操作系统提供自由、开源的编译器。GNU计划（GNU's Not UNIX）由理查德·斯托曼于1983年发起，目标是打造一套完全自由的操作系统。是 Linux 的默认compiler。

Clang 是一个支持 C、C++ 和 Objective-C 语言的轻量级编译器。它是 LLVM 项目的一部分，以 BSD 协议发布源代码。Clang 旨在提供快速的编译性能和较少的内存占用，同时兼容 GNU 编译器的规范。是 macOS 的默认compiler。

MSVC 是微软发布的适配 Windows 的 C++ 编译器，用这个你得先下10多个G的vsbt，直接抬走。

Clang 的优势就是现代化，轻量化，并且报错稍微人性化一点，并且对新特性的支持完善（至少gcc lambda表达式的调用bug在clang上不存在），这也是选择它的原因。

## 前期准备

下面所说的都是针对win下vsc的配置。

1. **下载MSYS2**
2. **下载gcc和clang编译器**
   
   由于mingw环境下的clang依赖外部的库，有两种选择：gcc库和msvc库，那还是gcc吧。。。

   >这里用的是使用URCT (Universal C RunTime)的MSYS2 URCT64。UCRT比MSVCRT现代化很多，即使是gcc配置也是推荐使用的UCRT。至于MSYS2环境的区别，可以看下图：
   >
   ><img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260317224117414.png"/>

   打开MSYS2 UCRT64终端

   下载gcc：
   ```bash
   pacman -S mingw-w64-ucrt-x86_64-gcc
   ```

   下载clang：
   ```bash
   pacman -S mingw-w64-ucrt-x86_64-clang
   ```

   下载lld：
   ```bash
   pacman -S mingw-w64-ucrt-x86_64-lld
   ```

   >**LLD是什么？**
   >
   >lld是链接器。它和 Clang / LLDB 一起，都是 LLVM 家族的工具
   >
   >编译（Clang 干）: .cpp → .o 目标文件
   >
   >链接（lld 干）: 一堆 .o 文件 + 系统库 → 合成一个 exe
   >
   >lld = 链接器负责把编译好的二进制拼起来，生成最终可运行文件。
   >
   >老的链接器（ld(gcc使用的) /link.exe）：慢、笨重
   >
   >lld：快、轻量、跨平台、和 Clang 完美配合

   下载lldb：
   ```bash
   pacman -S mingw-w64-ucrt-x86_64-lldb
   ```

   >**LLDB和GDB的区别**
   >
   >Clang 生成的调试信息，LLDB 理解最准，是LLVM官方套件，
   >报错更清晰、变量显示更友好，
   >C++ 新版语法支持更好（C++17/20），
   >架构支持更现代
   >
   >GNU 家族和 GCC 配套，
   >年龄大、非常稳，
   >Linux 标配


   除此之外，需要把ucrt64加入环境变量。打开powershell
   ```powershell
   setx PATH "%PATH%;C:\msys64\ucrt64\bin" #分号后接你安装的路径
   ```

   验证是否加入PATH：
   ```cmd
   gcc -v
   clang -v
   lldb -v
   ```
   如果能输出版本号说明添加成功。

## VS Code 配置
我们不再使用微软官方的C/C++ extension。而是使用更加方便的clangd。

```Ctrl + Shift + X``` 打开extensions market, 搜索 ```clangd``` 并安装。

Debug方面，我们也不使用C/C++ extension的Debug Tool，而是使用更快，轻量化，适合clang宝宝体质的 ```CodeLLDB```。

同样在market安装。

接下来需要配置clangd和编辑器。

1. **clangd配置**
   
   定位到 ```.\AppData\Local```:

   ```Win + R``` 输入```%localappdata%```进入，在此新建 ```clangd``` 文件夹，新建 ```config.yaml```

   以下是我的配置，可以参考：
   ```yaml
    # 编译标志配置（核心：告诉clangd如何编译你的C++代码）
    CompileFlags:
        # 添加编译参数
        Add: 
        - "-xc++"                  # 强制将所有文件按 C++ 语言解析（即使后缀是.c也会当成C++）
        - "-std=c++26"             # 使用最新 C++26 标准语法
        - "--target=x86_64-w64-windows-gnu"  # 目标平台：64位Windows + GNU环境（适配ucrt64）
        - "-fuse-ld=lld"           # 链接器使用 lld（快速、轻量的链接器）
        - "-I"                     # 头文件搜索路径（下一行是具体路径）
        - "C:/msys64/ucrt64/include"  # 指定ucrt64的头文件目录（让编辑器找到库头文件）
        - "-L"                     # 库文件搜索路径（下一行是具体路径）
        - "C:/msys64/ucrt64/lib"   # 指定ucrt64的库文件目录（链接时查找静态/动态库）
   
    # 索引配置
    Index:
        StandardLibrary: true      # 开启标准库索引（让智能提示支持C++标准库，如vector、string）
   
    # 代码补全配置
    Completion:
        AllScopes: true            # 代码补全显示所有作用域的变量/函数（补全更全面）
   
    # 代码诊断/静态检查配置
    Diagnostics:
        ClangTidy:                 # Clang-Tidy 代码规范检查
          Add: [modernize-*, bugprone-*, performance-*]
          # 开启三类检查：
          # modernize-*   → 代码现代化检查（推荐用C++11及以上新语法）
          # bugprone-*    → 潜在Bug检查（防止常见错误）
          # performance-* → 性能优化检查（提升代码效率）
   
    # 内联提示（代码里直接显示参数名、类型推导等）
    InlayHints:
        Designators: true          # 显示结构体赋值的字段名提示
        Enabled: true              # 总开关：开启内联提示
        ParameterNames: true       # 函数调用时显示参数名（最常用！）
        DeducedTypes: true         # 显示auto推导出来的实际类型
   ```

   保存后重启vsc或者 ```Ctrl + Shift + P``` 输入 ```clangd: Restart language server``` 

2. **编辑器配置**
   
   在你的C++项目（如./MyCpp）下新建 ```.vscode``` 文件夹。

   新建 ```tasks.json``` 用于明确编译指令：

   ```json
    {
        "version": "2.0.0",
        "tasks": [
            {
                "type": "shell",
                // 任务 1：编译并立即运行（主要用于平时刷题看结果）
                "label": "C/C++: clang++ build active file", 
                "command": "clang++",
                "args": [
                    "-fdiagnostics-color=always", // 强制开启终端彩色输出
                    "-fansi-escape-codes",       // 开启 ANSI 转义码（支持更炫酷的终端显示）
                    "-g",                         // 生成调试信息（虽然是运行任务，但也保留调试能力）
                    "-std=c++26",                 // 开启 C++26 标准支持
                    "-fuse-ld=lld",               // 使用 LLVM 的 LLD 链接器（极速链接）
                    "${file}",                    // 当前打开的源代码文件全路径
                    "-o",                         // 指定输出文件名参数
                    "${fileDirname}\\${fileBasenameNoExtension}.exe", // 生成的 .exe 路径
                    ";",                          // 【关键】PowerShell 分隔符，编译完执行下一条
                    "${fileDirname}/${fileBasenameNoExtension}.exe"   // 直接运行刚才生成的 .exe
                ],
                "options": {
                    "cwd": "${fileDirname}"       // 将工作目录设为源代码所在文件夹
                },
                "problemMatcher": {               // 错误解析器：把编译报错映射到编辑器红线上
                    "owner": "cpp",
                    "fileLocation": ["relative", "${workspaceFolder}"],
                    "pattern": {
                        "regexp": "^(.*):(\\d+):(\\d+):\\s+(warning|error):\\s+(.*)$", // 正则匹配 clang 的报错格式
                        "file": 1, "line": 2, "column": 3, "severity": 4, "message": 5
                    }
                },
                "group": {
                    "kind": "build",
                    "isDefault": true             // 默认生成任务：按 Ctrl+Shift+B 直接触发这个
                },
                "detail": "Task generated by Debugger."
            },
            {
                // 任务 2：纯编译（不运行，专门给 launch.json 的 preLaunchTask 调用）
                "label": "Clang++ Build", 
                "type": "shell",
                "command": "clang++",
                "args": [
                    "-g", 
                    "-std=c++26", 
                    "-fuse-ld=lld",
                    "${file}", 
                    "-o", 
                    "${fileDirname}/${fileBasenameNoExtension}.exe"
                ],
                "group": "build"
            }
        ]
    }
   ```

   新建 ```launch.json``` 用于配置调试指令：

   ```json
    {
      "version": "0.2.0",
      "configurations": [
        {
          "name": "C/C++: clang++ build and debug active file",
          "type": "lldb",  // 使用lldb作为debugger
          "request": "launch",
          "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
          "args": [],
          "cwd": "${fileDirname}",
          "preLaunchTask": "Clang++ Build"
        }
      ]
    }
   ```
   
   新建 ```settings.json``` 用于其他设置：
   
    ```json
    {
        "files.associations": {
            "algorithm": "cpp",
            "iostream": "cpp",
            "ostream": "cpp",
            "charconv": "cpp",
            "optional": "cpp",
            "format": "cpp",
            "ranges": "cpp",
            "system_error": "cpp",
            "array": "cpp",
            "functional": "cpp",
            "regex": "cpp",
            "tuple": "cpp",
            "type_traits": "cpp",
            "utility": "cpp",
            "cmath": "cpp",
            "iterator": "cpp",
            "random": "cpp",
            "iosfwd": "cpp",
            "vector": "cpp",
            "any": "cpp",
            "atomic": "cpp",
            "barrier": "cpp",
            "bit": "cpp",
            "bitset": "cpp",
            "cctype": "cpp",
            "cfenv": "cpp",
            "chrono": "cpp",
            "cinttypes": "cpp",
            "clocale": "cpp",
            "codecvt": "cpp",
            "compare": "cpp",
            "complex": "cpp",
            "concepts": "cpp",
            "condition_variable": "cpp",
            "coroutine": "cpp",
            "csetjmp": "cpp",
            "csignal": "cpp",
            "cstdarg": "cpp",
            "cstddef": "cpp",
            "cstdint": "cpp",
            "cstdio": "cpp",
            "cstdlib": "cpp",
            "cstring": "cpp",
            "ctime": "cpp",
            "cuchar": "cpp",
            "cwchar": "cpp",
            "cwctype": "cpp",
            "deque": "cpp",
            "forward_list": "cpp",
            "list": "cpp",
            "map": "cpp",
            "set": "cpp",
            "string": "cpp",
            "unordered_map": "cpp",
            "unordered_set": "cpp",
            "exception": "cpp",
            "expected": "cpp",
            "memory": "cpp",
            "memory_resource": "cpp",
            "numeric": "cpp",
            "ratio": "cpp",
            "source_location": "cpp",
            "string_view": "cpp",
            "flat_map": "cpp",
            "flat_set": "cpp",
            "fstream": "cpp",
            "future": "cpp",
            "generator": "cpp",
            "initializer_list": "cpp",
            "iomanip": "cpp",
            "istream": "cpp",
            "latch": "cpp",
            "limits": "cpp",
            "mutex": "cpp",
            "new": "cpp",
            "numbers": "cpp",
            "print": "cpp",
            "queue": "cpp",
            "scoped_allocator": "cpp",
            "semaphore": "cpp",
            "shared_mutex": "cpp",
            "span": "cpp",
            "spanstream": "cpp",
            "sstream": "cpp",
            "stack": "cpp",
            "stacktrace": "cpp",
            "stdexcept": "cpp",
            "stdfloat": "cpp",
            "stop_token": "cpp",
            "streambuf": "cpp",
            "syncstream": "cpp",
            "text_encoding": "cpp",
            "thread": "cpp",
            "typeindex": "cpp",
            "typeinfo": "cpp",
            "valarray": "cpp",
            "variant": "cpp"
        },
        "markdown-toc.depthFrom": 1,
        "markdown-toc.depthTo":6,
        "markdown-toc.insertAnchor": false,
        "markdown-toc.withLinks": true,
        "markdown-toc.updateOnSave": true,

        "files.autoSave": "afterDelay",
        "files.autoSaveDelay": 1000,

        "editor.suggest.preview": true,
        "editor.suggest.showMethods": true,
        "editor.suggest.showFunctions": true,
        "editor.acceptSuggestionOnEnter": "on",
        
        "editor.inlayHints.enabled": "on",
        "editor.inlayHints.fontSize": 14,
        "editor.codeLens": true,

        "clangd.arguments": [
            "--query-driver=C:\\msys64\\ucrt64\\bin\\clang++*",
            "--all-scopes-completion",
            "--completion-style=detailed",
            "--header-insertion=iwyu"
        ],

        "editor.codeActionsOnSave": {
            "source.organizeImports": "explicit"
        }
    }
    ```
   
   

## 配置完了

可以通过 ```Ctrl + Shift + B``` 编译并运行， ```F5``` 调试。

clangd最爽的一点是可以帮你自动补全 ```namespace```， 这样就不用冒着风险去写 ```using namespace std;``` ,
比如输入 ```sort``` 后按回车自动补全成 ```std::ranges::sort()``` ,还会帮你自动补齐头文件。

但要注意clangd的格式化是```llvm-format```，缩进默认是2格，可能会有点丑（，但我换了```Menlo```字体，看着就舒服很多
