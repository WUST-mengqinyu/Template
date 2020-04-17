# Template

WUSTACM 2019 一队模板

## 编译方式

需要 python2, [Texlive 环境](https://mirrors.tuna.tsinghua.edu.cn/CTAN/systems/texlive/Images/)

1. 修改 `settings.dat` 的配置信息和 `logo.jpg` 图标
2. 运行 `python generate.py` 生成 `tempalte.tex` 文件
3. 使用 Xelatex 将 tex 文件编译为 pdf 即可

如果不需要颜色可以自行处理 tex 文件

代码字体默认使用的是 FiraCode，如果想用这个可以在 [Github](https://github.com/tonsky/FiraCode/releases) 下载，注意 Windows 下安装字体需要用管理员权限否则 Xelatex 会读取不到自定义字体

否则需要更改字体

如果觉得 Texlive 太大了不想安装可以直接使用 Overleaf