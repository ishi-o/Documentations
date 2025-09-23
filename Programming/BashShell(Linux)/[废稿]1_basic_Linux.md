本文涉及Linux系统的基础知识，包括终端常用命令和Linux下的文件系统

---

[toc]

---

# Linux

## 虚拟机安装Linux

### 安装虚拟机

笔者使用的是VMware和Ubuntu发行版

<a>[下载 VMware Workstation Pro](https://www.vmware.com/cn/products/workstation-pro/workstation-pro-evaluation.html)</a>

读者可以自行搜索许可证

### 下载镜像源

下载UbuntuDesktop镜像源

官方:<a>[下载 Ubuntu Desktop](https://ubuntu.com/download/desktop)</a>

清华源:<a>https://mirrors.tuna.tsinghua.edu.cn/ubuntu-releases/jammy/ubuntu-22.04.3-live-server-amd64.iso</a>

源：这里的源指软件源，软件源就是一个**应用程序安装库**，很多很多的应用软件都在这个库里面。他可以是网络服务器，是光盘，甚至是硬盘上的一个目录。大部分 Linux 系统都是通过网络上的源来下载更新系统中的软件。系统**自带的源地址**一般是**外国服务器**，可以通过换源来加快下载速度。

Ubuntu 可以在应用与更新中换源。

### 创建虚拟机

点击创建，我们选择经典安装，可以在创建后"编辑虚拟机"里再自定义配置

选择"稍后安装操作系统"，根据实际需求选择版本，安装盘和分配的空间

创建好后，编辑虚拟机设置，在"CD/DVD(IDE)"项选择刚刚下载好的镜像文件位置，然后打开虚拟机

### 安装操作系统

打开虚拟机后会有安装向导

选择语言->分配空间->选择地区->开始安装

分配空间时，我的选择是剩下空间全给/home

| 名称                | 类型 | 大小   |
| ------------------- | ---- | ------ |
| / (根目录)          | ext4 | 10~30G |
| swap area(虚拟内存) | swap | 2~4G   |
| /boot               | ext4 | 200M   |
| /tmp                | ext4 | 5G     |
| /home               | ext4 | 尽量大 |

## 基础知识

### 常用命令

```shell
apt-get update					# 联网下获取软件包更新(常需要root权限)
apt-get install <soft>			# 安装某软件

cd /home/user					# 切换到绝对路径
cd ./file						# ~~~~~相对路径,表示当前目录下
cd ../file						# ~~~~~相对路径,表示上级目录下,../可以叠加

cat <file>						# 读取数据,默认输出到屏幕
cat -A 							# 显示所有数据

cp src des						# 将src文件复制到des下,会覆盖已有文件
									# 若des为文件,则新文件以它命名;若为目录,则以src命名
cp -i src des					# -i选项:文件覆盖时发出提示

env 							# 打印所有环境变量
echo 							# 打印后面跟着的常量或变量
export 							# 定义环境变量
$PATH							# 一个环境变量,储存可以搜索的路径,总会改变
# 我们使用命令时,实际上是在执行bin目录下的可执行文件,但是这个文件通常不在当前目录里,此时PATH就起作用

ls <dir/file/null>				# 查看目录下非隐藏文件或目录,null时查看所在目录
								# 有通配符*,?;效果与正则相同
ls -a 							# 查看所有~~~~~~~~~~~~~~~的权限
ls -l 							# 查看非隐藏~~~~~~~~~~~~~的权限
ls -R							# 递归查看
ls -al							# 标签可以相连
ll								# ls -al的缩写

ln src des						# 为src在des创建硬链接
ln -s src des					# 为src在des创建软链接(又叫符号链接)
unlink des						# 删除链接,rm也可以做到
# 软链接类似快捷方式,它是现实存在的文件,但内容只是对src的索引,文件大小为路径的字符所占空间,所以src需要是绝对路径
# 硬链接创建一个虚拟文件,实质上是同一个文件,修改其一,所有硬链接的文件都会修改
# 硬链接不能跨文件系统
# 硬链接的文件必须全部删除才会释放这个文件,而软链接只要删除src,这些快捷方式就会失效

ps -a 							# 查看所有进程
kill <nums>						# 杀死指定进程

touch <file>					# 创建文件,不会覆盖已有文件
mkdir(make directory)<dir>		# 创建目录
rm <file>						# 删除文件 
mv <file>						# 移动/改名
mv -i							# 覆盖时发出询问
rm -r <file/dir>				# 递归删除(可删除目录)
rmdir <dir>						# 删除目录

man (manual)<command> 			# 查看手册

pwd (print working directory)	# 打印当前工作目录

su(switch user)<username> 		# 改变用户

sudo <command>					# 系统默认有sudo组，只要用户在sudo组里，就可以执行sudo
sudo -i 						# 普通用户切换到root

chmod (change mode)<file>		# 改变文件权限
chgrp (change group)<file>		# 改变文件所在组
chown (change owner)<file>		# 改变文件拥有者
```
### vim
```
i			进入插入模式
:<command>	命令行模式
?<string>	查找某项
[esc]		退出插入模式
```

### 重定向
```shell
cat <something> > filename	# 将这些东西输出到file里
	>：	# 覆盖写入
	>>：	# 追加写入
```

### 快捷键

```
'clear' / ctrl+L		清屏
TAB					    自动补全命令
ctrl+C 		      		停止执行
exit					退出插入模式
```

### 文件权限

```shell
$ ls -l 	# 查看权限
- --- --- --- root group owner file/dirName
	第一个:
	-/d						# 普通文件/目录
	后三组(每3个字母为一组):
	管理员/组内成员/普通用户
	每一组:
	r/w/x					# 可读/可写/可执行
	可以用 数字 或 +-r/w/x 改变权限

	--- 对应二进制数，例如 
	rw- 代表 110 即 4+2+0=6
	r-x 代表 101 即 4+0+1=5
	
eg:
$ chmod 774 file		->	rwx rwx r--
$ chmod +w file			->	rwx rwx rw-
```

## 实现Windows客户端向Linux服务端的免密登录

### 原理

基于ssh服务，我们可以实现"记住"安全却复杂难记的密码

步骤:**本地**客户端生成密钥与公钥(本文采用RSA加密)->将**公钥**传进服务端的文件中->服务端开启服务->即可通过一行`ssh user@ip`远程登录服务器，读者可以切换到root账户下方便操作

关于RSA加密的原理，可以阅读

### 本地生成rsa密码

Win+R呼出cmd或打开内置powershell

输入如下命令生成密钥，弹出输入提示按回车即可

```shell
$ ssh-keygen -t rsa
```

如果读者发现报错，那么可以安装**Git**

<a>[Git - 下载 ](https://git-scm.com/downloads)</a>

按照电脑系统选择安装包，后面按照默认选项安装即可，参考<a>[Windows系统Git安装教程(详解Git安装过程)](https://zhuanlan.zhihu.com/p/242540359)</a>

或是安装**OpenSSH**，我选择了后者，在win11系统安装OpenSSH

电脑设置->系统->可选功能->添加**OpenSSH客户端**功能

安装后，你可以输入如下命令检查是否已安装

```shell
$ git --version
$ ssh -V
```

### 传进Linux虚拟机

生成公钥与密钥后，我们向上翻阅，可以发现默认生成在用户目录下的.ssh文件夹中

复制"id_rsa.pub"的内容，打开虚拟机，找到root下的**.ssh/authorized_keys**文件，使用如下命令写入

```shell
$ echo thePublicKey(复制的公钥) > authorized_keys
# 或
$ vi authorized_keys
# 在插入模式下shift+ctrl+V粘贴(需要安装VMtools)
```

### 打开Linux的ssh服务

安装OpenSSH服务器，在终端输入如下命令

```shell
$ apt-get install openssh-server	# Ubuntu发行版下
```

接下来，将.ssh和authorised_keys权限分别改为600和700

```shell
$ chmod 600 .ssh
$ chmod 700 ./authorised_keys
```

最后，编辑/etc/ssh/sshd_config，允许远程登录root

```shell
$ vi /etc/ssh/sshd_config
# 保证下列句子未被注释
PermitRootLogin yes
PubkeyAuthentication yes
AuthorizedKeysFile .ssh/authorized_keys

$ service ssh restart	# 重启ssh服务
```

`ifconfig`查询服务器ip地址

<img src="D:\Picture\Screenshots\屏幕截图 2023-12-17 120557.png" style="zoom:67%;" />

这样，就可以通过`ssh root@ip`远程登录虚拟机了!