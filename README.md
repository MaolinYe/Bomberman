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
玩家出生的三角位置不可以生成可销毁方块
```c++
	SpawnPlayerPositions = {
	FIntPoint(0, 0), FIntPoint(0, 1), FIntPoint(1, 0),
	FIntPoint(Width - 1, 0), FIntPoint(Width - 1, 1), FIntPoint(Width - 2, 0),
	FIntPoint(0, Height - 1), FIntPoint(0, Height - 2), FIntPoint(1, Height - 1),
	FIntPoint(Width - 1, Height - 1), FIntPoint(Width - 1, Height - 2), FIntPoint(Width - 2, Height - 1)
	};
```
奇数位置不可生成
```c++
void ABlockGenerator::FindSpawnBBPosition()
{
	for (int i = 0; i < Width; i++) {
		for (int j = 0; j < Height; j++) {
			if (SpawnPlayerPositions.Contains(FIntPoint(i, j))) {
				continue;
			}
			if (i % 2 == 0 || j % 2 == 0) {
				FVector Position = FVector((i - Width / 2) * BlockSize + 50, (j - Height / 2) * BlockSize + 50, 150);
				BreakBlockPositions.Add(Position);
			}
		}
	}
}
```
设置一个生成可销毁方块的密度值
```c++
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "1"), Category = "Block Generation|Setting")
	float BlockDensity=1;
```
随机找一个可生成的位置生成方块，在位置集合中去掉该位置，重复直到达到数量
```c++
void ABlockGenerator::SpawnBreakBlock()
{
	int BreakBlockNum = BreakBlockPositions.Num() * BlockDensity;
	for (int i = 0; i < BreakBlockNum; i++) {
		int Index = FMath::RandRange(0, BreakBlockPositions.Num() - 1);
		GetWorld()->SpawnActor<ABreakableBlock>(BreakableBlock, BreakBlockPositions[Index], FRotator::ZeroRotator);
		BreakBlockPositions.RemoveAt(Index);
	}
}

```
![img.png](images/BreakableBlock.png)
## 移动人物
人物类继承Character，赋值骨骼网格体  
上下移动
```c++
void ABombermanPlayer::MoveVertical(float Value)
{
	AddMovementInput(FVector::ForwardVector,Value);
}
```
左右移动
```c++
void ABombermanPlayer::MoveHorizontal(float Value)
{
	AddMovementInput(FVector::RightVector,Value);
}
```
绑定轴映射
```c++
// Called to bind functionality to input
void ABombermanPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveVertical", this, &ABombermanPlayer::MoveVertical);
	PlayerInputComponent->BindAxis("MoveHorizontal", this, &ABombermanPlayer::MoveHorizontal);
}

```
创建新的游戏模式蓝图，项目设置中更新游戏模式和默认Pawn类
## 生成炸弹
炸弹类同之前两个方块构造，碰撞预设设置为NoCollision，让小机器人可以走过去，不然有时候会卡住不能动  
给小机器人增加生成炸弹方法
```c++
void ABombermanPlayer::SpawnBomb()
{
	if (Bomb) {
		FVector Location = GetActorLocation();
		Location.Z = 140;
		GetWorld()->SpawnActor<ABomb>(Bomb,Location , FRotator::ZeroRotator);
	}
}
```
绑定操作映射，按下空格放炸弹
```c++
void ABombermanPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveVertical", this, &ABombermanPlayer::MoveVertical);
	PlayerInputComponent->BindAxis("MoveHorizontal", this, &ABombermanPlayer::MoveHorizontal);
	PlayerInputComponent->BindAction("SpawnBomb", IE_Pressed, this, &ABombermanPlayer::SpawnBomb);
}
```
![img.gif](images/生成炸弹.gif)
## 炸弹阻挡小机器人
目前是小机器人可以穿过炸弹，设置了Bomb的碰撞预设为NoCollision，可以给Bomb添加碰撞检测
```c++
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ABomb::OnOverlapEnd);
}
```
当第一次碰到小机器人离开的时候，重设碰撞响应为阻挡
```c++
void ABomb::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == GetOwner()) {
		BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECollisionResponse::ECR_Block);
	}
}
```
生成炸弹时添加参数拥有者为小机器人
```c++
void ABombermanPlayer::SpawnBomb()
{
	if (Bomb) {
		FActorSpawnParameters Parameters;
		Parameters.Owner = this;
		FVector Location = GetActorLocation();
		Location.Z = 140;
		GetWorld()->SpawnActor<ABomb>(Bomb,Location , FRotator::ZeroRotator,Parameters);
	}
}
```
这样当小机器人第一次生成炸弹时会和炸弹重叠，再次碰到炸弹时会被阻挡
![img.gif](images/炸弹阻挡小机器人.gif)