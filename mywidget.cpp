#include "mywidget.h"
#include "ui_mywidget.h"
#include <QMessageBox>
#include <QDir>
#include <QDebug>
#include "frmmain.h"

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{



    ui->setupUi(this);
    ui->login_lable->adjustSize();
    //ui->label->adjustSize();
    ui->stackedWidget->setCurrentWidget(ui->LoginPage);

    dir_str = QDir::currentPath();
    dir_str += "/";
    //qDebug()<<dir_str;


    filters << "*.jpg";

    diy_control = new frmMain();

    ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->label->setDisabled(true);

    connect(ui->pushButton0, &QPushButton::clicked, this, &MyWidget::dealNum);
    connect(ui->pushButton1, &QPushButton::clicked, this, &MyWidget::dealNum);
    connect(ui->pushButton2, &QPushButton::clicked, this, &MyWidget::dealNum);
    connect(ui->pushButton3, &QPushButton::clicked, this, &MyWidget::dealNum);
    connect(ui->pushButton4, &QPushButton::clicked, this, &MyWidget::dealNum);
    connect(ui->pushButton5, &QPushButton::clicked, this, &MyWidget::dealNum);
    connect(ui->pushButton6, &QPushButton::clicked, this, &MyWidget::dealNum);
    connect(ui->pushButton7, &QPushButton::clicked, this, &MyWidget::dealNum);
    connect(ui->pushButton8, &QPushButton::clicked, this, &MyWidget::dealNum);
    connect(ui->pushButton9, &QPushButton::clicked, this, &MyWidget::dealNum);

    diy_control->setBtnQss(ui->pushButton1, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    diy_control->setBtnQss(ui->pushButton2, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
    diy_control->setBtnQss(ui->pushButton3, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");
    diy_control->setBtnQss(ui->label, "#E74C3C", "#FFFFFF", "#EC7064", "#FFF5E7", "#DC2D1A", "#F5A996");
    diy_control->setBtnQss(ui->pushButtonExit, "#E74C3C", "#FFFFFF", "#EC7064", "#FFF5E7", "#DC2D1A", "#F5A996");
    diy_control->setBtnQss(ui->pushButton5, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    diy_control->setBtnQss(ui->pushButton6, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
    diy_control->setBtnQss(ui->pushButton9, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");
    diy_control->setBtnQss(ui->pushButton7, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    diy_control->setBtnQss(ui->pushButton8, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
    diy_control->setBtnQss(ui->pushButton4, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");
    diy_control->setBtnQss(ui->pushButtonDel, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    diy_control->setBtnQss(ui->pushButtonOK, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
    diy_control->setBtnQss(ui->pushButton0, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");


    diy_control->setTextEdit(ui->textEdit,"#DCE4EC", "#34495E");


    diy_control->setBtnQss(ui->pushButton, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");



    m_widget_search_filter = new SearchFilter();  //文件浏览
    m_widget_image_viewr = new ImageViewer();  //图片浏览

    m_widget_search_filter->setMinimumWidth(421);
    m_widget_search_filter->setMaximumWidth(421);



    PhotoLeftBtn = new QPushButton();
    PhotoRightBtn = new QPushButton();

    PhotoLeftBtn->setMinimumWidth(60);
    PhotoLeftBtn->setMaximumWidth(60);
    PhotoLeftBtn->setMinimumHeight(28);
    PhotoLeftBtn->setMinimumHeight(28);
    //diy_control->setBtnQss(PhotoLeftBtn, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");
    PhotoLeftBtn->setFlat(true);
    //PhotoLeftBtn->setStyleSheet("background: transparent;outline: none");

    //QIcon photo_left_ico(":/src_img/p_left.png");

    //PhotoLeftBtn->setIcon(photo_left_ico);
    //PhotoLeftBtn->setIconSize(QSize(60,28));
    PhotoLeftBtn->setObjectName("p_left_btn");

    PhotoLeftBtn->setStyleSheet("QPushButton#p_left_btn{border-image:url(:/src_img/p_left.png);background: transparent;outline: none}" );

    PhotoRightBtn->setMinimumWidth(60);
    PhotoRightBtn->setMaximumWidth(60);
    PhotoRightBtn->setMinimumHeight(28);
    PhotoRightBtn->setMinimumHeight(28);
    //diy_control->setBtnQss(PhotoRightBtn, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
    PhotoRightBtn->setFlat(true);
    PhotoRightBtn->setStyleSheet("background: transparent;outline: none");

    QIcon photo_right_ico(":/src_img/p_right.png");
    PhotoRightBtn->setIcon(photo_right_ico);
    PhotoRightBtn->setIconSize(QSize(60,28));

    QSpacerItem* mid = new QSpacerItem(75, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QHBoxLayout *tool_layout = new QHBoxLayout();
    tool_layout->addWidget(PhotoLeftBtn);
    tool_layout->addSpacerItem(mid);
    tool_layout->addWidget(PhotoRightBtn);

#if 0
    QSpacerItem* item_left = new QSpacerItem(75, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* item_right = new QSpacerItem(75, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

    tool_layout = new QHBoxLayout();
    tool_layout->addSpacerItem(item_left);
    tool_layout->addWidget(btn_prev);
    //tool_layout->addWidget(btn_zoom_out);
    //tool_layout->addWidget(btn_zoom_in);
    tool_layout->addWidget(btn_next);
    tool_layout->addWidget(btn_close);
    tool_layout->addSpacerItem(item_right);

    main_layout->addLayout(tool_layout);

    this->setLayout(main_layout);
    this->setStyleSheet("background-color: rgb(167, 175, 159);");
#endif

    QHBoxLayout *view_layout = new QHBoxLayout();
    view_layout->addWidget(m_widget_search_filter);
    view_layout->addWidget(m_widget_image_viewr);

    QVBoxLayout* main_layout = new QVBoxLayout();
    main_layout->addLayout(tool_layout);

    main_layout->addLayout(view_layout);

    //QWidget* main_widget = new QWidget(this);
    ui->PhotoPage->setLayout(main_layout);



    m_widget_search_filter->Init(dir_str, filters);

    connect(m_widget_search_filter, &SearchFilter::signal_current_select_file, this, &MyWidget::show_image);
    connect(m_widget_image_viewr, &ImageViewer::signal_next, this,  &MyWidget::show_next);
    connect(m_widget_image_viewr, &ImageViewer::signal_prev, this,  &MyWidget::show_prev);
    connect(m_widget_image_viewr, &ImageViewer::signal_close, this,  &MyWidget::closeAPP);

    connect(this, &MyWidget::load_image, this, &MyWidget::show_image);

    //对于子线程的东西（将被移入子线程的自定义对象以及线程对象），最好定义为指针
    myT = new MyThread;//将被子线程处理的自定义对象不能在主线程初始化的时候指定父对象
    thread = new QThread(this);//初始化子线程线程

    myT->moveToThread(thread);//将自定义对象移交给子线程，从此子线程控制他的成员函数

    //启动子线程，但是没有启动真正的子线程处理函数，
    //只是让子线程对象开始监控移交给他的相关对象
    thread->start();
    //绑定/连接关闭应用程序窗口的信号和主线程的dealClose槽函数
    connect(this, &MyWidget::destroyed, this, &MyWidget::dealClose);

    detectSerial();//探测当前系统可用的串口列表


}


void MyWidget::dealClose()
{
    if(thread->isRunning() == false)
     {
            return;
     }

    //2.如果调用的是子线程的函数（对象已被放入子线程，其成员函数均在子线程）
    //需要在子线程退出的之前调用

    myT->setFlag(true);//更新子线程的isStop标志--结束子线程的处理函数
    //3.退出子线程要显示的调用这两个函数，否则主线程退出但子线程还在运行
    thread->quit();
    //回收资源
    thread->wait();

    //4. 将要被放入子线程的对象在主线程初始化（构造）的时候不能指定父对象，且需要在子线程结束以后显示delete
    delete myT;
}

void MyWidget::detectSerial()
{


    //1. 绑定信号和曹的时候，如果带参数，在QT5中可以直接给出信号和槽函数名即可
    //但是，如果所传递的参数类型是未注册（非本地默认识别的可传递类型）的，需要在绑定之前进行注册
    qRegisterMetaType<QSerialPortInfo>("QSerialPortInfo");
    qRegisterMetaType<QImage>("QImage'");

    //连接子线程的isDone信号到主线程的serialDisplay槽函数，显示串口接收到的数据

    connect(myT,&MyThread::ImageOK,this,&MyWidget::show_image);
    connect(myT,&MyThread::ImageOK,this,&MyWidget::my_Init);

    //连接主线程的initUart信号到子线程的initSerial槽函数，开始串口初始化
    connect(this,&MyWidget::initUart,myT,&MyThread::initSerial);



    //获取可用串口列表
    QList<QSerialPortInfo>  infos = QSerialPortInfo::availablePorts();
    if(infos.isEmpty())//系统无可用串口
    {
        ui->comboBox->addItem("无效");//在串口选择下拉框显示“无效”
        return;
    }
    ui->comboBox->addItem("串口");//如果有可用串口则在串口选择下拉框显示“串口”

    //将每个可用串口号作为一个条目添加到串口选择下拉框
    foreach (QSerialPortInfo info, infos) {
        ui->comboBox->addItem(info.portName());
    }
}

MyWidget::~MyWidget()
{
    delete ui;
}


void MyWidget::my_Init(const QString& picture_path)
{
    m_widget_search_filter->Init(dir_str, filters);
}

void MyWidget::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->PhotoPage);


    emit load_image(m_widget_search_filter->init_file_name);
}

void MyWidget::closeAPP()
{
    ui->stackedWidget->setCurrentWidget(ui->LoginPage);
}

//数字键处理
void MyWidget::dealNum()
{
    //获取信号发送者
    QObject * mySender = sender();
    //转换为按钮类型
    QPushButton *p = (QPushButton *)mySender;
    if(NULL != p)
    {
        //获取按钮的内容
        QString numStr = p->text();
        resultStr += numStr;



        ui->textEdit->setText( resultStr );

        //初始化字符串结果，清空
        if(resultStr.length() == 20)
            resultStr.clear();


    }

}



void MyWidget::on_pushButtonDel_clicked()
{
    if(resultStr.size() == 1)
    {
        resultStr.clear();
        ui->textEdit->clear();
    }
    else
    {
        resultStr.chop(1); //截断最后一位字符
        ui->textEdit->setText(resultStr);
    }
}

void MyWidget::on_pushButtonOK_clicked()
{
    QMessageBox::information(this, "被骗了吧", "Mason Is HandSome！");
}



void MyWidget::show_next()
{
    m_widget_search_filter->SetCurrentSelectFile_Next();
}

void MyWidget::show_prev()
{
    m_widget_search_filter->SetCurrentSelectFile_Prev();
}

void MyWidget::show_image(const QString &picture_path)
{
    //qDebug()<<picture_path;
    m_widget_image_viewr->loadFile(picture_path);
}

void MyWidget::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QSerialPortInfo info;
    QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();//获取可用串口列表
    static char flag = 0;
    if(arg1 == "串口" && flag == 0)
    {
        flag = 1;
        return;
    }

    //遍历链表
    int i = 0;
    foreach (info, infos) {
        //如果在下拉框里选择的串口在系统可用串口链表里找到就跳出循环--表示能够操作该串口
        if(info.portName() == arg1) break;
        i++;
    }
    if(i != infos.size ()){//can find----没有遍历到可用串口链表尾部
        ui->label->setText("[已开启]");
        //ui->comboBox->setItemText(0,"选择串口");
        diy_control->setBtnQss(ui->label, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
        emit initUart(info);//发送串口初始化信号

    }
    else
    {
        ui->label->setText("[出错]");//没有找到可用串口

    }
}

void MyWidget::on_pushButtonExit_clicked()
{
    dealClose();
    this->close();
}
