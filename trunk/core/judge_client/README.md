## crazy_mad声明：

我对程序进行了部分修改，在judge_client模块中加了一个接口，在这个接口里面调用algorithm模块。

algorithm模块用于判断用户提交上来的代码中是否使用题目规定的语法，比如是否使用了 ‘swtich’。

原版HUSTOJ中，judge_client从数据库中查询到用户提交的代码，然后生成源代码文件，接着编译运行，

所以我在生成源代码文件之后创建了一个子进程，子进程用execl函数执行语法检查器模块，然后父进程

获取子进程的返回值，根据返回值判断代码是否符合语法要求。
