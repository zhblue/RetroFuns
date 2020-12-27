在T43/T4x笔记本上运行仙剑奇侠传1，dos版，需要的小技巧
--
1、使用dos6.22的himem.sys，使得可用XMS限制到64M
2、用noems加载emm386.exe，为OPL2LPT的adlipt提供基础
3、加载ramdrive.sys /e 32000 消耗掉32m内存，避免pal.exe检测xms时报负数。
4、用ndos.com做shell，降低常规内存占用
config.sys
```

```
