#include "searchfilter.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QListView>
#include <QDir>
#include <QStringListModel>
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>

MyLineEdit::MyLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

//重写mousePressEvent事件,检测事件类型是不是点击了鼠标左键
void MyLineEdit::mousePressEvent(QMouseEvent *event) {
    //如果单击了就触发clicked信号
    if (event->button() == Qt::LeftButton) {
        //触发clicked信号
        emit clicked();
        qDebug()<<"press";
    }
    //将该事件传给父类处理
    QLineEdit::mousePressEvent(event);
}

SearchFilter::SearchFilter(QWidget *parent) : QWidget(parent)
{
    //输入框
    m_input_edit = new MyLineEdit();
    m_input_edit->setMinimumHeight(35);
    m_input_edit->installEventFilter(this);
    key_show_flag = 0;
    //文件列表
    m_file_list_view = new QListView();

    m_file_list_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_file_list_view->setStyleSheet(QString::fromUtf8("font: 14pt \"Sans Serif\";"));


    m_string_list_model = new QStringListModel();
    m_proxy_model = new QSortFilterProxyModel();

    QVBoxLayout* main_layout = new QVBoxLayout();
    main_layout->addWidget(m_input_edit);
    main_layout->addWidget(m_file_list_view);
    diy_control = new frmMain();

    this->setLayout(main_layout);

    connect(m_input_edit, &QLineEdit::textChanged, this, &SearchFilter::textChanged_input_edit);
    connect(m_file_list_view, &QListView::clicked, this, &SearchFilter::onDoubleClick_listView);

    diy_control->setLineEditQss(m_input_edit,"#DCE4EC", "#3498DB");

    key_board = new MyKeyboard();
    key_board->setMaximumWidth(400);
    key_board->setMinimumWidth(400);
    key_board->setGeometry(0,300,400,300);



    for(int i =0; i < 9;i++)
    {
        connect(((key_board->key_board)+i), &QPushButton::clicked, this, &SearchFilter::dealInput);
    }
    connect(((key_board->key_board)+9), &QPushButton::clicked, this, &SearchFilter::dealOK);
    connect(((key_board->key_board)+10), &QPushButton::clicked, this, &SearchFilter::dealInput);
    connect(((key_board->key_board)+11), &QPushButton::clicked, this, &SearchFilter::dealDelete);
   // showKeyItem = new QWidget();

//    QSpacerItem* up = new QSpacerItem(40, 75, QSizePolicy::Minimum, QSizePolicy::Expanding);
//    QVBoxLayout *tmp_lay_out = new QVBoxLayout();
//    tmp_lay_out->addSpacerItem(up);
//    tmp_lay_out->addWidget(key_board);
//    showKeyItem->setLayout(tmp_lay_out);

    // my_model = m_file_list_view->selectionModel();
    //qDebug()<<static_cast<int*>(my_model);
    //这里绑定了选中变化时发生事件
    //connect(m_file_list_view->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                //this, SLOT(selectChanged_listView(QItemSelection)));
}

//数字键处理
void SearchFilter::dealInput()
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
        m_input_edit->setText( resultStr );
        //初始化字符串结果，清空
        if(resultStr.length() == 20)
            resultStr.clear();
    }

}
void SearchFilter::dealDelete()
{
    if(resultStr.size() == 1)
    {
        resultStr.clear();
        m_input_edit->clear();
    }
    else
    {
        resultStr.chop(1); //截断最后一位字符
        m_input_edit->setText(resultStr);
    }
}

void SearchFilter::dealOK()
{
    key_board->close();
    key_show_flag = 2;
    m_input_edit->setFocus();
}

bool SearchFilter::eventFilter(QObject *watched, QEvent *event)
{
     if (watched==m_input_edit)         //首先判断控件(这里指 lineEdit1)
     {
          if (event->type()==QEvent::FocusIn)     //然后再判断控件的具体事件 (这里指获得焦点事件)
          {
//              QPalette p=QPalette();
//              p.setColor(QPalette::Base,Qt::green);
//              ui->lineEdit1->setPalette(p);
              if(key_show_flag == 0)
              {
                    //key_board-setGeometry();
                    key_board->show();
                    //this->addWi showKeyItem->show();

                    key_show_flag = 1;
              }
              //key_board->show();

          }
          else if (event->type()==QEvent::FocusOut)    // 这里指 lineEdit1 控件的失去焦点事件
          {
//              QPalette p=QPalette();
//              p.setColor(QPalette::Base,Qt::white);
//              ui->lineEdit1->setPalette(p);
//              if(key_show_flag == 1)
//              {
//                    key_show_flag = 0;
//                    key_board->close();
//              }
           }
     }

 return QWidget::eventFilter(watched,event);     // 最后将事件交给上层对话框
}

//设置搜索过滤目录和文件后缀
void SearchFilter::Init(const QString &dir_str, const QStringList &filter_list)
{
    m_dir_str = dir_str;

    QDir* dir = new QDir(dir_str);
    dir->setNameFilters(filter_list);

    QStringList file_list = dir->entryList();

    m_string_list_model->setStringList(file_list);
    m_proxy_model->setSourceModel(m_string_list_model);

    m_file_list_view->setModel(m_proxy_model);
    m_file_list_view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //设置当前选中行 0行 0列
    QModelIndex index = m_proxy_model->index(0, 0);
    m_file_list_view->setCurrentIndex(index);


    QModelIndex curr_index = m_file_list_view->currentIndex();
    int rows = m_proxy_model->rowCount();

    if (rows == 0) {
        QMessageBox::information(this, tr("提示"), tr("没有图片"), QMessageBox::Ok);
        return ;
    }


    QString picture_name = curr_index.data().toString();
    QString picture_path = m_dir_str + picture_name;

    init_file_name = picture_path;
    //qDebug()<<init_file_name;

}

//选上一个
void SearchFilter::SetCurrentSelectFile_Prev()
{
    QModelIndex curr_index = m_file_list_view->currentIndex();
    int curr_row = curr_index.row();

    if (curr_row == 0) {
        QMessageBox::information(this, tr("提示"), tr("前面没有了"), QMessageBox::Ok);
        return ;
    }

    curr_row = curr_row - 1;

    curr_index = m_proxy_model->index(curr_row, 0);
    m_file_list_view->setCurrentIndex(curr_index);

    //当前选中
    curr_index = m_file_list_view->currentIndex();
    QString picture_name = curr_index.data().toString();
    QString picture_path = m_dir_str + picture_name;

    emit signal_current_select_file(picture_path);
}

//选中下一个
void SearchFilter::SetCurrentSelectFile_Next()
{
    QModelIndex curr_index = m_file_list_view->currentIndex();
    int curr_row = curr_index.row();

    int rows = m_proxy_model->rowCount();

    if (curr_row == (rows - 1)) {
        QMessageBox::information(this, tr("提示"), tr("后面没有了"), QMessageBox::Ok);
        return ;
    }

    curr_row = curr_row + 1;

    curr_index = m_proxy_model->index(curr_row, 0);
    m_file_list_view->setCurrentIndex(curr_index);

    //当前选中
    curr_index = m_file_list_view->currentIndex();
    QString picture_name = curr_index.data().toString();
    QString picture_path = m_dir_str + picture_name;

    emit signal_current_select_file(picture_path);
}

//QLineEdit输入发生变化事件
void SearchFilter::textChanged_input_edit(const QString &text)
{
    //正则方式
    QRegExp::PatternSyntax syntax = QRegExp::PatternSyntax(
                QRegExp::FixedString);
    QRegExp regExp(text, Qt::CaseInsensitive, syntax);
    m_proxy_model->setFilterRegExp(regExp);
}

//listview双击事件
void SearchFilter::onDoubleClick_listView(const QModelIndex &index)
{
    QString picture_name = index.data().toString();
    QString picture_path = m_dir_str + picture_name;

    emit signal_current_select_file(picture_path);

}


