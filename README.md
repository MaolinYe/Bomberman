# Bomberman
UE5.3 C++和蓝图实现的经典炸弹人
## 常见问题
GetWorld生成Actor必须要在对象已经初始化之后，如果在构造函数中调用会返回nullptr导致UE编译时崩溃  

