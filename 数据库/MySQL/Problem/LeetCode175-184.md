#### 175 组合两个表

```sql
select FirstName, LastName, City, State from Person left join Address on Address.PersonID = Person.PersonID; 
```



#### 176 第二高的薪水

```sql
select ifnull((select distinct Salary from Employee order by Salary desc limit 1,1), null) as SecondHighestSalary;
```

`ifnull(a,b)` a 为 NULL 返回 b

`distinct` 去重

`as` 别名设置



#### 177 第 N 高的薪水

```sql
CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
  SET N = N-1;
  RETURN (
      select ifnull((select distinct Salary from Employee order by Salary desc limit N, 1), NULL)
  );
END
```

limit 里无法使用 N-1



#### 178 分数排名

 ```sql
select Score, 
    (select count(distinct s2.Score)
    from Scores s2
    where s2.Score >= s1.Score)
    as 'Rank'
from Scores s1
order by Score desc;
 ```

看别人的，也看了半天。。

以 `'Rank'` 排序无效，估计是由外向内解释，先按分数排序，在计算得到有多少分数大于 `s1.Score`



还有一种通过函数的直接解法

```sql
SELECT Score,
dense_rank() over(order by Score desc) as 'Rank'
FROM Scores
```



#### 180 连续出现的数字

```sql
select distinct f.Num as 'ConsecutiveNums'
from Logs as f, Logs as u, logs as c
where f.Num = u.Num and f.Num = c.Num and f.Id = u.Id-1 and f.Id = c.Id-2;
```

还有题目变形，连续出现 n 次，太难了先放弃。



#### 181 超过经理收入的员工

```sql
select a.Name as 'Employee'
from Employee a, Employee b
where a.ManagerID = b.ID and a.Salary > b.Salary;
```



#### 182 查找重复的电子邮箱

```sql
# 这是我第一反应写的
select distinct a.Email
from Person a, Person b
where a.Email = b.Email and a.Id != b.Id;
```



还有种方法用 `group by` 和 `HAVING` ，having 对 group by 的对象进行筛选

```sql
select Email
from Person
group by Email
having count(Email) > 1;
```



#### 183 从不订购的客户

```sql
select a.Name as 'Customers'
from Customers a
where a.Id not in(
    select b.CustomerId from Orders b
);
```

或

```sql
select a.Name as 'Customers'
from Customers a
left join Orders b on a.Id = b.CustomerId
where b.CustomerId is null;
```



#### 184 部门工资最高的员工

```sql
select d.Name Department, e.Name Employee, e.Salary Salary
from Employee e, Department d
where e.DepartmentId = d.Id
and (e.Salary, e.DepartmentId) in (
    select max(Salary), DepartmentId
    from Employee
    group by DepartmentId
);
```

