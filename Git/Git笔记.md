# 创建克隆远程/本地仓库

首先这里再明确一下，所有的版本控制系统，其实只能跟踪文本文件的改动，比如TXT文件，网页，所有的程序代码等等

`git init` 初始化一个目录为可管理的仓库



`git remote add origin git@server-name:path/repo-name.git` 关联远程仓库 

`git push -u origin master` 本地master分支推送到远程库 `-u` 第一次推送关联用

`git push origin master` 之后可以简化命令，origin 远程主机名 master 本地分支



`git clone 链接` 克隆远程仓库到本地



# 基本操作

`git add 文件` 把文件的修改添加到暂存区

`git rm` 提交本次删除操作到暂存区

`git commit -m` 把暂存区的修改提交到当前分支，提交之后暂存区就被清空了

+ `-m` 后面输入的是本次提交的说明，可以输入任意内容



`git status ` 查看当前状态

`git diff 文件名` 查看工作区和暂存区差异

+ `--cached` 查看暂存区和仓库差异
+ `HEAD -- 文件名` 查看工作区和仓库差异



`git log` 命令显示从最近到最远的提交日志，大概就是HEAD到根

+ `--pretty=oneline` 单行显示

`git reflog` 查看历史操作，可以查找新版本id用



`git reset HEAD file` 去除暂缓区file



`git reset --hard HEAD^` 工作区和暂缓区版本回退

+ HEAD 表示当前版本 ^ 表示上一版本，上上版本则是 HEAD^^
+ 上百版本HEAD~100
+ 指定版本输入指定版本id



`git reset`

+ `--hard` 回退版本，删除暂存区，回退工作区
+ `--mixed` 回退版本，删除暂存区，工作区不变
+ `--soft` 回退版本，暂存区不变，工作区不变



`git checkout -- 文件名` 文件回到最近一次 `git commit` 或 `git add` 时的状态



# 分支管理

`git branch 分支名` 创建分支

`git checkout 分支名` 、`git switch master` 切换分支

`git checkout -b 分支名` 、`git switch -c 分支名` 创建分支并切换到该分支

`git branch` 列出所有分支，当前分支前面会标一个 `*` 号

`git branch -d 分支名` 删除分支

`git branch -D feature-vulcan` 删除没用合并过的分支

`git log --graph --pretty=oneline --abbrev-commit` 查看分支情况



`git merge 指定分支` 命令用于合并指定分支到当前分支



`git merge --no-ff -m "描述" 指定分支` 合并指定分支到当前分支，合并后的历史有分支，能看出来曾经做过合并，而`fast forward`合并就看不出来曾经做过合并。 



## Bug分支/stash管理

`git stash` 存储当前工作区到栈

`git stash list` 查看栈

`git stash apply` 回复到现场 stash 内容不变

`git stash apply stash@{0}` 回复指定现场

`git stash drop` 删除stash

`git stash pop` 弹出栈顶，会删除

`git cherry-pick 提交编号` 复制特顶提交到当前分支



## 多人协作

`git remote` 查看远程库信息

+ `-v` 更详细



哪些分支需要推送，哪些不需要呢？

- `maste` 分支是主分支，因此要时刻与远程同步；
- `dev` 分支是开发分支，团队所有成员都需要在上面工作，所以也需要与远程同步；
- bug分支只用于在本地修复bug，就没必要推到远程了，除非老板要看看你每周到底修复了几个bug；
- feature分支是否推到远程，取决于你是否和你的小伙伴合作在上面开发。

总之，就是在Git中，分支完全可以在本地自己藏着玩，是否推送，视你的心情而定！



克隆

`git clone`

`git checkout -b branch-name origin/branch-name` 在本地创建和远程分支对应的分支

`git pull` 默认拉取当前分支，当前分支与远程分支存在追踪关系时 `git pull` 就可以省略远程分支名。



推送

1. 首先，可以试图用 `git push origin <branch-name>` 推送自己的修改；
2. 如果推送失败，则因为远程分支比你的本地更新，需要先用 `git pull` 试图合并；
3. 如果合并有冲突，则解决冲突，并在本地提交；
4. 没有冲突或者解决掉冲突后，再用 `git push origin <branch-name>` 推送就能成功！

如果`git pull`提示`no tracking information`，则说明本地分支和远程分支的链接关系没有创建，用命令`git branch --set-upstream-to <branch-name> origin/<branch-name>`。



## Rebase

`git rebase` 将分叉的分支重新合并，` git push` 已经落后版本需要 `git pull` 后合并提交，这时会产生分支。使用后合并分支

`git pull --rebase`



# 标签管理

`git tag <name>` 默认标签是打在最新提交的commit上

`git tag` 查看标签

 `git tag <name> <commit id>` 给某个commit id打标签

`git show <tagname>` 查看标签信息

`git tag -a <tagname> -m "blablabla..." <commit id>` 指定标签信息

`git tag -d <tagname>` 删除标签

`git push origin <tagname>` 可以推送一个本地标签

`git push origin --tags` 可以推送全部未推送过的本地标签

`git push origin :refs/tags/<tagname>` 删除远程标签，要先删除本地标签。 



# 自定义Git

`git config --global color.ui true` git高亮，好像默认开了



## 忽略特殊文件

将要忽略的文件名输入到 `.gitignore` 文本中，`.gitignore` 最好也上传版本库管理

`git add -f App.class` 强制添加到

`git check-ignore -v 文件名` 查看指定文件名忽略信息



## 配置别名

`git config --global alias.别名 '本名'`

+ `--global` 针对当前用户有效，不加这个针对当前仓库有效



配置文件在仓库 `.git/config` 下，`[alias]` 后是别名，删除对应行即可删除某个别名



## 搭建Git服务器

<https://www.liaoxuefeng.com/wiki/896043488029600/899998870925664>



# 使用Source Tree

没钱买mac 算了，不过有类似管理工具

