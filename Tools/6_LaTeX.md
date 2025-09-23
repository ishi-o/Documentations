## `Latex`数学公式语法<a id="Latex"></a>

有关其他字符可以自行查阅[符号表](https://blog.csdn.net/wait_for_eva/article/details/84307306)

### 缩进符

`Latex`里空格不会被解析为实实在在的空格，需要使用转义符，即`'\ '(空格),'\\'(换行)`

### 颜色

`\color{color}{text}`：将`'text'`颜色变为`'color'`，例如：`\color{red}{abcd}`的效果是$\color{red}{abcd}$

### 关于函数

`Latex`默认字母为**斜体**，用函数符号得到的函数为正体，且可以规范写法，例如：$\begin{align}lim_{x\rightarrow0}，\lim_{x\rightarrow0}\end{align}$

如果需要使用正体，可以用**`\rm{text}`**，例如$abcd，\rm{abcd}$

### 常用特殊符号

如果需要**成块被纳入**范围需要使用`{}`，否则默认读取单个字符，例如：$x_abc和x_{abc}$
`{}`也同时担任块内解析的效果，即放缩符等出块后即失效

$x_a$ `x_a`
$e^x$ `e^x`
$\in$ `\in`
$\infty$ `\infty`
$\rightarrow$ `\rightarrow`(左箭头即`\leftarrow`，需加长则在前面加上`long`，下面同理)
$\leftrightarrow$ `\leftrightarrow`
$\leftrightarrows$ `\leftrightarrows`
$\rightleftharpoons$ `\leftrightharpoons`
$\Rightarrow$ `\Rightarrow`(若加长需加`Long`)
$\cup$ `\cup`
$\sim$ `\sim`
$\frac{UP}{DOWN}$ `\frac{UP}{DOWN}`

### 常用放缩符

$\small((\big(\Big(\bigg(\Bigg($ 从左往右依次是`\small 正常 \big \Big \bigg \Bigg`，'正常项'之后的放缩符只能对`(),[],{},|,<,>,/,\`起作用，其中`\,{}`需要**转义**

$\small a\normalsize a\large a\Large a\LARGE a\huge a\Huge a$ 从左往右依次是`\small \normalsize \large \Large LARGE \huge \Huge`，它们对所有字符都有效

### 常用环境符

环境符两两配对，其中的代码可以被分为多行并且可以对齐

`\begin{align}\end{align}`：**对齐**环境，它可以将$\lim_{x\rightarrow0}，\int_a^b，\sum_{i=1}^{10}$等变为$\begin{align}\lim_{x\rightarrow0}，\int_a^b，\sum_{i=1}^{10}\end{align}$
还可以将'&'置于每行开头，实现**左对齐**

`\begin{cases}\end{cases}`：**大括号**环境，它可以将多项列举在一个大括号范围内，例如：$sgn(x)=\begin{cases}1,&x>0\\0,&x=0\\-1,&x<0\end{cases}$，可以将'&'置于逗号后，实现**对齐条件**

### 常用特殊字母

$\alpha$ `\alpha`
$\beta$ `\beta`
$\gamma$ `\gamma`
$\Gamma$ `\Gamma`
$\delta$ `\delta`
$\Delta$ `\Delta`
$\epsilon$ `\epsilon`
$\varepsilon$ `\varepsilon`
$\xi$ `\xi`
$\varphi$ `\varphi`
$\phi$ `\phi`
$\Phi$ `\Phi`
$\eta$ `\eta`
$\theta$ `\theta`
$\pi$ `\pi`
$\lambda$ `\lambda`
$\mu$ `\mu`

### 常用运算符

$\le$ `\le(与Linux类似的less equal)`
$\ge$ `\ge(greater equal)`
$\xlongequal[a]{b}$ `\xlongequal[a]{b}`(自动伸长的等号)
$\ne$ `\ne(not equal)`
$\equiv$ `\equiv`
$\begin{align}\int\end{align}$ `\int`
$\begin{align}\iint\end{align}$ `\iint`
$\begin{align}\int_a^b\end{align}$ `\int_a^b`

$\begin{align}\sum_{i=1}^{10}\end{align}$ `\sum_{i=1}^{10}`

$\begin{align}\lim_{x\rightarrow+\infty}\end{align}$ `\lim_{x\rightarrow+\infty}`

$\sqrt a$ `\sqrt a`

$\sqrt[n]{abc}$ `\sqrt[n]{abc}`

$\begin{align}\Bigg|_a^b\end{align}$ `\Bigg|_a^b`
