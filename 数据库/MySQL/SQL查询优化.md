SQL 优化是为了提升语句执行的效率，如索引，分表，避免全局扫描等。

下面是一些对别人总结的总结（挑我大概看懂的）。

***

**思想方面**

表连接（join）不要太多

视图不要嵌套过深

少用子查询

考虑临时表或表变量存放中间结果

优先执行能大量减少结果的语句。



**具体语句**

查询语句中不要使用 *

尽量减少子查询，使用关联查询替代

使用 exists，not exists 或者关联查询代替 IN 和 NOT IN（这二者会执行全表遍历）

union 或 union all 代替 or（可能索引失效）

可以过滤掉多记录的条件写在 where 子句的最末尾（where 语句从后往前解析）

like 模糊查询左边尽可能确定（大概是 B+ 树确定前缀可以剪枝）

