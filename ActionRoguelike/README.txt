1.创建继承于Actor的C++类，实现添加组件、各种响应函数，并将控制器输入绑定到响应函数
2.实现任务前进后退、左右转身，设置静态网格是否随镜头转动、是否随控制器转动
3.实现修改对象的碰撞属性，自定义碰撞表，设置物理属性，使用粒子组件，设置冲量
4.创建可交互的宝箱继承Unreal接口类，并在Actor组件实现交互操作，在C++设置动画蒙太奇、定时器
    - 交互数据流程：按下键盘按键，触发PlayerInputComponent->BindAction绑定函数PrimaryInteract
    - 然后调用交互组件函数PrimaryInteract，该函数定义在交互组件中，意味着只要Actor包含该组件即可使用该交互函数
    - 交互函数中查询指定方向和范围内的Actor
    - 找到物品Actor后检测其是否实现了交互接口，Implements<USGameplayInterface>()，USGameplayInterface是接口，
      ISGameplayInterface::Execute_Interact是调用物品Actor的具体交互实现函数，
      可在c++实现也可在蓝图实现，void Interact_Implementation(APawn* pawn)以_Implementation结尾定义一个物品Actor交互实现函数，传入合适参数，属性必须为public
    - 最后进入物品Actor的处理函数
5.在蓝图中实现Unreal接口类定义的交互操作
