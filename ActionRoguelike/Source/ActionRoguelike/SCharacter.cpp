// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework\SpringArmComponent.h"
#include "Camera\CameraComponent.h"
#include "GameFramework\Character.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "SInteractionComponent.h"

//shift + alt + F，这是VA的查找函数快捷键

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_springArmComp = CreateDefaultSubobject<USpringArmComponent>("springArmComp");
	m_springArmComp->SetupAttachment(RootComponent);//关联到root组件
	m_springArmComp->bUsePawnControlRotation = true;

	m_cameraComp = CreateDefaultSubobject<UCameraComponent>("cameraComp");
	m_cameraComp->SetupAttachment(m_springArmComp);//关联到弹簧组件

	//1.角色旋转与控制器脱钩，确保鼠标移动不会导致角色跟着水平旋转
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;

	//2.让角色总是朝向运动方向
	UCharacterMovementComponent* movement = GetCharacterMovement();
	movement->bOrientRotationToMovement = true;

	m_interactComp = CreateDefaultSubobject<USInteractionComponent>("interactionComp");//交互组件
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASCharacter::MoveForward(float value)
{
	FRotator control = GetControlRotation();//获得控制器输入的俯仰角、偏航角、滚动角（有顺序的）
	control.Pitch = 0;//目前只需要让人物偏航即可，其他两个的输入改为0
	control.Roll = 0;
	AddMovementInput(control.Vector(), value);
	//AddMovementInput(GetActorForwardVector(), value);

}

void ASCharacter::MoveRight(float value)
{
	FRotator control = GetControlRotation();
	//control.Pitch = 0;
	//control.Roll = 0;

	/*UE是左手坐标系
	X向前
	Y向右
	Z向上	*/
	//获取控制器的Y轴向量
	FVector right = FRotationMatrix(control).GetScaledAxis(EAxis::Y);//获取control向量在Y轴上的投影

	AddMovementInput(right, value);
}

void ASCharacter::PrimaryAttack()
{
	FVector spawnLocation = GetMesh()->GetSocketLocation("Chest");
	//生成时的位置
	FTransform spawnTM = FTransform(GetControlRotation(), spawnLocation);
	//生成规则
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(m_projectileClass, spawnTM, spawnParams);
}

//将查询物体、交互操作放到组件对象中，实现交互功能与Actor类解耦
void ASCharacter::PrimaryInteract()
{
	if (m_interactComp)
	{
		m_interactComp->PrimaryInteract();
	}
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);//前后移动
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);//左右移动

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);//偏航角移动，使用继承的函数
	PlayerInputComponent->BindAxis("Pitch", this, &APawn::AddControllerPitchInput);//俯仰角

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Released, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Interaction", IE_Released, this, &ASCharacter::PrimaryInteract);
}

