# 从零开始的UEFI裸机编程 中文版示例代码

同人志《从零开始的UEFI裸机编程》中文版示例代码

本体可以在可以在 [>这里<](https://kagurazakakotori.github.io/ubmp-cn) 在线阅读，请配合使用

如果您发现示例代码中存在问题，欢迎在 [Issues](https://github.com/kagurazakakotori/ubmp-cn-code/issues) 中提出


## 目录结构

* `baremetal`: 裸机编程的例子的目录
* `gnuefi`: 使用gnu-efi的例子的目录
* `drivers`: UEFI驱动程序目录
  * `UsbMouseDxe.efi`: USB鼠标驱动 (提取自 Clover EFI bootloader r5070)
* `linux`: Linux相关例子所用内容目录

## 环境要求

* amd64(x86_64)平台
* GNU make
* GCC
* MinGW-w64 GCC交叉编译器
* QEMU
* OVMF
* gnu-efi (版本 >= 3.0.14)
* dos2unix
* imagemagick

在 Ubuntu 20.04 上安装上述工具的代码如下:

```shell
sudo apt install build-essential gcc-mingw-w64-x86-64 qemu-system-x86 ovmf gnu-efi dos2unix imagemagick
```

### 关于gnu-efi

绝大部分发行版提供的 gnu-efi 版本并不满足运行所有示例代码的要求。使用 Simple Text Input Ex 协议和 Device Path Utilities 协议的代码将无法编译，并且 `Pause()` 函数会产生非预期的结果。请务必确保使用的 gnu-efi 是 3.0.14 及更高版本，最新版的 gnu-efi 可以在 [https://gitlab.com/ncroxon/gnu-efi](https://gitlab.com/ncroxon/gnu-efi) 下载.

本示例代码也提供了一个更简便的方法来使用最新版的 gnu-efi. 运行 `source init-gnuefi` 命令将自动拉取新版本的 gnu-efi, 编译并安装至 `sysroot` 下(不会与既有安装冲突), 同时设置环境变量。运行该命令后, 在该 shell 进程及其子进程下, 将会使用 `sysroot` 中的 gnu-efi 编译示例代码。


## Makefile 规则

* `make`: 编译.efi可执行文件
* `make run`: 编译、构建文件系统并运行
* `make clean`: 删除中间文件和可执行文件

## 关于 Linux 内核

请在编译完Linux内核后将 `arch/x86/boot/bzImage` 文件复制到 `linux/kernel` 目录下
