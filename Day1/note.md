# RSOC Day1
## git
``` bash
git init
git add .
git commit -m "first commit"

# 给仓库地址设置一个别名(将本地项目与GitHub上的关联)
git remote add origin https://github.com/*.git 
# 查看配置的仓库
git remote -v
# 删除别名
git remote remove origin

git push -u origin master
```
## SConscript
加入这个文件可以使在当前文件夹里的也能被调用
``` SConscript
from building import *
import os

cwd     = GetCurrentDir()
src     = Glob('*.c')
CPPPATH = [cwd]

if GetDepend(['PKG_USING_RTDUINO']) and not GetDepend(['RTDUINO_NO_SETUP_LOOP']):
    src += ['arduino_main.cpp']

group = DefineGroup('Applications', src, depend = [''], CPPPATH = CPPPATH)

list = os.listdir(cwd)
for item in list:
    if os.path.isfile(os.path.join(cwd, item, 'SConscript')):
        group = group + SConscript(os.path.join(item, 'SConscript'))

Return('group')
```