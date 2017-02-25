函数说明

FILE * read_cmd_output(const char * fmt, ...);
    将准备要执行的命令传入该函数，然后将该命令的输出以文件指针的方式返回（这个函数使用
可变参数的形式传参）。

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
