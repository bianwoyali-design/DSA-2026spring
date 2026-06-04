# CLab v2 新特性简介

CLab v2 就是为了解决 Clab 的一些问题而立项的。Clab v2 把计算、存储、网络、GPU 和运维能力重新组织成更接近真实云平台的科研基础设施。它面向的不是单次演示，而是更长期、更稳定、更可复现的教学与科研使用。很多能力目前仍在 PoC 或调试阶段，但方向已经很清楚：让物理服务器上的 CPU、内存、GPU、网卡和存储，变成可调度、可隔离、可运维的云资源。

## 计算：从云主机到统一资源管理

v2 的 Compute 方向负责虚拟机、CPU/GPU 虚拟化、裸机虚拟化和高性能网络能力。短期仍保留 OpenStack 作为兼容路线，因为它已有 Nova、libvirt、Glance、Cinder 等部署和调试经验；但长期主线会转向 Kubernetes / KubeVirt。

KubeVirt 可以理解为“让虚拟机也成为 Kubernetes 管理的资源”。这样，云主机不再只是某台远程机器，而是可以被集群统一调度、监控和恢复的计算对象。v2 计划先跑通最小 VM 链路：创建虚拟机、进入 console、挂载存储、接入网络，再逐步接入 GPU、RDMA 和裸机能力。

v2 也开始关注 CPU 与 VM 性能。虚拟机能跑只是第一步，更重要的是知道它相比宿主机慢多少、慢在哪里。后续会建立宿主机、裸 QEMU、OpenStack VM、KubeVirt VM 的性能基线，分析 CPU、内存、NUMA、磁盘和网络路径上的开销。

## GPU：从独占显卡到可管理资源

GPU 是 v2 面向科研最重要的新能力之一。深度学习、图像分析、蛋白结构预测、分子模拟、材料计算都可能需要 GPU。v2 的 GPU 虚拟化路线分三类。

第一类是 PCIe 直通 / VFIO，把一张物理 GPU 直接交给一台虚拟机使用，适合短期 PoC 和高性能独占任务。第二类是 vGPU / SR-IOV，把 GPU 切分给多个虚拟机，适合共享和图形桌面，但受硬件、驱动和授权限制。第三类是 Remote GPU Pool / virtio-vcuda，目标是让纯 CPU 虚拟机也能远程使用 GPU，并支持调度和一定程度的池化。

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260604183935985.png)

这些能力的核心意义是：GPU 不再只是“某台服务器上的特殊硬件”，而是逐步变成平台可以申请、分配、回收和计量的资源。

## 存储：数据进入共享存储体系

v2 的 Storage 方向强调高性能共享存储和长期运维。当前 store / SigStore 已完成硬件整备、Ceph 调研、正式部署，上线了 RGW 和 RBD，并进入稳定运行与调优阶段。

对科研同学来说，块存储可以理解为挂到云主机上的数据盘，对象存储更像云端文件仓库。这样，实验数据、模型权重、模拟轨迹和中间结果不必跟着某台云主机一起消失，也更适合多人协作。

存储方向还在处理 RDMA 回归、PG balance、故障演练、quota、多租户访问控制、Cinder 迁移等问题。它们看起来偏运维，但本质上是在回答一个科研平台必须面对的问题：硬盘坏了、网络抖了、数据变多了、多人同时访问时，数据还能不能可靠保存。

未来的 DAOS 更偏高性能并行存储，适合 NVMe、高并发读写和大规模计算场景。它不属于 Compute，而是 Storage 的长期探索方向。

## RDMA 与高性能网络：让多机协作更快

当任务只在一台机器上跑时，普通网络通常够用；但多节点模拟、分布式训练、大规模数据处理会很快遇到网络瓶颈。v2 的 RDMA / 高性能网络方向，就是让虚拟机和容器也尽量获得接近裸机的低延迟、高带宽网络。

当前主线是 SR-IOV + Multus + KubeVirt：通过 device plugin 发现和分配网卡 VF，通过 Kubernetes resource、CDI 和 NetworkAttachmentDefinition 把设备交给容器或虚拟机。容器侧通常使用 `mlx5_core`，虚拟机侧使用 `vfio-pci`。后续还要继续完善 VF 资源池、driver 切换、健康检查、PFC / ECN / QoS 等能力。

对物理、化学、生物等科研任务来说，这类能力的价值在于：未来多台云主机协作时，数据交换不再轻易成为最慢的一环。

## 裸机虚拟化与 DPU：把整台服务器纳入云平台

有些任务对虚拟化开销非常敏感，或者需要特殊硬件和启动方式，普通虚拟机不一定合适。v2 的裸机虚拟化方向希望把完整物理服务器也作为云资源交付。

这里的关键是 DPU。v2 的设想是：DPU 侧虚拟化网络，让 Host 看到已经接入 VPC 的网口；DPU 侧访问远端存储，并把它暴露成块设备或 NVMe；裸机从 DPU 提供的存储启动；平台再通过 IPMI 控制服务器开机、关机和重启。同时，Host 侧需要封锁 IPMI，并让 DPU 进入 zero trust 模式。

这部分目前更接近设计和 PoC，但它说明 v2 不只想管理虚拟机，也希望把从云主机到整台物理服务器的不同计算形态都纳入统一体系。

## 对科研同学的意义

CLab v2 的新特性可以对应很多科研需求：物理中的蒙特卡洛模拟、有限元和流体计算；化学中的分子动力学、量子化学、分子 docking 和材料模拟；生物中的测序分析、蛋白结构预测、显微图像处理和模型训练；交叉学科中的大规模矩阵计算、优化、随机模拟和 AI 辅助科研。

这些场景共同需要更强的计算能力、更可靠的数据管理、更清晰的资源分配和更好的复现条件。CLab v2 提供的不是最终答案，而是让想法变大的基础设施：让一个小程序有机会变成可复现的实验，让一次手动运行变成一组系统的参数扫描，让个人电脑上的结果进入团队可以共同使用的数据和环境。

这也和数据结构与算法课有关。算法决定任务怎么计算，数据结构决定状态怎么保存，云平台决定这些计算能否被放大、复现和协作。对非计算机专业同学来说，理解 CLab v2 不需要成为云计算工程师；只需要知道，它正在把计算资源变成更像实验仪器一样可申请、可使用、可维护的科研工具。

# 如何更好的使用 Clab

## 了解 Linux 的基础知识

想要更为详尽的了解 Linux 知识可以参考 LCPU 编写的 [LCPU Getting Started 计算机入门系列课程](https://missing.lcpu.dev)
### 包管理器

对于使用 Windows 的同学，习惯的软件下载方式可能是在网络上搜索并下载打包好的安装程序（通常为`.exe`或`.msi`），对于使用 macOS 的同学，可能是在 App Store 下载或者是在网络上搜索并下载`.dmg`镜像挂载后拖入 Application 文件夹。

但是对于目前只能以 `ssh` 访问的 Clab 来说，我们想要安装软件只能通过终端进行，我们以 `Codex Cli` 为例：

https://developers.openai.com/codex/quickstart?setup=cli

要么通过 curl 抓取并执行下载脚本，要么从包管理器下载，都是下载的源码在本地编译后安装。

**常用的包管理器**
![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260604150158543.png)

#### 用 Conda (Anaconda) 管理 Python 版本和环境

在 Clab 上跑科研代码时，最常见的问题不是代码本身，而是 Python 版本和库版本对不上。Conda 的作用就是把不同项目的 Python 环境隔离开：这个项目用 Python 3.10 和 PyTorch，另一个项目用 Python 3.11 和 NumPy，它们互不影响。

在系统中安装 conda ：

```zsh
sudo dnf install conda             # fedora
```

常用指令如下。

查看当前有哪些环境：

```bash
conda env list
```

创建一个新环境，并指定 Python 版本：

```bash
conda create -n myenv python=3.11
```

进入环境：

```bash
conda activate myenv
```

退出当前环境：

```bash
conda deactivate
```

在当前环境中安装包：

```bash
conda install numpy pandas matplotlib
```

如果 conda 里没有需要的包，可以在进入环境后使用 pip：

```bash
pip install package-name
```

建议优先用 `conda install`，找不到包时再用 `pip install`。不要在没有激活环境时随便装包，否则容易把系统 Python 或 base 环境弄乱。

查看当前环境中已经安装的包：

```bash
conda list
```

更新某个包：

```bash
conda update numpy
```

删除某个包：

```bash
conda remove numpy
```

删除整个环境：

```bash
conda remove -n myenv --all
```

把当前环境导出为配置文件，方便之后复现：

```bash
conda env export > environment.yml
```

用 `environment.yml` 恢复环境：

```bash
conda env create -f environment.yml
```

如果只想快速记录核心依赖，也可以手写一个较简洁的 `environment.yml`：

```yaml
name: myenv
channels:
  - conda-forge
dependencies:
  - python=3.11
  - numpy
  - pandas
  - matplotlib
  - pip
```

实际使用时建议每个项目单独建一个环境，例如：

```bash
conda create -n bio-project python=3.10
conda activate bio-project
conda install numpy scipy pandas matplotlib
```

这样即使某个项目的库版本装坏了，也只需要删除这个环境重新创建，不会影响其他项目。

#### 用 uv 管理 Python 版本和环境

在系统中安装 uv：

```zsh
sudo dnf install uv                    # fedora等红帽系Distro
```

`uv` 是一个更现代、更快的 Python 项目和环境管理工具。它可以管理 Python 版本、虚拟环境、依赖、锁文件，也可以替代一部分 `pip`、`venv`、`pipx` 的工作。和 Conda 相比，`uv` 更适合纯 Python 项目；如果项目依赖很多非 Python 的系统库，Conda 仍然更稳。

查看 uv 版本：

```bash
uv --version
```

安装指定 Python 版本：

```bash
uv python install 3.11
```

查看 uv 能找到哪些 Python：

```bash
uv python list
```

在当前目录初始化一个 Python 项目：

```bash
uv init
```

指定 Python 版本初始化项目：

```bash
uv init --python 3.11
```

初始化后，项目中通常会出现 `pyproject.toml`。这是记录项目依赖和配置的文件，类似 Conda 项目里的 `environment.yml`，但更偏 Python 标准项目格式。

给项目添加依赖：

```bash
uv add numpy pandas matplotlib
```

添加开发依赖，例如格式化、测试工具：

```bash
uv add --dev pytest ruff
```

删除依赖：

```bash
uv remove numpy
```

根据 `pyproject.toml` 和 `uv.lock` 同步环境：

```bash
uv sync
```

运行项目中的 Python 文件：

```bash
uv run python main.py
```

运行一条临时 Python 命令：

```bash
uv run python -c "import sys; print(sys.version)"
```

如果只是想像 `pip install` 一样在当前环境里装包，可以使用：

```bash
uv pip install numpy
```

不过在 uv 项目里更推荐使用 `uv add`，因为它会把依赖写进 `pyproject.toml` 并更新锁文件，方便之后复现环境。

把已有 `requirements.txt` 安装到当前环境：

```bash
uv pip install -r requirements.txt
```

把依赖锁定到 `uv.lock`：

```bash
uv lock
```

运行命令行工具但不全局安装，例如临时运行 `ruff`：

```bash
uvx ruff check .
```

如果你从 GitHub 或别人那里拿到一个 uv 项目，通常只需要：

```bash
uv sync
uv run python main.py
```

一个简单的科研脚本项目可以这样开始：

```bash
mkdir simulation-demo
cd simulation-demo
uv init --python 3.11
uv add numpy matplotlib
uv run python main.py
```

简单来说：如果只是做课程作业或科研脚本，`uv init`、`uv add`、`uv sync`、`uv run` 这四个命令基本够用；如果需要 CUDA、复杂编译库或跨语言依赖，优先考虑 Conda。

### Linux 好用的小工具
#### fastfetch

帮助你快速查看系统的状态。
#### btop

终端中的任务管理器。
#### exa

替代ls。
#### fd

命令行搜索工具，Rust编写，很快。

#### ripgrep

替代grep查找内容。

#### fzf

模糊搜索。

### Linux 终端使用

#### 通过代理访问 Clab

首先需要在物理机配置 ssh 设置：

进入 .ssh 文件夹：

```zsh
### macOS
cd .ssh

### Windows
cd C:\\Users\YourUserName\.ssh
```

创建 `config` 文件并写入：

```zsh
# 普通 SSH 登录配置 
# 使用方式： 
# ssh 10.129.245.149 
Host 10.129.245.149
	# 实际连接的远程服务器地址，可以改成你的云主机 IP 
	HostName 10.129.245.149 
	# 默认登录用户名，可以改成 fedora / ubuntu / root 等 
	User fedora 
	
# 带远程端口转发的 SSH 登录配置 
# 使用方式： 
# ssh 10.129.245.149-proxy 
Host 10.129.245.149-proxy 
	# 实际连接的远程服务器地址，可以改成你的云主机 IP 
	HostName 10.129.245.149 
	# 默认登录用户名 User fedora 
	# 远程端口转发： 
	# 让远程服务器的 127.0.0.1:7897 
	# 转发到你本地电脑的 127.0.0.1:7897 
	# 
	# 常见用途： 
	# 如果你本地开了代理，例如 Clash / HTTP proxy， 
	# 并监听在本地 7897 端口， 
	# 那么云主机可以通过 127.0.0.1:7897 使用你本地的代理。 
	# 
	# 格式： 
	# RemoteForward <远程端口> <本地地址>:<本地端口> 
	# 
	# 如果你的本地代理端口是 7890，可以改成： 
	# RemoteForward 7890 127.0.0.1:7890 
	RemoteForward 7897 127.0.0.1:7897 
	
	# 如果端口转发失败，就直接退出 SSH 
	# 避免“SSH 连上了，但代理其实没转发成功”的情况 
	ExitOnForwardFailure yes 
	# 每 60 秒给服务器发一次保活包 
	# 防止 SSH 长时间空闲后被断开 ServerAliveInterval 60 
	# 如果连续 3 次保活没有响应，就认为连接断了 
	# 配合上面的 60 秒，大约 180 秒无响应后断开 
	ServerAliveCountMax 3
```

接下来需要在 Clab 机器中更改终端配置：

```bash
# 打开 bash 配置文件
nano ~/.bashrc

# Use the SSH-forwarded local HTTP proxy whenever it is reachable.
unset ALL_PROXY all_proxy HTTP_PROXY HTTPS_PROXY http_proxy https_proxy
if command -v timeout >/dev/null 2>&1 && command -v nc >/dev/null 2>&1 && timeout 1 nc -z 127.0.0.1 7897 >/dev/null 2>&1; then
	export HTTP_PROXY="http://127.0.0.1:7897"
	export HTTPS_PROXY="$HTTP_PROXY"
	export http_proxy="$HTTP_PROXY"
	export https_proxy="$HTTP_PROXY"
fi
ulimit -n 65535 2>/dev/null || true
```

`Ctrl + O` 写入配置文件保存，`Ctrl + X` 退出。

这样之后想要通过代理 ssh 连接 Clab 机器，首先在终端建立 proxy 通道：

```zsh
ssh -fN 10.129.245.149-proxy
```

之后正常连接：
```
ssh 10.129.245.149
```

进入云主机后检查是否连接成功：

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260604162108777.png)

#### Linux 终端美化

[【双语+纯享】🔥2026终极Zsh配置指南：打造比华尔街还炫酷的终端体验！⚡](https://www.bilibili.com/video/BV1f6Go6sEFW?vd_source=d266a3b264122fee28f4b4b7397ae4d8)

Linux 默认终端为 bash (不同发行版可能不一样)

这里的“终端”严格来说分成两层：一层是你看到的窗口或远程 SSH 会话，另一层是里面真正负责解释命令的 shell。`bash` 和 `zsh` 都是 shell。

`bash` 是 Linux 上最常见的默认 shell，兼容性最好，服务器脚本和教程里大量命令都默认按 bash 编写。它的配置文件通常是：

```bash
~/.bashrc
```

如果只是想让 Clab 稳定可用，保留 bash 就足够。前面配置代理时修改的也是 `~/.bashrc`，这样每次登录 bash 都会自动加载这些设置。

`zsh` 是另一个常见 shell，macOS 现在默认使用 zsh。它的优点是补全、主题、插件生态更丰富，常和 Oh My Zsh、Starship 等工具一起使用，适合做终端美化。它的配置文件通常是：

```zsh
~/.zshrc
```

简单来说：

- 想要稳定、少折腾：用 `bash`。
- 想要更好看的提示符、自动补全和插件：可以用 `zsh`。
- 改 bash 配置通常写 `~/.bashrc`。
- 改 zsh 配置通常写 `~/.zshrc`。

查看当前正在使用的 shell：

```bash
echo $SHELL
```

查看当前命令解释器：

```bash
echo $0
```

如果只是临时体验 zsh，可以直接运行：

```bash
zsh
```

退出当前 shell：

```bash
exit
```

不建议刚开始就随便修改默认 shell。对于 Clab 这种远程机器，优先保证能正常登录、能正常跑任务；终端美化可以后面再做。

## VS Code 和 Clab 协同

### 通过 Remote-SSH 插件连接 Clab

在插件市场搜索 `Remote-SSH` 并安装。

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/ssh-readme.gif)

首次连接需要较长时间下载vscode-server。

### 在 VS Code Server 上使用代理

可以在 `~/.vscode-server/data/Machine/settings.json` 中添加 proxy：

```json
	"http.proxy": "http://127.0.0.1:7897",
	"http.proxySupport": "on",
	"http.systemCertificates": true,
	"http.proxyStrictSSL": false,
```

### PKUTeX

[PKUTex](https://latex.pku.edu.cn/project) 是一个线上 LaTex 编辑器，支持实时编辑和编译，最大的优点是不需要本地化的编译环境，极大节省了本地存储空间，同时编译效率很高，推荐大家使用。

可以通过插件连接 VS Code 进行编辑和版本管理，同时可以连接 Agent 实现 Vibe TeXing。

首先在插件市场下载 `Overleaf Workshop`。

然后添加 PKUTeX 的服务器：`latex.pku.edu.cn`

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260604181804663.png)
需要 Cookie 登录：

**Safari：** `右键-检查元素 -> 储存空间 -> Cookie`   复制 `value` ，填写时带上 `overleaf.sid=...`;

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260604182504181.png)

**Edge：** 

In an already logged-in browser (Firefox for example):

1. Open "Developer Tools" (usually by pressing <kbd>F12</kbd>) and switch to the "Network" tab;
   Then, navigate to the Overleaf main page (e.g., `https://www.overleaf.com`) in the address bar.

2. Filter the listed items with `/project` and select the exact match.

3. Check the "Cookie" under "Request Headers" of the selected item and copy its value to login.
	>The format of the Cookie value would be like: `overleaf.sid=...`

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260604182847160.png)

