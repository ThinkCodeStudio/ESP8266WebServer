ESP8266WebServer
======
* ESP8266WebServer是基于ESP8266开发板的演示代码，平台是Arduino，根据ESP8266示例代码HelloServer改变，使用了HTML异步控制引脚，异步获取模拟量数据显示在居于Highcharts的图表上，供参考学习。

****
## 文件目录表
HelloServer
> HelloServer.ino

HTML
> asd.html (Button)
> index.html (Highcharts)

## 环境搭建
1. 在 [Arduino官网](https://www.arduino.cc/en/Main/Software?setlang=cn&setlang=cn) 下载IDE软件
2. 安装后点击 **文件 -> 首选项** 在 **附加开发板管理器网站**中把 *http://arduino.esp8266.com/stable/package_esp8266com_index.json* 添加上。点击“好”
3. 在 **工具->开发板：？？？？->开发板管理器** 中搜索 **esp8266** 
4. 把包安装上就可以了

## 运行代码
1. 配置好ESP8266 for Arduino 的环境
2. 打开HelloServer.ino文件，进入Arduino IDE
3. 修改宏定义中的 SSID（wifi名）和 Password（WiFi密码）
4. 烧写进ESP8266，打开串口监视器，获得IP，使用IP访问网站（直接使用IP，不用http://）