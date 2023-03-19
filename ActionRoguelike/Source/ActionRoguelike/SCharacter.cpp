// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework\SpringArmComponent.h"
#include "Camera\CameraComponent.h"
#include "GameFramework\Character.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "SInteractionComponent.h"

//shift + alt + F������VA�Ĳ��Һ�����ݼ�

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_springArmComp = CreateDefaultSubobject<USpringArmComponent>("springArmComp");
	m_springArmComp->SetupAttachment(RootComponent);//������root���
	m_springArmComp->bUsePawnControlRotation = true;

	m_cameraComp = CreateDefaultSubobject<UCameraComponent>("cameraComp");
	m_cameraComp->SetupAttachment(m_springArmComp);//�������������

	//1.��ɫ��ת��������ѹ���ȷ������ƶ����ᵼ�½�ɫ����ˮƽ��ת
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;

	//2.�ý�ɫ���ǳ����˶�����
	UCharacterMovementComponent* movement = GetCharacterMovement();
	movement->bOrientRotationToMovement = true;

	m_interactComp = CreateDefaultSubobject<USInteractionComponent>("interactionComp");//�������
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASCharacter::MoveForward(float value)
{
	FRotator control = GetControlRotation();//��ÿ���������ĸ����ǡ�ƫ���ǡ������ǣ���˳��ģ�
	control.Pitch = 0;//Ŀǰֻ��Ҫ������ƫ�����ɣ����������������Ϊ0
	control.Roll = 0;
	AddMovementInput(control.Vector(), value);
	//AddMovementInput(GetActorForwardVector(), value);

}

void ASCharacter::MoveRight(float value)
{
	FRotator control = GetControlRotation();
	//control.Pitch = 0;
	//control.Roll = 0;

	/*UE����������ϵ
	X��ǰ
	Y����
	Z����	*/
	//��ȡ��������Y������
	FVector right = FRotationMatrix(control).GetScaledAxis(EAxis::Y);//��ȡcontrol������Y���ϵ�ͶӰ

	AddMovementInput(right, value);
}

void ASCharacter::PrimaryAttack()
{
	//���Ŷ�����̫��
	PlayAnimMontage(m_AttackAnim);
	//���ö�ʱ�����ӳ�0.2s����������ӵ��ĺ���
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.3f);
	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);//�����ʱ��
}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	FVector spawnLocation = GetMesh()->GetSocketLocation("whip_IK_03_socket");
	//����ʱ��λ��
	FTransform spawnTM = FTransform(GetControlRotation(), spawnLocation);
	//���ɹ���
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	spawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(m_projectileClass, spawnTM, spawnParams);
}

//����ѯ���塢���������ŵ���������У�ʵ�ֽ���������Actor�����
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

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);//ǰ���ƶ�
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);//�����ƶ�

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);//ƫ�����ƶ���ʹ�ü̳еĺ���
	PlayerInputComponent->BindAxis("Pitch", this, &APawn::AddControllerPitchInput);//������

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Released, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Interaction", IE_Released, this, &ASCharacter::PrimaryInteract);
}

