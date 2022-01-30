# ABC 工具使用

## 目录

- [目录](#目录)
- [Verilog 学习](#Verilog-学习)
- [数字电路设计学习](#数字电路设计学习)
- [EDA 学习](#EDA-学习)
	- [EDA 设计流程](#EDA-设计流程)
	- [EDA 工具](#EDA-工具)
	- [IP 核](#IP-核)
	- [PLD](#Programmable-Logic-Device-PLD)
	- [VHDL 设计](#VHDL-设计)
		- [二选一多路选择器](#二选一多路选择器)
		- [四选一多路选择器](#四选一多路选择器)
		- [1 位半加器](#1-位半加器)
		- [1 位全加器](#1-位全加器)
		- [8 位加法器](#8-位加法器) 
		- [乘法器](#乘法器)
		- [多功能 D 触发器](#多功能-D-触发器)
		- [锁存器](#锁存器)
		- [移位寄存器](#移位寄存器)
		- [4 位二进制加法计数器](#4-位二进制加法计数器)
		- [4 位二进制减法计数器](#4-位二进制减法计数器)
		- [实用计数器](#实用计数器)
	- [含高阻态输出电路设计](#含高阻态输出电路设计)
		- [三态门](#三态门)
		- [双向端口](#双向端口)
		- [三态总线](#三态总线)
	- [VHDL 描述风格](#VHDL-描述风格) 
	- [VHDL 用户自定义数据类型](#VHDL-用户自定义数据类型)
- [参考链接](#参考链接)

## Verilog 学习

> Verilog 是一种 **硬件描述语言**，用于 **数字电路的系统设计**。可以对 **算法级**、**门级**、**开关级** 等多种抽象设计层次进行建模。

### 基础语法

#### 格式

- 区分大小写。
- 每个语句以 **分号** 为结束符。
- **空白符** 没有实际意义，编译阶段可忽略。

#### 注释

与 `C` 一样，`//` **单行注释**，`/**/` **多行注释**。

#### 标识符与关键字

标识符首字母必须是 **字母** 或 **下划线**，其他字母可以是 **`a-z`**、**`A-Z`**、**`0-9`**、**`$`** 和 **`_`**。

`module`：模块开始定义。
`input`：输入端口定义。
`output`：输出端口定义。
`inout`：双向端口定义。
`parameter`：信号的参数定义。
`wire`：wire 信号定义。
`reg`：reg 信号定义。
`always`：产生 reg 信号语句的关键字。
`assign`：产生 wire 信号。
`begin`：语句的起始标志。
`end`：语句的结束标志。
`posedge/negedge`：时序电路的标志。
`case`：Case 语句的起始标记。
`default`：Case 语句的默认分支标志。
`endcase`：Case 语句结束标志。
`if`： if/else 语句标记。
`else`：if/else 语句标记。
`for`：for 语句标记。
`endmodule`：模块结束定义。

#### 数值种类

- `0`：逻辑 0 或 "假"。
- `1`：逻辑 1 或 "真"。
- `x` 或 `X`：未知，即信号数值不确定。在实际电路里，信号可能为 1 或 0。
- `z` 或 `Z`：高阻，常见于信号没有驱动时的逻辑结果。

#### 数值表示

- **整数** 格式是 `(位宽)'[基数格式]数值`，其中 `位宽` 代表占用多少个 `bit`，是可选的参数。而 `基数格式` 代表使用的进制，有十进制 `d` 或 `D`，十六进制 `h` 或 `H`，二进制 `b` 或 `B`，八进制 `o` 或 `O`。使用关键字 `integer` 来声明。

```Verilog
4'b1011        // 4 bit 二进制数值 -5
32'h3022_c0de  // 32 bit 十六进制数值，下划线是为了增强代码可读性
'd100          // 不指明位宽，由编译器自动分频位宽，常见为 32 bit
100 					 // 直接写数字，默认十进制表示
```

- **负整数** 通常在表示位宽的数字前面加一个减号 `-` 来表示。但整型数字的第一个 `bit` 代表是符号位，代表负数，所以 -15 在 5 位二进制表示可以是 `5'b10001`。

- **实数** 则主要用 **十进制** 和 **科学计数法** 来表示，如 `30.123` 或 `1.2e4`。使用关键字 `real` 来声明。

- **时间** 是当前仿真时间的特殊时间寄存器变量，使用关键字 `time` 来声明，调用系统函数 `$time` 来获取当前仿真时间。

#### 字符串表示

**双引号包裹**，**不能多行书写**。如 `str = "www.runoob.com"`。**转义字符** 和 `C` 语言类似。

#### 数据类型

- **线网（wire）** 表示 **硬件单元之间的物理连线**，由其连接的器件输出端连续驱动，例如 `wire interrupt` 和 `wire gnd = 1'b0`。
- **寄存器（reg）** 表示 **存储单元**，始终保持数据原有的值直到被 **改写**。例如 `reg clk_temp`。
- **向量** 是 `wire` 或 `reg` 的声明形式。如 `reg [2:32 - 1] gpio_data` 就代表 30 `bit` 位宽的线性变量 `gpio_data`，位宽范围是 `2:31` 且最高有效位是 2。以及 `bit+:width` 代表从起始 `bit` 位开始递增，位宽为 `width`，相应的 `bit-:width` 则是从起始 `bit` 位开始递减，位宽为 `width`。
- **参数** 用来表示 **常量**，使用关键字 `parameter` 声明，只能 **初始化赋值一次**。例如 `parameter i = 1`。

#### 表达式

由 **操作符** 和 **操作数** 构成，可以在出现数值的任何地方使用。

- **操作数**：常数，整数，实数，线网，寄存器，时间，位选，域选，存储器及函数调用等。
- **操作符**：算术，关系，等价，逻辑，按位，归约，移位，拼接，条件等。

**算术操作符** 包括 **双目操作符** 乘`*`，除`/`，加`+`，减`-`，求幂`**`，取模`%` 和 **单目操作符** 正`+`，负`-`，非`!`，按位取反`~`。

**关系操作符** 有 大于`>`，小于`<`，大于等于`>=`，小于等于`<=`。如果操作数中有一位是 `x` 或 `z`，则关系表达式结果为 `x`。

**等价操作符** 包括 逻辑相等`==`，逻辑不等`!=`，全等`===`，非全等`!==`。全等比较按位比较，因此可以比较包含 `x`或 `z` 的操作数。

**逻辑操作符** 包括 逻辑与`&&`，逻辑或`||`，逻辑非`!`。

**按位操作符** 包括 取反`~`，与`&`，或`|`，异或`^`，同或`~^`。

**归约操作符** 包括 归约与`&`，归约与非`~&`，归约或`|`，归约或非`~|`，归约异或`^`，归约同或`~^`。仅有一个操作数，逐位操作，最终产生一个 `1 bit` 结果。

**移位操作符** 包括 左移`<<`，右移`>>`，算术左移`<<<`，算术右移`>>>`。逻辑右移时，左边高位会补 0，算术右移时，左边高位会补符号位。

**拼接操作符** 是 `{,}`，用于将多个操作数拼接成新的操作数，信号间用逗号`,`隔开。

**条件操作符** 结构是 `condition_expression ? true_expression : false_expression`。用法和 `C` 语言一致。

#### 编译指令

以反引号 `` ` `` 开头，是 `Verilog` 系统编译指令，类似于 `C` 中 `#`。

```Verilog
Verilog:  `define  ===  #define  :C
Verilog:  `undef   // 取消之前宏定义
Verilog:  `ifdef   ===  #ifdef   :C
Verilog:  `elsif   // 配合 `ifdef 使用
Verilog:  `else    // 配合 `ifdef 使用
Verilog:  `endif   ===  #endif   :C
Verilog:  `include ===  #include :C
Verilog:  `timescale time_unit / time_precision   // 将时间单位与实际时间相关联
Verilog:  `default_nettype`   // 用于为隐式的线网变量指定为线网类型。
Verilog:  `resetall`   // 将所有的编译指令重新设置为缺省值。
Verilog:  `celldefine, `endcelldefine   // 将模块标记为单元模块
Verilog:  `unconnected_drive, `nounconnected_drive   // 正偏电路状态和反偏电路状态
```

#### 连续赋值

数据流建模赋值，针对 `wire` 类型变量。只能赋值一次，且会随时变化，相当于 `C++` 中取别名，使用关键字 `assign` 或直接初始化赋值。

```Verilog
wire A, B;
wire Cout = A & B;

wire Cout, A, B;
assign Cout = A & B;
```

#### 时延

用于控制任意操作数发生变化到语句左端赋予新值之间的时间延时。

```Verilog
// 普通时延，A&B计算结果延时 10 个单位时间赋值给Z
wire Z, A, B
assign #10 Z = A & B;
// 隐式时延，声明时使用
wire A, B
wire #10 Z = A & B;
// 声明时延，对该变量所有的连续赋值都会被推迟到指定的时间。
wire A, B;
wire #10 Z;
assign Z = A & B;
```

#### 过程结构和过程赋值

`initial` 语句从 **0 时刻** 开始执行，只 **执行一次**，多个 `initial` 块之间相互独立。如有多个语句，则需搭配 `begin` 和 `end` 使用。

`always` 语句是 **重复执行**，常用与仿真时钟的产生，信号行为的检测等。

在 `initial` 或 `always` 语句块中的赋值是 **过程赋值**，分为 **阻塞赋值**`=`，即顺序执行，多用于`initial` 中。 和 **非阻塞赋值**`<=`，即并行执行，多用于 `always` 中。

## 数字电路设计学习

## EDA 学习

入门级学习，参考 [b 站教程](https://www.bilibili.com/video/BV1rK411W717?from=search&seid=4605110450993826459&spm_id_from=333.337.0.0)。

### EDA 设计流程

1. **设计输入**：有 **图形输入**（**原理图**、**波形图** 和 **状态图**）和 **HDL 输入** （**VHDL**、**Verilog HDL**、**System Verilog** 和 **System C**）两种方式。

**VHDL** 是 **电子设计主流硬件语言** 之一，**硬件描述语言的业界标准** 之一。具有 **与具体硬件电路无关和与设计平台无关** 的特性，具有良好的 **电路行为描述** 和 **系统描述** 的能力，具有很强的 **电路描述** 和 **建模能力**。

2. **综合**：将设计输入转换为 **门级电路** 甚至更底层的 **电路描述网表文件**。
3. **适配**：将由综合后产生的 **网表文件** 针对某一具体的目标器件进行 **底层器件配置**、**逻辑分割**、**逻辑优化** 和 **逻辑布局布线** 等操作。并生成 **仿真文件** 和 **编程的文件**。
4. **仿真测试**：模拟测试 **排除错误** 和 **验证设计是否满足要求**。
5. **编程下载**：把适配生成的下载或配置文件，通过编程器（下载器）向 FPGA 或 CPLD 下载。

### EDA 工具

1. **设计输入编辑器**：用于 **设计输入表达描述**。
2. **HDL 综合器**：用于 **将语言转换为硬件电路网表结构**。
3. **适配器**：用于 **目标系统在器件上的布局布线**。
4. **下载器**：用于 **下载程序到目标器件（软件部分）**。
5. **仿真器**：用于 **系统功能验证测试**。

**QUARTUS II**

集成的 EDA 开发软件，综合了上述五个软件的功能，且能够接入第三方工具。

### IP 核

使用 **EDA 技术** 进行 **电子设计** 出的 **电路功能模块**，通过 **申请知识产权** 得到 **IP 核**。

- **软 IP**：用 VHDL 等 **硬件描述语言** 描述的功能块，通常为 **VHDL 源文件**。
- **固 IP**：完成了 **综合** 的功能块，以 **网表文件** 的形式提交给客户使用。
- **硬 IP**：提供设计的最终阶段产品，将一些功能在出厂时就 **固化** 在 **芯片** 中。

### Programmable Logic Device (PLD)

可编程逻辑器件。**可编程** 指逻辑功能按照用户对器件 **编程** 来确定，而 **逻辑器件** 指 **集成电路（芯片）**。

由基本门构成的数字电路分为 **组合电路**（可以用 与门 和 或门 二级电路实现）和 **时序电路**（组合电路 + 存储元件）。

PLD 按照 **集成度**（一个芯片中含有逻辑门或者元件的个数）划分为 **简单的**（已经不再使用）和 **复杂的**（即 CPLD 和 FPGA）。按照 **编程工艺** 划分为 **熔丝型**、**反熔丝型**、**EPROM 型**（前三个均已不再使用）、**EEPROM 型**、**SRAM 型**（FPGA 使用，但掉电后信息容易丢失）和 **Flash 型**（CPLD 使用，掉电后不需要重新配置）。

#### Field Programmable Gate Array (FPGA)

现场可编程门阵列。即用户通过原理图或 HDL 语言描述了一个逻辑电路，FPGA 开发软件会 **自动计算逻辑电路的所有可能的结果**，并把结果事先写入 RAM，之后用户每输入一个信号进行逻辑运算，相当于输入一个地址 **进行查表** 并找出地址对应内容输出结果。

![Sign](./README/Sign.png)

### VHDL 设计

#### 二选一多路选择器

以 **二选一多路选择器** 为例。需要实现的功能如下图，如果 $s$ 端输入 1 则将 $a$ 赋值给输出端 $y$，如果 $s$ 端输入 0 则将 $b$ 赋值给输出端 $y$。

![Two-One](./README/Two-One.png)

使用 VHDL 编程如下。

```VHDL
ENTITY mux21a IS
	PORT(a, b: IN BIT;
			 s: IN BIT;
			 y: OUT BIT);
END ENTITY mux21a;

ARCHITECTURE bhv OF mux21a IS
	BEGIN
		PROCESS(a, b, s) BEGIN
			IF (s = '1') THEN y <= a;
			ELSE y <= b;
			END IF;
		END PROCESS;
	END ARCHITECTURE bhv;
```

- **实体描述**

```VHDL
ENTITY 实体名 IS
	PORT(端口信号名: 端口模式 数据类型;
	     ...
	     端口信号名: 端口模式 数据类型);
END ENTITY 实体名;
```

- **结构体描述**

```VHDL
ARCHITECTURE 结构体名 OF 实体名 IS
	[说明语句]
BEGIN
	(功能描述语句)
END ARCHITECTURE 结构体名;
```

- **端口模式**

有 **输入端口** `IN`，定义的通道为 **单向只读模式**。**输出端口** `OUT`，定义的通道为 **单向输出模式**。**输入输出双向端口** `INOUT` 和 **缓冲端口** `BUFFER`，功能与 `INOUT` 类似。

- **数据类型**

`BIT` 取值范围是逻辑位 `'0'` 和 `'1'`，**必须加单引号**。还有布尔类型，整数类型，有符号无符号等各种数据类型。

- **`IF` 条件语句**

`IF_THEN_ELSE_END IF` 顺序语句，即按照语句前后排序方式顺序执行，必须放在进程语句中。

```VHDL
IF 条件句 THEN 顺序语句;
ELSIF 条件句 THEN 顺序语句;
...
ELSIF 条件句 THEN 顺序语句;
ELSE 顺序语句;
END IF;
```

- **进程语句**

进程号用来标识不同的进程语句，敏感信号参数通常是输入端口号，进程说明部分可有可无。

```VHDL
[进程号: ]PROCESS[(敏感信号参数)][IS]
[进程说明部分]
BEGIN
顺序描述语句
END PROCESS[进程标号];
```

- **赋值符号**

`<=` 用于赋值，`=` 用于比较。赋值时两边信号的 **数据类型** 必须一致，无法像 `C` 语言进行隐式强制类型转换。

- **关键字和标识符**

关键字和标识符均 **不区分大小写**，且标识符不能含有 **数字开头** 或 **中文**。

#### 四选一多路选择器

即端口 `s0` 和端口 `d1` 输入的值两两组合的四种情况中，分别将端口 `a`、`b`、`c` 和 `d` 的值赋值给输出端口 `y`。

![Four-One](./README/Four-One.png)

```VHDL
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY mux41a IS
	PORT(a, b, c, d: IN std_logic;
			 s1, s0: IN std_logic;
			 y: OUT std_logic);
END ENTITY mux41a;

ARCHITECTURE bhv OF mux41a IS
	signal s: std_logic_vector(1 downto 0);
	BEGIN 
		s <= s1 & s0;
		PROCESS(a, b, c, d, s1, s0)
			BEGIN
				CASE S IS
					WHEN "00" => y <= a;
					WHEN "01" => y <= b;
					WHEN "10" => y <= c;
					WHEN "11" => y <= d;
					WHEN ORTHERS => null;
				END CASE;
			END PROCESS;
	END ARCHITECTURE bhv;
```

- **设计库和标准程序包**

`LIBRARY` 用来导入 **库**（用来存储预先定义好的程序包、数据集合和元件的仓库），类似于 `C++` 语言中 `#include`。而 `USE` 用来引用 **程序包**（预先定义好的数据类型、子程序等设计单元的集合体）。

- **标准的逻辑位数据类型 STD_LOGIC**

包含 `'U'`（未初始化），`'X'`，`'0'`（强逻辑 0），`'1'`（强逻辑 1），`'Z'`（高阻态），`'W'`，`'L'`，`'H'`，`'-'` 共 9 个取值，经常使用 `STD_LOGIC` 而不是 `BIT`。

- **信号定义和数据对象**

`SIGNAL 信号名: 数据类型`，作用类似于一根导线（数组），在实体、结构体和程序包中使用和定义，不能在进程和子程序的顺序语句内定义，端口的数据对象默认为信号。

- **标准逻辑位矢量数据类型**

`STD_LOGIC_VECTOR(高位 downto 低位)` 或 `STD_LOGIC_VECTOR(低位 to 高位)`，有点像数组定义。

```VHDL
signal a: std_logic_vector(3 downto 0);
a <= "1011";
a(3 downto 2) <= "11";
a(3) = '1';
```

- **并置操作符 `&`**

把信号和数组 **合并拼接** 形成新的数组矢量。

- **`CASE` 条件语句**

如果选择值不能覆盖表达式的所有取值，则 `OTHERS` 语句（相当于 `C` 语言中的 `default`）必须写。

```VHDL
CASE <表达式> IS
	WHEN <选择值> => <顺序语句>; ...;
	WHEN <选择值> => <顺序语句>; ...;
	...
	WHEN OTHERS => <顺序语句>;
	END CASE;
```

- **`WHEN_ELSE` 语句**

可以用来和 `CASE` 语句做替换，是一种并行语句，不需要嵌套在 `PROCESS` 语句中间。

```VHDL
赋值目标 <= 表达式 WHEN 赋值条件
				ELSE 表达式 WHEN 赋值条件
				...
				ELSE 表达式 WHEN 赋值条件
				ELSE 表达式;
```

- **`WITH_SELECT` 语句**

一种并行语句，不需要嵌套在 `PROCESS` 语句中间。如果选择值不能完全覆盖表达式的所有取值，则 `UNAFFECTED WHEN OTHERS` 必须写。

```VHDL
WITH 选择表达式 SELECT
赋值目标信号 <= 表达式 WHEN 选择值,
							...
							表达式 WHEN 选择值;
							UNAFFECTED WHEN OTHERS;
```

#### 1 位半加器

相当于 1 位加法，输入信号是 `A` 和 `B`，输出信号是 和值`SO` 和 进位`CO`。

$$
SO = A \bigoplus B \\
CO = A \cdot B \\
$$

```VHDL
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
ENTITY h_adder IS
	PORT(A, B: IN STD_LOGIC;
			 SO, CO: OUT STD_LOGIC);
END ENTITY h_adder;
ARCHITECTURE bhv OF h_adder IS
  BEGIN
    SO <= A XOR B;
    CO <= A AND B;
  END ARCHITECTURE bhv;
```

#### 1 位全加器

相当于三个数的加法，可以通过调用事先定义好的 1 位半加器和或门来完成。这种设计方法称为 **元件例化调用组装设计**。

![f_adder](./README/f_adder.png)

```VHDL
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
ENTITY f_adder IS
	PORT(ain, bin, cin: IN STD_LOGIC;
			 sum, cout: OUT STD_LOGIC);
END ENTITY f_adder;

ARCHITECTURE fs1 OF f_adder IS
	COMPONENT h_adder
		PORT(A, B: IN STD_LOGIC;
				 SO, CO: OUT STD_LOGIC);
	END COMPONENT
	COMPONENT or2a
		PORT(a, b: IN STD_LOGIC;
				 c: OUT STD_LOGIC);
	END COMPONENT;
	SIGNAL net1, net2, net3: STD_LOGIC; -- 连接线
  BEGIN
  u1: h_adder PORT MAP(A => ain, B => bin,
  SO => net1, CO => net2);
  u2: h_adder PORT MAP(A => net1, B => cin,
  SO => sum, CO => net3);
  u3: or2a PORT MAP(a => net3, b => net2, c => cout);
  END ARCHITECTURE fs1;
```

- **例化语句**

端口说明语句部分，位于结构体 `ARCHITECTURE` 和 `BEGIN` 之间。

```VHDL
COMPONENT 元件名 IS
	PORT(端口列表);
END COMPONENT 元件名;
```

端口映射语句部分，位于结构体 `BEGIN` 和 `END ARCHITECTURE` 之间。

```VHDL
例化名: 元件名 PORT MAP(端口名 => 连接端口名, ...)
```

#### 8 位加法器

可以通过调用 8 个 1 位加法器来完成。

![f_adder_8](./README/f_adder_8.png)

```VHDL
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
ENTITY adder8 IS
	PORT(A, B: IN STD_LOGIC_VECTOR(7 DOWNTO 0);
			 CIN: IN STD_LOGIC;
			 S: OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
			 COUT: OUT STD_LOGIC);
END ENTITY adder8;

ARCHITECTURE bhv OF adder8 IS:
	COMPONENT h_adder
		PORT(A, B: IN STD_LOGIC;
				 SO, CO: OUT STD_LOGIC);
	END COMPONENT
  SIGNAL net1, net2, net3, net4, net5, net6, net7: STD_LOGIC; -- 连接线
  BEGIN
    u1: h_adder PORT MAP(ain => A(0), bin => B(0), cin => CIN,
                         sum => S(0), cout => net1);
  	u2: h_adder PORT MAP(ain => A(1), bin => B(1), cin => net1,
                         sum => S(1), cout => net2);
    u3: h_adder PORT MAP(ain => A(2), bin => B(2), cin => net2,
                         sum => S(2), cout => net3);
    u4: h_adder PORT MAP(ain => A(3), bin => B(3), cin => net3,
                         sum => S(3), cout => net4);
    u5: h_adder PORT MAP(ain => A(4), bin => B(4), cin => net4,
                         sum => S(4), cout => net5);
    u6: h_adder PORT MAP(ain => A(5), bin => B(5), cin => net5,
                         sum => S(5), cout => net6);
    u7: h_adder PORT MAP(ain => A(6), bin => B(6), cin => net6,
                         sum => S(6), cout => net7);
    u8: h_adder PORT MAP(ain => A(7), bin => B(7), cin => net7,
                         sum => S(7), cout => COUT);
  END ARCHITECTURE bhv;
```

也可以直接使用 `VHDL` 预定义的算术运算符 `+`。**运算符重载**。

```VHDL
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
ENTITY adder8 IS
	PORT(A, B: IN STD_LOGIC_VECTOR(7 DOWNTO 0);
			 CIN: IN STD_LOGIC;
			 S: OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
			 COUT: OUT STD_LOGIC);
END ENTITY adder8;

ARCHITECTURE bhv OF adder8 IS
	SIGNAL DATA: STD_LOGIC_VECTOR(8 DOWNTO 0);
	BEGIN
		DATA <= ('0' & A) + ('0' & B) + ("00000000" & CIN); -- <=左右矢量位数必须一致
		S <= DATA(7 DOWNTO 0);
		COUT <= DATA(8);
	END ARCHITECTURE bhv;
````

#### 操作符

操作数数据类型必须满足要求，且操作符间的操作数必须是相同的数据类型。操作符的优先级。

`NOT` `ABS` `**` > `*` `/` `MOD` `REM` > 正号 `+` 负号`-` > `+` `-` `&` > `SLL` `SLA` `SRL` `SRA` `ROL` `ROR` > `=` `/=` `<` `<=` `>` `>=` > `AND` `OR` `NAND` `NOR` `XOR` `XNOR`。

**算术操作符**

| 操作符 | 功能 | 操作数数据类型 |
| :--: | :--: | :--: |
| `+` | 加 | 整数 |
| `-` | 减 | 整数 |
| `*` | 乘 | 整数、实数 |
| `/` | 除 | 整数、实数 |
| `&` | 并置 | 一维数组 |
| `MOD` | 取模 | 整数 |
| `REM` | 取余 | 整数 |
| `SLL` | 逻辑左移 | `BIT`、`BIT_VECTOR`、布尔型 |
| `SRL` | 逻辑右移 | `BIT`、`BIT_VECTOR`、布尔型 |
| `SLA` | 算术左移 | `BIT`、`BIT_VECTOR`、布尔型 |
| `SRA` | 算术右移 | `BIT`、`BIT_VECTOR`、布尔型 |
| `ROL` | 逻辑循环左移 | `BIT`、`BIT_VECTOR`、布尔型 |
| `ROR` | 逻辑循环右移 | `BIT`、`BIT_VECTOR`、布尔型 |
| `**` | 乘方 | 整数 |
| `ABS` | 取绝对值 | 整数 |

**关系操作符**

| 操作符 | 功能 | 操作数数据类型 |
| :--: | :--: | :--: |
| `=` | 等于 | 任何数据类型 |
| `/=` | 不等于 | 任何数据类型 |
| `<` | 小于 | 枚举、整数 |
| `>` | 大于 | 枚举、整数 |
| `<=` | 小于等于 | 枚举、整数 |
| `>=` | 大于等于 | 枚举、整数 |

**逻辑操作符**

| 操作符 | 功能 | 操作数数据类型 |
| :--: | :--: | :--: |
| `AND` | 与 | `BIT`、`BOOLEAN`、`STD_LOGIC` |
| `OR` | 或 | `BIT`、`BOOLEAN`、`STD_LOGIC` |
| `NAND` | 与非 | `BIT`、`BOOLEAN`、`STD_LOGIC` |
| `NOR` | 或非 | `BIT`、`BOOLEAN`、`STD_LOGIC` |
| `XOR` | 异或 | `BIT`、`BOOLEAN`、`STD_LOGIC` |
| `XNOR` | 同或 | `BIT`、`BOOLEAN`、`STD_LOGIC` |
| `NOT` | 非 | `BIT`、`BOOLEAN`、`STD_LOGIC` |

**符号操作符**

| 操作符 | 功能 | 操作数数据类型 |
| :--: | :--: | :--: |
| `+` | 正 | 整数 |
| `-` | 负 | 整数 |

#### 统计 8 位位矢中含 `'1'` 的个数

```VHDL
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
ENTITY CNT1 IS
	PORT(DIN: IN STD_LOGIC_VECTOR(7 DOWNTO 0);
	     CNT: OUT STD_LOGIC_VECTOR(3 DOWNTO 0));
END ENTITY CNT1;

ARCHITECTURE bhv OF CNTC IS
	BEGIN PROCESS(DIN)
			VARIABLE Q: STD_LOGIC_VECTOR(3 DOWNTO 0);
			BEGIN
				Q := "0000";
				FOR N IN 0 TO 7 LOOP
					IF (DIN(N) = '1') THEN Q := Q + 1;
					END IF;
				END LOOP;
				CNTH <= Q;
			END PROCESS;
	END BHV; 
```

- **`VARIABLE`**：变量数据类型，作为数据的暂存单元，赋值符号为 `:=`，定义位置在 `PROCESS` 语句内部。

- **循环语句**

```VHDL
-- 第一种方式
[LOOP标号: ] FOR 循环变量 IN 循环次数范围 LOOP
								循环语句
						END LOOP [LOOP标号];
						
-- e.g.
FOR N IN 0 TO 7 LOOP
	IF (DIN(N) = '1') THEN Q := Q + 1;
	END IF;
END LOOP;

-- 第二种方式
[LOOP标号: ] LOOP
							循环语句
						END LOOP [LOOP标号];

-- e.g.
L2: LOOP
			a := a + 1;
			EXIT L2 WHEN a > 10;
		END LOOP L2;
```

#### 乘法器

计算两个位数相等的数相乘后的结果，如下是 `4 * 4` 乘法器的代码样例。

```VHDL
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.STD_LOGIC_ARITH.ALL;
ENTITY MULT4B IS
	GENERIC(S: INTEGER := 4); -- 定义类属参数 S
	PORT(A, B: IN STD_LOGIC_VECTOR(S DOWNTO 1);
	     		R: OUT STD_LOGIC_VECTOR(2 * S DOWNTO 1));
END ENTITY MULT4B;

ARCHITECTURE BHV OF MULT4B IS
	SIGNAL A0: STD_LOGIC_VECTOR(2 * S DOWNTO 1);
	BEGIN
		A0 <= CONV_STD_LOGIC_VECTOR(0, S) & A; -- 将整数 0 变成 S 位二进制数
		PROCESS(A, B)
			VARIABLE R1: STD_LOGIC_VECTOR(2 * S DOWNTO 1);
			BEGIN
				R1 := (OTHERS => '0'); -- 使用省略操作符: (OTHERS => '0'), 使得 R1 的每一位都是 0
				FOR I IN 1 TO S LOOP
					IF (B(I) = '1') THEN
						R1 := R1 + TO_STDLOGICVECTOR(TO_BITVECTOR(A0) SLL (I - 1)); -- 左移数据类型须是 BIT_VECTOR
					END IF;
				END LOOP;
			R <= R1;
```

利用 `4 * 4` 乘法器来完成 `8 * 8` 乘法器的设计。

```VHDL
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
ENTITY MULT8B IS
	PORT(D1, D2: IN STD_LOGIC_VECTOR(7 DOWNTO 0);
						Q: OUT STD_LOGIC_VECTOR(15 DOWNTO 0));
END ENTITY MULT8B;

ARCHITECTURE BHV OF MULT8B IS
	COMPONENT MULT4B
		GENERIC(S: INTEGER);
		PORT(R: OUT STD_LOGIC_VECTOR(2 * S DOWNTO 1);
			A, B: IN STD_LOGIC_VECTOR(S DOWNTO 1));
		END COMPONENT;
	BEGIN
		U1: MULT4B GENERIC MAP(S => 8)
							 PORT MAP(R => Q, A => D1, B => D2);
	END
```

**`GENERIC` 参数传递语句**

**定义** 部分需要放在 **实体的说明语句部分**，`GENERIC` 语句在所定义参数类似于端口 `PORT`，从外部动态地接受赋值，从而 **改变电路内部规模或结构**。

```VHDL
GENERIC(常数名1: 数据类型[:= 设定值];
 				...
 				常数名n: 数据类型[:= 设定值]);
```

**映射** 部分可用于设计从外部端口改变元件内部参数或结构规模的元件（类属元件）。

```VHDL
例化名: 元件名 GENERICE MAP(类属表)
```

#### 多功能 D 触发器

时序电路，用于检测上升沿信号。

```VHDL
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
ENTITY DFF2 IS
	PORT(CLK, RST, EN, D: IN STD_LOGIC;
			 Q: OUT STD_LOGIC);
END ENTITY DFF2;

ARCHITECTURE BHV OF DFF2 IS
	SIGNAL Q1: STD_LOGIC;
	BEGIN PROCESS(CLK, Q1, RST, EN)
		BEGIN IF RST = '1' THEN Q1 <= '0'; -- 异步清零，独立于 CLK 控制
		ELSIF CLK'EVENT AND CLK='1' THEN
			IF EN = '1' THEN Q1 <= D; END IF; -- 时钟使能
		END IF;
	END PROCESS;
	Q <= Q1;
END BHV;
```

- **边沿检测语句**

用于检测时钟信号变化，分为 **上升沿** 和 **下降沿**。

```VHDL
1. CLK'EVENT AND (CLK = '1') -- 上升沿
   CLK'EVENT AND (CLK = '0') -- 下降沿
2. CLK = '1' AND (CLK'LAST_VALUE = '0') -- 上升沿
   CLK = '0' AND (CLK'LAST_VALUE = '1') -- 下降沿
3. RISING_EDGE(CLK) -- 上升沿 
   FALLING_EDGE(CLK) -- 下降沿
4. WAIT UNTIL CLK = '1' -- 上升沿
   WAIT UNTIL CLK = '0' -- 下降沿
```

#### 锁存器

当时钟周期信号 `CLK` 高电平时，`Q` 的值随 `D` 的值变化而变化。低电平时 `Q` 值保持不变。（增加异步复位 `RST`，即当 `RST = '1'` 时，`Q` 的值一定变成 `'0'`）。

```VHDL
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
ENTITY LTCH IS
	PORT(CLK, D, RST: IN STD_LOGIC;
			 Q: OUT STD_LOGIC);
END LTCH;

ARCHITECTURE BHV OF LTCH IS
	SIGNAL Q1: STD_LOGIC;
	BEGIN PROCESS(CLK, Q1)
		BEGIN
			IF RST = '1' THEN Q1 <= '0';
			ELSIF CLK = '1' THEN Q1 <= D;
			END IF;
		END PROCESS;
	Q <= Q1;
END BHV;
```

#### 移位寄存器

一个输入时钟信号 `CLK`，一个数据装载信号 `LOAD`，一个装载数据 `DIN`，一个串行输出数据 `QB`，一个并行输出数据 `COUT`。

以下是一个 8 位左移移位寄存器的 VHDL 设计。

```VHDL
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
ENTITY SHFT IS
	PORT(CLK, LOAD: IN STD_LOGIC;
			 QB: OUT STD_LOGIC;
			 DIN: IN STD_LOGIC_VECTOR(7 DOWNTO 0);
			 DOUT: OUT STD_LOGIC_VECTOR(7 DOWNTO 0));
END SHFT;

ARCHITECTURE BHV OF SHFT IS
	SIGNAL REG8: STD_LOGIC_VECTOR(7 DOWNTO 0);
	BEGIN 
		PROCESS(CLK, LOAD)
			BEGIN
				IF CLK'EVENT AND CLK = '1' THEN 
					IF LOAD = '1' THEN REG8 <= DIN;
					ELSE REG8(7 DOWNTO 1) <= REG8(6 DOWNTO 0);
					END IF;
				END IF;
		END PROCESS;
		QB <= REG8(7);
		DOUT <= REG8;
	END BHV;
```

左移：低位赋值给高位，最低位保持不变。

```VHDL
REG8(7 DOWNTO 1) <= REG8(6 DOWNTO 0)
```

右移：高位赋值给低位，最高位保持不变。

```VHDL
REG8(6 DOWNTO 0) <= REG8(7 DOWNTO 1)
```

循环左移：低位赋值给高位，最高位赋值给最低位，并行执行。

```VHDL
REG8(0) <= REG8(7)
REG8(7 DOWNTO 1) <= REG8(6 DOWNTO 0)
```

循环右移：高位赋值给低位，最低位赋值给最高位，并行执行。

```VHDL
REG8(7) <= REG8(0)
REG8(6 DOWNTO 0) <= REG8(7 DOWNTO 1)
```

#### 4 位二进制加法计数器

统计输入时钟信号 `CLK` 的上升沿个数，并输出成一个数据信号 `Q`。

```VHDL
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
ENTITY CNT4 IS
	PORT(CLK: IN BIT;
			 Q: BUFFER STD_LOGIC_VECTOR(3 DOWNTO 0));
END ENTITY CNT4;

ARCHITECTURE BHV OF CNT4 IS
	BEGIN
		PROCESS(CLK)
			BEGIN
				IF CLK'EVENT AND CLK = '1' THEN
					Q <= Q + 1;
				END IF;
		END PROCESS;
END BHV;
```

- **端口模式 `BUFFER`**

既是输出端，又是输入端。可以作为赋值符号的左右操作数同时使用。

#### 4 位二进制减法计数器

当输入时钟信号 `CLK` 是上升沿时刻时，输出信号 `Q` 的值减一。当 `Q = "0000"` 时，下一个上升沿之后的值为 `"1111"`。

```VHDL
...
ENTITY CNT4J IS
	PORT(CLK: IN BIT;
			 Q: OUT STD_LOGIC_VECTOR(3 DOWNTO 0));
END ENTITY CNT4J;
ARCHITECTURE BHV OF CNT4J IS
	SIGNAL Q1: STD_LOGIC_VECTOR(3 DOWNTO 0);
	BEGIN
		PROCESS(CLK) BEGIN
			IF CLK'EVENT AND CLK = '1' THEN Q1 <= Q1 - 1;
			END IF;
		END PROCESS;
		Q <= Q1;
	END BHV;
```

- **计数器分类**

按 **数值** 分为 **二进制计数器**、**十进制计数器** 和 **N 进制计数器**。

按 **计数方式** 分为 **加法计数器**、**减法计数器** 和 **可逆计数**。

按 **时钟控制** 分为 **同步计数器** 和 **异步计数器**。

#### 实用计数器

一个异步复位输入信号 `RST`，一个时钟输入信号 `CLK`，一个时钟使能输入信号 `EN`，一个同步使能数据装载输入信号 `LOAD`，一个计数值输出信号 `Q` 和一个计数进位输出信号 `COUT`。

```VHDL
...
ENTITY COUNT10 IS
	PORT(CLK, RST, EN, LOAD: IN STD_LOGIC;
			 DATA: IN STD_LOGIC_VECTOR(3 DOWNTO 0);
			 DOUT: OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
			 COUT: OUT STD_LOGIC);
END ENTITY COUNT10;

ARCHITECTURE BHV OF COUNT10 BEGIN
	PROCESS(CLK, RST, EN, LOAD)
		VARIABLE Q: STD_LOGIC_VECTOR(3 DOWNTO 0);
		BEGIN
			IF RST = '0' THEN Q := (OTHERS => '0');
			ELSIF CLK'EVENT AND CLK = '1' THEN
				IF EN = '1' THEN
					IF LOAD = '0' THEN Q := DATA;
					ELSE
						IF Q < 9 THEN Q := Q + 1;
						ELSE Q := (OTHERS => '0');
						END IF;
					END IF;
				END IF;
			END IF;
			IF Q = "1001" THEN COUT <= '1';
			ELSE COUT <= '0';
			END IF;
			DOUT <= Q;
		END PROCESS;
	END BHV;
```

### 含高阻态输出电路 VHDL 设计

理论上 **高阻态** 是对地或对电源电阻极大的状态。而实际应用上与引脚的悬空（断开）几乎是一样的。

#### 三态门

真值表是。（`A = X` 代表 `A` 的值无论是多少，只要 `EN = 0`，`Y = Z` 恒成立）。

| A | EN | Y |
| :--: | :--: | :--: |
| 1 | 1 | 1 |
| 0 | 1 | 0 |
| X | 0 | Z |

```VHDL
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
ENTITY tri_s IS
	PORT(enable: IN STD_LOGIC;
			 datain: IN STD_LOGIC_VECTOR(7 DOWNTO 0);
			 dataout: OUT STD_LOGIC_VECTOR(7 DOWNTO 0));
END ENTITY tri_s;

ARCHITECTURE bhv OF tri_s IS
	BEGIN
		PROCESS(enable, datain)
			BEGIN
				IF enable = '1' THEN dataout <= datain;
				ELSE dataout <= "ZZZZZZZZ"; -- Z 必须大写
				END IF;
		END PROCESS;
	END bhv;
```

#### 双向端口

当一个端口是 **输入模式** 时，其 **输出模式** 的电路部分须呈 **高阻态**。

```VHDL
...
ENTITY tri_state IS
	PORT(control: IN STD_LOGIC;
			 in1: IN STD_LOGIC_VECTOR(7 DOWNTO 0);
			 q: INOUT STD_LOGIC_VECTOR(7 DOWNTO 0);
			 x: OUT STD_LOGIC_VECTOR(7 DOWNTO 0));
END ENTITY tri_state;

ARCHITECTURE BHV OF tri_state IS
	BEGIN
		PROCESS(control, q, in1)
			BEGIN
				IF control = '0' THEN x <= q; q <= "ZZZZZZZZ"; -- q 作为输出端呈高阻态
				ELSE q <= in1; x <= "ZZZZZZZZ"; -- x 输出呈高阻态
				END IF;
			END PROCESS;
	END BHV;
```

#### 三态总线

多路输入信号共用一个总线输出，且同一时刻仅允许一路输入信号通过总线输出，其他路输入信号须全部断开（高阻态）。

以 4 路三态总线为例。端口都属于 "信号" 数据对象，在进程 `PROCESS` 中，对同一信号赋值，只有 **最后一句** 赋值语句有效。

```VHDL
...
-- 完全错误，没有并行执行。
-- 且只有最后一句 output <= (OTHERS => 'Z') 有效。
IF enable = "00" THEN output <= input3;
ELSE output <= (OTHERS => 'Z');
END IF;
IF enable = "01" THEN output <= input2;
ELSE output <= (OTHERS => 'Z');
END IF;
...
-- 多个 PROCESS，可以并行执行。
COM3: PROCESS(enable, input3) BEGIN
	IF enable = "00" THEN output <= input3;
	ELSE output <= (OTHERS => 'Z');
	END IF;
END PROCESS;
COM2: ...
```

也可以采用 `WHEN-ELSE` 并行语句来完成。每一个并行语句相当于一个 **独立** 的进程语句。**建议采用**。

```VHDL
ARCHITECTURE BHV OF tri2 IS
	BEGIN
		output <= input3 WHEN enable = "00" ELSE (OTHERS => 'Z');
		output <= input2 WHEN enable = "01" ELSE (OTHERS => 'Z');
		...
	END BHV;
```

### VHDL 描述风格

- **行为描述**

依据希望的功能，程序仅仅描述 **输入与输出之间的转换行为**，不存在任何与 **硬件选择**、**硬件连线** 等相关的语句。

通常是指含有 **进程（顺序语句）** 的非结构化描述。

- **数据流描述**

直观表达 **电路内部的逻辑结构**（逻辑关系表达式）。使用 **非结构化的并行语句** 描述和 **连续赋值语句**。

- **结构描述**

描述元件组成及之间的互连。基于 **元件例化语句** 实现。

### VHDL 用户自定义数据类型

- **限定型数组型数据类型**：将一组具有相同数据类型的元素集合在一起构成的新的数据类型。

```VHDL
TYPE 数组名 IS ARRAY(数组范围) OF 基本数据类型;
e.g.
TYPE MATRIX IS ARRAY(127 DOWNTO 0) OF STD_LOGIC_VECTOR(7 DOWNTO 0);
```

- **非限定型数组型数据类型**：不定义数据下标取值范围。

```VHDL
TYPE 数组名 IS ARRAY(数组下标名 RANGE <>) OF 数据类型;
e.g.
TYPE BIT_VECTOR IS ARRAY(NATURAL RANGE<>) OF BIT;
```

- **枚举型数据类型**：明确取值范围。

```VHDL
TYPE 数组类型名 IS 数据类型定义表述;
e.g.
TYPE my_logic IS ('1', 'Z', 'U', '0');
SIGNAL s1: my_logic;
s1 <= 'Z';
```

- **枚举型子类型数据类型**：TYPE 所定义的原数据类型中的一个子集。

```VHDL
SUBTYPE 子类型名 IS 基本数据类型 RANGE 约束范围;
e.g.
SUBTYPE digits IS INTEGER RANGE 0 to 9;
```

## 参考链接

[EDA b站教程](https://www.bilibili.com/video/BV1rK411W717?p=1)

[Verilog 教程](https://www.runoob.com/w3cnote/verilog-tutorial.html)

[ABC](https://people.eecs.berkeley.edu/~alanmi/abc/)

[EPFL](https://www.epfl.ch/labs/lsi/page-102566-en-html/benchmarks/)

[EPFL - GitHub](https://github.com/WilliamX1/benchmarks)

[谷歌布局布线开源论文](https://abopen.com/news/google-research-releases-circuit-training-an-open-source-framework-for-automated-chip-floorplanning/)

[谷歌布局布线开源论文 - GitHub](https://github.com/google-research/circuit_training)

