#include "MainWindow.h"

#include <QApplication>

#include "log.h"
#include "easylogging++.h"
//初始化日志库
INITIALIZE_EASYLOGGINGPP
#define ELPP_THREAD_SAFE


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    el::Configurations conf;
    // 启用日志
    conf.setGlobally(el::ConfigurationType::Enabled, "true");
    // 设置日志文件目录以及文件名
    conf.setGlobally(el::ConfigurationType::Filename, "log\\log_%datetime{%Y%M%d %H%m%s}.log");
    // 设置日志文件最大文件大小
    conf.setGlobally(el::ConfigurationType::MaxLogFileSize, "1920000");
    // 是否写入文件
    conf.setGlobally(el::ConfigurationType::ToFile, "true");
    // 是否输出控制台
    conf.setGlobally(el::ConfigurationType::ToStandardOutput, "true");
    // 设置日志输出格式
    conf.setGlobally(el::ConfigurationType::Format, "[%datetime] [%loc] [%level] : %msg");
    // 设置日志文件写入周期，每10条刷新到输出流中
    conf.setGlobally(el::ConfigurationType::LogFlushThreshold, "1");
    // 加载配置
    el::Loggers::reconfigureAllLoggers(conf);

    int verboseLevel = el::Loggers::verboseLevel();
    LOG(INFO) << "Verbose Level = " << verboseLevel;
    LOG(INFO) << "this is info log";
    LOG(WARNING) << "this is waring log";
    LOG(ERROR) << "this is error log";
    LOG(DEBUG) << "this is debug log";
    LOG(TRACE) << "this is trace log";

    VLOG(0) << "this is level 0 log";
    VLOG(1) << "this is level 1 log";


    MainWindow w;
    w.showMaximized();
    return a.exec();
}
