函数说明

FILE * read_cmd_output(const char * fmt, ...);
    将准备要执行的命令传入该函数，然后将该命令的输出以文件指针的方式返回（这个函数使用
可变参数的形式传参）。值得注意的是，这个函数区别于execute_cmd()函数，execute_cmd()是通过
system()函数的方式执行传入的命令，system()函数是通过开启一个shell子进程，让shell子进程去执
行传入的命令；而本函数是通过 popen() 函数执行的命令，popen()函数通过管道和子进程产生数据联系，
父进程可以通过popen()函数将父进程的文件流和子进程的输入输出关联起来，而system()函数显然没有这
个功能。

int data_list_has(char * file);
    传入一个测试数据文件名，然后遍历测试数据文件列表并更新文件夹中的测试文件，如果测试
数据文件列表中存在该测试数据文件名，则返回1，不存在的话返回0。

int get_test_file(char* work_dir, int p_id);
    传入工作目录和问题编号，然后生成测试数据文件列表，返回测试数据文件的数量。

int isInFile(const char fname[]);
    传入一个文件名，然后判断该文件是否是以 .in 为扩展名结尾的，如果不是的话，返回0，是
的话则返回出去 ".in"后的文件名长度。

void prepare_files(char * filename, int namelen, char * infile, int & p_id,
    char * work_dir, char * outfile, char * userfile, int runner_id);
    传入测试数据文件名、测试数据名长度

int execute_cmd(const char * fmt, ...);
    传入若干字符串参数，然后在该函数内拼合成一条命令，通过system()函数执行，返回system()函数
的返回值。

void get_solution_info(int solution_id, int & p_id, char * user_id, int &lang);
    传入solution表的键值'suolution_id'，从solution表中查询出该条记录的 问题编号、用户账号、
用户选择的评测语言。p_id：题号，user_id：用户账号，lang：语言类型。

void get_problem_info(int p_id, int & time_lmt, int & mem_lmt, int & isspj);
    传入problem表的键值‘problem_id’(就是p_id),获取题目的运行限制参数，以及是否要打开特殊评
测的标记。
