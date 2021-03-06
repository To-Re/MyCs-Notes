# 第 19 章 TCP 的交互数据流

## 19.1 引言

如果按照分组数量计算，约有一 半的 TCP 报文段包含成块数据，另一半则包含交互数据

如果按字节计算，则成块数据与交互数据的比例约为 $9:1$。因为成块数据的报文段基本上都是满长度的。

本章介绍交互数据流传输问题



## 19.2 交互式输入

Rlogin 连接远程主机后，每按一个交互按键都会产生一个数据分组。而且远程主机需要回显键入字符，这样会产生四个报文。

+ 来自客户的交互按键
+ 来自服务器的按键确认
+ 来自服务器的按键回显
+ 来自客户的按键回显确认

2、3 可以合并

下面出现一个例子，远程主机输入命令的例子，看看就好不做笔记。



## 19.3 经受时延的确认

通常 TCP 在接收到数据时并不立即发送 ACK，相反它推迟发送，以便将 ACK 与需要沿该方向发送的数据一起发送（也称数据捎带 ACK）。绝大多数实现采用的时延为 200 ms，TCP 将以最大 200 ms 的时延等待是否有数据一起发送。

时延等待使用计时器，所以下次溢出时间是 1-200 ms 中任何时刻。

这打游戏不卡到爆，继续看先。



## 19.4 Nagle算法

小数据多的情况，小分组会增加拥塞出现情况。

该算法要求一个 TCP 连接上最多只能有一个未被确认的未完成的小分组，在该分组的确认到达之前不能发送其他的小分组。TCP 收集这些少量的分组，并在确认到来时以一个分组的方式发出去。

该算法的优越之处在于它是自适应的：确认到达得越快，数据也就发送得越快。而在希望减少微小分组数目的低速广域网上，则会发送更少的分组。



后面讲了一个例子，看看过。



### 19.4.1 关闭Nagle算法

RFC 声明 TCP 必须实现 Nagle 算法，也必须为应用提供一种关闭该算法在某个连接上执行的方法。



### 19.4.2 一个例子

比如进行多字节输入时，使用 Nagle 算法会引起额外的时延。



## 19.5 窗口大小通告

应该就算 TCP 缓冲区的大小。



## 19.6 小结

举例交互式输入的 TCP 连接，Nagle 算法的思想，适用范围。