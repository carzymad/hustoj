hustoj
======
微信公众号:hustoj
![image](http://hustoj.com/wx.jpg)

HUSTOJ is an GPL FreeSoftware?.

HUSTOJ 是采用GPL的自由软件。

因googlecode受阻，最新更新迁移至此。

注意：基于本项目源码从事科研、论文、系统开发，"最好"在文中或系统中表明来自于本项目的内容和创意，否则所有贡献者可能会鄙视你和你的项目。
使用本项目源码和freeproblemset题库请尊重程序员职业和劳动

PS: GPL保证你可以合法忽略以上注意事项但不能保证你不受鄙视，呵呵。


Ubuntu14.04快速安装指南：  
(16.04见https://github.com/zhblue/hustoj/tree/php7)  

    1、安装Ubuntu 14.04 LTS  (16.04 need the php7 branch)  
    2、执行如下命令  
        sudo apt-get update  
        sudo apt-get install subversion  
        sudo svn co https://github.com/zhblue/hustoj/trunk/trunk/install hustoj  
        cd hustoj  
        sudo bash install-interactive.sh  
    3、安装后访问服务器80端口上的web服务JudgeOnline目录  
        例如 w3m http://127.0.0.1/JudgeOnline  

安装过程首先会询问您数据库的<b>账号和密码</b>

如果您提前安装了数据库，或使用其他服务提供的数据库服务，您应该<b>已经</b>获得了数据库的账号密码，那么请您确保输入正确。

如果您没有预先mysql服务器，安装安装过程中会自动安装，并触发root账户密码设置操作。这种情况下，第一次询问您数据库账号，请输入<b>root</b>,然后会有<b>三次</b>询问数据库密码的提示，请确保输入<b>完全相同的三次密码</b>，并自行<b>记录下来</b>，以做将来备份迁移时使用。
  
推荐用干净的Ubuntu安装，不推荐使用外挂的LAMP或LNMP打包程序，会与安装脚本冲突。



有问题请先查阅
<b>[FAQ](https://github.com/zhblue/hustoj/blob/master/wiki/FAQ.md)</b> 和
<b>[Wiki](https://github.com/zhblue/hustoj/tree/master/wiki)</b> 或使用搜索引擎。  

        
使用上需要帮助，请加用户交流QQ群23361372，仅限QQ手机加群，费用5元。   

或 购买在线服务hustoj.taobao.com。  

Linux不熟悉的用户推荐使用[HUSTOJ_LiveCD](http://pan.baidu.com/s/1o78D4x0)
或HUSTOJ_Windows（仅支持XP,QQ群23361372共享文件）进行安装。

使用说明见iso中README,也可以参考[LiveCD简介](https://github.com/zhblue/hustoj/tree/master/wiki/HUSTOJ_LiveCD.md)  

Linux新手请看[鸟哥的私房菜](http://cn.linux.vbird.org/linux_basic/linux_basic.php)

## crazy_mad 声明

这个fork版本主要是为了学习hustoj的源代码，我主要是在里面加上注释和自己的理解