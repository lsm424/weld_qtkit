#include "MainWindow.h"


//#include "easylogging++.h"
//#include "mysql_pool.h"

//#include "ElaApplication.h"
//#include "ElaWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	//ElaApplication::getInstance()->init();

	MainWindow w;
	//ElaWindow w;
	w.showMaximized();

//    MysqlPool *pool = MysqlPool::Instance();
//    pool->setParameter("rm-2vcn263i98963727lko.mysql.cn-chengdu.rds.aliyuncs.com", "vlog", "vlog_xiangjiang100", "vlog", 3306);
//    QVector<QVector<QVariant>> ret = pool->executeSql("SELECT * FROM t_user_info");


    return a.exec();
}

