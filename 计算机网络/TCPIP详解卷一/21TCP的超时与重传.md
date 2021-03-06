# 第 21 章 TCP 的超时与重传

## 21.1 引言

（复习建议先看小结，中间讲的顺序略乱，笔记也乱）

数据和确认都可能丢失，TCP 通过定时器解决，超时则重传数据。

接下来问题是，超时和重传的策略，超时时间间隔和重传频率。

TCP 管理四个不同的定时器

+ 重传定时器
+ 坚持定时器
+ 保活定时器
+ 2MSL定时器



## 21.2 超时与重传的简单例子

在这个例子中，超时重传时间间隔从 1.5 秒，一直翻倍到 64 秒，并在 9 分钟后放弃并发送 RST 信号。

其中倍数关系被称为『指数退避』



## 21.3 往返时间测量

往返时间（RTT）经常发生变化，TCP 跟踪这些变化并修改超时时间。

这一段我觉得不适合我。



## 21.4 往返时间RTT的例子

### 21.4.1 往返时间RTT的测量

这个例子中，有一个 TCP 定时器一次滴答 500 ms。

一个 550 ms RTT 可能被当成 1 或 2 个 TCP 时钟滴答。计算方式可以这么看，经过计时器结束和开始分界线数量来算时钟滴答。



### 21.4.2 RTT估计器的计算

我选择放弃



### 21.4.3 慢启动

20.6 节已经介绍



## 21.5 拥塞举例

举了一个 TCP 丢失重传的例子

快速重传算法：伯克利的 TCP 实现，对收到的重复 ACK 进行计数，当收到第3个时就假定那个序号的报文段已经丢失。

接收方对于收到失序的 TCP，将保存数据并返回期望的 ACK（这个重复 ACK 不应该被时延）。



## 21.6 拥塞避免算法

拥塞避免算法：一种处理丢失分组的方法，算法假定分组受到损坏引起的丢失是非常少的。

两种分组丢失的指示：

+ 超时
+ 接收到重复的确认



拥塞避免算法和慢启动算法需要维持两个变量：一个拥塞窗口 cwnd 和一个慢启动门限 ssthresh

（21.12 总结总体过程，如何进行拥塞控制）

算法流程如下：（这是大概的拥塞控制）

+ 对一个给定的连接，初始化 cwnd 为 1 个报文段，ssthresh 为 65535 个字节
+ TCP 发送方的输出不能超过 cwnd 和接收方通告窗口的大小
+ 当拥塞发生时（超时或收到重复确认），ssthresh 被设置为当前窗口大小的一半（cwnd 和接收方通告窗口大小的最小值，最少为 2个报文段） 。
  + 如果是超时引发的拥塞，还将 cwnd 被设置为 1 个报文段（因为超时更严重吧）
  + 重复 ACK cwnd 被置为原来窗口大小 1/2，书上没看到这句。如果收到重复 ACK 如果只执行 ssthresh 减半，有什么意义？之后如果超时引起拥塞，ssthresh 又被更新前面操作也不会有任何意义。可能是我没看见或者理解有问题。
    下面一节是讲这个问题。。不想删了这段思考过程



拥塞避免（窗口）是发送方使用的流量控制，发送方感受到的网络拥塞的估计。

通告窗口则是接收方进行的流量控制，接收方在该连接上的可用缓存大小有关。



慢启动算法：每收到一个确认，cwnd 增加 1。这样窗口大小会指数增长。

拥塞避免算法：每收到一个确认 cwnd 增加 1/cwnd（21.8 节有具体细节）。这样窗口大小是线性增长。



## 21.7 快速重传与快速恢复算法

收到三个重复 ACK 执行快速恢复算法流程如下：

+ 当收到 3 个以上重复的 ACK 时
  + 如果是第三次收到 ssthresh 设置为当前拥塞窗口 cwnd 的一半。
  + cwnd 被置为当前 ssthresh 加上所收到的重复的 ACK 数乘以报文段大小，然后发送重传数据。

+ 当下一个确认『新』数据的 ACK 到达时，设置 cwnd 为 ssthresh（在第 1 步中设置的值）。



每收到一个 ACK，说明一个报文段被接收



这里收到三个以上重复 ack，cwnd 设置的细节是通过 21.8 节例子补充，可能有误。



## 21.8 拥塞举例(续)

这里拥塞避免 cwnd 的增加算法是

$cwnd = cwnd + \frac{segsize*segsize}{cwnd}+\frac{segsize}{8}$

cwnd：拥塞窗口

segsize：单个报文段大小

前面提到增加的是 1/cwnd，应该指的是近似值。



## 21.9 按每条路由进行度量

路由表项中保存着度量 RTT 的数据。建立连接时，如果该连接将要使用的路由表项已经有这些度量的值，则用这些度量来对相应的变量进行初始化。



## 21.10 ICMP的差错

没看 ICMP 那章略过。



## 21.11 重新分组

当 TCP 超时并重传时，不一定要重传同样的报文段。TCP 允许进行重新分组发送一个较大的报文段，有助于提高性能



## 21.12 小结

主要讲了如下几个

慢启动：拥塞窗口指数的增长

拥塞避免：拥塞窗口线性的增长

快速重传：收到三个重复 ACK 进入重传

快速恢复：快速重传触发的算法



### 我的拥塞控制总结

cwnd：拥塞窗口

ssthresh：慢启动门限，当作阈值

拥塞控制流程如下：

- 对一个给定的连接，初始化（大概是） cwnd 为 1 个报文段，ssthresh 为 65535 个字节
- TCP 发送方的输出不能超过 cwnd 和接收方通告窗口的大小
  - 超时引发拥塞，ssthresh 被设置为当前窗口大小的一半（cwnd 和接收方通告窗口大小的最小值，最少为 2个报文段），cwnd 被设置为 1 个报文段。
  - 收到重复ACK引发拥塞，启动快速恢复算法。
- 『新』的数据被确认时，增加 cwnd，增加的方法通过判断 cwnd 是否小于或等于 ssthresh，是则慢启动，否则拥塞避免



快速恢复算法如下：

- 当收到 3 个以上重复的 ACK 时
  - 如果是第三次收到 ssthresh 设置为当前拥塞窗口 cwnd 的一半。
  - cwnd 被置为当前 ssthresh 加上所收到的重复的 ACK 数乘以报文段大小，然后发送重传数据。

- 当下一个确认『新』数据的 ACK 到达时，设置 cwnd 为 ssthresh（在第 1 步中设置的值）。

