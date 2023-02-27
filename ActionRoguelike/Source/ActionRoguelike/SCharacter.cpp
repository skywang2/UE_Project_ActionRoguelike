// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework\SpringArmComponent.h"
#include "Camera\CameraComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_springArmComp = CreateDefaultSubobject<USpringArmComponent>("springArmComp");
	m_springArmComp->SetupAttachment(RootComponent);//关联到root组件

	m_cameraComp = CreateDefaultSubobject<UCameraComponent>("cameraComp");
	m_cameraComp->SetupAttachment(m_springArmComp);//关联到弹簧组件

}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASCharacter::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
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

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);//偏航角移动，使用继承的函数
}

