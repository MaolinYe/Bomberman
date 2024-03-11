# Bomberman
UE5.3 C++和蓝图实现的经典炸弹人
## 常见问题
GetWorld生成Actor必须要在对象已经初始化之后，如果在构造函数中调用会返回nullptr导致UE编译时崩溃  
## 不可销毁的障碍物
Block类，头文件中声明组件
```c++
	UPROPERTY(EditAnywhere, Category = "Component")
	UStaticMeshComponent* Block;
```
构造函数中创建静态网格体，在派生蓝图中设置静态网格体
```c++
ABlock::ABlock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Block = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block"));
	RootComponent = Block;
}
```
## 生成不可销毁的障碍物
BlockGenerator类，头文件声明属性和生成函数
```c++
	UPROPERTY(EditAnywhere, Category = "Block Generation")
	TSubclassOf<class ABlock>Block;
	UPROPERTY(EditAnywhere, Category = "Block Generation|Setting")
	int Height = 15;
	UPROPERTY(EditAnywhere, Category = "Block Generation|Setting")
	int Width = 15;
	UPROPERTY(EditAnywhere, Category = "Block Generation|Setting")
	int BlockSize = 100;
	void SpawnBlock();
```
在奇数位置生成障碍物
```c++
void ABlockGenerator::SpawnBlock()
{
	for (int i = 0; i < Width; i++) {
		for (int j = 0; j < Height; j++) {
			if (i % 2 != 0 && j % 2 != 0) {
				FVector Position = FVector((i - Width / 2) * BlockSize + 50, (j - Height / 2) * BlockSize + 50, 150);
				GetWorld()->SpawnActor<ABlock>(Block, Position, FRotator::ZeroRotator);
			}
		}
	}
}
```
在开始函数而不是构造函数调用生成障碍物方法
```c++
void ABlockGenerator::BeginPlay()
{
	Super::BeginPlay();
	SpawnBlock(); // 必须在对象完全初始化之后调用，否则GetWorld返回nullptr
}
```
![img.png](images/Block.png)
## 主摄像机
MainCamera类，继承自摄像机，派生蓝图使用
```c++
protected:
	virtual void BeginPlay();
	APlayerController* PC;
```
将玩家控制器的视角设置为当前对象，并实现平滑过渡
```c++
void AMainCamera::BeginPlay()
{
	Super::BeginPlay();
	PC = UGameplayStatics::GetPlayerController(this, 0);
	PC->SetViewTargetWithBlend(this, 0);
}
```
## 可销毁方块
同不可销毁障碍物构建方法
### 随机生成可销毁方块