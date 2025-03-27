#include<iostream>
using namespace std;

/*----------全局变量声明区----------*/
// 系统状态标记
int newInformationRunNum = 0;       // 运动会基本信息设置状态（0未设置/1已设置）
int addProjectRunNum = 0;           // 比赛项目添加状态（0未添加/1已添加）

// 运动会时间信息
int month = 0;                      // 举办月份
int day = 0;                        // 起始日期（日）
int endDay = 0;                     // 结束日期（日）
int nowProjectNumber = 0;           // 当前已添加项目数量

// 系统容量限制
const int MAX_DAY = 3;              // 运动会最大持续天数
const int MAX_PROJECT = 8;          // 最大比赛项目数量
const int MAX_PLAYER = 10;          // 最大运动员数量

// 运动员信息存储
int PlayerNum = 0;                  // 当前已录入运动员数量
string player[MAX_PLAYER];          // 运动员姓名
string playerScore[MAX_PLAYER];     // 运动员比赛成绩 
string playerProject[MAX_PLAYER];   // 运动员参赛项目

// 比赛项目信息存储
string rules[MAX_PROJECT];          // 项目规则说明
int date[MAX_PROJECT];              // 项目日期（日）
string projects[MAX_PROJECT];       // 项目名称
int btime[MAX_PROJECT];             // 项目开始时间（小时）
string place[MAX_PROJECT];          // 项目举办地点

/*----------功能函数定义区----------*/

/**
 * 按日期查询比赛项目
 * 功能：根据用户输入的日期显示当天所有比赛信息
 * 限制：需要管理员先设置基本信息和添加项目
 */
void findDayCompetition() 
{
    int jDate = 0;

    // 前置条件检查
    if (newInformationRunNum == 0) 
    {
        cout << "请先联系管理员设置运动会信息！" << endl;
        return;
    }

    if (addProjectRunNum == 0) 
    {
        cout << "请联系管理员添加比赛项目！" << endl;
        return;
    }

    // 获取查询日期
    cout << "请输入您要查询的日期(日)：";
    cin >> jDate;
    
    // 遍历项目数组进行匹配
    bool found = false;
    for (int i = 0; i < nowProjectNumber; i++) 
    {
        if (jDate == date[i]) {
            cout << "比赛项目：" << projects[i] << endl;
            cout << "比赛时间：" << btime[i] << "点" << endl;
            cout << "比赛地点：" << place[i] << endl;
            found = true;
        }
    }
    // 未找到提示
    if (!found) 
    {
        cout << "该日期没有比赛项目。" << endl;
    }
}

/**
 * 按项目名称查询详细信息
 * 功能：显示指定项目的完整信息（含参赛运动员）
 * 限制：需要管理员先设置基本信息和添加项目
 */
void findProject() 
{
    string jProject;
    // 前置条件检查
    if (newInformationRunNum == 0) 
    {
        cout << "请先联系管理员设置运动会信息！" << endl;
        return;
    }

    if (addProjectRunNum == 0) 
    {
        cout << "请联系管理员添加比赛项目！" << endl;
        return;
    }

    // 获取查询项目名称
    cout << "请输入您要查询的比赛项目名称：";
    cin >> jProject;
    
    // 遍历项目数组进行匹配
    bool found = false;
    for (int i = 0; i < nowProjectNumber; i++) 
    {
        if (projects[i] == jProject) 
        {
            // 输出项目基本信息
            cout << "\n项目名称：" << projects[i] << endl;
            cout << "日期：" << month << "月" << date[i] << "日" << endl;
            cout << "时间：" << btime[i] << "点" << endl;
            cout << "地点：" << place[i] << endl;
            cout << "规则与技巧：" << rules[i] << endl;
            
            // 查找相关运动员信息
            cout << "参赛运动员及成绩：" << endl;
            bool hasPlayers = false;
            for (int j = 0; j < PlayerNum; j++) 
            {
                if (playerProject[j] == jProject) 
                {
                    cout << "姓名：" << player[j] << "\t成绩：" << playerScore[j] << endl;
                    hasPlayers = true;
                }
            }
            if (!hasPlayers) 
            {
                cout << "暂无参赛运动员信息" << endl;
            }
            found = true;
            break;
        }
    }
    if (!found) 
    {
        cout << "未找到该比赛项目！" << endl;
    }
}

/**
 * 查询运动员信息
 * 功能：根据姓名显示运动员参赛信息和成绩
 */
void findPlayer() 
{
    string jPlayer = "";
    bool found = false;
    cout << "请输入您要查询的运动员姓名：";
    cin >> jPlayer;
    
    // 遍历运动员数组进行匹配
    for (int i = 0; i < PlayerNum; i++) 
    {
        if (jPlayer == player[i]) {
            cout << "运动员姓名：" << player[i] << endl;
            cout << "参加项目：" << playerProject[i] << endl;
            cout << "比赛成绩：" << playerScore[i] << endl;
            found = true;
            break;
        }
    }
    if (!found) 
    {
        cout << "没有找到该运动员！" << endl;
    }
}

/**
 * 设置运动会基本信息
 * 功能：管理员设置举办月份和起始日期
 * 注意：设置成功后会将newInformationRunNum置为1
 */
void newInformation() 
{
    newInformationRunNum = 1;
    int jMonth = 0;
    int jDay = 0;
    int jChoice = -1;
    
    // 循环确认设置信息
    while(1) 
    {
        cout << "\n输入运动会信息\n";
        cout << "输入运动会举办月份：";
        cin >> jMonth;
        cout << "输入运动会开始日期（日）：";
        cin >> jDay;

        // 显示设置结果预览
        cout << "当前运动会为 " <<  jMonth << "月 " << jDay << "日 举办，" 
             << jMonth << "月 " << jDay + MAX_DAY << "日 结束"<< endl;
        cout << "是否确定？(1:确定/0:继续修改)";
        cin >> jChoice;
        
        if (jChoice == 1) 
        {
            // 保存设置并退出
            month = jMonth; 
            day = jDay; 
            endDay = jDay + MAX_DAY; 
            cout << "已保存！" << endl; 
            return;
        } else if (jChoice == 0) 
        {
            cout << "继续修改" << endl;
        } else 
        {
            cout << "输入错误，请重新选择！" << endl;
        }
    }
}

/**
 * 添加比赛项目
 * 功能：管理员录入新的比赛项目信息
 * 注意：需要先设置运动会基本信息，最多添加MAX_PROJECT个项目
 */
void addProject() 
{
    // 前置检查
    if (newInformationRunNum == 0) 
    {
        cout << "\n请先输入运动会信息！" << endl;
        newInformation();
    }

    string jName = "";
    string jPlace = "";
    int jDate = 0;
    int jTime = 0;
    string jRules = ""; 
    int jChoice = -1;

    // 收集项目信息
    cout << "\n创建比赛项目\n";
    cout << "请输入比赛名称：";
    cin >> jName;
    cout << "请输入比赛地点：";
    cin >> jPlace;
    cout << "请输入比赛日期（日）：";
    cin >> jDate;
    cout << "请输入比赛时间：";
    cin >> jTime;
    cout << "请输入比赛规则与技巧：";
    cin.ignore(); // 清除输入缓冲区残留的换行符
    getline(cin, jRules);

    // 存储到数组
    projects[nowProjectNumber] = jName;
    btime[nowProjectNumber] = jTime;
    place[nowProjectNumber] = jPlace;
    date[nowProjectNumber] = jDate;
    rules[nowProjectNumber] = jRules; 
    nowProjectNumber++;
    addProjectRunNum = 1;

    // 显示添加结果
    cout << "\n已创建比赛项目！" << endl;
    cout << "比赛信息：" << endl 
         << "名称：" << jName << endl
         << "时间：" << jTime << "点" << endl
         << "地点：" << jPlace << endl
         << "日期：" << month << "月" << jDate << "日" << endl
         << "规则与技巧：" << jRules << endl;
    
    // 判断是否继续添加
    cout << "是否继续创建？(1:继续/0:返回)";
    cin >> jChoice;

    if (jChoice == 1) 
    {
        addProject();
    }
}

/**
 * 添加运动员信息
 * 功能：录入运动员姓名、参赛项目和成绩
 * 注意：需要已存在比赛项目
 */
void addPlayer() {
    // 前置检查
    if (newInformationRunNum == 0) 
    {
        cout << "\n请先输入运动会信息！" << endl;
        newInformation();
    }
    if (addProjectRunNum == 0) 
    {
        cout << "请先添加比赛项目！" << endl;
        return;
    }

    string jpName;
    int choice;
    string jScore;

    // 收集运动员信息
    cout << "\n添加选手\n请输入选手姓名：";
    cin >> jpName;
    
    // 显示项目列表供选择
    cout << "\n当前比赛项目列表：" << endl;
    for (int i = 0; i < nowProjectNumber; i++) 
    {
        cout << i+1 << ". " << projects[i] << endl;
    }
    cout << "请选择项目：";
    cin >> choice;
    
    // 输入验证
    if (choice < 1 || choice > nowProjectNumber) 
    {
        cout << "无效选择！" << endl;
        return;
    }

    // 存储信息
    player[PlayerNum] = jpName;
    playerProject[PlayerNum] = projects[choice-1];
    cout << "请输入选手成绩：";
    cin >> jScore;
    playerScore[PlayerNum] = jScore;
    PlayerNum++;

    // 显示当前所有选手
    cout << "\n已添加选手！当前全部选手信息：" << endl;
    for (int i = 0; i < PlayerNum; i++) 
    {
        cout << "选手" << i+1 << " 姓名：" << player[i] 
             << "\t项目：" << playerProject[i] 
             << "\t成绩：" << playerScore[i] << endl;
    }
}

/**
 * 管理员功能菜单
 * 功能：验证密码后提供管理功能入口
 * 包含：设置基本信息、添加项目、添加运动员
 */
void guanLiYuan() 
{
    int jChoice = 0;
    const int password = 123456;   // 管理员密码
    int userPassword = 0;

    // 密码验证
    cout << "\n管理员助手\n输入管理员密码：";
    cin >> userPassword;

    if (password != userPassword) 
    {
        cout << "密码错误！\n自动退出。" << endl;
        return;
    }

    // 管理功能菜单循环
    while(true) 
    {
        cout << "\n管理员功能\n1.输入运动会信息\n2.创建比赛项目\n3.添加运动员\n4.返回主菜单\n请选择：";
        cin >> jChoice;
        
        switch(jChoice) 
        {
            case 1: 
                newInformation();
                break;
            case 2: 
                addProject();
                break;
            case 3: 
                addPlayer();
                break;
            case 4: 
                return;
            default: 
                cout << "请输入有效选项！" << endl;
        }
    }
}

/*----------主程序----------*/
int main() 
{
    int runNum = 0;        // 首次运行标记
    int choice = 0;        // 用户选择

    // 首次运行提示
    if (runNum == 0) 
    {
        cout << "欢迎使用校园运动会助手！\n初次使用请输入运动会信息！" << endl;
        runNum = 1;
    }

    // 主交互循环
    while(true) 
    {
        cout << "\n校园运动会助手\n1.查询当天比赛\n2.查询比赛项目\n3.查询运动员\n4.管理员功能\n0.退出程序\n请选择：";
        cin >> choice;
        switch(choice) 
        {
            case 1: 
                findDayCompetition(); 
                break;
            case 2: 
                findProject(); 
                break;
            case 3: 
                findPlayer(); 
                break;
            case 4: 
                guanLiYuan(); 
                break;
            case 0: 
                cout << "感谢使用，再见！" << endl; 
                return 0;
            default: 
                cout << "请输入有效选项！" << endl;
        }
    }
    return 0;
}