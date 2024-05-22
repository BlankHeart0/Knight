# ✨ Knight 🗡️
Knight is a Programming Language to protect the Security of Information Flow
__If you want to know details, please read KnightDocument, KnightGrammar, etc.__

<center>
<img src=Knight.jpg width="450"/>
</center>

The whole Knight project, toolchain includes four parts:

* __Knight :__ The Programming Language
* __Trial :__ Knight's Compiler
* __Steed :__ The Virtual Machine to run Knight programs(Knight Assembly)
* __Duke :__ A toy System to show Knight program's behavior

## Build
```shell
make -j8
```

## Install
```shell
make install
```

## Uninstall
```shell
make uninstall
```

## Usage
### Trial
```shell
trial [-LUTA] knight_file 
```
**-L**: Compile to lower-case KnightAssembly file (default)
**-U**: Compile to upper-case KnightAssembly file
**-T**: Scan the code, print tokens
**-A**: Parse the code, print abstract syntax tree
### Steed
```shell
steed KnightAssembly_file
```
### Duke
In the directory where you want duke to use the files
, such as "test/duke/Env"
```shell
duke
```



***Knight is not an industry standard language, so it's done now.  2024 5***
