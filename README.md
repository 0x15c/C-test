# C-test
RV22，好像我又得出题，先写几个候选方案

感觉去年的培训极其失败，一方面我不懂C语言（好为人师），另一方面选题太为差劲。
今年的培训主要侧重`struct`/`union`等关键字的应用（不然看HAL库看的太头晕），另外也要把指针数组什么的搞一搞。

嵌入式开发还是比较注意内存管理的，在vscode里面写个指针，用gcc-arm的交叉工具链编译报一堆错，而intelli-sense检查不出来。
## 下面是changelog
- 9/25 上传了一个很傻逼的三角形旋转demo，从早晨写到中午，又debug到第二天才勉强跑起来。

- 9/27 突然想起来《C与指针》书上第一个例子，还挺好玩的，在此收录一下。

- 9/28 有了个很脑残的想法，写点矩阵数学库（接下来会主力写这个）（主要是对于MCU而言，好像没有现成的库（或者就是我单纯的没找到））Cortex-M4还是集成了FPU的，不知道需不需要调用库文件
(诶，好像CMSIS有矩阵运算库)

- 10/4 笑死，一个转置写了好几天才勉强实现，接下来先做难一点的也就是行列式

当然，对于正经机器人而言，矩阵的最终实现还是要搁上位机上用SIMD指令集，这个矩阵数学库就当成是练习指针的使用吧。
