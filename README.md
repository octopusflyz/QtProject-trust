# QtProject-trust
（一）程序功能介绍
我们的大作业总体上，程序主旨是研究博弈论中的囚徒困境问题，并且实现了博弈论中经典囚徒困境问题的决策的可视化，同时提供了足够丰富的策略以便于研究不同策略在长期竞争中的表现，并提供了为用户提供了修改各个参数的接口，有助于加深对于囚徒困境问题及其中所演化的信任的理解。以下是详细功能的介绍：

1.主体框架：程序总共分为6个页面，用户可以通过下方的1-6这6个按键跳转到任意一个页面，其中第1个页面为起始页面，第2个为我们囚徒困境模型的介绍，第3-4个页面提供了该模型下one vs one，也就是双人囚徒困境的过程的可视化演示，第5-6个页面提供了不同策略在长期竞争下表现的可视化演示。此外，用户还可以通过点击程序右下方的“music”按钮循环播放音乐“The Road Not Taken”。

2.one vs one动画演示：
（1）在第3个页面中，程序为用户提供了最基本one vs one的功能实现，用户可以通过按下“cooperate”或者是“cheat”按钮来选择是否与对方合作，并且将通过动画表现双方的决策以及产生的结果，同时用户可以通过上方的分数显示框实时看到自己以及对手在多轮博弈下积累的分数。在这一页面中，我们提供了代表5种不同策略的小人，他们将分别与用户博弈。
（2）在第4个页面中，程序为用户展示了我们为使模型更贴合现实引入的随机性，用户可以在引导下看到小人偏离自己的选择（或者策略）产生错误选择的动画。

3.多人多策略锦标赛动画演示以及参数的自由实时调整：
在第5个页面中，程序提供了我们一轮多人多策略锦标赛流程演示，随后在第六个页面中提供了一个多人多策略锦标赛的模型，它实现了下面的功能：
在左边的锦标赛ui中：
（1）用户可以通过按下“start”按钮开始无限循环的锦标赛过程，动画将演示在当前参数下每一轮的所有参赛者的得分，以及淘汰者退出，随后新加入者的过程。
（2）用户可以通过按下“step”按钮进行步进操作，程序将按照：加入新人、进行一轮比赛并且显示所有人得分、淘汰的循环顺序进行动画演示，每按下一次“step”就依次展示其中的一个过程。
（3）用户可以通过按下“reset”按钮，终止当前的锦标赛并返回到初始设置。

在右边的参数调整ui中：
（1）Population部分：用户可以通过拖动滑动条或者输入数字来调整代表该策略的小人数量，同时代表其他策略的小人数量将会随机减少以保持总人数的一致。
（2）Payoffs部分：用户可以在这里调整不同选择下双方的得分以更深入地比较不同策略。同时，无论左边的锦标赛演示在任何状态下（“start”后的无限循环状态，或者是“step”的步进状态），Payoffs的修改都将同步到锦标赛中，并将在下一轮锦标赛中体现出来。
（3）Rules部分：在这里，用户可以对锦标赛的基本规则进行调整：包括每一轮锦标赛中，两两间的博弈次数；每一轮锦标赛中根据分数淘汰也即补充进来的人数；在比赛过程中，小人们犯错的概率。与上面的Payoffs部分一样，这些参数的修改都是实时的，他们将即时地体现在下一轮锦标赛中。

（二）项目各模块与类设计细节  

1.项目配置与构建模块
CMakeLists.txt:
●定义项目名称和版本。
●设置C++标准为17。
●启用Qt的自动UI、MOC和资源文件处理。
●查找Qt的Widgets和Multimedia模块。
●包含源代码文件和资源文件。

2.主窗口模块
MainWindow类: 继承自QMainWindow。
●为应用程序的主窗口，包含菜单栏、状态栏以及中心部件。
●负责应用程序的生命周期管理以及用户交互的顶层逻辑。
●功能实现：
(1)页面跳转：在MainWindow中通过加入stackedWidget并将其提升为自定义的qt设计界面类。加入下方按钮，通过信号与槽的绑定实现页面切换。
(2)音乐播放：在成员函数Play函数中实现控制

3. UI页面模块
包含以下几个类：
(1)pg_welcome: 继承自QWidget。
  Ui::pg_welcome: UI布局类，自动生成，负责欢迎页面的布局。
(2)pg_rules: 继承自QWidget。
  Ui::pg_rules: UI布局类，自动生成，负责规则页面的布局。
  qtextedit文字插入，基本规则介绍。
(3)pg_twoplayers: 继承自QWidget。
负责展示两个玩家的交互界面，包括动画效果。
●动画展示：ui设计界面将上传图片与qlabel进行绑定，通过信号与槽的绑定实现图片的动画效果。文字引导式介绍。
●动画实现：
  (1)通过成员函数on_cheatButton_clicked和on_cooperateButton_clicked实现选择每轮合作或者背叛（传入对应选择参数至此轮对手对应的函数中），并开始一轮的动画实现。每进行五轮更新一次对手，用户方将面对五种策略的对手（即copycat、cheater、cooperator、grudger、detective）。
  (2)通过QPropertyAnimation类下成员函数将带有图片的qlabel（即小人和硬币），实现点到点的位移、移动路径、时长的设置。使用QSequentialAnimationGroup实现多个图片不同动画片段的整合以同时进行。使用信号和槽的绑定实现不同动画先后顺序进行。
  (3)依据每轮选择合作或背叛，传入参数至Match_Result类下成员函数myresult，返回本轮双方是被合作还是被背叛，依据两者四种结果可能性给出响应（即为reaction函数），显示对应小人心情的图片，显示对应结果的machine图片。
  (4)上方计分牌，将每轮的current_score、opponent_score、total_score与ui连接，在每轮投币后更新分数。
(4)pg_mistakes: 继承自QWidget。
  负责展示游戏中的失误或特殊动画的页面。
  引导式介绍错误机制。与pg_twoplayers动画实现基本一致，在第二轮用户方更新错误动作，传入参数默认为背叛。上方更新文字说明。
(5)pg_tournament: 继承自QWidget。
  Ui::pg_tournament: UI布局类，负责锦标赛页面的布局。
  引导式说明多人多策略竞标赛中，不同策略小人如何两两进行十轮博弈，并且展示各自得分。点击continue按钮即可演示每两个小人之间对局结果。
(6)pg_allplayers: 继承自QWidget。
  Ui::pg_allplayers: UI布局类，负责所有玩家页面的布局。
  ●ui设计界面插入tabWidget，实现切换自定义的population、payoffs和rules三界面。各界面有相应的参数值传至相应逻辑部分。
    (1)将population界面调整八种不同策略小人的widget提升为自定义的类slider，以实现拖动滑条和数字变化显示的关联。
    (2)Payoffs界面插入spinbox以调整相关参数。
    (3)将rules界面相关参数调整的horizontalSlider和spinBox关联，以实现拖动滑条和数字变化显示的关联。

4.基本囚徒困境模型的逻辑模块
(1)Match_Result:
  ●存储单个比赛的结果，包括双方的行为和得分变化。
(2)Judge:
  ●负责管理比赛逻辑，包括存储比赛结果、历史选择和判定矩阵（以及判定矩阵的修改），以及根据上面数据完成两个小人一对一博弈。
  ●功能实现：
    (1)判定矩阵修改：由成员函数reward_reset实现
    (2)根据存储数据完成小人一对一博弈的选择输出：由成员函数match实现

5.小人模块
(1)Player: 继承自Qwidget
  ●小人的基类，定义了小人的基本属性和行为，如得分、类型，犯错概率等
  ●以及小人的图片，控制其他辅助部件的动画
  ●同时负责进行决策，以及随机犯错等功能的实现。
  ●功能实现：
    (1)小人决策：由纯虚函数choice实现，并在派生类实现具体的策略。
    (2)随机犯错：由成员函数random_mistake实现。
(2)Player_Copy_Cat: 继承自Player类
  ●实现从众策略：永远复制对方上一次的决策，在最开始总是选择合作。
(3)Player_Cheater: 继承自Player类
  ●实现背叛策略：永远背叛。
(4)Player_Cooperator: 继承自Player类
  ●实现合作策略：永远合作。
(5)Player_Grudger: 继承自Player类
  ●实现记仇策略：在最开始选择合作，但是当被对方背叛后，永远背叛。
(6)Player_Detective: 继承自Player类
  ●实现侦探策略，尝试根据历史行为分析对手的决策：在最开始四次博弈中采取合作，背叛，合作，合作的决策，随后在这四次博弈中对方若有选择过背叛，则从第5次起采取模仿策略，反之采取背叛策略。
(7)Player_Random: 继承自Player类
  ●实现随机策略：随机选择合作或作弊。
(8)Player_Copy_Kitten: 继承自Player类
  ●实现更加宽容的模仿策略：只有当被对方连续背叛两次时，才会选择背叛对方。
(9)Player_Simpleton: 继承自Player类
  ●实现单纯策略：当对方选择合作时采取和上次一样的决策，反之采取相反的决策。

6. 辅助控件模块
  slider:
  自定义的滑块控件，提供一组绑定好的QSlider和QSpinBox。

7. 辅助工具模块
  Connection_Line:
    表示玩家间关系的连接线。主要负责动态展示对局进度，具有出现、淡出和移动动画。
  Trash_Can:
    用于存储和管理不再需要的Connection_Line对象。防止重复删除以及简化接口。

8.锦标赛管理模块
(1)Tournament_Worker: 继承自QObject
  ●在后台负责运算锦标赛结果以及控制小人的ui。
  ●功能实现：
    (1)所有人加入到锦标赛数据集以及做出相应ui更新：在成员函数LetThemIn中实现。
    (2)进行一轮单循环博弈(两两之间进行多轮博弈)计算以及ui更新：在成员函数Competition中实现
    (3)淘汰分数最低的若干人并做出相应ui更新：在成员函数KickThemOut中实现
    (4)集成控制ui给出指令并作出相应控制：集成在成员函数Tournament_Round(负责实现“start”控制功能)，Work_OnStep(负责实现“step”(步进)功能)中，通过调用(1)-(3)中的模块实现控制，在成员函数         reset实现“reset”功能。
    (5)在一轮锦标赛后从Tournament中读取更新后的参数数据：通过发送信号Update_signal并在Tournament的成员函数Update中实现。

(2)Tournament: 继承自QWidget
  ●接收控制ui给出的锦标赛进程的信号，并将信号集成传入Tournament_Worker中以控制锦标赛进程，同时更新部分ui。
  ●接收参数ui给出的参数调整的信号，并根据当前情况做出相应ui响应，并将调整后的参数读入缓存，在Tournament_Worker发出更新信号后将缓存中的数据输入到负责计算的Tournament_Worker类中。
  ●功能实现：
    (1)实现按下“start“,“step”,“reset”按钮后将信号同步到Tournament_Worker中并实现相应锦标赛流程管理：在构造函数中将“start“,“step”被按下的信号绑定到Tournament_Worker类的成员函数              Button_OnPush上，并在该函数中做相应处理。在构造函数中将“reset”被按下的信号绑定到成员函数reset上，实现Tournament以及Tournament_Worker的全部ui以及数据的重置。
    (2)实现修改不同策略小人数量后更新后即时更新所有策略小人数量的ui，同时使(无论是否正在进行)锦标赛立刻重置为一轮锦标赛的初始状态：在构造函数中将代表小人数量的ui更新的信号绑定到成员函数          PlayerNum_Change以及Tournament_Worker类的成员函数Button_OnPush上，前者负责实现所有代表小人数量的数据的更新(在保证总和一定的前提下随机修改其他策略的小人数量)以及ui的修改，后者负        责更新Tournament_Worker类的计算状态。
    (3)实现修改判断矩阵和规则参数后在下一轮锦标赛前即时更新到Tournament_Worker中：前者的ui数值变化信号绑定到成员函数ValueMatrix_Change上，并在其中将最新数据读入缓存中，后者信号则绑定到        成员函数Rule_Change上并完成类似功能。
9.资源和多媒体模块
  ●使用Qt资源系统(.qrc)来管理多媒体资源，包括图像、音频等。
